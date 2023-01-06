#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <fcntl.h>

#include <unistd.h>

#include <ctype.h>

int main(int argc, char * argv[]) {
    const int SIZE = 1024;
    int reverse = 0, shift = 0, args = argc,
      num = 0, Flag = 0, numRead = 0, j = 0, fd;
    char buf[SIZE];
    char c;
    char * n;
    //CHECK FOR NO ARGS
    if (argc == 1) {
      printf("Usage: %s -EnT file.txt\n", argv[0]);
      exit(0);
    }
    //PARSE ARGS FOR SWITCHES
    while (args--) {
      if (argv[args][0] == '-') {
        int switchLen = (int) strlen(argv[args]);
        while (switchLen--) {
          if (argv[args][switchLen] == 'r') reverse = 1;
          if (argv[args][switchLen] == 's') shift = 1;
        }
      }
    }
    n = argv[argc - 2];
    num = atoi(n);

    if (reverse == 1 && shift == 0 && num == 0) {
      printf("Enter number of shifts!");
      exit(0);
    } else if (reverse == 1 && shift == 1) {
      printf("Undoing CCiper by shifting back %d", num);
	Flag = 1;
    } else if (shift == 1 && reverse == 0) {
      printf("Encryting using CCipher by shifting forward %d", num);
    	Flag = 2;
    }
   printf("\n");

    //OPEN FILE
    fd = open(argv[argc - 1], O_RDONLY);
    if (fd == -1) {
      perror(
        argv[argc - 1]);
      exit(1);
    }
    //READ FILE
    while ((numRead = read(fd, buf, SIZE)) > 0) {
      //PARSE BUFFER
      for (j = 0; j < numRead; j++) {
        c = buf[j];
	if(Flag==2){
	if(isupper(c)){printf("%c",(c+num-65)%26+65);}
	else if(islower(c)){printf("%c", (c+num-97)%26+97);}
	else {printf("%c",c);}

	}else if (Flag==1){
	if(isupper(c)){printf("%c",(c-num+65)%26+65);}
	else if(islower(c)){printf("%c", (c-num+97)%26+97);}
	else {printf("%c",c);}
}
 }
     //CLOSE FILE
	printf("\n");
      close(fd);
      return 0;
    }
}
