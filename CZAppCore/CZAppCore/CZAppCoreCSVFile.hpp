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
    CSVFile(const std::string&, int theColumnTitlesRow, int theFirstDataRow, char theEOL);
    
    inline std::vector<std::string> GetColumnTitles();
    CSVVector GetDataRecords();
    std::vector<std::string>::size_type GetDataRecordsSize();
    
    CSVVector GetColumn(const int&);
    CSVVector GetColumnsInGroup(const std::vector<int>&);
    CSVVector GetNamedColumn(const std::string&);
    CSVVector GetNamedColumnsInGroup(const std::vector<std::string>&);
    
    std::vector<std::string> GetRow(const int&);            //Return 1 Row
    CSVVector GetRowsInRange(const int&, const int&);       //Return All Rows in Range
    
    long GetNamedColumnIndex(const std::string&);
    long FindRowByValue(const std::string& theString, unsigned long theColumnNumber);
    std::string GetNeighborValue(const std::string& theString, unsigned long theColumnNumber, long theNeighbor);
    
    void DumpColumnTitles();
    void DumpAllRows();
    void DumpColumn(unsigned long theColumnNumber);
    
private:
    std::vector<std::string> ColumnTitles;
    CSVVector DataRecords;
    
    std::vector<std::string> StringToRecord(const std::string& theInputString);
    std::string RecordToString(const std::vector<std::string>&);
    std::vector<std::string> GetNamedColumnVector(const std::string&);
};

#endif /* CZAppCoreCSVFile_hpp */
