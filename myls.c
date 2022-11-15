#include <stdio.h> /* Header file for system call printf */
#include <unistd.h> /* Header file for system call gtcwd */
#include <sys/types.h> /* Header file for system calls opendir, readdir y closedir */
#include <dirent.h>
#include <string.h>



int main(int argc, char *argv[]){
	DIR *dir; //pointer of type DIR
	struct dirent *dent;

	if(argc<2){ //show current directory as no argument was passed as a parameter
	  char cwd[PATH_MAX];
		if (getcwd(cwd, sizeof(cwd)) != NULL){;  //getcwd is a function that returns a pointer to the currect directory
			dir= opendir(cwd); //opens current directory 
		}else{
			perror("\nError of getcwd()");
			return -1;
		}
	}else{ //open the directory passed as a parameter
		dir= opendir(argv[1]);
	}



	//if directory is not empty, access and show the elements 
	if(dir != NULL) {
		while((dent=readdir(dir)) != NULL){ //read until the directory is empty, it returns a pointer to the next directory entry
				printf("%s\n", dent->d_name); //access the name of the element 
		}
	}else{
		perror("\nInexistent directory");
		return -1;
	}
	
	closedir(dir); //close directory 
	return 0;
}

