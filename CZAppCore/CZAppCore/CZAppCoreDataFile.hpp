//
//  CZAppCoreDataFile.hpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/5/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#ifndef CZAppCoreDataFile_hpp
#define CZAppCoreDataFile_hpp

#include <stdio.h>

#ifndef fi
#define fi

class DataFile{
public:
    char name[64];
    long int len;
    int startpos;
    
    char* get_file_name();
    long int get_file_length();
    int get_startpos();
};

#endif // fi

#define MAX_FILES 16
#define MAX_FILE_LEN 1000
#ifndef fs
#define fs
#include<fstream>
using namespace std;
class DataFileSys
{
public:
    DataFile files[MAX_FILES];
    int CLmain(int argc, char* argv[]);
    void initialize();
    void read_from_file();
    void write_to_file();
    void set_file_system_name();
    DataFileSys(char f_name[]);
    char file_system_name[20];
    void list_files();
    char* show_file_content(char* f_name);
    char* search_file(char* f_name);
    void search_keyword(char* f_name, char* keyword);
    void delete_file(char* f_name);
    void create_file(char* f_name, char* file_contents);
};

#endif // fs
#endif /* CZAppCoreDataFile_hpp */
