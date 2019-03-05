#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.h"

typedef enum option_e {FIND_ONE, NB_SOL, FIND_ALL} option;

void usage(){
    printf("Usage: net_solve FIND_ONE|NB_SOL|FIND_ALL <nom_fichier_pb> <prefix_fichier_sol>.\n");
    exit(EXIT_FAILURE);
}

option check_option(char* opt){
    if(!opt){
        usage();
    }
    if(strlen(opt)<6){ //test to be sure not to go out of range
        usage();
    }
    if(opt[0]=='N'){
        if(!strcmp(opt,"NB_SOL")){
            return NB_SOL;
        }
    }
    if(opt[0]=='F'){
        if(opt[5]=='O'){
            if(!strcmp(opt,"FIND_ONE")){
                return FIND_ONE;
            }
        }
        if(opt[5]=='A'){
            if(!strcmp(opt,"FIND_ALL")){
                return FIND_ALL;
            }
        }
    }
    usage();
}

void main(int argc, char** argv){
    if(!argv || argc!=4){
        usage();
    }
    resolve(check_option(argv[1]),load_game(argv[2]),argv[3]);
}