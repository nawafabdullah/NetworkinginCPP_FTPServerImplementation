/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/



#include "ftp_server_command.hpp"
#include "ftp_server_connection.hpp"
#include "ftp_server_passive.hpp"
#include "ftp_server_nlist.hpp"
#include "ftp_server_retrieve.hpp"
#include "ftp_server_response.hpp"


char* recieved_command;
char* argument; 
//string command;
int char_size = 512;

void interpreteCommand(char* command, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser, bool& isLoggedIn, const char* rootDir)

//Determines, which valid command (FTP request) has been sent, only the commands defined in this header file are valid for this FTP server.
//Calls appropriate 'handleCommandXXXX()' function to handle a valid command.
//Calls 'handleCommandUnSupported()' if an invalid command has been received.
{
  //Separates the command and its argument calling 'parseCommandLine()' function.

  //Caller retrieves the parts through the references ('command' and 'argument').


  char* recieved_command = new char[COMMAND_BUFFER_SIZE]; 
  char* argument= new char[COMMAND_ARG_MAX_CHARACTER_COUNT]; 
 // parseCommandLine(command, recieved_command, argument);
  
  char* token = new char[COMMAND_BUFFER_SIZE]; 
  char* rest; 
  
  token = strtok_r(command, COMMAND_DELIMITER, &rest); 
  printf("%s\n", token); 
  recieved_command = token; 
  
 // token = strtok_r(rest, " ", &rest);
//  printf("%s\n", token); 
  
	argument = rest; 
	
	printf ("%s", recieved_command);



  string command_str = recieved_command;
  
  if (command_str.empty())
  {
    printf(" you have entered an empty command \n calling help function \n") ;         
    handleCommandUnSupported(controlSockDescriptor);
  }else if(command_str == COMMAND_USER)
  {
    handleCommandUSER(argument, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor,  isClientConnected,  isUser);
  }
  else if(command_str == COMMAND_PASSWORD)
  {
    handleCommandPASS(argument, controlSockDescriptor,  dataListenerSockDescriptor, dataSockDescriptor, isClientConnected,  isUser, isLoggedIn);
  }else if(command_str == COMMAND_PWD)
  {
    handleCommandPWD(controlSockDescriptor,  dataListenerSockDescriptor,  dataSockDescriptor, isClientConnected, isLoggedIn);
  }else if(command_str == COMMAND_CWD)
  {
    handleCommandCWD(argument, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
  }else if(command_str == COMMAND_CDUP)
  {
    handleCommandCDUP(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn, rootDir);
  }else if(command_str == COMMAND_PASV)
  {
    handleCommandPASV(argument, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
  }else if(command_str == COMMAND_NLST)
  {
     handleCommandNLST(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
  }else if(command_str == COMMAND_RETR)
  {
    handleCommandRETR(argument, controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected, isLoggedIn);
  }else if(command_str == COMMAND_QUIT)
  {
    handleCommandQUIT(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  }else 
  {
    printf("invalid command.. \n calling help function .. \n");
    handleCommandUnSupported(controlSockDescriptor);
  }
}


void parseCommandLine(char* commandLine, char* command, char* argument)
//Assigns command part to reference parameter 'command' and argument part to reference parameter 'argument'.
//Caller retrieves the parts through the references ('command' and 'argument').
{
  //Breaks the command line string that has been received through the first argument 'commandLine' into its parts 'command' and 'argument'.
  char* token = new char[COMMAND_BUFFER_SIZE]; 
  char* rest = commandLine; 
  
  token = strtok_r(commandLine, COMMAND_DELIMITER, &rest); 
  printf("%s\n", token); 
  command = token; 
  
 // token = strtok_r(rest, " ", &rest);
  printf("%s\n", token); 
  argument = rest; 
}
void handleCommandUSER(char* username, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser)
//Handles USER command by comparing 'username' with the DEFAULT_USERNAME.
//If the 'username' matches, sets 'true' to 'isUser' and sends appropriate response to the client.
//If the 'username' does not match, sends appropriate response to the client and closes all connections by calling 'closeAllConnections()' function from 'ftp_server.connection.hpp'.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
{

printf (" INSIDE USER FUNCTIONS....");

  string username_str = username;
  
  if (username_str == DEFAULT_USERNAME) 
  {
    isUser = true; 
    sendToRemote(controlSockDescriptor,  USERNAME_OK_RESPONSE, FTP_RESPONSE_MAX_LENGTH);        
  } else 
  {
    sendToRemote(controlSockDescriptor, INVALID_USERNAME_RESPONSE, FTP_RESPONSE_MAX_LENGTH);
    closeAllConnections(controlSockDescriptor,dataListenerSockDescriptor,dataSockDescriptor, isClientConnected);
  }
}

void handleCommandPASS(char* password, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isUser, bool& isLoggedIn)
//Handles PASS command by comparing 'password' with the DEFAULT_PASSWORD.
//It also checks whether USER command was successful or not before this PASS command by checking the value in 'isUser'.
//A 'false' value in 'isUser' means USER command has not been successful before this PASS command.
//If there was no successful USER command, sends an appropriate response to the client and closes all connections by calling 'handleNotLoggedIn()' function.
//If the password does not match, sends appropriate response to the client and closes all connections by calling ''handleNotLoggedIn()' function.
//If the password matches, sets 'true' to 'isLoogedIn' and sends appropriate response to the client.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
{
  string password_str = password;

  if (isUser != true ) 
  {    
    sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, FTP_RESPONSE_MAX_LENGTH);
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);     
  } else 
  {
    if (password_str == DEFAULT_PASSWORD)
    {
      isLoggedIn = true; 
      sendToRemote(controlSockDescriptor, LOGIN_RRESPONSE, FTP_RESPONSE_MAX_LENGTH);
    } else 
    { 
      handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    }

  }
}

void handleCommandPWD(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn) 
//Handles PWD command.
//First, checks whether the client is logged in or not by checking the value in 'isLoggedIn'.
//If the client is not logged in, sends an appropriate response to the client and closes all connections by calling 'handleNotLoggedIn()' function.
//If the client is logged in, determines the current working directory sends it to the client in an appropriate response.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
{
  if (isLoggedIn != true)
  {
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  } else
  {      
	char* dir;
    	char buff[COMMAND_BUFFER_SIZE];
    //GetCurrentDir( buff, COMMAND_BUFFER_SIZE );
	dir = getcwd(buff, sizeof(buff));     
	//string current_dir(buff);
	if(dir != NULL)
	{
    	sendToRemote(controlSockDescriptor, buff, COMMAND_BUFFER_SIZE);	
	}
  }	
}

void handleCommandCWD(char* directory, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
//Handles CWD command.
{

  //First, checks whether the client is logged in or not by checking the value in 'isLoggedIn'.
  //If the client is not logged in, sends an appropriate response to the client and closes all connections by calling 'handleNotLoggedIn()' function.
  if (isLoggedIn != true)
  {
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
    //If the client is logged in, determines whether the requested 'directory' is valid or not.
  } else
  {
    //string desired_dir = directory;
    // DIR *dir;
    char* dir;
	char buff[1024];
    dir = getcwd(buff, sizeof(buff)); 
    
    if (dir != NULL)
    {    
      //If the requested directory is valid, changes the current directory to the requested directory and sends an appropriate response to the client.
      //Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
    
      printf("directory found!");
	
      char * path = new char[100];
      strcpy (path,dir);
      strcat (path,"/");
      strcat (path,directory);
      

      int returned_change = chdir(path);
      if (returned_change == 0)
      {   
		sendToRemote(controlSockDescriptor, CHANGE_DIRECTORY_RESPONSE, FTP_RESPONSE_MAX_LENGTH);
		
      } else 
      {
		perror("chdir() failed");
		sendToRemote(controlSockDescriptor, CWD_FAIL_RESPONSE, FTP_RESPONSE_MAX_LENGTH); 
      }
    } else 
    {  
      sendToRemote(controlSockDescriptor, CWD_FAIL_RESPONSE, FTP_RESPONSE_MAX_LENGTH);
    }                         
  }

}

void handleCommandCDUP(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn, const char* rootDir)
//Handles CDUP command.
//If the move does not go beyond project's root directory, changes the current working directory to the parent directory and sends an appropriate response to the client.
//If the the move goes beyond project's root directory, sends an appropriate response to the client.
//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
{



//First, checks whether the client is logged in or not by checking the value in 'isLoggedIn'.
//If the client is not logged in, sends an appropriate response to the client and closes all connections by calling 'handleNotLoggedIn()' function.

  if (isLoggedIn != true)
  {
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  } else
  {    
    //If the client is logged in, determines whether moving up to the parent directory is not falling beyond the project's root directory.
    char* current_dir;
    char buff[1024];
    current_dir = getcwd(buff, sizeof(buff)); 
    
    if(strcmp(rootDir,current_dir) != 0)
    {
      char back [3] = "..";
      char* back_ptr = back;
      int returned_change = chdir(back_ptr);   
      if (returned_change == 0)
      {   
	sendToRemote(controlSockDescriptor, CHANGE_DIRECTORY_RESPONSE, FTP_RESPONSE_MAX_LENGTH);             
      } else 
      {	
	sendToRemote(controlSockDescriptor, CDUP_FAIL_RESPONSE, COMMAND_BUFFER_SIZE);                
      }    
    } else 
    {
      perror("failed to ge dir name");	
      sendToRemote(controlSockDescriptor, CDUP_FAIL_RESPONSE, COMMAND_BUFFER_SIZE);
    }
  }

}
void handleCommandPASV(char* argument, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
//Handles PASV command.
{

  //First, checks whether the client is logged in or not by checking the value in 'isLoggedIn'.
  //If the client is not logged in, sends an appropriate response to the client and closes all connections by calling 'handleNotLoggedIn()' function.

  if (isLoggedIn != true)
  {
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  } else
  {
    //If the client is logged in, enters into passive mode by calling 'enteringIntoPassive()' function from 'ftp_server_passive.hpp'
    //'enteringIntoPassive()' function starts a passive connection listener, sends an appropriate response to the client.
    //'enteringIntoPassive()' function waits for a specific time interval for the client to send a connection request on the listener.
    //'enteringIntoPassive()' function accepts client's connection request, if there is any, and opens a data connection with the client.
    //'enteringIntoPassive()' function closes the connection listener after opening the data connection with the client.
    //'enteringIntoPassive()' function also sends appropriate response to the client using control connection.
    enteringIntoPassive(argument, controlSockDescriptor, dataListenerSockDescriptor,dataSockDescriptor);
  }


}

void handleCommandNLST(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
//Handles NLST command.
{

//First, checks whether the client is logged in or not by checking the value in 'isLoggedIn'.
//If the client is not logged in, sends an appropriate response to the client and closes all connections by calling 'handleNotLoggedIn()' function.
  if (isLoggedIn != true)
  {
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  } else
  {
	
    //If the client is logged in, it checks whether the data connection has already been established by a PASV command before this NLST command.
    //If a data connection has already been established 'dataSockDescriptor' parameter should have a non-negative value.
    if (dataSockDescriptor > 0)
    {
      //If a data connection has already been established, prepares and sends the list of current directory entries by calling 'listDirEntries()' function
      //from 'ftp_server_nlist.hpp'. 'listDirEntries()' function sends the list of current directory entries using the data connection
      //and returns the count of entries.
      int NL_descriptor = listDirEntries(dataSockDescriptor);
      
      char *buffer = new char[char_size];	
      //Sends the count of entries in an appropriate response message to the client using the control connection.
      sprintf(buffer, NLST_CONNECTION_CLOSE_RESPONSE , NL_descriptor);
      
      //Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
      sendToRemote(controlSockDescriptor, buffer , FTP_RESPONSE_MAX_LENGTH);
      //Closes the data connection.         
      close(dataSockDescriptor);						
    } else
    {
      //If a data connection has not been established, sends an appropriate response to the user.
      sendToRemote(controlSockDescriptor, DATA_OPEN_CONNECTION_ERROR_RESPONSE, COMMAND_BUFFER_SIZE);
    }
  }
}
void handleCommandRETR(char* argument, int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected, bool& isLoggedIn)
//Handles RETR command.
{
  if (isLoggedIn != true)
  {
    //First, checks whether the client is logged in or not by checking the value in 'isLoggedIn'.
    //If the client is not logged in, sends an appropriate response to the client and closes all connections by calling 'handleNotLoggedIn()' function. 
    handleNotLoggedIn(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  } else
  {
    //If the client is logged in, it checks whether the data connection has already been established by a PASV command before this RETR command.
    //If a data connection has already been established 'dataSockDescriptor' parameter should have a non-negative value.
    if (dataSockDescriptor > 0)
    {
      //If a data connection has already been established, reads from the file and sends the content of the file by calling 'sendFile()' function
      //from 'ftp_server_retrieve.hpp'. 'sendFile()' function sends the content of the file using the data connection
      //and returns the count of the bytes sent.
      int send_descriptor = sendFile(argument,dataSockDescriptor);
      if (send_descriptor > 0)
      {
	char *buffer = new char[char_size];	
	//Sends the count of entries in an appropriate response message to the client using the control connection.
	sprintf(buffer, NLST_CONNECTION_CLOSE_RESPONSE , send_descriptor);
	
	//Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
	sendToRemote(controlSockDescriptor, buffer , FTP_RESPONSE_MAX_LENGTH);
	//Closes the data connection.         
	close(dataSockDescriptor);
       }else 
       {
	 sendToRemote(controlSockDescriptor, DATA_LOCAL_ERROR_RESPONSE, FTP_RESPONSE_MAX_LENGTH);    
       }  
      close(dataSockDescriptor);
    } else 
    {
      //If a data connection has not been established, sends an appropriate response to the user.
      sendToRemote(controlSockDescriptor, DATA_OPEN_CONNECTION_ERROR_RESPONSE, FTP_RESPONSE_MAX_LENGTH);  
    }
  }
}
void handleCommandQUIT(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor,bool& isClientConnected)
{
 
//Handles QUIT command by sending appropriate response to the client.
  //Closes all connections by calling 'closeAllConnections()' function from 'ftp_server.connection.hpp'.
  closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);
  //Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
  sendToRemote(controlSockDescriptor, QUIT_RESPONSE, FTP_RESPONSE_MAX_LENGTH);
}
void handleCommandUnSupported(const int controlSockDescriptor)
{
  //Sends an appropriate response saying the requested command is not supported by this FTP server.
  //Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
  sendToRemote(controlSockDescriptor, UNSUPPORTED_COMMAND_RESPONSE, FTP_RESPONSE_MAX_LENGTH);
} 

void handleNotLoggedIn(int& controlSockDescriptor, int& dataListenerSockDescriptor, int& dataSockDescriptor, bool& isClientConnected)

{

	 //Calls 'sendToRemote()' function from 'ftp_server_connection.hpp' to send a response to the client.
    sendToRemote(controlSockDescriptor, NOT_LOGGED_IN_RESPONSE, FTP_RESPONSE_MAX_LENGTH);

  //Sends an appropriate response saying the user is not logged in.
  //Closes all connections by calling 'closeAllConnections()' function from 'ftp_server.connection.hpp'.
  closeAllConnections(controlSockDescriptor, dataListenerSockDescriptor, dataSockDescriptor, isClientConnected);

}
