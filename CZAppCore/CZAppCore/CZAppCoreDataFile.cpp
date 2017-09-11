//
//  CZAppCoreDataFile.cpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/5/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#include<iostream>
#include<fstream>
#include<string.h>
#include<stdio.h>
#include<string>
#include<math.h>

#include "CZAppCoreDataFile.hpp"

//Test commit 10 11 11 11


char* DataFile :: get_file_name()
{
    return name;
}
long int DataFile :: get_file_length()
{
    return len;
}

int DataFile :: get_startpos()
{
    return startpos;
}

using namespace std;
using namespace std;

int DataFileSys::CLmain(int argc, char* argv[])    //Enter command line arguments to open a previously created file system
// or leave blank to create a new one.
{
    char name[80], content[200], name1[80], keyword[60], *c = NULL;
    cout<< "-----------------------------------------------------------------------------\n";
    cout<< "************************ Virtual File System *********************************\n";
    cout<< "-----------------------------------------------------------------------------\n";
    int choice;
    DataFileSys f1(argv[1]);
    
    while(1)
    {
        cout << "\nEnter your choice:\n";
        cout << "1. List files in the file system\n";
        cout << "2. Show file content\n";
        cout << "3. Search a file\n";
        cout << "4. Search for a keyword in a file\n";
        cout << "5. Create new file\n";
        cout << "6. Delete a file\n";
        cin >> choice;
        switch(choice)
        {
            case 1:
                f1.list_files();
                break;
            case 2:
                cout << "Enter file name\n";
                cin >> name;
                c = f1.show_file_content(name);
                if(c != NULL)
                    cout << c;
                break;
            case 3:
                cout << "Enter file name\n";
                cin >> name;
                c = f1.search_file(name);
                if(c != NULL)
                    cout << c;
                break;
            case 4:
                cout << "Enter the file name\n";
                cin >> name;
                cout << "Enter the keyword to be searched\n";
                cin >> keyword;
                f1.search_keyword(name, keyword);
                break;
            case 5:
                cout << "Enter the name of new file\n";
                cin >> name;
                cout << "Enter the content of the file\n";
                cin.clear();
                fflush(stdin);
                cin.getline(content, sizeof(content));
                f1.create_file(name, content);
                break;
            case 6:
                cout << "Enter the name of the file to be deleted\n";
                cin >> name;
                f1.delete_file(name);
                break;
                
//Server
//                FILE *filehandle = fopen("imagefile.jpg", "rb");
//                if (filehandle != NULL)
//                {
//                    sendfile(clientsocket, filehandle);
//                    fclose(filehandle);
//                }
                
                
//Client
//                FILE *filehandle = fopen("imagefile.jpg", "wb");
//                if (filehandle != NULL)
//                {
//                    bool ok = readfile(clientsocket, filehandle);
//                    fclose(filehandle);
//                    
//                    if (ok)
//                    {
//                        // use file as needed...
//                    }
//                    else
//                        remove("imagefile.jpg");
//                }
                
            default:
                cout << "Enter a valid option!\n";
        }
        cout << "\nEnter 0 to exit; 1 to continue\n";
        cin >> choice;
        if(!choice)
            break;
    }
    return 0;
}

void DataFileSys::set_file_system_name()
{       cout << "Enter file system name\n";
    char temp[80];
    cin >> temp;
    strcpy(file_system_name, temp);
    initialize();
}

DataFileSys::DataFileSys(char f_name[])
{
    if(f_name == NULL)
        set_file_system_name();
    else
    {
        cout << "Existing File System\n";
        strcpy(file_system_name, f_name);
        read_from_file();
    }
}
void DataFileSys::initialize()
{
    fstream myfile(file_system_name, ios::out);
    int i;
    myfile.seekp(0, ios::beg);
    for(i = 0; i < MAX_FILES; i++)
    {
        strcpy(files[i].name, "\0");
        files[i].len = 0;
        files[i].startpos = 0;
    }
    myfile.close();
    write_to_file();
}

void DataFileSys::list_files()
{
    for(int i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), "\0"))
            break;
        cout << files[i].get_file_name() << endl;
    }
}

char* DataFileSys::show_file_content(char* f_name)
{
    fstream myfile(file_system_name, ios::in);
    int i;
    char* file_contents = new char[MAX_FILE_LEN];
    cout << f_name << "\n";
    for(i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), f_name))
        {
            myfile.seekg(files[i].get_startpos(), ios::beg);
            myfile.read(file_contents, files[i].get_file_length());
            *(file_contents + files[i].get_file_length()) = '\0';
            myfile.close();
            return file_contents;
        }
    }
    cout<<"File not found!";
    myfile.close();
    return NULL;
}
char* DataFileSys::search_file(char* f_name)
{
    int i;
    for(i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), f_name))
        {
            cout<<"File found\nFile name:";
            return files[i].get_file_name();
        }
    }
    
    cout<<"File not found!";
    return NULL;
    
}
void DataFileSys :: search_keyword(char* f_name, char* keyword)
{
    fstream myfile(file_system_name, ios::in);
    for(int i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(f_name, files[i].get_file_name()))
        {
            char* file_content = new char[MAX_FILE_LEN];
            myfile.seekg(files[i].get_startpos());
            myfile.read(file_content, files[i].get_file_length());
            char* p = strstr(file_content, keyword);
            if(p == NULL)
            {
                cout<<"\nKeyword not Found!\n";
                myfile.close();
                return;
            }
            long pos = p - file_content + 1;      // The difference between the address of substring in the string and
            // the base address plus 1
            cout<<"\nKeyword Found!\nPosition of keyword:\t"<<pos;
            myfile.close();
            return;
            
        }
    }
    cout<<"\nFile not found!\n";
    myfile.close();
    return;
}

