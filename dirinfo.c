#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>


int main()
{
    DIR *dir = opendir(".");
    struct dirent *file;
    while( file = readdir(dir) ) {
        if(file->d_type == DT_DIR)
            printf("[DIR]\t");
        else if(file->d_type == DT_REG)
            printf("[FILE]\t");
        printf("%s\n", file->d_name);
    }
    return 0;
}
