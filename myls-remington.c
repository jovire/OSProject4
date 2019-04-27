#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
 * List the files in a given directory
 * No arguments: print files in current directory
 * -l flag: print info about each file (stat info)
 * -l flag + directory: print info about each file in directory
 */

void printPermissions(const struct stat currFile) {
 /* The flags for the permission bits are set to 1 or 0
  * and we can use the & (AND) operator to tell us
  * whether or not the file has that specific permission
  * for that specific group. The ternary ? operator
  * allows us to condense it to one line.
  */
    printf((currFile.st_mode & S_IRUSR) ? "r":"-");
    printf((currFile.st_mode & S_IWUSR) ? "w":"-");
    printf((currFile.st_mode & S_IXUSR) ? "x":"-");
    printf(" ");
    printf((currFile.st_mode & S_IRGRP) ? "r":"-");
    printf((currFile.st_mode & S_IWGRP) ? "w":"-");
    printf((currFile.st_mode & S_IXGRP) ? "x":"-");
    printf(" ");
    printf((currFile.st_mode & S_IROTH) ? "r":"-");
    printf((currFile.st_mode & S_IWOTH) ? "w":"-");
    printf((currFile.st_mode & S_IXOTH) ? "x":"-");
}

int main(int argc, char** argv){
   
    if (argc < 3) {
      //No directory passed in
      char cwd[256];
      getcwd(cwd, sizeof(cwd));
      assert(cwd != NULL);

      DIR *currDIR = opendir(cwd);
      assert(currDIR != NULL);
      struct dirent *dir;
      if (argc == 1) { //Print files
        while ((dir = readdir(currDIR)) != NULL) {
          printf("%s ", dir->d_name);
        }
        printf("\n");
        closedir(currDIR);

      } else if (!strcmp(argv[1], "-l")) {
         //print stats for each file
         struct stat file;
         while ((dir = readdir(currDIR)) != NULL) {
	   stat(dir->d_name, &file);
           printf("%d %5d %2d ",file.st_ino, file.st_size,
                   file.st_nlink);
           printPermissions(file);
           printf(" %s\n", dir->d_name);
         }
         closedir(currDIR);
      }
    }

    if (argc == 3) {
      //Directory passed in
      DIR *currDIR = opendir(argv[2]);
      assert(currDIR != NULL);
      struct dirent *dir;
      struct stat file;
      while ((dir = readdir(currDIR)) != NULL) {
        stat(dir->d_name, &file);
        printf("%d %5d %2d ",file.st_ino, file.st_size,
                file.st_nlink);
        printPermissions(file);
        printf(" %s\n", dir->d_name);
      }
      closedir(currDIR);
    }
    return 0;
}
