#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>

char perms[] = {
    "---", "--x", "-w-", "-wx",
    "r--", "r-x", "rw-", "rwx",
};

int main()
{
    int n_files = 0;
    int n_dirs  = 0;
    DIR *dir = opendir(".");
    while( file = readdir(dir) ) {
        if(file->d_type == DT_DIR)
            ++n_dirs;
        else if(file->d_type == DT_REG)
            ++n_files;
    }
    closedir(dir);

    dir = opendir(".");
    struct dirent *files[ n_files ];
    struct dirent *dirs[ n_dirs ];

    return 0;
}
