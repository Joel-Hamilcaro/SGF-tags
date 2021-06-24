#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include<sys/types.h>
#include<dirent.h>
#include "lsFile.h"




int main(int argc, char *argv[]){
    //printf("argc %d\n", argc );
    if( argc% 2 == 1 ){
        printf("reference error!\n");
        return 0 ;
    }

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

    char** ficherList = (char**) malloc(sizeof(char**)*100);
    ficherList = lsFile(argv[1]);
    int len =lenList(ficherList);
    printf("%s\n","--------" );

    for (int i =0;i<len;i++ ){
      int j=2;
      while(j<argc){
      if (strcmp(argv[j],"^")==0){
        char cheminAbsol [1024];
        memset(cheminAbsol,'\0',sizeof(cheminAbsol));
        strcpy(cheminAbsol,cwd);
        strcat(cheminAbsol,"/.tags/");
        strcat(cheminAbsol,argv[j+1]);
        strcat(cheminAbsol,"/");
        strcat(cheminAbsol,ficherList[i]);
        if (access(cheminAbsol,F_OK)!=0){
          j++;
          break;
        }
      }else if(strcmp(argv[j],"!")==0){
        char cheminAbsol [1024];
        memset(cheminAbsol,'\0',sizeof(cheminAbsol));
        strcpy(cheminAbsol,cwd);
        strcat(cheminAbsol,"/.tags/");
        strcat(cheminAbsol,argv[j+1]);
        strcat(cheminAbsol,"/");
        strcat(cheminAbsol,ficherList[i]);
        if (access(cheminAbsol,F_OK)==0){
          j++;
          break;
        }
        printf("le resultat :%s\n",ficherList[i] );
      }
      j++;
    }
    }
}
