//
//  CZAppCoreIniFile.hpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/5/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#ifndef CZAppCoreIniFile_hpp
#define CZAppCoreIniFile_hpp

#include <stdio.h>

#define ValueType_int8
#define ValueType_int16
#define ValueType_int32
#define ValueType_int64
#define ValueType_int128

class IniFileField
{
public:
    const char* GetText();
    void GetText(const char* text);
};

class IniFileRow
{
//GroupName,FieldName,ValueType,ValueString,UserString
public:
    int GetFieldCount();
    IniFileField* GetField(int index);
    IniFileField* AddField(int index);
};

class IniFileBody
{
public:
    int GetRowCount();
    IniFileRow* GetRow(int index);
    IniFileRow* AddRow();
};

class IniFile
{
public:
    void Load(const char* file);
    void Save(const char* file);
    
    IniFileBody* GetBody();
};

#endif /* CZAppCoreIniFile_hpp */

//
//
