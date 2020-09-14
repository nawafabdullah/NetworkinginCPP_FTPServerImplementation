
#include <dirent.h>


#ifndef FTP_SERVER_PASSIVE_H
#define FTP_SERVER_PASSIVE_H

#define PASSIVE_DEFAULT_PORT "0"
#define DATA_CONNECTION_TIME_OUT_SEC 20
#define DATA_CONNECTION_TIME_OUT_USEC 0

void enteringIntoPassive(char* argument, const int controlSockDescriptor, int& passiveListenerSockDescriptor, int& dataSockDescriptor);
//Starts a passive connection listener by calling 'startPassiveListener()' function.
//Once successful on the above function call, sends an appropriate response to the client.
//Waits for a specific time interval for the client to send a connection request on the listener by calling
//isListenerSocketReady() from 'ftp_server_connection_listener.hpp'.
//Accepts client's connection request, if there is any, and opens a data connection with the client by calling
//'acceptClientConnetion() function from 'ftp_server_connection_listener.hpp'.
//Closes the connection listener after opening the data connection with the client by calling 'closeListenerSocket()'
//function from 'ftp_server_connection_listener.hpp'.
//Sends appropriate response to the client using control connection.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send response to client.

void startPassiveListener(int& listenerSockDescriptor, bool& succeded);
//Starts a passive listener socket that can listen connection requests from the remote computer.
//by calling 'startListenerSocket()' function from 'ftp_server_connection_listener.hpp'.


void createPassiveSuccessResponse(char* response, const int passiveListenerSockDescriptor);
//Creates a Passive success response.
//Determines the passive listener port number from 'passiveListenerSockDescriptor' by calling
//'getPortFromSocketDescriptor()' function from 'ftp_server_net_util.hpp'.
//Determines the local IP address by calling 'getHostIPAddress()' function from 'ftp_server_net_util.hpp'.
//Includes both the IP address and the port number into passive success response according to RFC.    

#endif
