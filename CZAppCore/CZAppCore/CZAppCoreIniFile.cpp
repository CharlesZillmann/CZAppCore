//
//  CZAppCoreIniFile.cpp
//  CZAppCore
//
//  Created by Charles Zillmann on 9/5/17.
//  Copyright © 2017 Charles Zillmann. All rights reserved.
//

#include "CZAppCoreIniFile.hpp"

//Order of Operations Per Segment
//Read a Segment String as Input
//Remove Whitespace
//Remove Unwanted Char Based on Type
//Apply Case
//Truncate to Max Length
//Append Segment Seperator

Char:Dec

0:48, 9:57
A:65, Z:90
a:97, z:122
try this:

char str[50] = "Remove The Spaces!!";

int i =0;
for(; i<strlen(str); i++)
{
    if(str[i]>=48 && str[i]<=57 || str[i]>=65 && str[i]<=90 || str[i]>=97 && str[i]<=122)
        //This is equivalent to
        //if(str[i]>='0' && str[i]<='9' || str[i]>='A' && str[i]<='Z' || str[i]>='a' && str[i]<='z')
        printf("alphaNumeric:%c\n", str[i]);
        else
        {
            printf("special:%c\n", str[i]);
            //remove that
        }
}

void remove_spaces (char* restrict str_trimmed, const char* restrict str_untrimmed)
{
    while (*str_untrimmed != '\0')
    {
        if(!isspace(*str_untrimmed))
        {
            *str_trimmed = *str_untrimmed;
            str_trimmed++;
        }
        str_untrimmed++;
    }
    *str_trimmed = '\0';
}

void camel_case (char* restrict str_camel, const char* restrict str_input)
{
    bool hump == true;
    while (*str_input != '\0')
    {
        if( ( isspace(*str_input) || isspecial(*str_input) ) && (!hump) )
        {
            hump == true;
        } else {
            hump == false;
        }
        
        if(!isspace(*str_input))
        {
            hump == true;
            *str_trimmed = *str_untrimmed;
            str_trimmed++;
        } else {
            hump == false;
        }
        str_untrimmed++;
    }
    *str_trimmed = '\0';
}

void capitalize(char *str, char *new)
{
    int i=0;
    
    new[i] = toupper(str[0]);
    i++;//increment after every look
    while(str[i] != '\0')
    {
        if(isspace(str[i]))
        {
            new[i] = str[i];
            new[i+1] = toupper(str[i+1]);
            i+=2;//look twice, increment twice
        }
        else
        {
            new[i] = str[i];
            i++;//increment after every look
        }
    }
}

char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;
    
    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }
    
    len = strlen(str);
    endp = str + len;
    
    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }
    
    if( str + len - 1 != endp )
        *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
        *str = '\0';
    
    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
        while( *frontp ) { *endp++ = *frontp++; }
        *endp = '\0';
    }
    
    
    return str;
}

int main(int argc, char *argv[])
{
    char *sample_strings[] =
    {
        "nothing to trim",
        "    trim the front",
        "trim the back     ",
        " trim one char front and back ",
        " trim one char front",
        "trim one char back ",
        "                   ",
        " ",
        "a",
        "",
        NULL
    };
    char test_buffer[64];
    int index;
    
    for( index = 0; sample_strings[index] != NULL; ++index )
    {
        strcpy( test_buffer, sample_strings[index] );
        printf("[%s] -> [%s]\n", sample_strings[index],
               trim(test_buffer));
    }
    
    /* The test prints the following:
     [nothing to trim] -> [nothing to trim]
     [    trim the front] -> [trim the front]
     [trim the back     ] -> [trim the back]
     [ trim one char front and back ] -> [trim one char front and back]
     [ trim one char front] -> [trim one char front]
     [trim one char back ] -> [trim one char back]
     [                   ] -> []
     [ ] -> []
     [a] -> [a]
     [] -> []
     */
    
    return 0;
}
