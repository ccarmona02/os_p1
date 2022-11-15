#include <stdio.h>		/* Header file for printf */
#include <sys/types.h>		/* Header file for system call  open */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>		/* Header file for system calls read, write y close */

#define BUFFER_SIZE 1024

int fileExists(char * fileName){  /* Function that checks the existence of the file */
  struct stat buf;
  return stat(fileName, &buf);  /* Returns 0 if it exists */
}

int readFile(char * fileName){  /*Function for reading the file specified */
  int fd, nread;    /* Declaration of variables */
  char buffer[BUFFER_SIZE];

  if (fileExists(fileName) < 0){    /* Call of the function fileExists */
    return -1;
  }

  fd = open(fileName, O_RDONLY);    /* File is opened */
  if (fd < 0){
    return -2;
  }
  while((nread = read(fd, buffer, BUFFER_SIZE)) > 0){    /* File content is read and stored */
    if (write(STDOUT_FILENO, buffer, nread)< nread){    /* Stored content is written */
      close(fd);
      return -3;
    }
  }
  close(fd);
  return 0;    /* Returns to main if everything worked */
}

int main(int argc, char **argv){
  if (argc < 2){    /* Checks if an argument was provided */    
    printf("\nERROR: No argument was passed\n");
    return -1;
  }else{
    int result;
    result = readFile(argv[1]);    /* Call of the function */
    if (result == 0){    /* Message if it worked */
    	// Code below would be used if we wanted the program to confirm it was succesful, but in order to make the output exactly the same, we will leave it as a comment
    	// printf("\n\nFile %s has been succesfully read\n", argv[1]);
    }else if (result == -1){    /* Messages if function failed */
      printf("\nERROR: File does not exist\n");
      return -1;
    }else if (result == -2){
      printf("\nERROR: File could not be opened\n");
      return -1;
    }else{
      printf("\nERROR: Could not show file's content\n");
      return -1;
    }
    return 0;    /* Returns 0 if an error did not ocurr */
  }
}
