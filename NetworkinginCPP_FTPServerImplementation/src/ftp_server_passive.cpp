/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/




#include "ftp_server_passive.hpp"
#include "ftp_server_connection_listener.hpp"
#include "ftp_server_connection.hpp"
#include "ftp_server_net_util.hpp"
#include "ftp_server_command.hpp"
#include "ftp_server_string_util.hpp"
#include "ftp_server_response.hpp"
#include <bits/stdc++.h> 


int charsize = 512;
void enteringIntoPassive(char* argument, const int controlSockDescriptor, int& passiveListenerSockDescriptor, int& dataSockDescriptor)
//Closes the connection listener after opening the data connection with the client by calling 'closeListenerSocket()'
//function from 'ftp_server_connection_listener.hpp'.
//Sends appropriate response to the client using control connection.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send response to client.
{

   //Starts a passive connection listener by calling 'startPassiveListener()' function.
   bool examine = false;
   bool isError = false;
   bool isTimedout = false;   
   startPassiveListener(passiveListenerSockDescriptor,examine);

   //Once successful on the above function call, sends an appropriate response to the client.
   if(examine){
      char *buffer = new char[charsize];
      createPassiveSuccessResponse(buffer,passiveListenerSockDescriptor);
      sendToRemote(controlSockDescriptor, buffer, FTP_RESPONSE_MAX_LENGTH);

      //Waits for a specific time interval for the client to send a connection request on the listener by calling
     //isListenerSocketReady() from 'ftp_server_connection_listener.hpp'.
     if(isListenerSocketReady(passiveListenerSockDescriptor, DATA_CONNECTION_TIME_OUT_SEC, DATA_CONNECTION_TIME_OUT_USEC, isError,isTimedout))
     {

	//Accepts client's connection request, if there is any, and opens a data connection with the client by calling
//'acceptClientConnetion() function from 'ftp_server_connection_listener.hpp'.
	acceptClientConnection(passiveListenerSockDescriptor, dataSockDescriptor);

//Closes the connection listener after opening the data connection with the client by calling 'closeListenerSocket()'
//function from 'ftp_server_connection_listener.hpp'.       
              closeListenerSocket(passiveListenerSockDescriptor);


//Sends appropriate response to the client using control connection.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send response to client.    
              sendToRemote(controlSockDescriptor, DATA_CONNECTION_SUCCESS_RESPONSE, FTP_RESPONSE_MAX_LENGTH);



} else 
{	
perror ("listener not ready");

}


}

}
void startPassiveListener(int& listenerSockDescriptor, bool& succeded)
{

//Starts a passive listener socket that can listen connection requests from the remote computer.
//by calling 'startListenerSocket()' function from 'ftp_server_connection_listener.hpp'.
 startListenerSocket((char*)PASSIVE_DEFAULT_PORT,listenerSockDescriptor,succeded);

}

void createPassiveSuccessResponse(char* response, const int passiveListenerSockDescriptor)
//'getPortFromSocketDescriptor()' function from 'ftp_server_net_util.hpp'.
//Determines the local IP address by calling 'getHostIPAddress()' function from 'ftp_server_net_util.hpp'.
//Includes both the IP address and the port number into passive success response according to RFC.    
{

//Creates a Passive success response.
//Determines the passive listener port number from 'passiveListenerSockDescriptor' by calling
   int port  = getPortFromSocketDescriptor(passiveListenerSockDescriptor);
   char *ip = getHostIPAddress();

   string bin = bitset<16>(port).to_string();
  
   string p1Str = bin.substr(0,8);
   string p2Str = bin.substr(8,16);

   bitset<32> b(p1Str);
   int P1 =b.to_ulong();

   bitset<32> c(p2Str);
   int P2 =c.to_ulong();
    
   replaceCharWith(ip,'.',',');

   sprintf(response, PASSIVE_SUCCESS_RESPONSE , ip, P1,P2);



}
