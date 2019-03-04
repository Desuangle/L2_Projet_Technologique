#include "game.h"
#include "game_io.h"
#include "net_solve.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main(int argc, char* argv[]) {
	if(argc != 4)
		usage();
	game g = load_game(argv[2]);
	option o;
	if (argv[1][0] == 'F' && argv[1][5] == 'O') // c'est find one
		o = FIND_ONE;
	else if (argv[1][0] == 'F') // c'est find all
		o = FIND_ALL;
	else // c'est nb_sol
		o = NB_SOL;

	solver(g, o, argv[3]);
}

void usage(){
	printf("net_solve FIND_ONE|NB_SOL|FIND_ALL <nom_fichier_pb> <prefix_fichier_sol>\n");
	exit(EXIT_FAILURE);
}

void solver(cgame g, option o, char* filename) {
	game g2 = copy_game(g);
	int n = 0;
	solver_rec(g2, o, 0, &n, filename);
	//return n;
	solver_print_nbsolv_or_no_sol(o,&n,filename);

}

void solver_rec(game g, option o, int i, int* n, char* filename) {
	int w = game_width(g), h = game_height(g);
	if(i == w * h) {
		if(is_game_over(g)) {	
		solver_print(g, n, o, filename);
		}
		return;
	}
	int x = i - (i/w), y = i/w, x2 = x, y2 = y;
	piece p = get_piece(g, x, y);
	bool bonne_dir;
	direction end_dir;
	if (p == LEAF || p == CORNER || p == TEE)
		end_dir = W;
	else if (p == SEGMENT)
		end_dir = E;
	else
		end_dir = N;
	for(direction d = N; d <= end_dir; d++) {
		switch (d) {
		case E:
			bonne_dir = true;
			break;
		case S:
			bonne_dir = true;
			break;
		case N:
			y2--;
			bonne_dir = is_edge_coordinates(g, x2, y2, S);
			break;
		case W:
			x2--;
			bonne_dir = is_edge_coordinates(g, x2, y2, E);
			break;
		default:
			bonne_dir = false;
		}
		if(bonne_dir && is_edge_coordinates(g, x, y, d)) { 
			set_piece_current_dir(g, x, y, d);
			solver_rec(g, o, i+1, n, filename);
		}
	}
}

void solver_print(game g,int *c,option opt,char* filename)
{
	*c=*c+1;
	if (opt == FIND_ONE)
	{
			save_game(g, filename);
			exit(EXIT_SUCCESS);
	}
	else if (opt == FIND_ALL)
	{
		char *chaine = (char*) malloc(SIZE_PREFIX * sizeof(char));
		sprintf(chaine, "%s.sol%d", filename, *c);
		save_game(g,chaine);
	}
}

void solver_print_nbsolv_or_no_sol(option opt,int*c,char* filename)
{
	if ((opt == FIND_ONE || opt == FIND_ALL) && *c ==0)
	{
		create_file(filename,"NO SOLUTION");
	}
	else if (opt == NB_SOL)
	{
		char *chaine = (char*) malloc(SIZE_CHAINE * sizeof(char));
		sprintf(chaine, "NB_SOL = %d", *c);
		create_file(filename,chaine);
	}
}
void create_file(char* filename, char* msg) {
	FILE* savefile;
	savefile = fopen(filename, "w");
	if(!savefile){
		fprintf(stderr, "Not enough memory\n");
		exit(EXIT_FAILURE);
	}
	fprintf(savefile, "%s\n", msg);
	fclose(savefile);
	
	
}