void DataFileSys::delete_file(char* f_name)
{
    int i,j;
//    char* file_content = new char[MAX_FILE_LEN];
    for(i = 0; i < MAX_FILES; i++)
    {
        if(!strcmp(files[i].get_file_name(), f_name))
        {
            int del_len;
            strcpy(files[i].name, "\0");
            del_len = files[i].get_file_length() ;
            files[i].len = 0;
            files[i].startpos = 0;
            write_to_file();        //Will skip the content of the file to be deleted
            for(j = i + 1; j < MAX_FILES ; j++)
            {
                strcpy(files[j - 1].name, files[j].get_file_name());
                files[j - 1].len = files[j].get_file_length();
                files[j - 1].startpos = files[j].get_startpos() - del_len;
            }
            write_to_file();
            cout << "\nFile deleted!\n";
            return;
        }
    }
    cout<<"File not found!";
}


void DataFileSys::create_file(char* f_name, char* file_contents)
{
    int i;
    for(i = 0; i < MAX_FILES; i++){
        if(!strcmp(files[i].get_file_name(), "\0"))
            break;
    }
    if(i == MAX_FILES)
        cout<<"No space";
    else
    {
        fstream myfile(file_system_name, ios::out | ios::app);
        strcpy(files[i].name, f_name);
        files[i].len = strlen(file_contents);
        myfile.seekp(0, ios::end);
        files[i].startpos = myfile.tellp();
        myfile.write(file_contents,sizeof(char) * strlen(file_contents));
        myfile.close();
        write_to_file();
    }
}


void DataFileSys::read_from_file()
{
    fstream myfile(file_system_name, ios::in);
    int i;
    myfile.seekg(0 , ios::beg);
    for(i = 0; i < MAX_FILES; i++)          //read already created files till null string is encountered or max limit
    {
        myfile.read((char*)&(files[i].name) , sizeof(files[i].name));
        if(!strcmp(files[i].name,"\0"))
            break;
        myfile.read((char*)&files[i].len , sizeof(long int));
        myfile.read((char*)&files[i].startpos , sizeof(int));
    }
    while(i < MAX_FILES)
    {
        strcpy(files[i].name,"\0");
        files[i].len = 0;
        files[i].startpos = 0;
        i++;
    }
    myfile.close();
}

void DataFileSys::write_to_file()
{
    fstream myfile(file_system_name, ios::in);
    fstream newfile("temp.txt", ios::out);
    int i;
    char file_content[MAX_FILE_LEN];
    newfile.seekp(0 , ios::beg);
    for(i = 0; i < MAX_FILES; i++)
    {
        newfile.write((char*)&files[i].name , sizeof(files[i].name));
        newfile.write((char*)&files[i].len , sizeof(long int));
        newfile.write((char*)&files[i].startpos , sizeof(int));
    }
    for(i = 0; i < MAX_FILES; i++)
    {
        if(files[i].get_file_length())
        {
            myfile.seekg(files[i].get_startpos(), ios::beg);
            myfile.read((char*)&file_content, sizeof(char) * files[i].len);
            newfile.seekp(0 , ios::end);
            newfile.write((char*)&file_content, sizeof(char) * files[i].len);
        }
    }
    newfile.close();
    myfile.close();
    remove(file_system_name);
    rename("temp.txt", file_system_name);
    
}

bool senddata(SOCKET sock, void *buf, int buflen)
{
    unsigned char *pbuf = (unsigned char *) buf;
    
    while (buflen > 0)
    {
        int num = send(sock, pbuf, buflen, 0);
        if (num == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                // optional: use select() to check for timeout to fail the send
                continue;
            }
            return false;
        }
        
        pbuf += num;
        buflen -= num;
    }
    
    return true;
}

bool sendlong(SOCKET sock, long value)
{
    value = htonl(value);
    return senddata(sock, &value, sizeof(value));
}

bool sendfile(SOCKET sock, FILE *f)
{
    fseek(f, 0, SEEK_END);
    long filesize = ftell(f);
    rewind(f);
    if (filesize == EOF)
        return false;
    if (!sendlong(sock, filesize))
        return false;
    if (filesize > 0)
    {
        char buffer[1024];
        do
        {
            size_t num = min(filesize, sizeof(buffer));
            num = fread(buffer, 1, num, f);
            if (num < 1)
                return false;
            if (!senddata(sock, buffer, num, 0))
                return false;
            filesize -= num;
        }
        while (filesize > 0);
    }
    return true;
}

//Client
bool readdata(SOCKET sock, void *buf, int buflen)
{
    unsigned char *pbuf = (unsigned char *) buf;
    
    while (buflen > 0)
    {
        int num = recv(sock, pbuf, buflen, 0);
        if (num == SOCKET_ERROR)
        {
            if (WSAGetLastError() == WSAEWOULDBLOCK)
            {
                // optional: use select() to check for timeout to fail the read
                continue;
            }
            return false;
        }
        else if (num == 0)
            return false;
        
        pbuf += num;
        buflen -= num;
    }
    
    return true;
}

bool readlong(SOCKET sock, long *value)
{
    if (!readdata(sock, value, sizeof(value)))
        return false;
    *value = ntohl(*value);
    return true;
}

bool readfile(SOCKET sock, FILE *f)
{
    long filesize;
    if (!readlong(sock, &filesize))
        return false;
    if (filesize > 0)
    {
        char buffer[1024];
        do
        {
            int num = min(filesize, sizeof(buffer));
            if (!readdata(sock, buffer, num))
                return false;
            int offset = 0;
            do
            {
                size_t written = fwrite(&buffer[offset], 1, num-offset, f);
                if (written < 1)
                    return false;
                offset += written;
            }
            while (offset < num);
            filesize -= num;
        }
        while (filesize > 0);
    }
    return true;
}
