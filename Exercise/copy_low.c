// copyright 2018 <Kin Chan>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUF_SIZE 1024

int  main(int argc, char *argv[])
{
	// int inputFd = 0;
	// int outputFd = 0;
	int openFlags = 0;

	mode_t filePerms;
	ssize_t numRead;
	ssize_t numWrite;
	char buf[BUF_SIZE];

	openFlags = O_CREAT | O_WRONLY | O_TRUNC; //Write-output
	filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;      /* rw-rw-rw- */

	if (argc != 3)
	{
		printf("Usage: %s <source> <destination>\n", argv[0]);
		exit(1);
	}
	int fd_old, fd_new;
	// 1. open source file -> argv[1] : open()
  fd_old = open(argv[1], O_RDWR);
  if(fd_old != -1){
    // 2. open destination file -> argv[2] : open()
    fd_new = open(argv[2], openFlags, filePerms);
    if(fd_new != -1){
      numRead = read(fd_old, buf, BUF_SIZE);
      if(numRead == -1){
        printf("Problem with reading the file.\n");
        exit(0);
      }
			// 3. Read from source and write it to destination : read(), write()
    	/*while (Soruce is available)
    	{
    	}*/
      while(numRead!= 0){
        numWrite = write(fd_new, buf, numRead);
				if(numWrite!= -1)
        	numRead = read(fd_old, buf, BUF_SIZE);
      }
    }
    else{
      printf("The file '%s' is not existed\n", argv[2]);
      exit(0);
    }
  }
  else{
    printf("The file '%s' is not existed\n", argv[1]);
    exit(0);
  }
	// 4. close source file : close()
  close(fd_old);
	// 5. close destination file : close()
  close(fd_new);
}
