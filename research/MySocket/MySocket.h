#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string>

using namespace std;

class MySocket
{
    private:
        struct sockaddr_un addr;
        static const int bufferSize;
        char *buf;
        int backlog;
        int listeningSocket;
        bool isServer;

    public:

        MySocket(string socket_path, int buffer_size, int back_log, bool is_Server);
        
        void Write();
       

        void Read();

        ~MySocket();
     
};
