#include <stdio.h>
#include <sys/stat.h>//mkdiir
#include <unistd.h>//access
#include <string.h>//strcat
#include<sys/types.h>
#include<dirent.h>
#include <stdlib.h>

void makeTags(char *nameTags){
	char pwd[1024];
	getcwd(pwd,sizeof(pwd));
	char* token2;
	char* str =malloc( sizeof(char*)*1024);
	str= memset(str,'\0',strlen(str));
	token2 =strtok(pwd,"/");
	for(int i=0; i<2;i++){
		strcat(str,"/");
		strcat(str,token2);
		token2 = strtok(NULL,"/");
	}

	strcat(str,"/tags/.tags/");
  strcat(str,nameTags);
    int len=strlen(str);
    for( int i=0; i<len; i++ ){
        if(str[i]=='/'){

            str[i] = '\0';
            if(access(str,F_OK)!=0){
                mkdir( str, 0777 );
                //printf("creer le rep:%s\n", str );
            }
            str[i]='/';
        }
    }
    if(len>0 && access(str,0)!=0){
      printf("Tag créé --> %s\n", nameTags);
      mkdir( str, 0777 );
    }

    return;
}


int main(int argc, char* argv[]){
  for (int  i=1 ; i<argc; i++){
    makeTags(argv[i]);
  }
  return 0;
}
