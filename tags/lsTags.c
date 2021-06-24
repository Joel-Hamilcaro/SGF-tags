#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include "lsTags.h"


int main(int argc, char *argv[]){
    if(2 != argc){
        printf("Arguments invalide :\nDoit être de la forme \"lsTags filename\"\n");
        return 0 ;
    }
    lsTags(argv[1]);
    return 0;
}
