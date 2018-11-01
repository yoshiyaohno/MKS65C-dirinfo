#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>


int main()
{
    DIR *dir = opendir(".");
    struct dirent *fileinfo;
    while( fileinfo = readdir(dir) ) {
        printf("%s\n", fileinfo->d_name);
    }
    return 0;
}
