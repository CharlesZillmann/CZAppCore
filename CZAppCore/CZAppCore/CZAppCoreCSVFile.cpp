//
//  CZAppCoreCSVFile.cpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/22/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#include "CZAppCoreCSVFile.hpp"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <array>

// file doc: http://www.cplusplus.com/doc/tutorial/files/
// stream_readtream constructor: http://www.cplusplus.com/forum/general/17771/#msg89650
CSVFile::CSVFile(const std::string& file_name) {
    stream_read.open(file_name, std::ios::binary);
    std::string out_file = remove_extension(file_name) + "_OUT.csv";
    stream_write.open(out_file, std::ios::binary);
    stream_write << stream_read.rdbuf(); // Copy read file into output file
    bool line_is_header = true; // First line assumed to be the header
    stream_read.seekg(0); // "Rewind" infile stream
    while (stream_read) {
        // Grab whole row
        std::string s;
        if (!getline(stream_read, s))
            break;
        
        std::istringstream ss (s);
        std::vector<std::string> record;
        
        while(ss) {
            // Split string by comma delimiter
            std::string s;
            if (!getline(ss, s, ','))
                break;
            record.push_back(s);
        }
        
        if (line_is_header)
            header = record;
        else
            contents.push_back(record);
        line_is_header = false; // First iteration clears through the header
    }
}

void CSVFile::write_row(const std::map<std::string,std::string>& row_map) {
    std::vector<std::string> row_vec(header.size(), "NULL");
    std::map<long,std::string> index_map = index_from_string(row_map);
    for(auto it = index_map.begin(); it != index_map.end(); ++it) {
        row_vec[it->first] = it->second;
    }
    // for(auto&& i : row_vec) { cout << i << endl; }
    
    std::string v_string = merge_row_vector(row_vec);
    stream_write << std::endl << v_string;
}

std::map<long,std::string> CSVFile::index_from_string(const std::map<std::string,std::string>& row_map) {
    std::map<long,std::string> index_map;
    for(auto it = row_map.begin(); it != row_map.end(); ++it) {
        index_map[index_from_string(it->first)] = it->second;
    }
    return index_map;
}

long CSVFile::index_from_string(const std::string& s) {
    // Given column string, returns index of column
    long pos = find(header.begin(), header.end(), s) - header.begin();
    if (pos == header.size()) {
        throw std::out_of_range("\nColumn: " + s + " not found in header");
    }
    return pos;
}

// http://stackoverflow.com/questions/1430757/c-vector-to-string
std::string CSVFile::merge_row_vector(const std::vector<std::string>& row_vec) {
    std::stringstream sstream;
    for(std::vector<std::string>::size_type ctr = 0; ctr < row_vec.size(); ++ctr) {
        std::string current = row_vec[ctr];
        // cout << "called : " << current << endl;
        if (ctr == 0)
            sstream << current << ",";
        else if (current == "NULL")
            sstream << ",";
        else if (ctr == row_vec.size() - 1)
            sstream << current;
        else
            sstream << current << ",";
    }
    return sstream.str();
}

std::vector<std::string> CSVFile::column_info(const std::string& s) {
    // Returns all data in the passed column(s)
    // Need to overload this function later
    std::vector<std::string> data;
    long index = index_from_string(s);
    
    for (auto&& i : contents) {
        data.push_back(i[index]);
    }
    
    return data;
}

CSVFile::CsvVector CSVFile::get_column(const int& index) {
    CSVFile::CsvVector column_data;
    std::vector<std::string> buffer;
    
    for(unsigned i = 0; i < contents.size(); ++i) {
        buffer.push_back(contents[i][index]);
    }
    column_data.push_back(buffer);
    return column_data;
}

CSVFile::CsvVector CSVFile::get_column(const std::vector<int>& indices) {
    CSVFile::CsvVector column_data;
    for(auto&& index : indices)
    {
        std::vector<std::string> buffer;
        for(unsigned i = 0; i < contents.size(); ++i)
        {
            buffer.push_back(contents[i][index]);
        }
        column_data.push_back(buffer);
    }
    return column_data;
}

CSVFile::CsvVector CSVFile::get_column(const std::string& s) {
    CSVFile::CsvVector column_data;
    column_data.push_back(column_info(s));
    return column_data;
}

CSVFile::CsvVector CSVFile::get_column(const std::vector<std::string>& col_vec) {
    CSVFile::CsvVector column_data;
    for (auto&& column : col_vec) {
        column_data.push_back(column_info(column));
    }
    return column_data;
}

std::vector<std::string> CSVFile::get_row(const int& i) {
    return contents[i];
}

CSVFile::CsvVector CSVFile::get_row(const int& start, const int& end) {
    CsvVector row_range;
    for(unsigned i = start; i != end; ++i) {
        row_range.push_back(contents[i]);
    }
    return row_range;
}

std::ostream& print(std::ostream& os, const CSVFile& csv) {
    std::string csv_string;
    for (auto&& i : csv.contents) {
        std::stringstream s;
        for (auto&& j : i) {
            s << j << ' ';
        }
        s << "\n";
        csv_string += s.str();
    }
    os << csv_string;
    return os;
}
