#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

char * perm[8] = {
  "---", "--x", "-w-", "-wx",
  "r--", "r-x", "rw-", "rwx",
};


int printDirec(char * path, char * tab, struct stat * reuse){
  struct dirent * file;
  DIR * dir = opendir(path);
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
  
  char f_name[256];
  char permish[9];
  int mode;
  int s;
  
  for(i = 0; i < n_files; i++){
    strcpy(f_name, path);
    strcat(f_name, "/"); 
    strcat(f_name, files[i] -> d_name);
    stat(f_name, reuse);
    mode = reuse -> st_mode % 512;
    strcpy(permish, perm[mode / 64]);
    strcat(permish, perm[(mode / 8) % 8]);
    strcat(permish, perm[mode % 8]);
    printf("%s%s %s %ld\n",tab, permish, files[i] -> d_name, reuse -> st_size);
    sum += reuse -> st_size;
  }
  
  for(i = 0; i < n_dirs; i++){
    strcpy(f_name, dirs[i] -> d_name);
    if(strcmp(f_name, ".") && strcmp(f_name, "..") && strcmp(f_name, ".git")){
      strcpy(temp2, path);
      strcat(temp2, "/");
      strcat(temp2, f_name);
      strcpy(temp1, tab);
      strcat(temp1, "    ");

      printf("%s-%s\n", tab, f_name);

      s = printDirec(temp2, temp1, reuse);
      sum += s;
      
      printf("%s (%d)\n", tab, s);

    }
  }
  return sum;
}


int main()
{
  struct stat * buff = malloc(sizeof(struct stat));
  char tab[256];
  strcpy(tab, "");
  char path[256];
  strcpy(path, ".");
   
  printf("\n\nTOTAL SIZE IS: %d\n\n", printDirec(path, tab, buff));
  
  return 0;
}
