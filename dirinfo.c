#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

void insert( struct dirent **list, int size, struct dirent *new )
{
    int i = 0;
    struct dirent *temp;
    while (i <= size) {
        if (!list[i] || i == size) {
            list[i] = new;
        }
        else {
            if( strcmp( new->d_name, list[i]->d_name ) < 0 ) {
                temp = list[i];
                list[i] = new;
                new = temp;
            }
        }
        ++i;
    }
}

char *perm[8] = {
  "---", "--x", "-w-", "-wx",
  "r--", "r-x", "rw-", "rwx",
};


int printDirec(char *path, char *tab, struct stat *reuse){
    struct dirent *file;

    DIR *dir = opendir(path);

    while(dir == 0){
        printf("\n%s\nPlease enter a valid path:\n>>", strerror(errno));
	if(errno == 24){
	  printf("\n\n---You called this on a directory with too many sub directories to recursively open, please run the program again\n\n\n");
	  exit(1);
	}
	fgets(path, 256, stdin);
	path[strlen(path) - 1] = 0;
	dir = opendir(path);
    }

    
    int sum = 0;
    char temp1[256];
    char temp2[256];
  
    int n_files = 0;
    int n_dirs  = 0;
    
    while( file = readdir(dir) ) {
        if(file->d_type == DT_DIR)
            ++n_dirs;
        else if(file->d_type == DT_REG)
            ++n_files;
    }
    closedir(dir);
  
    dir = opendir(path);
    
    struct dirent *files[ n_files ];
    struct dirent *dirs[ n_dirs ];
    //struct dirent **files = malloc( sizeof(void*) * n_files );
    //struct dirent **dirs = malloc( sizeof(void*) * n_dirs );
    
    n_dirs = 0;
    n_files = 0;
    
    struct dirent *temp;
    int i;
    
    while( file = readdir(dir) ) {
        if(file->d_type == DT_DIR){
            insert( dirs, n_dirs, file );
            ++n_dirs;
        }
        else if(file->d_type == DT_REG){
            insert( files, n_files, file );
            ++n_files;
        }
    }

    //closedir(dir);
    
    char f_name[256];
    char permish[9];
    int mode;
    int s;
    
    printf("%s##DIRECTORIES##\n", tab);
    for(i = 0; i < n_dirs; i++){
      strcpy(f_name, dirs[i] -> d_name);
      if(strcmp(f_name, ".") && strcmp(f_name, "..")) {
        strcpy(temp2, path);
        strcat(temp2, "/");
        strcat(temp2, f_name);
        strcpy(temp1, tab);
        strcat(temp1, "    ");
  
        printf("%s[%s]\n", tab, f_name);
        //printf("%s-%s\n", tab, f_name);
  
        s = printDirec(temp2, temp1, reuse);
        sum += s;
        printf("%s    Total size %d\n", tab, s);
  
      }
    }

    printf("\n%s##FILES########\n", tab);
    for(i = 0; i < n_files; i++){
        strcpy(f_name, path);
        strcat(f_name, "/"); 
        strcat(f_name, files[i] -> d_name);
        stat(f_name, reuse);
        mode = reuse -> st_mode % 512;
        strcpy(permish, perm[mode / 64]);
        strcat(permish, perm[(mode / 8) % 8]);
        strcat(permish, perm[mode % 8]);
        printf("%s%s\t%ld\t%s\n",tab, permish, reuse->st_size, files[i]->d_name);
        sum += reuse -> st_size;
    }
    closedir(dir);
    return sum;
}


int main( int argc, char *argv[] )
{
    struct stat * buff = malloc(sizeof(struct stat));
    char tab[256];
    strcpy(tab, "");
    char path[256];

    strcpy(path, ".");
    
    if( argc == 2 ) {
        //printf("OOF\n");
        strcpy(path, argv[1]);
    }
    else{
        printf("Please enter a valid path to a directory:\n>>");
	fgets(path, 256, stdin);
	path[strlen(path) - 1] = 0;
        //printf("path: '%s'\n", path);
    }

    printf("\n\nTOTAL SIZE IS: %d\n\n", printDirec(path, tab, buff));
    
    return 0;
}
