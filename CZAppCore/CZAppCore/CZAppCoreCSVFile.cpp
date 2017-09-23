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

//Constructor that open files and reads all data
CSVFile::CSVFile(const std::string& file_name, int theColumnTitlesRow, int theFirstDataRow, char theEOL) {
    std::ifstream myInputFileStream;
    std::string myInputString;
    //Open the Input File
    myInputFileStream.open(file_name, std::ios::binary);
    
    if (myInputFileStream) {
        //Advance to the Column Header Row and Get the headers
        //Advance
        myInputFileStream.seekg(std::ios::beg);
        for(int i=0; i < theColumnTitlesRow - 1; ++i){
            getline(myInputFileStream, myInputString, theEOL);
        }
        // Read the Column Header Row
        if (getline(myInputFileStream, myInputString, theEOL)){
            ColumnTitles = StringToRecord(myInputString);
        }

        //Advance to the Column Header Row and Get the headers
        //Advance
        myInputFileStream.seekg(std::ios::beg);
        for(int i=0; i < theFirstDataRow - 1; ++i){
            getline(myInputFileStream, myInputString, theEOL);
        }
        // Read the Data Rows until EOF
        while (myInputFileStream) {
            // Grab a row of values from the CSV File
            if (!getline(myInputFileStream, myInputString, theEOL))
                break;
            DataRecords.push_back(StringToRecord(myInputString));
        }
        //Close the File
        myInputFileStream.close();
    }
}

//Methods to Abstract Private Data
std::vector<std::string> CSVFile::GetColumnTitles() {
    return ColumnTitles;
}

CSVFile::CSVVector CSVFile::GetDataRecords() {
    return DataRecords;
}

std::vector<std::string>::size_type CSVFile::GetDataRecordsSize() {
    return DataRecords.size();
}

//Parsing and Concatenation
std::vector<std::string> CSVFile::StringToRecord(const std::string& theInputString) {
    
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

std::string CSVFile::RecordToString(const std::vector<std::string>& row_vec) {
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

long CSVFile::GetNamedColumnIndex(const std::string& s) {
    // Given column string, returns index of column
    long pos = find(ColumnTitles.begin(), ColumnTitles.end(), s) - ColumnTitles.begin();
    if (pos == ColumnTitles.size()) {
        throw std::out_of_range("\nColumn: " + s + " not found in ColumnTitles");
    }
    return pos;
}

std::vector<std::string> CSVFile::GetNamedColumnVector(const std::string& s) {
    // Returns all data in the passed column(s)
    // Need to overload this function later
    std::vector<std::string> data;
    long index = GetNamedColumnIndex(s);
    
    for (auto&& i : DataRecords) {
        data.push_back(i[index]);
    }
    
    return data;
}

CSVFile::CSVVector CSVFile::GetColumn(const int& index) {
CSVVector column_data;
    std::vector<std::string> buffer;
    
    for(unsigned i = 0; i < DataRecords.size(); ++i) {
        buffer.push_back(DataRecords[i][index]);
    }
    column_data.push_back(buffer);
    return column_data;
}

CSVFile::CSVVector CSVFile::GetColumnsInGroup(const std::vector<int>& indices) {
CSVVector column_data;
    for(auto&& index : indices)
    {
        std::vector<std::string> buffer;
        for(unsigned i = 0; i < DataRecords.size(); ++i)
        {
            buffer.push_back(DataRecords[i][index]);
        }
        column_data.push_back(buffer);
    }
    return column_data;
}

CSVFile::CSVVector CSVFile::GetNamedColumn(const std::string& s) {
    CSVVector column_data;
    column_data.push_back(GetNamedColumnVector(s));
    return column_data;
}

CSVFile::CSVVector CSVFile::GetNamedColumnsInGroup(const std::vector<std::string>& col_vec) {
    CSVVector column_data;
    for (auto&& column : col_vec) {
        column_data.push_back(GetNamedColumnVector(column));
    }
    return column_data;
}

std::vector<std::string> CSVFile::GetRow(const int& i) {
    return DataRecords[i];
}

CSVFile::CSVVector CSVFile::GetRowsInRange(const int& start, const int& end) {
    CSVVector row_range;
    for(unsigned i = start; i != end; ++i) {
        row_range.push_back(DataRecords[i]);
    }
    return row_range;
}

long CSVFile::FindRowByValue(const std::string& theString,unsigned long theColumnNumber){
    for(unsigned long i = 0; i < DataRecords.size(); ++i) {
        if ((!DataRecords[i][theColumnNumber].empty()) and (DataRecords[i][theColumnNumber].compare(theString) == 0))
            return i;
    }
    return -1;
}

std::string CSVFile::GetNeighborValue(const std::string& theString,unsigned long theColumnNumber, long theNeighbor){
    for(unsigned long i = 0; i < DataRecords.size(); ++i) {
        if ((!DataRecords[i][theColumnNumber].empty()) and (DataRecords[i][theColumnNumber].compare(theString) == 0))
            return DataRecords[i][theColumnNumber+theNeighbor];
    }
    return "";
}

void CSVFile::DumpColumnTitles() {
    std::cout << "T: ";
    std::cout << RecordToString(ColumnTitles);
    std::cout << "\n";
    return;
}

void CSVFile::DumpAllRows() {
    unsigned long myCount = DataRecords.size();
    std::cout << "\n";
    std::cout << "Number of Records: ";
    std::cout << myCount;
    std::cout << "\n";
    
    for(unsigned long i = 0; i < DataRecords.size(); ++i) {
        std::cout << i;
        std::cout << ": ";
        std::cout << RecordToString(DataRecords[i]);
        std::cout << "\n";
    }
    return;
}

void CSVFile::DumpColumn(unsigned long theColumnNumber) {
    std::cout << "\n";
    std::cout << "Column Number: ";
    std::cout << theColumnNumber;
    std::cout << "\n";
    
    for(unsigned long i = 0; i < DataRecords.size(); ++i) {
        std::cout << i;
        std::cout << ": ";
        std::cout << DataRecords[i][theColumnNumber];
        std::cout << "\n";
    }
    return;
}
