#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/* Print out the last few lines of a file.
 * Usage example:
 * mytail -n file
 * n = number of lines at end of file to print
 */


int main(int argc, char** argv) {

    if (argc != 3) {
      fprintf(stderr, "Usage: %s <-n> <file>\n",argv[0]);
      exit(-1);
    }

    int flag = 0;
    int bytes = 0;
    int lastBytes = 0;
    int numOfLines = -1 * atoi(argv[1]);

 
    //Open the file in READONLY 
    int fd = open(argv[2], O_RDONLY);
    assert(fd != -1);
 
    char c[1]; //Read in a single character

    int endOfFile = lseek(fd, 0, SEEK_END);
    
    lseek(fd, -1, SEEK_CUR);
    while (numOfLines != 0) {
      if(lseek(fd, -1, SEEK_CUR) != -1) {
        
        if (read(fd, c, 1) == 1) {
          lseek(fd, -1, SEEK_CUR);
        }
 
        bytes++;

        if (*c == '\n') {
           numOfLines--;
        }

      } else {
        //User entered more lines than exist in the file
        flag = 1;
        break;
     }
    }
   
    //Read and print last -n lines of the file

    if (flag == 0) {
      char buffer[bytes+1];
      buffer[bytes+1] = '\0';

      //lastBytes = the last number bytes to read from file
      lastBytes = endOfFile - bytes;

      lseek(fd, lastBytes, SEEK_SET);
      read(fd, buffer, bytes-1);
    
      printf("%s\n", buffer);
    } else {
      //User input more lines than exist in entire file. Print entire file.
      char buffer[2048];
      lseek(fd, 0, SEEK_SET);
      read(fd, buffer, 2047);
      printf("%s\n", buffer);
    }
    close(fd);
    return 0;
}
