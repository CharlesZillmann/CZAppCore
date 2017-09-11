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
#include <python2.7/Python.h>

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

long DataFile :: get_startpos()
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
        cout << "7. Pull a file from the Network\n";
        cout << "8. Push a file to the Network\n";
        cout << "9. Monitor Network for file pull requests\n";
        cout << "10. Launch a Python script to process data\n";
        cout << "11. Launch a Program to process data";
        cout << "12. Mount a Container Data Volume";
        cout << "13. Unmount a Container Data Volume";
        
        
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
            long del_len;
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

bool DataFileSys::senddata(SOCKET sock, void *buf, int buflen)
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

bool DataFileSys::sendlong(SOCKET sock, long value)
{
    value = htonl(value);
    return senddata(sock, &value, sizeof(value));
}

bool DataFileSys::sendfilenetwork(SOCKET sock, FILE *f)
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
bool DataFileSys::readdatasocket(SOCKET sock, void *buf, int buflen)
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

bool DataFileSys::readlongsocket(SOCKET sock, long *value)
{
    if (!readdata(sock, value, sizeof(value)))
        return false;
    *value = ntohl(*value);
    return true;
}

bool DataFileSys::readfilenetwork(SOCKET sock, FILE *f)
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

#define PORT 20000
#define LENGTH 512

int DataFileSys::main(int argc, char *argv[]){
    int sockfd;
    int nsockfd;
    char revbuf[LENGTH];
    struct sockaddr_in remote_addr;
    
    /* Get the Socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
        exit(1);
    }
    
    /* Fill the socket address struct */
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &remote_addr.sin_addr);
    bzero(&(remote_addr.sin_zero), 8);
    
    /* Try to connect the remote */
    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
        exit(1);
    }
    else
        printf("[Client] Connected to server at port %d...ok!\n", PORT);
    
    /* Send File to Server */
    //if(!fork())
    //{
    char* fs_name = "house.jpg";
    char sdbuf[LENGTH];
    
    char buffer[256];
    int n;
    fgets(buffer,255,stdin);
    bzero(buffer,256);
    n = write(sockfd,buffer, strlen(buffer));
    if(n<0) printf("Error: sending filename");
    
    printf("[Client] Sending %s to the Server... ", fs_name);
    FILE *fs = fopen(fs_name, "r");
    if(fs == NULL)
    {
        printf("ERROR: File %s not found.\n", fs_name);
        exit(1);
    }
    
    bzero(sdbuf, LENGTH);
    int fs_block_sz;
    while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs)) > 0)
    {
        if(send(sockfd, sdbuf, fs_block_sz, 0) < 0)
        {
            fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
            break;
        }
        bzero(sdbuf, LENGTH);
    }
    printf("Ok File %s from Client was Sent!\n", fs_name);
    //}
    
    
    close (sockfd);
    printf("[Client] Connection lost.\n");
    return (0);
}

//server
char buffer[256];
int n;
fgets(buffer,255,stdin);
bzero(buffer,256);
n = write(sockfd,buffer, strlen(buffer));
if(n<0) printf("Error: sending filename");

#define PORT 20000
#define BACKLOG 5
#define LENGTH 512

