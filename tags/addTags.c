#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include "addTags.h"



int main(int argc, char *argv[]){
  if(3 != argc){
      printf("Arguments invalides :\n Doit être de la forme \"addTags filename tagname\"\n");
      return 0 ;
  }
  addTags(argv[1],argv[2]);
  return 0;
}
