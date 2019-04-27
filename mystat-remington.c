#include <stdio.h>
#include <sys/stat.h>

/*
 * Call stat() on a file or directory.
 * output: file size,
 * 	   number of blocks allocated,
 * 	   reference (link) count,
 * 	   file permissions,
 * 	   file inode
 */

void printPermissions(const struct stat currFile) {
 /* The flags for the permission bits are set to 1 or 0
  * and we can use the & (AND) operator to tell us
  * whether or not the file has that specific permission
  * for that specific group. The ternary ? operator
  * allows us to condense it to one line
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

int main(int argc, char** argv) {

    if (argc != 2) {
       fprintf(stderr, "Include a file/directory in the command line.\n");
    }

    struct stat file;
    stat(argv[1], &file);

    printf("File size: %d\n", file.st_size);
    printf("Num of blocks allocated: %d\n", file.st_blocks);
    printf("Link count: %d\n", file.st_nlink);
    printf("File permissions (USER GROUP OTHERS): ");
    printPermissions(file);
    printf("\nFile INODE: %d\n", file.st_ino);

    return 0;
}
