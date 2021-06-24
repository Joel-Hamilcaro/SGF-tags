# ifndef RMTAGS_H
# define RMTAGS_H
#include <stdlib.h>
#include "rmTags.h"
#include "lsFile.h"

void rmTags(char* file, char* name);
void rmTags(char* file, char* name){
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
	strcat(cwd,"/tags");

  char * filename;
  int x =strlen(file);
  filename = malloc(sizeof(char*)*x);
  strcpy(filename,file);
  char * nameTags;
  int y = strlen(name);
  nameTags = malloc(sizeof(char*)*y);
  strcpy(nameTags,name);


  //printf("rmTags - filname %s\n",filename );
  //printf("rmTag - nameTags %s\n",nameTags );
  //char cheminAbsol [1024];
  //strcpy(cheminAbsol,cwd);
  //strcat(cheminAbsol,"/.tags/");
  //strcat(cheminAbsol,nameTags);

  char** ficherList = (char**) malloc(sizeof(char**)*100);
  ficherList = lsFile(nameTags);
  if (ficherList==NULL){
    perror("list NULL");
    return;
  }

  int len=0;
  char *tem=ficherList[0];

  while(tem){
      //printf("rm - ls tags %s\n", ficherList[len]);
      len++;
      tem=ficherList[len];
  }
  //printf("rm tags %d\n",len );

  char cheminAbsol2 [1024];
  memset(cheminAbsol2,'\0',sizeof(cheminAbsol2));
  if (file[0]!='/'){
    getcwd(cheminAbsol2,sizeof(cheminAbsol2));
    strcat(cheminAbsol2,"/");
  }
  strcat(cheminAbsol2,file);

  for (int i=0 ; i<len;i++){
    if (ficherList[i]==NULL){
      break;
    }



    char cheminAbsol4 [1024];
    strcpy(cheminAbsol4,cwd);
    strcat(cheminAbsol4,"/.tags/");
    strcat(cheminAbsol4,nameTags);
    strcat(cheminAbsol4,"/");
    strcat(cheminAbsol4,ficherList[i]);
    //printf("rm cheminAbsol4 %s\n", cheminAbsol4);

    ssize_t  size;
    char     buf[1024];
    if ((size = readlink(cheminAbsol4, buf, 1024)) < 0) {
        perror("readlink");
        return ;
    } else {
        buf[size] = '\0';
    }

    //printf("rm buf %s\n",buf );
    //printf("cheminAbsol2 %s\n",cheminAbsol2 );
    if (strcmp(buf,cheminAbsol2)==0){
      int rm = remove(cheminAbsol4);
      if (rm<0){
        perror("remove");
        return ;
      }
      break;
    }

}

  //tags fic
  char* token2;
  char* tags;
  token2 =strtok(nameTags,"/");
  tags =token2;
  while(token2 !=NULL){
    tags =token2;
    token2 = strtok(NULL,"/");
  }

  //chemin 3
  char cheminAbsol3 [1024];
  memset(cheminAbsol3,'\0',sizeof(cheminAbsol3));
  strcpy(cheminAbsol3,cwd);
  strcat(cheminAbsol3,"/.file");
  strcat(cheminAbsol3,cheminAbsol2);
  strcat(cheminAbsol3,"/");
  strcat(cheminAbsol3,tags);
  //printf("mv-cheminAbsol3 %s\n", cheminAbsol3 );
  //printf("chemin 3 %s\n", cheminAbsol3);
  int n =remove(cheminAbsol3);
  if (n<0){
    //perror("remove");
    printf("Le tag n'a pas été trouvé pour ce fichier.\n");
    return ;
  }
  return;
}
#endif
