/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/



#include "ftp_server_connection.hpp"
#include "ftp_server_net_util.hpp"
int sendToRemote(int sockDescriptor, const char* message, int messageLength)
{
//Sends the 'message' of length 'messageLength' to the remote computer.
//Uses a stream socket, represented by 'sockDescriptor', to send the message.
int send_descriptor = send(sockDescriptor, message, messageLength, 0);
return send_descriptor;
}
bool isConnectionReadyToRead(int sockDescriptor, int timeoutSec, int timeoutUSec, bool& isError, bool&isTimedout)
{
//Returns true if there is any data sent by the remote computer on the stream socket represented by 'sockDescriptor'.
//Waits for the data until 'timeoutSec' + 0.000001x'timeoutUsec' time.
//If no data has been received before the wait time times out, sets 'isTimedout' value to 'true'.
//If any error occurs, sets 'isError' value to 'true'.
//Calls 'isSocketReadyToRead()' function from 'ftp_server_net_util.hpp' to do all of the above.
return isSocketReadyToRead(sockDescriptor, timeoutSec,timeoutUSec,isError,isTimedout);
}

int receiveFromRemote(int sockDescriptor, char* message, int messageLength)
{
   //Receives data from the remote computer into a buffer 'message'.
   //Sets the length of the received data into 'messageLength'.
   //Uses a stream socket, represented by 'sockDescriptor', to receive the data.
   int read_descriptor = read(sockDescriptor, message, messageLength);
   return read_descriptor;
}

void closeConnection(int& sockDescriptor)
//Closes the stream socket, represented by 'sockDescriptor'.
{
close(sockDescriptor);
}
void closeAllConnections(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected)

{
//Closes all the stream sockets, represented by 'controlSockDescriptor', 'dataListenerSockDescriptor', and 'dataSockDescriptor'.   
   close(controlSockDescriptor);
   close(dataListenerSockDescriptor);
   close(dataSockDescriptor);
   //Sets 'false' to 'isClientConnected'.
   isClientConnected = false;
}
