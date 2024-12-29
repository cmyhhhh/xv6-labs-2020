#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pong_fd[2], ping_fd[2];
  char buf[4];
  if(pipe(pong_fd) < 0 || pipe(ping_fd) < 0)
  {
    fprintf(2, "pipe error\n");
    exit(1);
  }
  if(fork() == 0)
  {
    read(pong_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
    write(ping_fd[1], "ping", 4);
  }
  else {
    write(pong_fd[1], "pong", 4);
    // wait(0);
    read(ping_fd[0], buf, 4);
    printf("%d: received %s\n", getpid(), buf);
  }
  exit(0);
}
