/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/


#include"ftp_server_nlist.hpp"
#include <sys/stat.h>
int listDirEntries(int dataSockDescriptor)
{
//Determines and sends the list of current directory entries to the client using 
//the data connection, represented by 'dataSockDescriptor'.
//Returns the count of entries to the caller.

struct stat  statbuf;
int counter = 0;
DIR *dir;
struct dirent *ent;
if ((dir = opendir (".")) != NULL) 
{
  /* print all the files and directories within directory */
  while ((ent = readdir (dir)) != NULL) 
  {
    /// printf ("%s\n", ent->d_name);
    if (ent->d_type == DT_DIR){
        
      dprintf(dataSockDescriptor, "D\t\t%s\n", ent->d_name);
                   
     }else
     {
       stat(ent->d_name, &statbuf);
       int size = statbuf.st_size;           
       dprintf(dataSockDescriptor, "F\t\t%s\t\t%d\n",ent->d_name,size);          
     }
    counter++;  
  }
  closedir (dir);
} else {
  /* could not open directory */
  perror ("");
  return EXIT_FAILURE;
}
return counter;
}
