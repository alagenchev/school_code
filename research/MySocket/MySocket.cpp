#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string>
#include "MySocket.h"
#include <unistd.h>
#include <iostream>

using namespace std;

const int MySocket::bufferSize = 255;

MySocket::MySocket(string socket_path, int buffer_size, int back_log, bool is_Server)
{
    buf = new char[bufferSize];
    backlog = back_log;
    isServer = is_Server;

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;

    strncpy(addr.sun_path, socket_path.c_str(), sizeof(addr.sun_path)-1);
    listeningSocket = socket(AF_UNIX, SOCK_STREAM, 0);

    struct sockaddr* socket_address;
    socket_address = (struct sockaddr*)&addr;


    if (listeningSocket  < 0) 
    {
        perror("socket error");
        exit(-1);
    }

    if(isServer)
    {
        unlink(socket_path.c_str());

        int isBindSuccessful = bind(listeningSocket, socket_address, sizeof(addr));

        if (isBindSuccessful < 0) 
        {
            perror("bind error");
            exit(-1);
        }

        int startListening = listen(listeningSocket, backlog);

        if (startListening == -1) 
        {
            perror("listen error");
            exit(-1);
        }

    }
    else
    {
        int connection = connect(listeningSocket, socket_address, sizeof(addr));
    }

}

void MySocket::Write()
{    
    int socketToUse = -1;

    if(isServer)
    {

        int connectedSocket = accept(listeningSocket, NULL, NULL);
        if ( connectedSocket == -1) 
        {
            perror("accept error");
            return;
        }
        socketToUse = connectedSocket;
        strcpy(buf, "from server\0");
    }
    else
    {
        strcpy(buf, "from client\0");
        socketToUse = listeningSocket;
    }

    write(socketToUse, buf, bufferSize);
    close(socketToUse);
}

void MySocket::Read()
{
    int socketToUse = -1;

    if(isServer)
    {
        socketToUse = accept(listeningSocket, NULL, NULL);
        cout<<"connected to socket: " <<socketToUse<<endl;
        if (socketToUse < 0) 
        {
            perror("accept error");
            return;
        }

    }
    else
    {
        socketToUse = listeningSocket;
    }

    int num_read = read(socketToUse,buf,bufferSize);

    if(num_read > 0)
    {
        printf("read %u bytes: %s\n", num_read,  buf);
    }
    else if (num_read < 0 ) 
    {
        perror("read error");
        exit(-1);
    }

    close(socketToUse);

}


MySocket::~MySocket()
{
    delete [] buf;
}
