#include "game.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_io.h"

/*
shows the grid of the game
 */

//Future co-author: Mathis Gendron
//Future co-author: Killian Le Guen
//Future co-author: Alouini Walid

char* leaf[] = {
	"^", ">", "v", "<"
};
char* segment[] = {
	"|", "-", "|", "-"
};
char* corner[] = {
	"└", "┌", "┐", "┘"
};
char* tee[] = {
	"┴", "├", "┬", "┤"
};
char* cross[] = {
	"+", "+", "+", "+"
};
char** symbols[] = {
	leaf, segment, corner, tee, cross
};

void num_input(int tab[], unsigned int size) {
	if(size == 2) {
		tab[0] = -1;
		tab[1] = -1;
		char c;
		while (tab[0] < 0 && tab[1] < 0){
			scanf("%d%d", &tab[0], &tab[1]);
			if (tab[0] < 0 || tab[1] < 0)
				printf("mauvaises coordonnées, veuillez recommencer.\n$");
			while((c = getchar()) != '\n' && c != EOF)
				/* discard */ ;
		}
	}
}

void show_grid(game g) {
	printf("\n");
	for(int i = 0; i < game_width(g); i++) {
		printf("##");
	}
	printf("###\n");
	/*
    	beginning of the loop
   	*/
	char* s;
	for(int y = game_height(g) - 1; y >= 0; y--) { // vertical
		printf("# ");
		for(int x = 0; x < game_width(g); x++) { // horizontal
			if(get_piece(g, x, y) == EMPTY)
				printf("  ");
			else{
				s = symbols[get_piece(g, x, y)][get_current_dir(g, x, y)];
				printf("%s ", s);
			}
		} // end of x loop
		printf("#\n");
	}
	printf("\n");
}

int main(int argc, char** argv) {
	/*
    Setting up the parameters of the game
   */
	game ex;
	if(argc > 2){
		fprintf(stderr, "Usage : %s <file>\n", argv[0]);
		return(EXIT_FAILURE);
	}
	if(argc==1){
		piece p1[] = {
			LEAF, TEE, LEAF, LEAF, LEAF,
			LEAF, TEE, TEE, CORNER, SEGMENT,
			LEAF, LEAF, TEE, LEAF, SEGMENT,
			TEE, TEE, TEE, TEE, TEE,
			CORNER, LEAF, LEAF, CORNER, LEAF
		};
		direction p2[] = {
			E, W, S, E, S,
			S, S, N, W, N,
			E, N, W, W, E,
			S, W, N, E, E,
			W, N, W, N, S,
		};
		ex = new_game_ext(5, 5, p1, p2, false);
	}
	else {
		ex = load_game(argv[1]);
	}
	/*
		Starting the game
	*/

	int coords[2]; //coords[0] = x, coords[1] = y
	
	while(!is_game_over(ex)) {
		show_grid(ex);
		printf("Entrer des coordonnées (de la forme <x> <y>) :\n$");
		num_input(coords, 2);
		
		if(coords[0] >= 0 && coords[0] < game_width(ex) && coords[1] >= 0 && coords[1] < game_height(ex)) {
			rotate_piece_one(ex, coords[0], coords[1]);
		}
	}
			
	show_grid(ex);

	delete_game(ex);
	ex = NULL;
	return EXIT_SUCCESS;
}
