#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include "addTags.h"
#include "rmTags.h"
#include "lsTags.h"

void mv (char* file,char * newFile){
  //cwd :le chemin  du tous les ficher de projet
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
  //copier le ficher
  rename(file,newFile);
  //si c'est le meme nom , on fait rien
  if (strcmp(file,newFile)==0){
    perror("mv - no copied");
    return;
  }

  //on prend le vrai chemin du ficher
  char cheminAbsol2 [1024];
  memset(cheminAbsol2,'\0',sizeof(cheminAbsol2));
  if (file[0]!='/'){
    getcwd(cheminAbsol2,sizeof(cheminAbsol2));
    strcat(cheminAbsol2,"/");
  }
  strcat(cheminAbsol2,file);

  //on va prendre tous les tags de ce ficher
  char** ficherList = (char**) malloc(sizeof(char**)*100);
  //printf("mv 00- filename %s\n", file );
  //printf("mv-lstags cheminAbsol2 %s\n", cheminAbsol2 );
  ficherList = lsTags(cheminAbsol2);
  //printf("mv 00- filename %s\n", file );
  if (ficherList==NULL){
    return;
  }
    //on veut le nombre de tags
  int len=0;
  char *tem=ficherList[0];
  while(tem){
      //printf("mv - ls tags %s\n", ficherList[len]);
      len++;
      tem=ficherList[len];
  }
  //pour chaque tags, on addtags pour le new file
  char * ele ;
  ele =malloc(sizeof(char*)*50);
  ele= memset(ele,'\0',strlen(ele));
  for (int i=0 ; i<len;i++){
    //printf(" ele %s\n",ele );
    // le nom du tags c'est un nom simple
    //on  veut des nom compete,par exemple red -> color/red
    // donc on va faire readlink
    //cheminAbsol3=cwd+/.file/+filename+/+tags

    char cheminAbsol3 [1024];
    strcpy(cheminAbsol3,cwd);
    strcat(cheminAbsol3,"/.file");
    strcat(cheminAbsol3,cheminAbsol2);
    strcat(cheminAbsol3,"/");
    if (i>0){
      strcat(cheminAbsol3,ele);
    }else{
      strcat(cheminAbsol3,ficherList[i]);
    }


    //printf("mv 60- cheminAbsol3 %s\n", cheminAbsol3 );
    //on va prendre les chemin du tags
    //normalment buf sera des chemin aboslu de tags
    ssize_t  size;
    char     buf[1024];
    if ((size = readlink(cheminAbsol3, buf, 1024)) < 0) {
        perror("readlink");
        return ;
    } else {
        buf[size] = '\0';
    }
    //printf("mv 71- cheminAbsol %s\n", buf );
    //maintenant on a des chemin absolu de Tag
    //et on  veut juste la parite apre le .tags
    //par exemple /home/user/tags/.tags/color/red --> color/red
    char* token2;
    char *nameTags;
    nameTags =malloc(sizeof(char*)*50);
    memset(nameTags,'\0',strlen(nameTags));
    token2 =strtok(buf,"/");
    int b=0;
    while(token2 !=NULL){
      if (token2[0]=='.'
       && token2[1]=='t'
       && token2[2]=='a'
       && token2[3]=='g'
       && token2[4]=='s'){
        b=1;
        token2 = strtok(NULL,"/");
      }
      if (b==1){
        strcat(nameTags,token2);
        strcat(nameTags,"/");
      }
      token2 = strtok(NULL,"/");
	    if (token2==NULL){
	      nameTags[strlen(nameTags)-1]='\0';
	    }
    }
    //printf("mv 94- simple nameTags %s\n", nameTags);
    memset(ele,'\0',strlen(ele));
    if(ficherList[i+1]){
      strcat(ele ,ficherList[i+1]);
    }

    //printf("mv 40-ficherList next : %s\n",ele);

    //printf("mv 134 file %s\n",file );
    //printf("nameTags %s\n",nameTags );
    rmTags(file,nameTags);
    //on add tous les tags pour new file
    //printf("mv 131 newfile%s\n",newFile );
    //printf("mv nameTags %s\n", nameTags );
    addTags(newFile,nameTags);

  }
}

int main(int argc, char *argv[]){
    if(3 != argc){
        printf("Arguments invalides :\nDoit être de la forme \"mv filename1 filename2.\"\n");
        return 0 ;
    }
    mv(argv[1],argv[2]);
    return 0;
}
