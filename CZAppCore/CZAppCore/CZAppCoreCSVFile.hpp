//
//  CZAppCoreCSVFile.hpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/22/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#ifndef CZAppCoreCSVFile_hpp
#define CZAppCoreCSVFile_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class CSVFile {
    
    typedef std::vector<std::vector<std::string>> CsvVector;
    friend std::ostream& print(std::ostream&, const CSVFile&);
    
public:
    CSVFile() = default;
    CSVFile(const std::string&);
    
    inline std::vector<std::string>::size_type get_size();
    inline void headers();
    inline std::vector<std::string> get_header();
    
    CsvVector get_column(const int&);
    CsvVector get_column(const std::vector<int>&);
    CsvVector get_column(const std::string&);
    CsvVector get_column(const std::vector<std::string>&);
    
    std::vector<std::string> get_row(const int&);
    CsvVector get_row(const int&, const int&); // Rows in range
    void write_row(const std::map<std::string,std::string>&);
    inline CsvVector rows();
    
private:
    std::vector<std::string> header;
    CsvVector contents;
    std::ifstream stream_read;
    std::ofstream stream_write;
    inline std::string remove_extension(const std::string&);
    std::vector<std::string> column_info(const std::string&);
    std::string merge_row_vector(const std::vector<std::string>&);
    long index_from_string(const std::string&);
    std::map<long,std::string> index_from_string(const std::map<std::string,std::string>& row_map);
};

std::ostream& print(std::ostream&, const CSVFile&);

void CSVFile::headers() {
    for (auto&& i : header)
        std::cout << i << ", ";
}

std::vector<std::string>::size_type CSVFile::get_size() {
    return contents.size();
}

std::string CSVFile::remove_extension(const std::string& s) {
    std::string ret = s;
    ret.erase(ret.find_last_of("."), std::string::npos);
    return ret;
}

std::vector<std::string> CSVFile::get_header() {
    return header;
}

CSVFile::CsvVector CSVFile::rows() {
    return contents;
}

#endif /* CZAppCoreCSVFile_hpp */
