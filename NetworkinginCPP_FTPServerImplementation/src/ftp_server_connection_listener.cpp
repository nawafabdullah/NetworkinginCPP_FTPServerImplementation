/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/


#include "ftp_server_connection_listener.hpp"
#include "ftp_server_connection.hpp"
#include "ftp_server_net_util.hpp"


struct sockaddr_in server, client; 
//https://www.youtube.com/watch?v=WDn-htpBlnU
//socket - bind - listen  
void startListenerSocket(char* port, int& listenerSockDescriptor, bool& succeded)
{
 //Starts a listener socket that can listen connection requests from the remote computer.
  listenerSockDescriptor = socket (AF_INET, SOCK_STREAM,0);
  int port_int = atoi(port); 
  if (listenerSockDescriptor < 0)
  {
    perror ("could not create");
    succeded = false;
    return; 
  }

  bzero((char *) &server, sizeof(server));
//Creates a stream socket and binds it to a local IP address and to the given port number.
  char* IP_addr = getHostIPAddress(); //ftp server net util
  server.sin_family = AF_INET;
  server.sin_port = htons(port_int);
  server.sin_addr.s_addr = INADDR_ANY;

  int bind_descriptor = bind(listenerSockDescriptor, (struct sockaddr*) &server, sizeof(server));
  if (bind_descriptor < 0)
  {
    perror("could not BIND \n");
    succeded = false; 
    return; 
  } 

//Once the binding is successful listens for connection request from the remote computers.
  int listen_descriptor = listen(listenerSockDescriptor, MAX_PENDING_CONNECTIONS);
  if(listen_descriptor < 0)
  {
    perror("could not LISTEN");
    succeded = false;
    //return;
  } else
  {
    printf("SUCCESS! Listening for connection requests at IP: %s and port %i \n", IP_addr,port_int);
    succeded = true;   
 }
}
bool isListenerSocketReady(int sockDescriptor, int timeoutSec, int timeoutUSec, bool& isError, bool&isTimedout)
{

  //Returns true if there is any remote connection request on the listener socket represented by 'sockDescriptor'.
//Waits for a connection request until 'timeoutSec' + 'timeoutUsec' time.
//If no connection request has been received before the wait time times out, sets 'isTimedout' value to 'true'.
//If any error occurs, sets 'isError' value to 'true'.
//Calls 'isSocketReadyToRead()' function from 'ftp_server_net_util.hpp' to do all of the above.
  return isSocketReadyToRead(sockDescriptor, timeoutSec, timeoutUSec, isError, isTimedout);
}

void acceptClientConnection(int listenerSockDescriptor, int& clientSockDescriptor)
{
  //bzero((char *) &client, sizeof(client));
  socklen_t size = sizeof(client); 
  //Accepts a connection request on the listener socket represented by 'listenerSockDescriptor'.
  //Opens the connection to the remote computer and represents the connection by 'clientSockDescriptor'.
  clientSockDescriptor = accept(listenerSockDescriptor, (struct sockaddr *)&client, &size);
  if (clientSockDescriptor < 0)
  {
    perror(" could not accept connection...");
  } else
  {
    printf("accepted connection...\n");
  } 
}

void closeListenerSocket(int& listenerSockDescriptor)
{
 //Closes the listener socket represented by 'listenerSockDescriptor'.
  close (listenerSockDescriptor);
}
