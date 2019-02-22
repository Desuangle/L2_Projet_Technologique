#include "game.h"
#include "game_io.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 409

char* read_next_line1(FILE* p_f, uint* p_size){
    char* s = malloc(MAX*sizeof(char));
    if(s==NULL){return NULL;}
    long old_pos=ftell(p_f), len = 0;
    if(fgets(s,MAX,p_f)!=NULL){
        len = ftell(p_f)-old_pos;
        if(s[len-1]=='\n'){
            s[len-1]='\0';
            len--;
        }else{ //feof return 0 if not end of file
        if(!feof(p_f)){ //to detect error from last line without ’\n’
            fprintf(stderr,"Line too long...");
            exit(EXIT_FAILURE);
        }
        }
        (*p_size)=len;
        return s;
    }
    free(s);
    return NULL; // in case of eof
}

long* convert_line1(char* line,uint* p_size){
    long* tab = malloc((*p_size)*sizeof(long));
    if(tab == NULL){ return NULL; }
    long arr_s=0;
    char * token = strtok(line," ");
    while(token != NULL){
        char* en = token;
        long val = strtol(token, &en, 10);
        if ((*en)=='\0') { // convert was successfull
            tab[arr_s]=val;
            arr_s++;
        }else{
            free(tab);
            return NULL;
        }
        token = strtok(NULL, " ");
    }
    (*p_size)=arr_s;
    return tab;
}

void error(char* message) {
	fprintf(stderr, message);
	exit(EXIT_FAILURE);
}

game load_game(char* filename) {
	if (filename==NULL){
    	fprintf(stderr,"Problem opening file");
        exit(EXIT_FAILURE);
    }
	FILE* f=fopen(filename,"r");
    if (f==NULL){
        fprintf(stderr,"FILE ERR!\n");
        exit(EXIT_FAILURE);
    }
	uint taille=0;
	bool wrapping;
	char* ligne=read_next_line1(f, &taille);
	char tmp=ligne[taille-1];
	char* endptr = ligne;
	int width =(int)strtol(ligne, &endptr, 10);
	//gestion d'erreur
	int height =(int)strtol(ligne, &endptr, 10);
    if(tmp=='N')
	    wrapping = false;
        else
        {
            wrapping = true;
        }
        


	game g = new_game_empty_ext(width,height,wrapping);
    fclose(f);
	return g;
}

=======
}
// TO DO
void print_piece(FILE* savefile, piece p, direction d);

void save_game(cgame g, char* filename) {
	FILE* savefile;
	int w, h;
	savefile = fopen(filename, "w");
	if(!savefile)
		error("Not enough memory\n");
	w = game_width(g);
	h = game_height(g);
	fprintf(savefile, "%d %d ", w, h);
	if(is_wrapping(g))
		fprintf(savefile, "S\n");
	else
		fprintf(savefile, "N\n");
	for(int y = 0; y < h; y++){
		for(int x = 0; x < w; x++){
			print_piece(savefile, get_piece(g, x, y), get_current_dir(g, x, y));
		}
		fprintf(savefile, "\n");
	}
	fclose(savefile);
}

=======
// TO DO

void print_piece(FILE* savefile, piece p, direction d) {
	switch(p){
	case LEAF:
		fprintf(savefile, "L");
		break;
	case SEGMENT:
		fprintf(savefile, "S");
		break;
	case CORNER:
		fprintf(savefile, "C");
		break;
	case TEE:
		fprintf(savefile, "T");
		break;
	case CROSS:
		fprintf(savefile, "F");
		break;
	}
	
	switch(d){
	case N:
		fprintf(savefile, "N");
		break;
	case E:
		fprintf(savefile, "E");
		break;
	case S:
		fprintf(savefile, "S");
		break;
	case W:
		fprintf(savefile, "W");
		break;
	}
	fprintf(savefile, " ");
}

	


    
>>>>>>> d561051fa546b3afbff09ac1ed16762a49b354c1
