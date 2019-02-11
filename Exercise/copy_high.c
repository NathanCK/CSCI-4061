// copyright 2018 <Kin Chan>
#include <stdio.h>
#include <stdlib.h>

int  main(int argc, char *argv[])
{
  if (argc != 3)
	{
		printf("Usage: %s <source> <destination>\n", argv[0]);
		exit(1);
	}

  // 1. open source file
  FILE *source = fopen(argv[1], "r");
  if (source != NULL) {

    // 2. open destination file
    FILE *dest = fopen(argv[2], "w+");
    char buf[1024];

    // 3. Read from source and write it to destination
    while(fgets(buf, 1024, source) != NULL) {
      if(fputs(buf, dest) < 0) {
        printf("Error on writing the destination file.\n");
        exit(-1);
      }
    }
    // 4. close destination file
    fclose(dest);
  } else {
    printf("The file you entered is not existed. Please check and come back later\n");
    exit(-1);
  }
  // 5. close source file
  fclose(source);
}
