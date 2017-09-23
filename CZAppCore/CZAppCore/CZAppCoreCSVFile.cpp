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

std::vector<std::string>::size_type CSVFile::GetCSVDataSize() {
    return contents.size();
}
std::vector<std::string> CSVFile::get_header() {
    return header;
}

std::string CSVFile::remove_file_extension(const std::string& s) {
    std::string ret = s;
    ret.erase(ret.find_last_of("."), std::string::npos);
    return ret;
}

CSVFile::CSVVector CSVFile::GetCSVData() {
    return contents;
}

unsigned int CSVFile::GoToInputFileLine( unsigned int theLineNum ){
    stream_read.seekg(std::ios::beg);
    for(int i=0; i < theLineNum - 1; ++i){
        stream_read.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return theLineNum;
}

std::vector<std::string> CSVFile::InputStringToRecord(const std::string& theInputString) {
    
    std::istringstream myInputStringStream( theInputString );
    std::vector<std::string> myInputRecord;

    while(myInputStringStream) {
        // Split string by comma delimiter
        std::string myLocalString;
        if (getline(myInputStringStream, myLocalString, ',')){
            myInputRecord.push_back(myLocalString);
        }
    }
    return myInputRecord;
}

CSVFile::CSVFile(const std::string& file_name, int theColumnHeadersRow, int theFirstDataRow) {
    
    std::string myInputString;
    
    //Open the Input File
    stream_read.open(file_name, std::ios::binary);
    
    //Advance to the Column Header Row
    GoToInputFileLine( theColumnHeadersRow );
    if (stream_read) {
        // Read the Column Header Row
        if (getline(stream_read, myInputString)){
            header = InputStringToRecord(myInputString);
        }
    }
    
    GoToInputFileLine( theFirstDataRow );
    while (stream_read) {
        // Grab a row of values from the CSV File
        if (!getline(stream_read, myInputString))
            break;
        contents.push_back(InputStringToRecord(myInputString));
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

CSVFile::CSVVector CSVFile::get_column(const int& index) {
    CSVFile::CSVVector column_data;
    std::vector<std::string> buffer;
    
    for(unsigned i = 0; i < contents.size(); ++i) {
        buffer.push_back(contents[i][index]);
    }
    column_data.push_back(buffer);
    return column_data;
}

CSVFile::CSVVector CSVFile::get_column(const std::vector<int>& indices) {
    CSVFile::CSVVector column_data;
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

CSVFile::CSVVector CSVFile::get_column(const std::string& s) {
    CSVFile::CSVVector column_data;
    column_data.push_back(column_info(s));
    return column_data;
}

CSVFile::CSVVector CSVFile::get_column(const std::vector<std::string>& col_vec) {
    CSVFile::CSVVector column_data;
    for (auto&& column : col_vec) {
        column_data.push_back(column_info(column));
    }
    return column_data;
}

std::vector<std::string> CSVFile::GetRow(const int& i) {
    return contents[i];
}

CSVFile::CSVVector CSVFile::GetRowsInRange(const int& start, const int& end) {
    CSVVector row_range;
    for(unsigned i = start; i != end; ++i) {
        row_range.push_back(contents[i]);
    }
    return row_range;
}

std::ostream& CSVFile::print(std::ostream& os, const CSVFile& csv) {
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
