/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/




#include"ftp_server_net_util.hpp"

/*
#define MAX_IP_ADDRESS_LENGTH 1024
*/
void closeSocket(int& sockDescriptor)
{
  //Closes the stream socket, represented by 'sockDescriptor'.
  close(sockDescriptor);
}

//https://pubs.opengroup.org/onlinepubs/009696699/basedefs/sys/socket.h.html
int getPortFromSocketDescriptor(int sockDescriptor)
//Determines and returns the associated port number from a given socket descriptor.

{
  struct sockaddr_in sin;
  socklen_t size = sizeof (sin);

  int port_desriptor = getsockname(sockDescriptor, (struct sockaddr*) &sin, &size);

  if (port_desriptor == -1)
  { 
    perror ("failed to get port");
    return 0;
  }
  return ntohs(sin.sin_port); 
}

bool isSocketReadyToRead(int sockDescriptor, int timeoutSec, int timeoutUSec, bool& isError, bool& isTimedout)
{

//Returns true if there is any data sent by the remote computer on the stream socket represented by 'sockDescriptor'.
//Waits for the data until 'timeoutSec' + 0.000001x'timeoutUsec' time.
//If no data has been sent before the wait time times out, sets 'isTimedout' value to 'true'.
//If any error occurs, sets 'isError' value to 'true'.

   fd_set readset;
   struct timeval timeout;
   int val;
   bool status = false;
   FD_ZERO(&readset);
   FD_SET(sockDescriptor , &readset);
   timeout.tv_sec = timeoutSec;
   timeout.tv_usec = timeoutUSec;

   val = select(sockDescriptor + 1, &readset, NULL, NULL, &timeout);


   if(val == -1){

      isError = true;
      status = false;

   }else if(val == 0){

      isTimedout = true;
      status = false;

   }else{
     
      status = true;   
   }
   return status;
}

char* getHostIPAddress()
//Determines and returns an IP address of the local host.
{
//Determines and returns an IP address of the local host.
   int size = 512;
   char buffer[size];
   struct hostent *host;   
   gethostname(buffer, size); //store in buffer
   host = gethostbyname(buffer);
   // get host ip 
   char *buffer_ptr = inet_ntoa(*((struct in_addr*) host->h_addr_list[0]));
   return buffer_ptr;  
}

