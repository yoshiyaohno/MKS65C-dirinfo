#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>

char * perms[8] = {
  "---", "--x", "-w-", "-wx",
  "r--", "r-x", "rw-", "rwx",
};

struct dirent * inserter(struct dirent * list, struct dirent * file, int size){
  struct dirent * temp;
  int i = 0;
  while(i <= size){
    if(i < size){
      if(strcmp(file -> d_name, list[i] -> d_name) < 0){
	temp = list[i];
	list[i] = file;
	file = temp;
      }
    }else{
      list[i] = file;
    }
    i++;
  }
  return list;
}


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

  
  while( file = readdir(dir) ) {
    if(file->d_type == DT_DIR){
      dirs = insert(dirs, file, n_dirs);
      ++n_dirs;
    }
    else if(file->d_type == DT_REG){
      files = insert(files, file, n_files);
      ++n_files;
    }
  }
  
  
  for(i = 0; i < n_files; i++){
    printf("%s\n", files[i] -> d_name);
  }
  
  return 0;
}
