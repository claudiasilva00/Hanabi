#ifndef _hanabi_model_ 
#define _hanabi_model_
#pragma warning(disable : 4996)
#define DECK_SIZE 50
char deck_char[50][3]={"1R","1R","1R","2R","2R","3R","3R","4R","4R","5R",
				 	   "1G","1G","1G","2G","2G","3G","3G","4G","4G","5G",
				  	   "1B","1B","1B","2B","2B","3B","3B","4B","4B","5B",
			 	       "1Y","1Y","1Y","2Y","2Y","3Y","3Y","4Y","4Y","5Y",
		 		       "1W","1W","1W","2W","2W","3W","3W","4W","4W","5W"};

int deck[50]={1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,
			  11,12,13,14,15,16,17,18,19,20,
			  21,22,23,24,25,26,27,28,29,30,
			  31,32,33,34,35,36,37,38,39,40,
			  41,42,43,44,45,46,47,48,49,50};
			  
int discarded_table[5][5] = {{0,0,0,0,0},
 							 {0,0,0,0,0}, 
 							 {0,0,0,0,0}, 
 							 {0,0,0,0,0},
 							 {0,0,0,0,0}};

int player_1[]={0,0,0,0,0};
int player_2[]={1,3,5,8,10};
char player_1_info[5][3]={"","","","",""};
char player_2_info[5][3]={"","","","",""};

int r_table[]={0,0,0,0,0};
int g_table[]={0,0,0,0,0};
int b_table[]={0,0,0,0,0};
int y_table[]={0,0,0,0,0};
int w_table[]={0,0,0,0,0};

int lives=3;
int tips=8;
char menu=0;
int descartar;
int i,j;
char clr,n,points,prev_points;
char player_name[16];
char menu_p;
int NO_DELAY=1;
int count,deck_taken;
int count_deck;
int discard_selec;
int plays;
char color;
char num;
int disc_n=0;
int no_possible;
int card_play;
int menu_pos;
int decksize(int *d, int n)								//função de contagem de cartas restantes no deck por dar aos jogadores 
{														// função chamada em viewdeck
	int c=0, i;											
	for (i=0;i<n;i++) if(d[i]>0) c++;
	return c; 
}
#endif
