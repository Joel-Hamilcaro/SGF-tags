#ifndef LSFILE_H
#define LSFILE_H
#include <sys/stat.h>
char** lsFile(char* nameTags);
int lenList(char** list);
char** lsFile(char* nameTags){
  // Chemin de tous les tags
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


  char cheminAbsol [1024];
  strcpy(cheminAbsol,cwd);
  strcat(cheminAbsol,"/.tags/");
  strcat(cheminAbsol,nameTags);
  // printf("lsfile -cheminAbsol %s\n", cheminAbsol );

  struct dirent **ficherList;
char ** nameFicher;
nameFicher =(char**)malloc(sizeof(char**)*100);
  int n;
  n = scandir(cheminAbsol, &ficherList, 0, alphasort);
  if (n < 0){
    printf("Tag introuvable\n");
    return  NULL;
  }else{
    //printf("%d\n",n );
    int i=0;
    int j=0;
    while(i<n){
      char cheminAbsol4 [1024];
      strcpy(cheminAbsol4,cheminAbsol);
      strcat(cheminAbsol4,"/");
      strcat(cheminAbsol4,ficherList[i]->d_name);



      ssize_t  size4;
  	  char     buf4[1024];
  	  if ((size4 = readlink(cheminAbsol4, buf4, 1024)) > 0) {
  			buf4[size4] = '\0';
        //printf("ls file buf -%s\n", buf4);
        if (strcmp(ficherList[i]->d_name,".")!=0
         && strcmp(ficherList[i]->d_name,"..")!=0){
           printf("%s:  %s\n", nameTags,ficherList[i]->d_name);
           nameFicher[j]=ficherList[i]->d_name;
           j++;

        }
      }else{
        if (strcmp(ficherList[i]->d_name,".")!=0
         && strcmp(ficherList[i]->d_name,"..")!=0){
           //printf("%s\n", ficherList[i]->d_name);
           //nameFicher[j]=ficherList[i]->d_name;
           //j++;
           struct stat info;
           stat(cheminAbsol4,&info);
           if(S_ISDIR(info.st_mode)){
             char * sousTags =malloc(sizeof(char* )*1024);
             strcpy(sousTags,nameTags);
             strcat(sousTags,"/");
             strcat(sousTags,ficherList[i]->d_name);

             lsFile(sousTags);
           }



        }
      }
      free(ficherList[i]);
      i++;
    }
    // printf("lsfile nombre %d\n",j );
    free(ficherList);
  }
  return nameFicher;
}
int lenList(char** list){
  int len=0;
  char *tem=list[0];
  while(tem){
      len++;
      tem=list[len];
  }
  return len;
}
#endif
