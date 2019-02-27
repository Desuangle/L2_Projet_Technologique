#include "game.h"
#include "game_io.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX 409


void error(char* message) {
	fprintf(stderr, message);
	exit(EXIT_FAILURE);
}

piece convert_piece(char tmp){
	switch(tmp){
	case 'L':
		return LEAF;
		break;
	case 'S':
		return SEGMENT;
		break;
	case 'C':
		return CORNER;
		break;
	case 'T':
		return TEE;
		break;
	case 'F':
		return CROSS;
		break;
	}
}

direction convert_direction(char tmp){
	switch(tmp){
	case 'N':
		return N;
		break;
	case 'S':
		return S;
		break;
	case 'E':
		return E;
		break;
	case 'W':
		return W;
		break;
	}
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
	int width, height;
	char tmp;
	int err = fscanf(f,"%d %d %c", width, height, tmp);
	if(err != 3)
		error("Can't convert first line\n");
	bool wrapping;
    if(tmp=='N')
	    wrapping = false;
    else
        wrapping = true;
	
	piece p[width*height];
	direction d[width*height];
	int i = 0;
	tmp = fgetc(f); // on garde cette ligne si c'est une nouvelle ligne
	while(tmp != EOF) {
		tmp = fgetc(f);
		p[i] = convert_piece(tmp);
		tmp = fgetc(f);
		d[i] = convert_direction(tmp);
		tmp = fgetc(f);
		i++;
	}

	game g = new_game_ext(width, height, p, d, wrapping) ;
	
    fclose(f);
	return g;
}


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

	


    
