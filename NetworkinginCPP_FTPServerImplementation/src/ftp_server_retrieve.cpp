/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/



#include "ftp_server_retrieve.hpp"
#include "ftp_server_connection.hpp"
#include "ftp_server_response.hpp"

int sendFile(char* filename, int& dataSockDescriptor)
//Checks whether the file with the 'filename' is accessible or not.
//If the file is accessible, opens the file and reads and sends the file content chunk by chunk to the client.
//DATA_SOCKET_SEND_BUFFER_SIZE is used as the chunk size.
//Sends file chunks using data connection represented by 'dataSockDescriptor'.
//Returns the total number of bytes sent to the client.
{

  FILE *file = NULL;
  char *buff = new char[DATA_SOCKET_SEND_BUFFER_SIZE];  // array of bytes, not pointers-to-bytes
  size_t Read = 0;

   int tByte = 0;
   file = fopen(filename, "rb");   

   if (file != NULL)
   {
     // read up to sizeof(buffer) bytes
     while ((Read = fread(buff, 1, sizeof(buff), file)) > 0)
     {
       // process bytesRead worth of data in buffer
       sendToRemote(dataSockDescriptor, buff, Read);
       tByte += Read;
     }

     return tByte;
   }else{
     printf("%s does not exist.\n", filename);
     return -1;
   }

   
}
