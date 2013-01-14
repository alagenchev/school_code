#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>

char *socket_path = "hidden";

int main(int argc, char *argv[]) 
{
  struct sockaddr_un addr;
  const int bufferSize = 255;
  char buf[bufferSize];
  int backlog = 5;

  int listeningSocket = socket(AF_UNIX, SOCK_STREAM, 0);

  if (listeningSocket  < 0) 
  {
    perror("socket error");
    exit(-1);
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);

  unlink(socket_path);

  int isBindSuccessful = bind(listeningSocket, (struct sockaddr*)&addr, sizeof(addr));

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

  while (1) 
  {
      int connectedSocket = accept(listeningSocket, NULL, NULL);
      if ( connectedSocket == -1) 
      {
          perror("accept error");
          continue;
      }


      strcpy(buf, "from server\0");
      write(connectedSocket, buf, sizeof(buf));

      int num_read = read(connectedSocket,buf,sizeof(buf));

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
      else if (num_read == 0) 
      {
          printf("EOF\n");
          close(connectedSocket);
      }
      close(connectedSocket);
  }


  return 0;
}

