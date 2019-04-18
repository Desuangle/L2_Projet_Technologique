/*

 */

typedef enum option_e {FIND_ONE, NB_SOL, FIND_ALL, GEN_SEQ} option;
#define NB_OPTIONS 3

option check_option(char* opt);
void solver(cgame g, option o, char* filename);
void solver_rec(game g, option o, int i, int* n, char* filename, bool* fini, int* seq_list, int* seq_n, game g3);
void solver_print(game g,int *c,option opt,char* filename, bool* fini);
void solver_print_nbsolv_or_no_sol(option opt,int*c, char* filename);
void solver_print_genseq(int* list, int n, char* prefix, int w, int h);
#define SIZE_CHAINE 128 // "NB_SOL = " : 9 characters + *c < 1,000,000 solutions : 6 + '\0' : 1 = 16
#define SIZE_PREFIX 128
#define SIZE_LIST 1024
void create_file(char* filename, char* msg);
