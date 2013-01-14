#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//char *socket_path = "./socket";
char *socket_path = ".socket";

int main(int argc, char *argv[]) 
{
    struct sockaddr_un addr;
    const int bufferSize = 255;
    char buf[bufferSize];

    //create a socket
    int mySocket = socket(AF_UNIX, SOCK_STREAM, 0);

    if ( mySocket == -1) 
    {
        perror("socket error");
        exit(-1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;

    strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

    struct sockaddr* socket_address;
    socket_address = (struct sockaddr*)&addr;
    int connection = connect(mySocket, socket_address, sizeof(addr));

    if ( connection == -1) 
    {
        perror("connect error");
        exit(-1);
    }

    /*
    int num_read = read(mySocket,buf,sizeof(buf));

    if(num_read > 0)
    {
        printf("read %u bytes: %s\n", num_read,  buf);
        if(strcmp(buf, "q") == 0)
        {
            return 0;
        }
    }
    else if (num_read < 0 ) 
    {
        perror("read error");
        exit(-1);
    }
    */

    strcpy(buf, "ivan\0");

    write(mySocket, buf, bufferSize);


    close(mySocket);
    return 0;
}
