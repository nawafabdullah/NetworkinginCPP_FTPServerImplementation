#ifndef FTP_SERVER_NLIST_H
#define FTP_SERVER_NLIST_H

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define DEFAULT_DIRECTORY_PATH "./"

int listDirEntries(int dataSockDescriptor);
//Determines and sends the list of current directory entries to the client using 
//the data connection, represented by 'dataSockDescriptor'.
//Returns the count of entries to the caller.

#endif
