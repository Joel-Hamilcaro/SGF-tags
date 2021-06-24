#ifndef LSTAGS_H
#define LSTAGS_H

char ** lsTags(char* filename);
char ** lsTags(char* filename){

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


  char cheminAbsol2 [1024];
  //si file est un chemin absolu on met cheminAbsol2 = file
  //si c'est pas un chemin absolu ,on met cheminAbsol2 = pwd/file
  memset(cheminAbsol2,'\0',sizeof(cheminAbsol2));
  if (filename[0]!='/'){
    getcwd(cheminAbsol2,sizeof(cheminAbsol2));
    strcat(cheminAbsol2,"/");
  }
  strcat(cheminAbsol2,filename);


  //printf("lstags 14-filname %s\n", filename);
  char cheminAbsol3 [1024];
  strcpy(cheminAbsol3,cwd);
  strcat(cheminAbsol3,"/.file");
  strcat(cheminAbsol3,cheminAbsol2);


  //printf("lstags 39-cheminAbsol3 %s\n", cheminAbsol3);
  struct dirent **ficherList;
  char ** nameTags;//malloc?
  nameTags =(char**)malloc(sizeof(char**)*100);
  int n;
  n = scandir(cheminAbsol3, &ficherList, 0, alphasort);
  if (n < 0){
    //printf("Le fichier n'a pas été trouvé.\n");
    return NULL;
  }else{
    //printf("%d\n",n );
    int i=0;
    int j=0;
    while(i<n){
        if (strcmp(ficherList[i]->d_name,".")!=0
         && strcmp(ficherList[i]->d_name,"..")!=0){
          //printf("%s\n", ficherList[i]->d_name);
          //
          // le nom du tags c'est un nom simple
          //on  veut des nom compete,par exemple red -> color/red
          // donc on va faire readlink
          //cheminAbsol3=cwd+/.file/+filename+/+tags

          char cheminAbsol3 [1024];
          strcpy(cheminAbsol3,cwd);
          strcat(cheminAbsol3,"/.file");
          strcat(cheminAbsol3,cheminAbsol2);
          strcat(cheminAbsol3,"/");
          strcat(cheminAbsol3,ficherList[i]->d_name);
          

          //printf("lstags 71- cheminAbsol3 %s\n", cheminAbsol3 );
          //on va prendre les chemin du tags
          //normalment buf sera des chemin aboslu de tags
          ssize_t  size;
          char     buf[1024];
          if ((size = readlink(cheminAbsol3, buf, 1024)) < 0) {
              perror("readlink");
              return NULL;
          } else {
              buf[size] = '\0';
          }
          //printf("lstags 82- cheminAbsol %s\n", buf );
          //maintenant on a des chemin absolu de Tag
          //et on  veut juste la parite apre le .tags
          //par exemple /home/user/tags/.tags/color/red --> color/red
          char* token2;
          char *fullname;
          fullname =malloc(sizeof(char*)*50);
          memset(fullname,'\0',strlen(fullname));
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
              strcat(fullname,token2);
              strcat(fullname,"/");
            }
            token2 = strtok(NULL,"/");
      	    if (token2==NULL){
      	      fullname[strlen(fullname)-1]='\0';
      	    }
          }
          printf("%s\n", fullname);

          //
          nameTags[j]=ficherList[i]->d_name;
          j++;
        }

        free(ficherList[i]);
        i++;
    }
    //printf("ls- nombre de tags %d\n",j );
    int len=0;
    char *tem=nameTags[0];
    while(tem){
        //printf(" ++ls tags %s\n", nameTags[len]);
        len++;
        tem=nameTags[len];

    }
    //printf("%d\n", i);
    free(ficherList);
  }

  return nameTags;
}

#endif
