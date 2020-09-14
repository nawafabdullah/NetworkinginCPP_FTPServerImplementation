#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/select.h>

#ifndef FTP_SERVER_NET_UTIL_H
#define FTP_SERVER_NET_UTIL_H

#define MAX_IP_ADDRESS_LENGTH 1024

void closeSocket(int& sockDescriptor);
//Closes the stream socket, represented by 'sockDescriptor'.

int getPortFromSocketDescriptor(int sockDescriptor);
//Determines and returns the associated port number from a given socket descriptor.

bool isSocketReadyToRead(int sockDescriptor, int timeoutSec, int timeoutUSec, bool& isError, bool& isTimedout); 
//Returns true if there is any data sent by the remote computer on the stream socket represented by 'sockDescriptor'.
//Waits for the data until 'timeoutSec' + 0.000001x'timeoutUsec' time.
//If no data has been sent before the wait time times out, sets 'isTimedout' value to 'true'.
//If any error occurs, sets 'isError' value to 'true'.

char* getHostIPAddress();
//Determines and returns an IP address of the local host.

#endif
