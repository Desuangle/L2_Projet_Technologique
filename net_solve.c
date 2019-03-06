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
	option o = check_option(argv[1]);
	solver(g, o, argv[3]);
}

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

void solver(cgame g, option o, char* filename) {
	game g2 = copy_game(g);
	int n = 0;
	solver_rec(g2, o, 0, &n, filename);
	//return n;
	solver_print_nbsolv_or_no_sol(o,&n,filename);

}

//bool is_current_good(cgame g, int f);

void solver_rec(game g, option o, int i, int* n, char* filename) {
	int w = game_width(g), h = game_height(g);
	if(i == w * h) {
		//show_grid(g);
		if(is_game_over(g))
			printf("Trouvé\n");
		else
			printf("PAS Trouvé\n");
		
		solver_print(g, n, o, filename);
		return;
	}
	int x = i%w, y = i/w;
	piece p = get_piece(g, x, y);
	//		if(!(is_current_good(g, i))){
	//			return;
	//		}
	//		printf("good\n");
	bool bonne_dir;
	direction end_dir;
	if (p == LEAF || p == CORNER || p == TEE)
		end_dir = W;
	else if (p == SEGMENT)
		end_dir = E;
	else
		end_dir = N;
	for(direction d = N; d <= end_dir; d++) {
		set_piece_current_dir(g, x, y, d);
		bonne_dir = true;// Bonne direction
		if(is_edge_coordinates(g, x, y, S)){ // vise le nord
			if(y == 0)
				bonne_dir = false;
			if(!is_edge_coordinates(g, x, y-1, N))
				bonne_dir = false;
		}
		else{ // ne vise pas le nord
			if(y != 0 && is_edge_coordinates(g, x, y-1, N))
				bonne_dir = false;
		}
		
		if(is_edge_coordinates(g, x, y, W)){ // vise l'ouest
			if(x == 0)
				bonne_dir = false;
			if(!is_edge_coordinates(g, x-1, y, E))
				bonne_dir = false;
		}
		else{ // ne vise pas l'ouest
			if(x != 0 && is_edge_coordinates(g, x-1, y, E))
				bonne_dir = false;
		}

		if(is_edge_coordinates(g, x, y, N)){ // vise le sud
			if(y == h-1)
				bonne_dir = false;
		}
		else{ // ne vise pas le sud
			
		}

		if(is_edge_coordinates(g, x, y, E)){ // vise l'est
			if(x == w - 1)
				bonne_dir = false;
		}
		else{ // ne vise pas l'est

		}
		if(bonne_dir)
			solver_rec(g, o, i+1, n, filename);
	}
}

/*
bool is_connected_coordinates(cgame g, int x, int y, direction d);

bool is_current_good(cgame g, int f){
	int w = game_width(g);
	int fy= f/w;
	for(int i = 0; i < (f - w); i++){
		int x = i%w, y = i/w;
		for(direction d = 0; d < 4; d++) {			 // d = direction
			// 1-
			if(is_edge_coordinates(g, i % w , i % w , d) && !is_connected_coordinates(g, i % w , i % w , d)) {
				return false;
			}
		}
	}
	return true;
}
*/
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

