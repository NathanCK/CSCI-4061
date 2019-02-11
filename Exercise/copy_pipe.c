// copyright 2018 <Kin Chan>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 1024

int  main(int argc, char *argv[]){
  if(argc != 3)
  {
    printf("Usage: %s <source> <destination>\n", argv[0]);
    exit(1);
  }

  int openFlags = O_CREAT | O_WRONLY | O_TRUNC; //Write-output
  pid_t childpid;
  int ends[2];
  pipe(ends);

  childpid = fork();
  if(childpid == -1)
  {
    perror("Error with fork!\n");
    exit(-1);
  }
  else if(childpid == 0) //child - write the destination file from the pipe
  {
    // close write end from pipe : close()
    close(ends[1]);

    // open destination file -> argv[2] : open()
    int fd_new = open(argv[2], openFlags);
    if(fd_new == -1)
    {
      printf("The file '%s' is not existed\n", argv[2]);
      exit(0);
    }
    ssize_t numRead_child;
    char buf_child[BUF_SIZE];

    // Read from pipe and write it to destination : read(), write()
    while((numRead_child = read(ends[0], buf_child, BUF_SIZE)) > 0){
      write(fd_new, buf_child, numRead_child);
    }
    // close read end from pipe : close()
    close(ends[0]);

    // close destination file : close()
    close(fd_new);
    exit(0);
  }
  // parent part

  // close read end from pipe : close()
  close(ends[0]);

  // open source file -> argv[1] : open()
  int fd_old = open(argv[1], O_RDONLY);
  if(fd_old == -1)
  {
    printf("The file '%s' is not existed\n", argv[1]);
    exit(0);
  }
  ssize_t numRead_parent;
  char buf_parent[BUF_SIZE];

  // Read from source and write it to destination : read(), write()
  while((numRead_parent = read(fd_old, buf_parent, BUF_SIZE)) > 0){
    write(ends[1], buf_parent, numRead_parent);
  }

  // close write end from pipe : close()
  close(ends[1]);
  int status;
  if(waitpid(childpid, &status, 0) == -1) {
    printf("Could not wait for a child\n");
    exit(-1);
  }

  // close source file : close()
  close(fd_old);
  exit(0);

}
