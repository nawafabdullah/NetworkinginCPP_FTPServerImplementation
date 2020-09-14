#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>


#ifndef FTP_SERVER_CONNECTION_H
#define FTP_SERVER_CONNECTION_H

int sendToRemote(int sockDescriptor, const char* message, int messageLength);
//Sends the 'message' of length 'messageLength' to the remote computer.
//Uses a stream socket, represented by 'sockDescriptor', to send the message.

bool isConnectionReadyToRead(int sockDescriptor, int timeoutSec, int timeoutUSec, bool& isError, bool&isTimedout);
//Returns true if there is any data sent by the remote computer on the stream socket represented by 'sockDescriptor'.
//Waits for the data until 'timeoutSec' + 0.000001x'timeoutUsec' time.
//If no data has been received before the wait time times out, sets 'isTimedout' value to 'true'.
//If any error occurs, sets 'isError' value to 'true'.
//Calls 'isSocketReadyToRead()' function from 'ftp_server_net_util.hpp' to do all of the above.

int receiveFromRemote(int sockDescriptor, char* message, int messageLength);
//Receives data from the remote computer into a buffer 'message'.
//Sets the length of the received data into 'messageLength'.
//Uses a stream socket, represented by 'sockDescriptor', to receive the data.

void closeConnection(int& sockDescriptor);
//Closes the stream socket, represented by 'sockDescriptor'.

void closeAllConnections(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected);
//Closes all the stream sockets, represented by 'controlSockDescriptor', 'dataListenerSockDescriptor', and 'dataSockDescriptor'.
//Sets 'false' to 'isClientConnected'.

#endif
