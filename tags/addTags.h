#ifndef ADDTAGS_H
#define ADDTAGS_H
#include <stdlib.h>


void addTags(char* file, char* name);

void addTags(char* file, char* name){
  /*on veut prendre les chemins absolus de tous les fichers à partir #ifndef SYMBOL
  /~/tags */
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
  //cwd = home/user/tags

  /*on creer un copie de file: filename, un copie de name:nameTags
 eviter des modification sur nom du ficher et nom du tags*/
  char * filename;
  int x =strlen(file);
  filename = malloc(sizeof(char*)*x);
  strcpy(filename,file);
  char * nameTags;
  int y = strlen(name);
  nameTags = malloc(sizeof(char*)*y);
  strcpy(nameTags,name);
  //filename=file, nameTags=name
  //printf("add tags filename %s\n",filename );
  //printf("add tags nameTags %s\n",nameTags );
  /*filename peut etre un chemin ,
  on veut simplement le nom de ficher
  on utilise token pour prendre le dernier nom dans le chemin*/
  char* token;
  char* fic;
  token =strtok(filename,"/");
  fic =token;
  while(token !=NULL){
    fic =token;
    token = strtok(NULL,"/");
  }
  //par exemple file= rep/ficher alors on a fic=ficher

  /*predre le chemin absolu pour tags
  par exemple /home/user/tags/.tags/system*/
  char cheminAbsol [1024];
  memset(cheminAbsol,'\0',sizeof(cheminAbsol));
  strcpy(cheminAbsol,cwd);
  strcat(cheminAbsol,"/.tags/");
  strcat(cheminAbsol,nameTags);
  //printf("addTags 49 cheminAbsol %s\n",cheminAbsol );

  /*on veut mettre un symlink dans ce chemin absolu
  on ouvre ce chemin*/
  DIR *dir = opendir(cheminAbsol);
  if (dir==NULL){
    perror("opendir");
    return;
  }
  int fd = dirfd(dir);
  if (fd<0){
    perror("dirfd");
    return;
  }

  /*cheminabsol2 est le chemin  du  ficher */
  char cheminAbsol2 [1024];
  //si file est un chemin absolu on met cheminAbsol2 = file
  //si c'est pas un chemin absolu ,on met cheminAbsol2 = pwd/file
  memset(cheminAbsol2,'\0',sizeof(cheminAbsol2));
  if (file[0]!='/'){
    getcwd(cheminAbsol2,sizeof(cheminAbsol2));
    strcat(cheminAbsol2,"/");
  }
  strcat(cheminAbsol2,file);

/*on veut savoir que ce cheminAbsol2 est un symlink ou pas,
si c'est un symlink ,
on utilise readlink() pour touver le vrai chemin du ficher */
  ssize_t  size;
  char     buf[1024];
  if ((size = readlink(cheminAbsol2, buf, 1024)) > 0) {
 	  buf[size] = '\0';
    printf("%s\n",buf);
	  memset(cheminAbsol2,'\0',strlen(cheminAbsol2));
    //getcwd(cheminAbsol2,sizeof(cheminAbsol2));
  	//strcat(cheminAbsol2,"/");
  	strcat(cheminAbsol2,buf);
	  token =strtok(buf,"/");
  	fic =token;
  	while(token !=NULL){
    	fic =token;
    	token = strtok(NULL,"/");
  	}
    //on renouve le chemin absolu 2 et le nom du ficher
  }
  //creer symlink
  //printf("add tags cheminAbsol %s\n", cheminAbsol);
  //printf("add tags cheminAbsol2 %s\n", cheminAbsol2);
  //printf("add tags fic %s\n", fic);
	/*on cree un cheminAbsol4= cheminAbsol2+fic
  on va verifier qu'il y a deja un symlink ou pas */
	char cheminAbsol4 [1024];
  strcpy(cheminAbsol4,cheminAbsol);
  strcat(cheminAbsol4,"/");
  strcat(cheminAbsol4,fic);
	//printf("addTags cheminAbsol4 %s\n",cheminAbsol4 );
  /*on cree un cheminAbsol5 pour presente le original ficher de symlinkat
  si il y a deja un symlink qui a le meme nom du ficher*/
	while(access(cheminAbsol4,F_OK)==0){
		ssize_t  size4;
	  char     buf4[1024];
	  if ((size4 = readlink(cheminAbsol4, buf4, 1024)) > 0) {
			buf4[size4] = '\0';
			//printf("cheminAbsol4 buf4 %s\n", cheminAbsol5);
			//printf("addTags buf4 %s\n", buf4);
			if (strcmp(buf4,cheminAbsol2)==0){
				//printf("addtags %s\n","Tags exists" );
        break;
			}else{
        //si c'est pas le meme symlink, on renome notre nom du symlink a fic2
				char * fic4 =(char*)malloc(sizeof(char*)*50);
				memset(fic4,'\0',strlen(fic4));
				strcat(fic4,fic);
				strcat(fic4,"2");
				fic = fic4;
				//printf("fic4 %s\n", fic );
        memset(cheminAbsol4,'\0',strlen(cheminAbsol4));
        strcpy(cheminAbsol4,cheminAbsol);
        strcat(cheminAbsol4,"/");
        strcat(cheminAbsol4,fic);
        //printf("add 138 cheminAbsol4 %s\n",cheminAbsol4 );
			}
		}
	}

  //on cree le symlink
  int sym = symlinkat(cheminAbsol2,fd,fic);
  if (sym <0){
    //perror("symlinkat");
    printf("Ce tag existe déjà pour ce fichier\n");
    return;
  }
  close(fd);



  /*on cree un repertoire qui est nome par fic ,
  et ce repertoire contient tous les symlink de tags,
  on cree un cheminAbsol3
  par defaut c'est home/user/tags/.file/file*/

  char cheminAbsol3 [1024];
  //getcwd(cheminAbsol3,sizeof(cheminAbsol3));
  strcpy(cheminAbsol3,cwd);
  strcat(cheminAbsol3,"/.file");
  strcat(cheminAbsol3,cheminAbsol2);
  //printf("addTags cheminAbsol3 %s\n",cheminAbsol3 );
  int len3 =strlen(cheminAbsol3);
  char * cheminTmp = cheminAbsol3;
  int len=strlen(cheminAbsol3);
  for( int i=0; i<len; i++ ){
      if(cheminAbsol3[i]=='/'){
          cheminAbsol3[i] = '\0';
          if(access(cheminAbsol3,F_OK)!=0){
              mkdir( cheminAbsol3, 0777 );
              //printf("creer le rep file:%s\n", cheminAbsol3 );
          }
          cheminAbsol3[i]='/';
      }
  }
  if(len>0 && access(cheminAbsol3,F_OK)!=0){
    //printf("creer le rep sous file :%s\n", cheminAbsol3 );
    mkdir( cheminAbsol3, 0777 );
  }
  // symlink .tags -> .file
  //printf("cheminTmp %s\n",cheminTmp );
  DIR *dir2 = opendir(cheminTmp);
  if (dir2==NULL){
    perror("opendir2");
    return;
  }
  int fd2 = dirfd(dir2);
  if (fd2<0){
    perror("dirfd2");
    return;
  }

  char* token2;
  char* tags;
  token2 =strtok(nameTags,"/");
  tags =token2;
  while(token2 !=NULL){
    tags =token2;
    token2 = strtok(NULL,"/");
  }
  //printf("tags %s\n",tags  );
  //printf("add tags - cheminabsol %s\n",cheminAbsol );
  //printf("add tags - tags %s\n",tags );
  //printf("1cheminabsol tmp%s\n",cheminTmp);
  int sym2 = symlinkat(cheminAbsol,fd2,tags);
  if (sym2 <0){
    perror("symlinkat2");
    return;
  }
  close(fd2);


}
#endif
