CC = g++
WFLAG = -Wall  		#Warning Flag
DFLAG = -ggdb		#Debugging Flag
CFLAG = -c			#Compiling Flag
SOURCES = src
INCLUDES = include
BUILDS = build
BINARY = bin

all:ftp_server

ftp_server: ftp_server.o ftp_server_connection_listener.o ftp_server_net_util.o ftp_server_string_util.o \
ftp_server_connection.o ftp_server_session.o ftp_server_command.o ftp_server_passive.o ftp_server_nlist.o \
ftp_server_retrieve.o
	${CC} ${WFLAG} ${DFLAG} -o ${BINARY}/myftpserver ${BUILDS}/ftp_server.o ${BUILDS}/ftp_server_connection_listener.o \
	${BUILDS}/ftp_server_net_util.o	${BUILDS}/ftp_server_string_util.o ${BUILDS}/ftp_server_connection.o \
	${BUILDS}/ftp_server_session.o ${BUILDS}/ftp_server_command.o ${BUILDS}/ftp_server_passive.o \
	${BUILDS}/ftp_server_nlist.o ${BUILDS}/ftp_server_retrieve.o

ftp_server.o: ${SOURCES}/ftp_server.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server.o ${SOURCES}/ftp_server.cpp

ftp_server_connection_listener.o: ${SOURCES}/ftp_server_connection_listener.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_connection_listener.o ${SOURCES}/ftp_server_connection_listener.cpp

ftp_server_connection.o: ${SOURCES}/ftp_server_connection.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_connection.o ${SOURCES}/ftp_server_connection.cpp

ftp_server_session.o: ${SOURCES}/ftp_server_session.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_session.o ${SOURCES}/ftp_server_session.cpp

ftp_server_net_util.o: ${SOURCES}/ftp_server_net_util.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_net_util.o ${SOURCES}/ftp_server_net_util.cpp

ftp_server_string_util.o: ${SOURCES}/ftp_server_string_util.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_string_util.o ${SOURCES}/ftp_server_string_util.cpp

ftp_server_command.o: ${SOURCES}/ftp_server_command.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_command.o ${SOURCES}/ftp_server_command.cpp

ftp_server_passive.o: ${SOURCES}/ftp_server_passive.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_passive.o ${SOURCES}/ftp_server_passive.cpp

ftp_server_nlist.o: ${SOURCES}/ftp_server_nlist.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_nlist.o ${SOURCES}/ftp_server_nlist.cpp

ftp_server_retrieve.o: ${SOURCES}/ftp_server_retrieve.cpp
	${CC} ${WFLAG} ${DFLAG} ${CFLAG} -I${INCLUDES} -o ${BUILDS}/ftp_server_retrieve.o ${SOURCES}/ftp_server_retrieve.cpp

.PHONY: clean

clean:
	rm -rf ${BINARY}/*
	rm -rf ${BUILDS}/*