#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

/* Recursive Search
 * Prints out name of each file and directory
 * in the directory tree.
 *
 * If no argument passed, use CWD else use directory given
 */

void printContents(const char *cwd);

void RecursiveSearch(const char *cwd) {
    /* Print contents at current directory
     * if any subdirectories found, go into them
     */

   DIR *currDIR;
   struct dirent *dir;
   
   //Base Case
   if ((currDIR = opendir(cwd)) == NULL) {
     return;
   }
   
   //Use custom function to print contents of the directory
   printContents(cwd);
   while((dir = readdir(currDIR)) != NULL) {
     
     //Check if file is a directory
     if (dir->d_type == DT_DIR) {
       char filePath[512];
       if ((strcmp(dir->d_name, ".") == 0) || (strcmp(dir->d_name, "..") == 0)) {
         continue; //Don't need to use these
       }
       //create path to enter to. Easiest example was to use snprintf
       //Call recursion after
       snprintf(filePath, sizeof(filePath), "%s/%s", cwd, dir->d_name);
       printf("\nDirectory: %s\n", filePath);
       RecursiveSearch(filePath);
     } 
   }

   closedir(currDIR);
}

void printContents(const char *cwd) {

   DIR *thisDIR;
   struct dirent *dir;

   thisDIR = opendir(cwd);
   assert(thisDIR != NULL);
   while ((dir = readdir(thisDIR)) != NULL) {
     printf("%s ", dir->d_name);
   }
   printf("\n");
   closedir(thisDIR);
}

int main(int argc, char** argv) {
 
   char *cwd;

   if (argc < 2) {

   //No args passed
   char cwd[256];
   getcwd(cwd,sizeof(cwd));
   assert(cwd != NULL);

   printf("\nCurrent Directory:\n");
   RecursiveSearch(cwd);
   } else {
    //User passed in a directory
    cwd = strdup(argv[1]);
    printf("\nDirectory: %s\n", cwd);
    RecursiveSearch(cwd);
   }

   return 0;
}
