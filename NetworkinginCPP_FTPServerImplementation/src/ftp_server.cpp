/**
*
* Nawaf Alharbi 
* CSCI460
* Project2
*
**/



#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include "ftp_server_connection_listener.hpp"
#include "ftp_server_session.hpp"

using namespace std;

#define FTP_DEFAULT_LISTENER_PORT "21"

void usage(const char* prog);
char* baseName(const char* pathname);

int main (int argc, char** argv) {
    char* port = new char[3];
    strcpy(port, FTP_DEFAULT_LISTENER_PORT);
    if(argc<2) {
        usage(baseName(argv[0]));
    }
    else{
        port = argv[1];
    }
    
    int listenerSockDescriptor = -1;
    bool succeded = false;
    startListenerSocket(port, listenerSockDescriptor, succeded);
    if(succeded && listenerSockDescriptor != -1) {
        while(1) {
            int clientSockDescriptor = -1;
            acceptClientConnection(listenerSockDescriptor, clientSockDescriptor);
            if(clientSockDescriptor != -1) {
                startClientFTPSession(clientSockDescriptor);
            }
        }
    }
    delete [] port;
    return 0;

}

void usage(const char* prog) {
    cout<<setw(6)<<" "<<"Usage:  "<<prog<<" <server_port>"<<endl;
    cout<<setw(6)<<" "<<setfill('*')<<setw(18)<<"*"
    <<" <server_port> is optional. Port 21 is used, when <server_port> is not mentioned."<<endl;
}

char* baseName(const char* pathname) {
    char* path_name = const_cast<char*>(pathname);
    char* base_name = path_name;
    if((base_name=strrchr(path_name, '/')) != NULL) {
        ++base_name;
    }
    return base_name;
}
