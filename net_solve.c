#include "game.h"
#include "game_io.h"
#include "game_solve.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void solver(cgame g, option o, char* filename) {
	game g2 = copy_game(g);
	int n = 0;
	solver_rec(g2, o, 0, &n, filename);
	//return n;
	solver_print_nbsolv_or_no_sol(o,n,filename);

}

void solver_rec(game g, option o, int i, int* n, char* filename) {
	int w = game_width(g), h = game_height(g);
	if(i == w * h) {
		if(is_game_over(g)) {	
		solver_print(g, o, n, filename);
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

void solver_print(game g,int *c,option opt,char filename)
{
	*c=*c+1;
	if (opt == FIND_ONE)
	{
			save_game(c, g, prefixe);
			return EXIT_SUCCESS;
	}
	else if (opt == FIND_ALL)
	{
		char *chaine;
		sprintf(&chaine, "%s.sol%d", filename, *c);
		save_game(c,g,chaine);
	}
}

void solver_print_nbsolv_or_no_sol(option opt,int*c,filename)
{
	if ((opt == FIND_ONE || opt = FIND_ALL) && *c ==0)
	{
		create_file(filename,"NO SOLUTION")
	}
	else if (opt = NB_SOL)
	{
		char *chaine;
		sprintf(&chaine, "NB_SOL = %d", *c);
		create_file(filename,&chaine)
	}
}
void create_file(char* filename, char* msg) {
	FILE* savefile;
	savefile = fopen(filename, "w");
	if(!savefile)
		error("Not enough memory\n");

	fprintf(savefile, "%s\n", msg);
	fclose(savefile);
	}
	
}
