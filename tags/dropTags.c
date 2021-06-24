#include <stdio.h>
#include <sys/stat.h>//mkdiir,rmdir
#include <unistd.h>//access
#include <string.h>//strcat
#include <stdlib.h>

void dropTags(char *nameTags){
  //le chemin de tous les ficher du projet
  char pwd[1024];
	getcwd(pwd,sizeof(pwd));
	char* token0;
	char* cwd =malloc( sizeof(char*)*1024);
	cwd= memset(cwd,'\0',strlen(cwd));
	token0 =strtok(pwd,"/");
	for(int i=0; i<2;i++){
		strcat(cwd,"/");
		strcat(cwd,token0);
		token0 = strtok(NULL,"/");
	}
  //le chemin pour tags
	strcat(cwd,"/tags");
  char cheminAbsol [1024];
  strcpy(cheminAbsol,cwd);
  strcat(cheminAbsol,"/.tags/");
  strcat(cheminAbsol,nameTags);
  //printf("drop tags  %s\n",cheminAbsol );
  int r = rmdir(cheminAbsol);
  if (r<0){
    printf("Le tag n'a pas pu ếtre supprimé\n");
  }
  else {
    printf("Tag suprimé.\n");
  }
  return;
}

int main(int argc, char* argv[]){
  for (int  i=1 ; i<argc; i++){
    dropTags(argv[i]);
  }
  return 0;
}
