#include "game.h"
#include "game_io.h"
#include "solve.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
void usage_main();

int main(int argc, char* argv[]) {
	if(argc != 4)
		usage_main();
	game g = load_game(argv[2]);
	option o = check_option(argv[1]);
	solver(g, o, argv[3]);
	delete_game(g);
	g=NULL;
}

void usage_main(){
    printf("Usage: net_solve FIND_ONE|NB_SOL|FIND_ALL <nom_fichier_pb> <prefix_fichier_sol>.\n");
    exit(EXIT_FAILURE);
}
