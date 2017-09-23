//
//  main.cpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/5/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#include <iostream>
#include "CZAppCoreCSVFile.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    CSVFile myCSVFile("/Users/zillmann/Documents/testdata.csv",1,2, 0x0D);
    myCSVFile.DumpColumnTitles();
    myCSVFile.DumpAllRows();
    myCSVFile.DumpColumn(0);
    std::cout << myCSVFile.FindRowByValue("206",0);
    std::cout << "\n";
    std::cout << myCSVFile.GetNeighborValue("206", 0, 1);
    std::cout << ",";
    std::cout << myCSVFile.GetNeighborValue("206", 0, 2);
    std::cout << "\n";
    
    CSVFile myCSV2File("/Users/zillmann/Documents/testdata2.csv",1,2, 0x0D);
    myCSV2File.DumpColumnTitles();
	myCSV2File.DumpAllRows();
    myCSV2File.DumpColumn(0);
    std::cout << "\n";
    std::cout << myCSV2File.FindRowByValue("206",0);
    std::cout << "\n";
    std::cout << myCSV2File.GetNeighborValue("206",0,1);
    std::cout << ",";
    std::cout << myCSV2File.GetNeighborValue("206",0,2);
    std::cout << "\n";
    std::cout << "Hello, World!\n";
    //AppCoreArgs           Construct (int argc, const char * argv[])
    //AppCoreError          Construct (Args)
    //AppCoreHostProfile    Construct (Args, Error)
    //AppCoreMessages       Construct (Args, Error, HostProfile)
    //AppCoreIniFile        Construct (Args, Error, HostProfile, Messages)
    //AppCoreStorage        Construct (Args, Error, HostProfile, Messages, IniFile)
    //AppCoreProcess        Construct (Args, Error, HostProfile, Messages, IniFile, Storage)
    
    //AppCoreProcess        ProcessStorage (Args, Error, HostProfile, Messages, IniFile, Storage)
    
    //AppCoreProcess        Destruct (Void)
    //AppCoreStorage        Destruct (Void)
    //AppCoreIniFile        Destruct (Void)
    //AppCoreMessages       Destruct (Void)
    //AppCoreHostProfile    Destruct (Void)
    //AppCoreError          Destruct (Void)
    //AppCoreArgs           Destruct (Void)
    return 0;
}
