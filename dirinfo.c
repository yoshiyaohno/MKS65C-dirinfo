#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

char * perms[8] = {
  "---", "--x", "-w-", "-wx",
  "r--", "r-x", "rw-", "rwx",
};


int main()
{
  int n_files = 0;
  int n_dirs  = 0;
  struct dirent * file;
  
  DIR *dir = opendir(".");
  while( file = readdir(dir) ) {
    if(file->d_type == DT_DIR)
      ++n_dirs;
    else if(file->d_type == DT_REG)
      ++n_files;
  }
  closedir(dir);
  
  dir = opendir(".");
  
  struct dirent * files[ n_files ];
  struct dirent * dirs[ n_dirs ];

  n_dirs = 0;
  n_files = 0;

  struct dirent * temp;
  int i;
  
  while( file = readdir(dir) ) {
    if(file->d_type == DT_DIR){
      i = 0;
      while(i <= n_dirs){
	if(i < n_dirs){
	  if(strcmp(file -> d_name, dirs[i] -> d_name) < 0){
	    temp = dirs[i];
	    dirs[i] = file;
	    file = temp;
	  }
	  i++;
	}else{
	  dirs[i] = file;
	  i++;
	}
      }
      ++n_dirs;
    }
    else if(file->d_type == DT_REG){
      i = 0;
      while(i <= n_files){
        if(i < n_files){
          if(strcmp(file -> d_name, files[i] -> d_name) < 0){
            temp = files[i];
            files[i] = file;
            file = temp;
          }
          i++;
        }else{
          files[i] = file;
          i++;
        }
      }
      ++n_files;
    }
  }

  struct stat * buff = malloc(sizeof(struct stat));

  char * name;

  printf("THE FILES ARE:\n\n");
  
  for(i = 0; i < n_files; i++){
    name = files[i] -> d_name;
    stat(name, buff);
    printf("%s  Size : %ld\n", name, buff -> st_size);
  }

  printf("\nTHE DIRECTORIES ARE:\n\n");
  
  for(i = 0; i < n_dirs; i++){
    name = dirs[i] -> d_name;
    printf("%s\n", name);
  }
  return 0;
}
