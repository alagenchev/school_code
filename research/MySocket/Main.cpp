#include <iostream>
#include "MySocket.h"

int main(int argc, char ** argv)
{
    if(argc < 1)
    {
        cout<<"Usage: ./mySocket 1 for server ./mySocket 0 for client"<<endl;
        return -1;
    }

    int isServer = atoi(argv[1]);
    if(isServer)
    {
        MySocket socket(".socket", 255, 5, true);
        socket.Write();
    }
    else
    {
        MySocket socket(".socket",255, 5, false);
        socket.Read();
    }
    return 0;
}
