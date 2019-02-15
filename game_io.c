#include "game.h"
#include "game_io.h"
#include <stdio.h>
#include <stdlib.h>

void error(char* message) {
	fprintf(stderr, message);
	exit(EXIT_FAILURE);
}

game load_game(char* filename) {
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

	
