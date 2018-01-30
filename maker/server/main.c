#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>	/* basic system data types */
#include <sys/socket.h>	/* basic socket definitions */
#include <sys/time.h>	/* timeval{} for select() */
#include <time.h>		/* timespec{} for pselect() */
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h>	/* inet(3) functions */
#include <errno.h>
#include <fcntl.h>		/* for nonblocking */
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>	/* for S_xxx file mode constants */
#include <sys/uio.h>		/* for iovec{} and readv/writev */
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>		/* for Unix domain sockets */

#define	LISTENQ	1024
#define	MAX_LINE 4096
#define SERVER_PORT 8888
#define	SA	struct sockaddr

void str_echo(int sockfd)
{
  ssize_t n;
  char line[MAX_LINE];

  for (;;) {
    if ((n = Readline(sockfd, line, MAX_LINE)) == 0) {
      return; // connection closed by other end
    }
    Writen(sockfd, line, n);
  }
}

int main(int argc, char *argv[])
{
  int listenfd, connfd;
  pid_t child_pid;
  socklen_t client_len;
  struct sockaddr_in client_addr, server_addr;

  listenfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  server_addr.sin_port = htons(SERVER_PORT);

  Bind(listenfd, (SA *) &server_addr, sizeof(server_addr));

  Listen(listenfd, LISTENQ);

  for (;;) {
    client_len = sizeof(client_addr);
    connfd = Accept(listenfd, (SA *) &client_addr, &client_len);

    if ((child_pid = Fork()) == 0) { // child process
      Close(listenfd); // close the listening socket
      str_echo(connfd); // process the request
      exit(0);
    }
    Close(connfd); // parent closes connected socket
  }
}
