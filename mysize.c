#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>


int main (int argc, char *argv[]){
	DIR *dir; //initialize the dir type variable for the directory later
	struct dirent *dent;
	char cwd[PATH_MAX];

	if (getcwd(cwd, sizeof (cwd)) != NULL){        // we get the current directory
		dir= opendir(cwd);     //in case there is no error, we open it on the DIR type variable we had previously initialized
	}
	else{
		perror ("Could not get current directory");
		return -1; //if the directory is not reachable, we exit
	}
	dent =readdir(dir);  //we read the entries of the directory

	while (dent != NULL){  //while there are still entries to be read
		if (dent->d_type == DT_REG){  // if the entry is a regular file
			int fd= open(dent->d_name, O_RDONLY); //open a file for reading only and save the file's descriptor//
			int size=lseek(fd, 0, SEEK_END); //lseek function with a starting offset of 0 (begining of file) and we tell it to look for the end of the file and save the number of bytes it has read to get to the end

			printf("%s    %d\n", dent->d_name, size); //print the d_name element of the dent structure followed by 4 blank spaces and the size of the file we has previously gotten with lseek
			close(fd); //close the file that has already been read
		}
		/* If we wanted the program to print the files that are not regular ones, we would use the code commented below
		else { 
			printf("[%s] is not a regular file\n", dent->d_name);	
		}*/ 
		dent = readdir(dir);  //read the next file
	}

	closedir(dir); //close the directory

	return 0;
}

