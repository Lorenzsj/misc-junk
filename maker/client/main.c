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

#define	MAX_LINE 4096
#define SERVER_PORT 8888
#define	SA struct sockaddr

void str_client(FILE *fp, int sockfd)
{
  char send_line[MAX_LINE], recv_line[MAX_LINE];

  while (Fgets(send_line, MAX_LINE, fp) != NULL) {
    Writen(sockfd, send_line, strlen(send_line));

    if (Readline(sockfd, recv_line, MAX_LINE) == 0) {
      err_quit("str_cli: server terminated prematurely");
    }
    Fputs(recv_line, stdout);
  }
}

int main(int argc, char *argv[])
{
  int sockfd;
  struct sockaddr_in server_addr;

  if (argc != 2) {
    err_quit("usage: tcpcli <IP address>");
  }
  sockfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  Inet_pton(AF_INET, argv[1], &server_addr, sizeof(server_addr));

  Connect(sockfd, (SA *) &server_addr, sizeof(server_addr));

  str_client(stdin, sockfd); // do it all

  exit(0);
}
