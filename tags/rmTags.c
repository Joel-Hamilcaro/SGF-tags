#include<stdio.h>
#include<unistd.h>
#include <string.h>
#include<sys/types.h>
#include<dirent.h>
#include "rmTags.h"
#include "lsTags.h"


int main(int argc, char *argv[]){
    if(3 != argc){
        printf("Arguments invalides :\nDoit être de la forme \"rmTags filename tagname\"\n");
        return 0 ;
    }
    rmTags(argv[1],argv[2]);
    return 0;
}
