#ifndef FTP_SERVER_STR_UTIL_H
#define FTP_SERVER_STR_UTIL_H

void replaceCharWith(char* str, char find, char replace);
//Replaces all the occurrences of 'find' character in 'str' with 'replace' character.

bool startsWith(const char* prefix, const char* str);
//Returns true if 'str' starts with 'prefix'.

void toUpper(char* str);
//Changes all characters of 'str' to upper case.

char* stripSpaceAtStart(char* str);
//Removes all the spaces, if there is any, from the beginning of 'str'.

void stripNewlineAtEnd(char* str);
//Removes new line character ('\n'), if there is any, from the end of 'str'.

#endif
