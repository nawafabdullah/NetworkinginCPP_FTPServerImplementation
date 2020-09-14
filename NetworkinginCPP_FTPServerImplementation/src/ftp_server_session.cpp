/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/




#include"ftp_server_session.hpp"
#include"ftp_server_connection.hpp"
#include"ftp_server_command.hpp"
#include"ftp_server_response.hpp"
int char_size_ = 512;

void startClientFTPSession(int& controlSockDescriptor)
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send response to the client.
{
//Starts a client FTP session against a client control connection represented by 'controlSockDescriptor'.
//Keeps track of the states of the session using various local variables including 'controlSockDescriptor'.
//Other local variables that a session needs to maintain are as follows:
//      isClientConnected = true
//      isUser = false
//      isLoggedIn = false
//      dataSocketDescriptor = -1
//      dataListenerSockDescriptor = -1
//      rootDir
   bool isClientConnected = false;
   bool isUser = false;
   bool isLoggedIn = false;
   int dataSocketDescriptor = -1;
   int dataListenerSockDescriptor = -1;
   char* rootDir;

   bool isError = false;
   bool isTimedout = false;

//https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.3.0/com.ibm.zos.v2r3.bpxbd00/rtgtc.htm
//Determines the root directory of the FTP server and sets it to the local variable 'rootDir'
   char current_working_directory[char_size_];
   if (getcwd(current_working_directory, sizeof(current_working_directory)) != NULL) 
   {
     rootDir = current_working_directory;
   } else 
   {
     perror ("could not set root directory");
   }

//Passes the other references of these local variables in various function calls, the called functions then sets
//the appropriate value to these variables using the references.


   sendToRemote(controlSockDescriptor, CONNECTED_RESPONSE, FTP_RESPONSE_MAX_LENGTH);

	//calling 'isConnectionReadyToRead()' function from 'ftp_server_connection.hpp'.

   bool connection_status = isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError,isTimedout);

   
   if (connection_status)
   {		
     while(connection_status)
     {            
       //Waits for client's FTP request for FTP_CLIENT_SESSION_TIMEOUT_SEC + 0.000001xFTP_CLIENT_SESSION_TIMEOUT_USEC time
       if (!isError && !isTimedout)
       {
	 char *command = new char[COMMAND_BUFFER_SIZE];
	 memset(command, '\0', COMMAND_BUFFER_SIZE);
	 receiveFromRemote(controlSockDescriptor,command,COMMAND_BUFFER_SIZE);
	 
	 interpreteCommand(command, controlSockDescriptor, dataListenerSockDescriptor, dataSocketDescriptor, isClientConnected,isUser,isLoggedIn,rootDir);
	//printf ("INTREPRET FROM SESSION \n");
	//calling 'isConnectionReadyToRead()' function from 'ftp_server_connection.hpp'.
        //If a request comes before the timeout, reads the request.
	 connection_status = isConnectionReadyToRead(controlSockDescriptor, FTP_CLIENT_SESSION_TIMEOUT_SEC, FTP_CLIENT_SESSION_TIMEOUT_USEC, isError,isTimedout);
       } else
       {
	 //Waits for client's FTP request for FTP_CLIENT_SESSION_TIMEOUT_SEC + 0.000001xFTP_CLIENT_SESSION_TIMEOUT_USEC time
	 if(isTimedout)
	 {
	   perror ("TIME OUT!! \n");
	 } else
	 {               
	   sendToRemote(controlSockDescriptor, CONNECTION_RESET_BY_PEER, FTP_RESPONSE_MAX_LENGTH);
	 }
	 closeAllConnections(controlSockDescriptor,dataListenerSockDescriptor,dataSocketDescriptor, isClientConnected); 
       }
     }
      
   }else
   {   
    //Interprets the request, takes appropriate action, and sends appropriate response to the client by calling
    //'interpreteCommand()' function from 'ftp_server.command.hpp'.
    //If timeout or error happens before a FTP request comes, sends an appropriate response to the client
    //and closes all connections calling 'closeAllConnections()' function from 'ftp_server_connection.hpp'.
     closeAllConnections(controlSockDescriptor,dataListenerSockDescriptor,dataSocketDescriptor, isClientConnected);		
   }
}

