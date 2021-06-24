#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <string.h>
#include<sys/types.h>
#include<dirent.h>
#include "lsFile.h"
int main(int argc, char *argv[]){
    if(2 != argc){
        printf("Arguments invalides :\nDoit être de la forme \"lsFile tagname\"\n");
        return 0 ;
    }
    lsFile(argv[1]);
    return 0;
}
