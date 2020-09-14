#ifndef FTP_SERVER_SESSION_H
#define FTP_SERVER_SESSION_H

#define FTP_CLIENT_SESSION_TIMEOUT_SEC 600 //10 minutes
#define FTP_CLIENT_SESSION_TIMEOUT_USEC 0

void startClientFTPSession(int& controlSockDescriptor);
//Starts a client FTP session against a client control connection represented by 'controlSockDescriptor'.
//Keeps track of the states of the session using various local variables including 'controlSockDescriptor'.
//Other local variables that a session needs to maintain are as follows:
//      isClientConnected = true
//      isUser = false
//      isLoggedIn = false
//      dataSocketDescriptor = -1
//      dataListenerSockDescriptor = -1
//      rootDir
//Determines the root directory of the FTP server and sets it to the local variable 'rootDir'
//Passes the other references of these local variables in various function calls, the called functions then sets
//the appropriate value to these variables using the references.
//Waits for client's FTP request for FTP_CLIENT_SESSION_TIMEOUT_SEC + 0.000001xFTP_CLIENT_SESSION_TIMEOUT_USEC time
//calling 'isConnectionReadyToRead()' function from 'ftp_server_connection.hpp'.
//If a request comes before the timeout, reads the request.
//Interprets the request, takes appropriate action, and sends appropriate response to the client by calling
//'interpreteCommand()' function from 'ftp_server.command.hpp'.
//If timeout or error happens before a FTP request comes, sends an appropriate response to the client
//and closes all connections calling 'closeAllConnections()' function from 'ftp_server_connection.hpp'.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send response to the client.

#endif
