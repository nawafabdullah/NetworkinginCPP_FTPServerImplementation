/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/




#include "ftp_server_net_util.hpp"
void replaceCharWith(char* str, char find, char replace)
//Replaces all the occurrences of 'find' character in 'str' with 'replace' character.
{
  int i =0;
  while (str[i] != '\0'){
    if(str[i] == find){
      str[i] = replace;
    }
    i++;
  }

}
bool startsWith(const char* prefix, const char* str)
//Returns true if 'str' starts with 'prefix'.
{
return true;
}
void toUpper(char* str)
//Changes all characters of 'str' to upper case.
{

}
char* stripSpaceAtStart(char* str)
//Removes all the spaces, if there is any, from the beginning of 'str'.
{
return str;
}
void stripNewlineAtEnd(char* str)
//Removes new line character ('\n'), if there is any, from the end of 'str'.
{
}
