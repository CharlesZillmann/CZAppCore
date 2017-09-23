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
    
    typedef std::vector<std::vector<std::string>> CSVVector;
    friend std::ostream& print(std::ostream&, const CSVFile&);
    
public:
    CSVFile() = default;
    CSVFile(const std::string&, int theColumnHeadersRow, int theFirstDataRow);
    
    inline void headers();
    inline std::vector<std::string> get_header();
    
    inline std::vector<std::string>::size_type GetCSVDataSize();
    inline CSVVector GetCSVData();
    
    CSVVector get_column(const int&);
    CSVVector get_column(const std::vector<int>&);
    CSVVector get_column(const std::string&);
    CSVVector get_column(const std::vector<std::string>&);
    
    std::vector<std::string> GetRow(const int&);            //Return 1 Row
    CSVVector GetRowsInRange(const int&, const int&);       //Return All Rows in Range
    
private:

    std::vector<std::string> header;
    CSVVector contents;
    std::ifstream stream_read;
    std::ofstream stream_write;
    
    unsigned int GoToInputFileLine(unsigned int theLineNum);
    std::vector<std::string> InputStringToRecord(const std::string& theInputString);
    
    inline std::string remove_file_extension(const std::string&);
    std::vector<std::string> column_info(const std::string&);
    std::string merge_row_vector(const std::vector<std::string>&);
    long index_from_string(const std::string&);
    std::map<long,std::string> index_from_string(const std::map<std::string,std::string>& row_map);
    std::ostream& print(std::ostream&, const CSVFile&);
};

#endif /* CZAppCoreCSVFile_hpp */