int main ()
{
    int sockfd;
    int nsockfd;
    int num;
    int sin_size;
    struct sockaddr_in addr_local; /* client addr */
    struct sockaddr_in addr_remote; /* server addr */
    char revbuf[LENGTH];
    
    /* Get the Socket file descriptor */
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor. (errno = %d)\n", errno);
        exit(1);
    }
    else
        printf("[Server] Obtaining socket descriptor successfully.\n");
    
    /* Fill the client socket address struct */
    addr_local.sin_family = AF_INET; // Protocol Family
    addr_local.sin_port = htons(PORT); // Port number
    addr_local.sin_addr.s_addr = INADDR_ANY; // AutoFill local address
    bzero(&(addr_local.sin_zero), 8); // Flush the rest of struct
    
    /* Bind a special Port */
    if( bind(sockfd, (struct sockaddr*)&addr_local, sizeof(struct sockaddr)) == -1 )
    {
        fprintf(stderr, "ERROR: Failed to bind Port. (errno = %d)\n", errno);
        exit(1);
    }
    else
        printf("[Server] Binded tcp port %d in addr 127.0.0.1 sucessfully.\n",PORT);
    
    /* Listen remote connect/calling */
    if(listen(sockfd,BACKLOG) == -1)
    {
        fprintf(stderr, "ERROR: Failed to listen Port. (errno = %d)\n", errno);
        exit(1);
    }
    else
        printf ("[Server] Listening the port %d successfully.\n", PORT);
    
    int success = 0;
    while(success == 0)
    {
        sin_size = sizeof(struct sockaddr_in);
        
        /* Wait a connection, and obtain a new socket file despriptor for single connection */
        if ((nsockfd = accept(sockfd, (struct sockaddr *)&addr_remote, &sin_size)) == -1)
        {
            fprintf(stderr, "ERROR: Obtaining new Socket Despcritor. (errno = %d)\n", errno);
            exit(1);
        }
        else
            printf("[Server] Server has got connected from %s.\n", inet_ntoa(addr_remote.sin_addr));
        
        
        char buffer[256];
        bzero(buffer,256);
        int n = 0;
        n = read(nsockfd, buffer, 255);
        if (n < 0) error("ERROR reading from socket");
        printf("msg: %s\n",buffer);
        
        /*Receive File from Client */
        char* fr_name = "/house.jpg";
        FILE *fr = fopen(fr_name, "a");
        if(fr == NULL)
            printf("File %s Cannot be opened file on server.\n", fr_name);
        else
        {
            bzero(revbuf, LENGTH);
            int fr_block_sz = 0;
            while((fr_block_sz = recv(nsockfd, revbuf, LENGTH, 0)) > 0)
            {
                int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
                if(write_sz < fr_block_sz)
                {
                    error("File write failed on server.\n");
                }
                bzero(revbuf, LENGTH);
                if (fr_block_sz == 0 || fr_block_sz != 512)
                {
                    break;
                }
            }
            if(fr_block_sz < 0)
            {
                if (errno == EAGAIN)
                {
                    printf("recv() timed out.\n");
                }
                else
                {
                    fprintf(stderr, "recv() failed due to errno = %d\n", errno);
                    exit(1);
                }
            }
            printf("Ok received from client!\n");
            fclose(fr); 
        }
    }
}

//client

char buffer[256];
bzero(buffer,256);
int n = 0;
n = read(nsockfd, buffer, 255);
if (n < 0) error("ERROR reading from socket");
printf("msg: %s\n",buffer);

////Launch Python script from C++
//#include <python2.7/Python.h>
//int main(){
//    Py_SetProgramName("myPythonProgram");
//    Py_Initialize();
//    // parDict is a parameter to send to python function
//    PyObject * parDict;
//    parDict = PyDict_New();
//    PyDict_SetItemString(parDict, "x0", PyFloat_FromDouble(1.0));
//    // run python code to load functions
//    PyRun_SimpleString("exec(open('cpptest.py').read())");
//    // get function showval from __main__
//    PyObject* main_module = PyImport_AddModule("__main__");
//    PyObject* global_dict = PyModule_GetDict(main_module);
//    PyObject* func = PyDict_GetItemString(global_dict, "showval");
//    // parameter should be a tuple
//    PyObject* par = PyTuple_Pack(1, parDict);
//    // call the function
//    PyObject_CallObject(func, par);
//    Py_Finalize();
//}
//
//Function defined in cpptest.py is:
//
//1
//2
//3
//4
//5
//import numpy as np
//def showval(par):
//print "in function showval"
//print par
//print np.array([1, 2, 3])
//we get the result:
//
//1
//2
//3
//in function showval
//{'x0': 1.0}
//[1 2 3]
