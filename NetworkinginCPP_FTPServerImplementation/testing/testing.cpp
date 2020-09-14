#include <iostream>
#include <stdio.h> 
#include <string.h> 

#define COMMAND_BUFFER_SIZE 512
#define COMMAND_CODE_CHARACTER_COUNT 5
#define COMMAND_ARG_MAX_CHARACTER_COUNT 256

using namespace std;

int main()
{
     const char* commandLine = "user csci460"; 
     char* tmp [COMMAND_BUFFER_SIZE]; 
     char* command = new char [COMMAND_BUFFER_SIZE]; 
     char* argument = new char [COMMAND_ARG_MAX_CHARACTER_COUNT];
     char* rest = commandLine; 
     command =  strtok_r(rest, " ",&rest );
     
 
 /* 
    token = strtok_r(rest, " ", &rest); 
    printf("%s\n", token); 
	command = token; 
	
	token = strtok_r(NULL, rest);
	
	token = strtok_r(rest, " ", &rest);
	printf("%s\n", token); 
	argument = token; 
	
	
	
	token = strtok_r(NULL, rest);
  */ 
  
//  command = token; 
  argument = rest; 

  printf("COMMAND IS: %s \n ARGUMENT IS: %s", command, argument);  
  

} 
