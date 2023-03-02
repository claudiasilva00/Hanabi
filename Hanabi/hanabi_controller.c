#ifndef _hanabi_controller_ 
#define _hanabi_controller_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lab.h"
#include <locale.h>
#include <string.h>
#include "hanabi_model.h"
#include "hanabi_view.c"

int gamesave() 
{
	int i=0;
	FILE *file = NULL;
	file = fopen("gamesave.txt", "w");
	if(file == NULL) {
		printf("Ficheiro não encontrado!\n");
		return 0;
	}
	for(i=0; i<50; i++) {
		fprintf(file,"(%i)",deck[i]);
	}
	fprintf(file,"(%i)", lives);
	for(i=0; i<5; i++) 
	{
		fprintf(file,"(%i,%c,%c)", player_1[i],player_1_info[i][0],player_1_info[i][1]);
	}
	for(i=0; i<5; i++) 
	{
		fprintf(file,"(%i,%c,%c)", player_2[i], player_2_info[i][0],player_2_info[i][1]);
	}
	for(i=0; i<5; i++)
	{
		fprintf(file,"(%i,%i,%i,%i,%i)", w_table[i], y_table[i],b_table[i],g_table[i],r_table[i]);
	}
	fprintf(file,"(%i)", tips);
	for(i=0; i<5; i++)
	{
		fprintf(file,"(%i,%i,%i,%i,%i)",discarded_table[i][0],discarded_table[i][1],discarded_table[i][2],discarded_table[i][3],discarded_table[i][4]);
	}
	for(i=0;i<16;i++)
	{	
	fprintf(file,"(%c)",player_name[i]);
	}
	fprintf(file,"(%d)",deck_taken);
	fprintf(file,"(%i)",points);
	fclose(file);
	end();
	menu='m';
	return 0;
}
int gameload()
{
	int i=0, num=0;
	char spc=' ';
	FILE *file = NULL;
	file = fopen("gamesave.txt", "r");
	if(file == NULL) {
		printf("Não existem jogos salvos.\n");
		return 0;
	}
	for(i=0; i<50; i++) 
	{
		fscanf(file, "(%i)",&deck[i]);
	}	
	fscanf(file, "(%i)", &lives);
		for(i=0; i<5; i++)
			{
			fscanf(file,"(%i,%c,%c)",&player_1[i],&player_1_info[i][0],&player_1_info[i][1]);
			}
		for(i=0; i<5; i++)			
			{
			fscanf(file,"(%i,%c,%c)",&player_2[i],&player_2_info[i][0],&player_2_info[i][1]);
			}
		for(i=0; i<5; i++)
	{
		fscanf(file,"(%i,%i,%i,%i,%i)", &w_table[i], &y_table[i],&b_table[i],&g_table[i],&r_table[i]);
	}
	fscanf(file, "(%i)",&tips);
	for(i=0; i<5; i++)
	{
		fscanf(file,"(%i,%i,%i,%i,%i)",&discarded_table[i][0], &discarded_table[i][1],&discarded_table[i][2],&discarded_table[i][3],&discarded_table[i][4]);
	}

		for(i=0;i<16;i++)
	{	
	fscanf(file,"(%c)",&player_name[i]);
	}
	fscanf(file,"(%d)",&deck_taken);
	fscanf(file,"(%i)",&points);
	system("pause");
	fclose(file);
	return 0;
}
void intro_control ()										//funçção que pede ao utilizador por ENTER para continuar 
{
	printf("\n\nPRESS ENTER TO CONTINUE....");
	do
	{	
		menu=getch();
	}
	while ((menu!=13));
	system("cls");
}
void menu_control()											//função que espera que espera pela por uma das 4 opções do menu principal
{															
	printf("\n\n\n");
	do														//caso o utilizador escolha uma opção que nao uma das 4 existente permanece
	{														//no menu até que o utilizador escolha uma das 4 opções existentes
		menu_p=getch();		
	}
	while ((menu_p!='1')&&(menu_p!='2')&&(menu_p!='3')&&(menu_p!='4')&&(menu_p!='5'));
	return;
}
void shuffle_deck()											//baralha o vetor <int deck>
{
	int i,a,t;
	srand(time(NULL));
	for (i=0;i<DECK_SIZE;i++)
	{
	   a=rand()%50;
 	   t=deck[i];
 	   deck[i]=deck[a];
	   deck[a]=t;
	}
}
void deal()													//da os 10 ultimos valores do vetor <int deck> aos vetor <int player_1> e <int player_2>
{															//1 a 5 a ambos os players
	int a;
	for (deck_taken=1;deck_taken<6;deck_taken++)
	{
		player_1[deck_taken-1]=deck[DECK_SIZE-deck_taken];
		deck[DECK_SIZE-deck_taken]=0;								//depois de dado a carta a sua porsição é definida como 0 de modo a poder fazer-se a contagem de cartas nao dadas do deck
	}
	for (deck_taken=6;deck_taken<11;deck_taken++)
	{
		player_2[deck_taken-6]=deck[DECK_SIZE-deck_taken];
		deck[DECK_SIZE-deck_taken]=0;
	}
}
void lernome()                                                //lê o nome do jogador 
{
    int Ch=0;
    gotoxy(50,11);

    while(Ch < 10)
        {
            player_name[Ch] = getch();
            if(Ch > 0 && player_name[Ch] == '\b')
                {
                    Ch --;
                    putch(16);
                }
            else
                putch(player_name[Ch]);

            if(player_name[Ch] == '\r')
                break;
            Ch++;
        }
    system("cls");
}
void Keys_menu()											//espera que o utilizador prima introduza uma opçãao valida
{
	do
	{	
		menu=getch();		
	}
	while ((menu!='m')&&(menu!='M')&&(menu!='p')&&(menu!='P')&&(menu!='c')&&(menu!='C')&&(menu!='n')&&(menu!='N')&&(menu!='d')&&(menu!='D')&&(menu!='s')&&(menu!='S')&&(menu!='l')&&(menu!='L'));
}
void hand_filler()
{
	if((deck_taken<50))
	{
		int i;
		if(plays==0)
		{
			for (i=0;i<5;i++)
			{
				if(player_1[i]<1||player_1[i]>50)
				{
					player_1[i]=deck[DECK_SIZE-deck_taken+1];
					deck[DECK_SIZE-deck_taken+2]=0;
					deck_taken++;
				}	
			}	
		}
		if(plays==1)
		{
			for (i=0;i<5;i++)
			{
				if(player_2[i]<1||player_2[i]>50)
				{
					player_2[i]=deck[DECK_SIZE-deck_taken+1];					
					deck[DECK_SIZE-deck_taken+2]=0;	
					deck_taken++;
				}	
			}
		}	
	}
}
void play()
{
	prev_points=points;
	if(plays==1) card_play=player_2[menu_pos];
	if(plays==0) card_play=player_1[menu_pos];
	if(plays==1) player_2[menu_pos]=0;
	if(plays==0) player_1[menu_pos]=0;
	if(plays==0) player_1_info[menu_pos][0]='\0';	
	if(plays==0) player_1_info[menu_pos][1]='\0';	
	if(plays==1) player_2_info[menu_pos][0]='\0';	
	if(plays==1) player_2_info[menu_pos][1]='\0';	
	hand_filler();
	if(card_play>0&&card_play<11)
	{
		if(r_table[0]==0&&((card_play==1)||(card_play==2)||(card_play==3)))
		{
			r_table[0]=card_play;
			points++;
		}
		else if(r_table[0]!=0&&r_table[1]==0&&((card_play==4)||(card_play==5)))
		{
			r_table[1]=card_play;
			points++;
		}
		else if(r_table[0]!=0&&r_table[2]!=0&&r_table[3]==0&&((card_play==6)||(card_play==7)))
		{
			r_table[2]=card_play;
			points++;
		}
		else if(r_table[0]!=0&&r_table[2]!=0&&r_table[1]!=0&&r_table[3]==0&&((card_play==8)||(card_play==9)))
		{
			r_table[3]=card_play;
			points++;
		}
		else if(r_table[0]!=0&&r_table[1]!=0&&r_table[2]!=0&&r_table[3]!=0&&r_table[4]==0&&(card_play==10))
		{
			r_table[4]=card_play;
			points++;
		}
		else
		{
			lives--;
		}
	}
	if(card_play>10&&card_play<21)
	{
		if(g_table[0]==0&&((card_play==11)||(card_play==12)||(card_play==13)))
		{
			g_table[0]=card_play;
			points++;
		}
		else if(g_table[0]!=0&&g_table[1]==0&&((card_play==14)||(card_play==15)))
		{
			g_table[1]=card_play;
			points++;
		}
		else if(g_table[0]!=0&&g_table[2]!=0&&g_table[3]==0&&((card_play==16)||(card_play==17)))
		{
			g_table[2]=card_play;
			points++;
		}
		else if(g_table[0]!=0&&g_table[2]!=0&&g_table[1]!=0&&g_table[3]==0&&((card_play==18)||(card_play==19)))
		{
			g_table[3]=card_play;
			points++;
		}
		else if(g_table[0]!=0&&g_table[1]!=0&&g_table[2]!=0&&g_table[3]!=0&&g_table[4]==0&&(card_play==20))
		{
			g_table[4]=card_play;
			points++;
		}
		else
		{
			lives--;
		}
	}
	if(card_play>20&&card_play<31)
	{
		if(b_table[0]==0&&((card_play==21)||(card_play==22)||(card_play==23)))
		{
			b_table[0]=card_play;
			points++;
		}
		else if(b_table[0]!=0&&b_table[1]==0&&((card_play==24)||(card_play==25)))
		{
			b_table[1]=card_play;
			points++;
		}
		else if(b_table[0]!=0&&b_table[2]!=0&&b_table[3]==0&&((card_play==26)||(card_play==27)))
		{
			b_table[2]=card_play;
			points++;
		}
		else if(b_table[0]!=0&&b_table[2]!=0&&b_table[1]!=0&&b_table[3]==0&&((card_play==28)||(card_play==29)))
		{
			b_table[3]=card_play;
			points++;
		}
		else if(b_table[0]!=0&&b_table[1]!=0&&b_table[2]!=0&&b_table[3]!=0&&b_table[4]==0&&card_play==30)
		{
			b_table[4]=card_play;
			points++;
		}
		else
		{
			lives--;
		}
	}
	if(card_play>30&&card_play<41)
	{
		if(y_table[0]==0&&((card_play==31||card_play==32||card_play==33)))
		{
			y_table[0]=card_play;
			points++;
		}
		else if(y_table[0]!=0&&y_table[1]==0&&((card_play==34)||(card_play==35)))
		{
			y_table[1]=card_play;
			points++;
		}
		else if(y_table[0]!=0&&y_table[2]!=0&&y_table[3]==0&&((card_play==36)||(card_play==37)))
		{
			y_table[2]=card_play;
			points++;
		}
		else if(y_table[0]!=0&&y_table[2]!=0&&y_table[1]!=0&&y_table[3]==0&&((card_play==38)||(card_play==39)))
		{
			y_table[3]=card_play;
			points++;
		}
		else if(y_table[0]!=0&&y_table[1]!=0&&y_table[2]!=0&&y_table[3]!=0&&y_table[4]==0&&(card_play==40))
		{
			y_table[4]=card_play;
			points++;
		}
		else
		{
			lives--;
		}
	}
	if(card_play>40&&card_play<51)
	{
		if(w_table[0]==0&&((card_play==41)||(card_play==42)||(card_play==43)))
		{
			w_table[0]=card_play;
			points++;
		}
		else if(w_table[0]!=0&&w_table[1]==0&&((card_play==44)||(card_play==45)))
		{
			w_table[1]=card_play;
			points++;
		}
		else if(w_table[0]!=0&&w_table[2]!=0&&w_table[3]==0&&((card_play==46)||(card_play==47)))
		{
			w_table[2]=card_play;
			points++;
		}
		else if(w_table[0]!=0&&w_table[1]!=0&&w_table[2]!=0&&w_table[3]==0&&((card_play==48)||(card_play==49)))
		{
			w_table[3]=card_play;
			points++;
		}
		else if(w_table[0]!=0&&w_table[1]!=0&&w_table[2]!=0&&w_table[3]!=0&&w_table[4]==0&&(card_play==50))
		{
			w_table[4]=card_play;
			points++;
		}
		else
		{
			lives--;
		}
	}
}
void tips_number()
{
	no_possible=0;
	switch (menu_pos)
	{
		case 1:
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_1[i]-1][0]=='1')
				{
					player_1_info[i][0]='1';
				}
				if(deck_char[player_1[i]-1][0]!='1')
				{
					no_possible++;
				}
			}	
		}
		if (plays==0)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_2[i]-1][0]=='1')
				{
					player_2_info[i][0]='1';
				}
				if(deck_char[player_2[i]-1][0]!='1')
				{
					no_possible++;
				}
			}
		}
		break;
		case 2:
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_1[i]-1][0]!='2')
				{
					no_possible++;
				}
				if(deck_char[player_1[i]-1][0]=='2')
				{
				player_1_info[i][0]='2';
				}
			}
		}	
		if(plays==0)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_2[i]-1][0]!='2')
				{
					no_possible++;
				}
				if(deck_char[player_2[i]-1][0]=='2')
				{
					player_2_info[i][0]='2';
				}
			}
		}
		break;
		case 3:
		for (i=0;i<5;i++)
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_1[i]-1][0]!='3')
				{
					no_possible++;
				}
				if(deck_char[player_1[i]-1][0]=='3')
				{
				player_1_info[i][0]='3';
				}
			}
		}	
		if(plays==0)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_2[i]-1][0]!='3')
				{
					no_possible++;
				}
				if(deck_char[player_2[i]-1][0]=='3')
				{
					player_2_info[i][0]='3';
				}
			}
		}
		break;
		case 4:
		for (i=0;i<5;i++)
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_1[i]-1][0]!='4')
				{
					no_possible++;
				}
				if(deck_char[player_1[i]-1][0]=='4')
				{
				player_1_info[i][0]='4';
				}
			}
		}	
		if(plays==0)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_2[i]-1][0]!='4')
				{
					no_possible++;
				}
				if(deck_char[player_2[i]-1][0]=='4')
				{
					player_2_info[i][0]='4';
				}
			}
		}
		break;
		case 5:
		for (i=0;i<5;i++)
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_1[i]-1][0]!='5')
				{
					no_possible++;
				}
				if(deck_char[player_1[i]-1][0]=='5')
				{
				player_1_info[i][0]='5';
				}
			}
		}	
		if(plays==0)
		{
			for (i=0;i<5;i++)
			{
				if(deck_char[player_2[i]-1][0]!='5')
				{
					no_possible++;
				}
				if(deck_char[player_2[i]-1][0]=='5')
				{
					player_2_info[i][0]='5';
				}
			}
		}
		break;
	}
	if (no_possible==5) 
	{
		gotoxy (63,27);
		printf("Não é possível dar essa dica!");
	}
}
void descarte()
{
	menu_pos--;
if(player_2[menu_pos]==41||player_2[menu_pos]==42||player_2[menu_pos]==43)	discarded_table[0][0]++;
if(player_2[menu_pos]==44||player_2[menu_pos]==45)							discarded_table[0][1]++;
if(player_2[menu_pos]==46||player_2[menu_pos]==47)							discarded_table[0][2]++;
if(player_2[menu_pos]==48||player_2[menu_pos]==49)							discarded_table[0][3]++;
if(player_2[menu_pos]==50)													discarded_table[0][4]++;
if(player_2[menu_pos]==31||player_2[menu_pos]==32||player_2[menu_pos]==33)	discarded_table[1][0]++;
if(player_2[menu_pos]==34||player_2[menu_pos]==34)							discarded_table[1][1]++;
if(player_2[menu_pos]==36||player_2[menu_pos]==37)							discarded_table[1][2]++;
if(player_2[menu_pos]==38||player_2[menu_pos]==39)							discarded_table[1][3]++;
if(player_2[menu_pos]==40)													discarded_table[1][4]++;
if(player_2[menu_pos]==21||player_2[menu_pos]==22||player_2[menu_pos]==23)	discarded_table[2][0]++;
if(player_2[menu_pos]==24||player_2[menu_pos]==25)							discarded_table[2][1]++;
if(player_2[menu_pos]==26||player_2[menu_pos]==27)							discarded_table[2][2]++;
if(player_2[menu_pos]==28||player_2[menu_pos]==29)							discarded_table[2][3]++;
if(player_2[menu_pos]==30)													discarded_table[2][4]++;
if(player_2[menu_pos]==11||player_2[menu_pos]==12||player_2[menu_pos]==13)	discarded_table[3][0]++;
if(player_2[menu_pos]==14||player_2[menu_pos]==15)							discarded_table[3][1]++;
if(player_2[menu_pos]==16||player_2[menu_pos]==17)							discarded_table[3][2]++;
if(player_2[menu_pos]==18||player_2[menu_pos]==19)							discarded_table[3][3]++;
if(player_2[menu_pos]==20)													discarded_table[3][4]++;
if(player_2[menu_pos]==1||player_2[menu_pos]==2||player_2[menu_pos]==3)		discarded_table[4][0]++;
if(player_2[menu_pos]==4||player_2[menu_pos]==5)							discarded_table[4][1]++;
if(player_2[menu_pos]==6||player_2[menu_pos]==7)							discarded_table[4][2]++;
if(player_2[menu_pos]==8||player_2[menu_pos]==9)							discarded_table[4][3]++;
if(player_2[menu_pos]==10)													discarded_table[4][4]++;
if (tips<8) tips++;
player_2[menu_pos]=0;
player_2_info[menu_pos][0]='\0';	
player_2_info[menu_pos][1]='\0';	
hand_filler();			
}
void tips_color()
{	
	no_possible=0;
	gotoxy (63,27);
	switch (color)
	{
		case 'r':
		case 'R':
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if (player_1[i]>0&&player_1[i]<11)
				{
					player_1_info[i][1]='R';
				}
				if (player_1[i]>=11)
				{
					no_possible++;
				}
			}
		}
		if (plays==0)
		{
			for (i=0;i<5;i++)
			{
				if (player_2[i]>0&&player_2[i]<11)
				{
					player_2_info[i][1]='R';
				}
				if (player_2[i]>=11)
				{
					no_possible++;
				}
			}
			tips--;
		}
		if (no_possible==5) 
		{
			printf("Não é possível dar essa dica!");
		}
		break;
		case 'g':
		case 'G':
		if(plays==1)
		{
			for (i=0;i<5;i++)
			{
				if (player_1[i]>10&&player_1[i]<21)
				{
					player_1_info[i][1]='G';
				}
				if (player_1[i]<=10||player_1[i]>=21)
				{
					no_possible++;
				}
			}
		}
		if(plays==0)
		{
			for (i=0;i<5;i++)
			{
				if (player_2[i]>10&&player_2[i]<21)
				{
					player_2_info[i][1]='G';
				}
				if (player_2[i]<=10||player_2[i]>=21)
				{
					no_possible++;
				}
			}
			tips--;
		}
		if (no_possible==5) 
		{
			printf("Não é possível dar essa dica!");
		}
		break;
		case 'b':
		case 'B':
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if (player_1[i]>20&&player_1[i]<31)
				{
					player_1_info[i][1]='B';
				}
				if (player_1[i]<=20||player_1[i]>=31)
				{
						no_possible++;
				}
			}
		}
		if (plays==0)
		{
			for (i=0;i<5;i++)
			{
				if (player_2[i]>20&&player_2[i]<31)
				{
					player_2_info[i][1]='B';
				}
				if (player_2[i]<=20||player_2[i]>=31)
				{
						no_possible++;
				}
			}
			tips--;
		}
		if (no_possible==5) 
		{
			printf("Não é possível dar essa dica!");
		}
		break;
		case 'Y':
		case 'y':
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if (player_1[i]>30&&player_1[i]<41)
				{
					player_1_info[i][1]='Y';			
				}
				if (player_1[i]<=30||player_1[i]>=41)
				{
					no_possible++;
				}
			}
		}
		if (plays==0)
		{
			for (i=0;i<5;i++)
			{
				if (player_2[i]>30&&player_2[i]<41)
				{
					player_2_info[i][1]='Y';			
				}
				if (player_2[i]<=30||player_2[i]>=41)
				{
					no_possible++;
				}
			}
			tips--;
		}
		if (no_possible==5) 
		{
			printf("Não é possível dar essa dica!");
		}
		break;
		case 'W':
		case 'w':
		if (plays==1)
		{
			for (i=0;i<5;i++)
			{
				if (player_1[i]>40&&player_1[i]<51)
				{
					player_1_info[i][1]='W';	
				}
				if (player_1[i]<=40)
				{
					no_possible++;
				}
			}
		}
		if (plays==0)
		{
			for (i=0;i<5;i++)
			{
				if (player_2[i]>40&&player_2[i]<51)
				{
					player_2_info[i][1]='W';	
				}
				if (player_2[i]<=40)
				{
					no_possible++;
				}
			}
			tips--;
		}
		if (no_possible==5) 
		{
			printf("Não é possível dar essa dica!");
		}
		break;
	}
}
char selc_action()
{
	if ((menu=='p')||(menu=='P'))
	{
		do
		{	
			menu_pos=getch();
			menu_pos-=48;		
		}
		while ((menu_pos!=1)&&(menu_pos!=2)&&(menu_pos!=3)&&(menu_pos!=4)&&(menu_pos!=5));
		menu_pos--;
		play();
	}
	if ((menu=='d')||(menu=='D'))
	{
		do
		{	
			menu_pos=getch();
			menu_pos-=48;		
		}
		while ((menu_pos!=1)&&(menu_pos!=2)&&(menu_pos!=3)&&(menu_pos!=4)&&(menu_pos!=5));
		printf(" %i",menu_pos);
		gotoxy (63,28);
		system("pause");
		descarte();
	}   
	if ((menu=='c')||(menu=='C'))
	{
		do
		{
			if (no_possible==5) mensagens();
			do
			{	
				color=getch();
			}
			while ((color!='W')&&(color!='w')&&(color!='b')&&(color!='B')&&(color!='r')&&(color!='R')&&(color!='g')&&(color!='G')&&(color!='y')&&(color!='Y'));
			printf(" %c",color);
			tips_color();
			gotoxy (63,28);
			system("pause");
			gotoxy(0,0);
		}
		while(no_possible==5);
		no_possible=0;
		tips--;
	}
	if ((menu=='n')||(menu=='N'))
	{
		do
		{
			if (no_possible==5) mensagens();
			do
			{	
				menu_pos=getch();
				menu_pos-=48;		
			}
			while ((menu_pos!=1)&&(menu_pos!=2)&&(menu_pos!=3)&&(menu_pos!=4)&&(menu_pos!=5));
			tips_number();
			gotoxy (63,28);
			system("pause");
			gotoxy(0,0);
		}
		while (no_possible==5);
		no_possible=0;
		tips--;
	}
	if ((menu=='s')||(menu=='S'))
	{
		gamesave();
	}	
		if ((menu=='l')||(menu=='L'))		
	{
		menu='m';
	}
}
void deck_reset()											//faz reset ao vetor <int deck>
 {
 	lives=3;
 	tips=8;
	for (i=0;i<50;i++)
	{
		deck[i]=i+1;
	}
	for(i=0;i<5;i++)
	{
		r_table[i]=0;
		g_table[i]=0;
		b_table[i]=0;
		y_table[i]=0;
		w_table[i]=0;	
		for(j=0;j<5;j++)
		{
			discarded_table[i][j]=0;
		}
		player_2_info[i][0]='\0';
		player_1_info[i][0]='\0';
		player_2_info[i][1]='\0';
		player_1_info[i][1]='\0';
	}
	for (i=0;i<16;i++)
	{
		player_name[16]='0';
	}
} 
char delay_control()
{
	do
	{	
		menu=getch();
	}
	while ((menu!=13)&&(menu!='m')&&(menu!='M'));
	return menu;
	system("cls");
}
int starter_def()
{
	srand(time(NULL));
	plays=rand() % 2;
}
void bot_descarte()
{
if(player_1[menu_pos]==41||player_1[menu_pos]==42||player_1[menu_pos]==43)	discarded_table[0][0]++;
if(player_1[menu_pos]==44||player_1[menu_pos]==45)							discarded_table[0][1]++;
if(player_1[menu_pos]==46||player_1[menu_pos]==47)							discarded_table[0][2]++;
if(player_1[menu_pos]==48||player_1[menu_pos]==49)							discarded_table[0][3]++;
if(player_1[menu_pos]==50)													discarded_table[0][4]++;
if(player_1[menu_pos]==31||player_1[menu_pos]==32||player_1[menu_pos]==33)	discarded_table[1][0]++;
if(player_1[menu_pos]==34||player_1[menu_pos]==34)							discarded_table[1][1]++;
if(player_1[menu_pos]==36||player_1[menu_pos]==37)							discarded_table[1][2]++;
if(player_1[menu_pos]==38||player_1[menu_pos]==39)							discarded_table[1][3]++;
if(player_1[menu_pos]==40)													discarded_table[1][4]++;
if(player_1[menu_pos]==21||player_1[menu_pos]==22||player_1[menu_pos]==23)	discarded_table[2][0]++;
if(player_1[menu_pos]==24||player_1[menu_pos]==25)							discarded_table[2][1]++;
if(player_1[menu_pos]==26||player_1[menu_pos]==27)							discarded_table[2][2]++;
if(player_1[menu_pos]==28||player_1[menu_pos]==29)							discarded_table[2][3]++;
if(player_1[menu_pos]==30)													discarded_table[2][4]++;
if(player_1[menu_pos]==11||player_1[menu_pos]==12||player_1[menu_pos]==13)	discarded_table[3][0]++;
if(player_1[menu_pos]==14||player_1[menu_pos]==15)							discarded_table[3][1]++;
if(player_1[menu_pos]==16||player_1[menu_pos]==17)							discarded_table[3][2]++;
if(player_1[menu_pos]==18||player_1[menu_pos]==19)							discarded_table[3][3]++;
if(player_1[menu_pos]==20)													discarded_table[3][4]++;
if(player_1[menu_pos]==1||player_1[menu_pos]==2||player_1[menu_pos]==3)		discarded_table[4][0]++;
if(player_1[menu_pos]==4||player_1[menu_pos]==5)							discarded_table[4][1]++;
if(player_1[menu_pos]==6||player_1[menu_pos]==7)							discarded_table[4][2]++;
if(player_1[menu_pos]==8||player_1[menu_pos]==9)							discarded_table[4][3]++;
if(player_1[menu_pos]==10)													discarded_table[4][4]++;
if (tips<8) tips++;	
player_1[menu_pos]=0;	
player_1_info[menu_pos][0]='\0';	
player_1_info[menu_pos][1]='\0';	
hand_filler();			
}
bot_play()
{
	for (i=0;i<5;i++)
	{
		if (r_table[0]==0&&player_1_info[i][0]=='1'&&player_1_info[i][1]=='R')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (r_table[0]!=0&&r_table[1]==0&&player_1_info[i][0]=='2'&&player_1_info[i][1]=='R')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (r_table[0]!=0&&r_table[1]!=0&&r_table[2]==0&&player_1_info[i][0]=='3'&&player_1_info[i][1]=='R')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (r_table[0]!=0&&r_table[1]!=0&&r_table[2]!=0&&r_table[3]==0&&player_1_info[i][0]=='4'&&player_1_info[i][1]=='R')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (r_table[0]!=0&&r_table[1]!=0&&r_table[2]!=0&&r_table[3]!=0&&r_table[4]==0&&player_1_info[i][0]=='5'&&player_1_info[i][1]=='R')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (g_table[0]==0&&player_1_info[i][0]=='1'&&player_1_info[i][1]=='G')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (g_table[0]!=0&&g_table[1]==0&&player_1_info[i][0]=='2'&&player_1_info[i][1]=='G')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (g_table[0]!=0&&g_table[1]!=0&&g_table[2]==0&&player_1_info[i][0]=='3'&&player_1_info[i][1]=='G')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (g_table[0]!=0&&g_table[1]!=0&&g_table[2]!=0&&g_table[3]==0&&player_1_info[i][0]=='4'&&player_1_info[i][1]=='G')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (g_table[0]!=0&&g_table[1]!=0&&g_table[2]!=0&&g_table[3]!=0&&g_table[4]==0&&player_1_info[i][0]=='5'&&player_1_info[i][1]=='G')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (b_table[0]==0&&player_1_info[i][0]=='1'&&player_1_info[i][1]=='B')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (b_table[0]!=0&&b_table[1]==0&&player_1_info[i][0]=='2'&&player_1_info[i][1]=='B')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (b_table[0]!=0&&b_table[1]!=0&&b_table[2]==0&&player_1_info[i][0]=='3'&&player_1_info[i][1]=='B')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (b_table[0]!=0&&b_table[1]!=0&&b_table[2]!=0&&b_table[3]==0&&player_1_info[i][0]=='4'&&player_1_info[i][1]=='B')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (b_table[0]!=0&&b_table[1]!=0&&b_table[2]!=0&&b_table[3]!=0&&b_table[4]==0&&player_1_info[i][0]=='5'&&player_1_info[i][1]=='B')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (y_table[0]==0&&player_1_info[i][0]=='1'&&player_1_info[i][1]=='Y')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (y_table[0]!=0&&y_table[1]==0&&player_1_info[i][0]=='2'&&player_1_info[i][1]=='Y')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (y_table[0]!=0&&y_table[1]!=0&&y_table[2]==0&&player_1_info[i][0]=='3'&&player_1_info[i][1]=='Y')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (y_table[0]!=0&&y_table[1]!=0&&y_table[2]!=0&&y_table[3]==0&&player_1_info[i][0]=='4'&&player_1_info[i][1]=='Y')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (y_table[0]!=0&&y_table[1]!=0&&y_table[2]!=0&&y_table[3]!=0&&y_table[4]==0&&player_1_info[i][0]=='5'&&player_1_info[i][1]=='Y')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (w_table[0]==0&&player_1_info[i][0]=='1'&&player_1_info[i][1]=='W')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (w_table[0]!=0&&w_table[1]==0&&player_1_info[i][0]=='2'&&player_1_info[i][1]=='W')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (w_table[0]!=0&&w_table[1]!=0&&w_table[2]==0&&player_1_info[i][0]=='3'&&player_1_info[i][1]=='W')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (w_table[0]!=0&&w_table[1]!=0&&w_table[2]!=0&&w_table[3]==0&&player_1_info[i][0]=='4'&&player_1_info[i][1]=='W')
		{
			menu_pos=i;
			play();
			plays=1;
		}
		else if (w_table[0]!=0&&w_table[1]!=0&&w_table[2]!=0&&w_table[3]!=0&&w_table[4]==0&&player_1_info[i][0]=='5'&&player_1_info[i][1]=='W')
		{
			menu_pos=i;
			play();
			plays=1;
		}		
	}
}
void bot_tips()
{
	for (i=0;i<5;i++)
	{
		if ((r_table[0]==0)&&(deck_char[player_2[i]-1][0]=='1')&&(deck_char[player_2[i]-1][1]=='R'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((r_table[0]!=0)&&(r_table[1]==0)&&(deck_char[player_2[i]-1][0]=='2')&&(deck_char[player_2[i]-1][1]=='R'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0')tips_number();
			plays=1;
		}
		else if ((r_table[0]!=0)&&(r_table[1]!=0)&&(r_table[2]==0)&&(deck_char[player_2[i]-1][0]=='3')&&(deck_char[player_2[i]-1][1]=='R'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((r_table[0]!=0)&&(r_table[1]!=0)&&(r_table[2]!=0)&&(r_table[3]==0)&&(deck_char[player_2[i]-1][0]=='4')&&(deck_char[player_2[i]-1][1]=='R'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((r_table[0]!=0)&&(r_table[1]!=0)&&(r_table[2]!=0)&&(r_table[3]!=0)&&(r_table[4]==0)&&(deck_char[player_2[i]-1][0]=='5')&&(deck_char[player_2[i]-1][1]=='R'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((g_table[0]==0)&&(deck_char[player_2[i]-1][0]=='1')&&(deck_char[player_2[i]-1][1]=='G'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((g_table[0]!=0)&&(g_table[1]==0)&&(deck_char[player_2[i]-1][0]=='2')&&(deck_char[player_2[i]-1][1]=='G'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0')tips_number();
			plays=1;
		}
		else if ((g_table[0]!=0)&&(g_table[1]!=0)&&(g_table[2]==0)&&(deck_char[player_2[i]-1][0]=='3')&&(deck_char[player_2[i]-1][1]=='G'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((g_table[0]!=0)&&(g_table[1]!=0)&&(g_table[2]!=0)&&(g_table[3]==0)&&(deck_char[player_2[i]-1][0]=='4')&&(deck_char[player_2[i]-1][1]=='G'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((g_table[0]!=0)&&(g_table[1]!=0)&&(g_table[2]!=0)&&(g_table[3]!=0)&&(g_table[4]==0)&&(deck_char[player_2[i]-1][0]=='5')&&(deck_char[player_2[i]-1][1]=='G'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((b_table[0]==0)&&(deck_char[player_2[i]-1][0]=='1')&&(deck_char[player_2[i]-1][1]=='B'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((b_table[0]!=0)&&(b_table[1]==0)&&(deck_char[player_2[i]-1][0]=='2')&&(deck_char[player_2[i]-1][1]=='B'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0')tips_number();
			plays=1;
		}
		else if ((b_table[0]!=0)&&(b_table[1]!=0)&&(b_table[2]==0)&&(deck_char[player_2[i]-1][0]=='3')&&(deck_char[player_2[i]-1][1]=='B'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((b_table[0]!=0)&&(b_table[1]!=0)&&(b_table[2]!=0)&&(b_table[3]==0)&&(deck_char[player_2[i]-1][0]=='4')&&(deck_char[player_2[i]-1][1]=='B'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((b_table[0]!=0)&&(b_table[1]!=0)&&(b_table[2]!=0)&&(b_table[3]!=0)&&(b_table[4]==0)&&(deck_char[player_2[i]-1][0]=='5')&&(deck_char[player_2[i]-1][1]=='B'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((y_table[0]==0)&&(deck_char[player_2[i]-1][0]=='1')&&(deck_char[player_2[i]-1][1]=='Y'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((y_table[0]!=0)&&(y_table[1]==0)&&(deck_char[player_2[i]-1][0]=='2')&&(deck_char[player_2[i]-1][1]=='Y'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0')tips_number();
			plays=1;
		}
		else if ((y_table[0]!=0)&&(y_table[1]!=0)&&(y_table[2]==0)&&(deck_char[player_2[i]-1][0]=='3')&&(deck_char[player_2[i]-1][1]=='Y'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((y_table[0]!=0)&&(y_table[1]!=0)&&(y_table[2]!=0)&&(y_table[3]==0)&&(deck_char[player_2[i]-1][0]=='4')&&(deck_char[player_2[i]-1][1]=='Y'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((y_table[0]!=0)&&(y_table[1]!=0)&&(y_table[2]!=0)&&(y_table[3]!=0)&&(y_table[4]==0)&&(deck_char[player_2[i]-1][0]=='5')&&(deck_char[player_2[i]-1][1]=='Y'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((w_table[0]==0)&&(deck_char[player_2[i]-1][0]=='1')&&(deck_char[player_2[i]-1][1]=='W'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((w_table[0]!=0)&&(w_table[1]==0)&&(deck_char[player_2[i]-1][0]=='2')&&(deck_char[player_2[i]-1][1]=='W'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0')tips_number();
			plays=1;
		}
		else if ((w_table[0]!=0)&&(w_table[1]!=0)&&(w_table[2]==0)&&(deck_char[player_2[i]-1][0]=='3')&&(deck_char[player_2[i]-1][1]=='W'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((w_table[0]!=0)&&(w_table[1]!=0)&&(w_table[2]!=0)&&(r_table[3]==0)&&(deck_char[player_2[i]-1][0]=='4')&&(deck_char[player_2[i]-1][1]=='W'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
		else if ((w_table[0]!=0)&&(w_table[1]!=0)&&(w_table[2]!=0)&&(w_table[3]!=0)&&(r_table[4]==0)&&(deck_char[player_2[i]-1][0]=='5')&&(deck_char[player_2[i]-1][1]=='W'))
		{
			menu_pos=i;
			if (player_2_info[i][0]=='\0') tips_number();
			plays=1;
		}
	}
}
void bot_play_full_table()
{
	if(r_table[0]==0&&(g_table[0]==0)&&b_table[0]==0&&y_table[0]==0&&w_table[0]==0)
	{
    	for(i=1;i<5;i++)
    	{
        	if(player_1_info[i][0]='1')
        	{
        	    menu_pos=i;
        	    play();
        	    plays=1;
        	    break;
        	}
    	}
    	if(plays==1)
    	{
    		exit;
		}
	}else if(r_table[1]==0&&g_table[1]==0&&b_table[1]==0&&y_table[1]==0&&w_table[1]==0) 
	{
    	for(i=1;i<5;i++)
    	{
        	if(player_1_info[i][0]='2')
        	{
        	    menu_pos=i;
        	    play();
        	    plays=1;
        	    break;
        	}
    	}
    	if(plays==1)
    	{
    		exit;
		}
	}else if(r_table[2]==0&&g_table[2]==0&&b_table[2]==0&&y_table[2]==0&&w_table[2]==0) 
	{
    	for(i=1;i<5;i++)
    	{
        	if(player_1_info[i][0]='3')
        	{
            	menu_pos=i;
            	play();
           		plays=1;
           		break;
        	}
    	}
    	if(plays==1)
    	{
    		exit;
		}
	}else if(r_table[3]==0&&g_table[3]==0&&b_table[3]==0&&y_table[3]==0&&w_table[3]==0) 
	{
    	for(i=1;i<5;i++)
    	{
        	if(player_1_info[i][0]='4')
        	{
            	menu_pos=i;
           		play();
            	plays=1;
            	break;
       		}
   		}
   		if(plays==1)
    	{
    		exit;
		}
	}else if(r_table[4]==0&&g_table[4]==0&&b_table[4]==0&&y_table[4]==0&&w_table[4]==0) 
	{
  	  	for(i=1;i<5;i++)
	    {
 	       if(player_1_info[i][0]='5')
 	       {
	            menu_pos=i+1;
  	          	play();
 	           	plays=1;
 	           	break;
			}
		}
	}
	if(plays==1)
    	{
    		exit;
		}
}
void bot_play_descarte()
{
	int descartar=0,j;
	for(i=0;i<5;i++)
	{
		for (j=0;j<5;j++)
		{
			if (deck_char[r_table[i]-1][0]==player_1_info[j][0]&&deck_char[r_table[i]-1][1]==player_1_info[j][1]) 
			{
				descartar=1;
			}
			if (descartar==1) break;
			if (deck_char[g_table[i]-1][0]==player_1_info[j][0]&&deck_char[r_table[i]-1][1]==player_1_info[j][1]) 
			{
				descartar=1;
			}
			if (descartar==1) break;
			if (deck_char[b_table[i]-1][0]==player_1_info[j][0]&&deck_char[r_table[i]-1][1]==player_1_info[j][1]) 
			{
				descartar=1;
			}
			if (descartar==1) break;
			if (deck_char[y_table[i]-1][0]==player_1_info[j][0]&&deck_char[r_table[i]-1][1]==player_1_info[j][1]) 
			{
				descartar=1;
			}
			if (descartar==1) break;
			if (deck_char[w_table[i]-1][0]==player_1_info[j][0]&&deck_char[r_table[i]-1][1]==player_1_info[j][1]) 
			{
				descartar=1;
			}
			if (descartar==1) break;
		}
		if (descartar==1) break;
	}
	if (descartar==1) 
	{
		plays=1;
		menu_pos=i+1;
		bot_descarte();
		hand_filler();
	}
}
void pilha_cheia()
{
    if(r_table[4]!=0)
    {
        for (i=0;i<5;i++)
        {
            if(player_1_info[i][1]='r')
         {
             menu_pos=i;
             bot_descarte();
             plays=1;
             break;
         }
        }
    }
    else if(g_table[4]!=0)
    {
        for (i=0;i<5;i++)
        {
            if(player_1_info[i][1]='r')
         {
             menu_pos=i;
             bot_descarte();
             plays=1;
             break;
         }
        }
    }
    else if(b_table[4]!=0)
    {
        for (i=0;i<5;i++)
        {
            if(player_1_info[i][1]='r')
         	{
             menu_pos=i;
             bot_descarte();
             plays=1;
             break;
         	}
        }
    }
    else if(y_table[4]!=0)
    {
        for (i=0;i<5;i++)
        {
            if(player_1_info[i][1]='r')
         	{
             	menu_pos=i;
             	bot_descarte();
             	plays=1;
            	 break;
         	}
        }
    }
    else if(w_table[4]!=0)
    {
        for (i=0;i<5;i++)
        {
            if(player_1_info[i][1]='r')
         	{
             menu_pos=i;
             bot_descarte();
             plays=1;
             break;
         	}
        }
    }
}
void bot_gameplay()
{
	menu_pos=3;
	play();
//	bot_descarte();
//	tips_number();
//	color='W';
//	tips_color();
//		plays=0;
//		bot_play();
//		if(plays==1) exit;
//		else 
//		{
//			menu_pos=rand()%5+1;
//			bot_descarte();
//		}
}
void game_repeater()
{
	game_table();
	starter_def();
	starter_view();
	system("pause");
	
	msg_box();
	msg_inicial();
	do
	{
		if (plays==0)
		{
			game_table();
			clear_msgbox();
			bot_gameplay();
			hand_filler();		
			game_table();
			plays=1;
		} 
		if(plays==1)
		{
			game_table();
			clear_msgbox();
			mensagem_selec();
			Keys_menu();
			if (menu=='m') break;
			mensagens();
			selc_action();
			hand_filler();
			game_table();
			gotoxy(0,55);
			system("pause");
			plays=0;
		}
		if (menu=='m') 
		{
			menu='0';
			break;
		}
	}
	while((player_1[0]!=0&&player_1[1]!=0&&player_1[2]!=0&&player_1[3]!=0&&player_1[4]!=0&&deck_taken==50&&player_2[0]!=0&&player_2[1]!=0&&player_2[2]!=0&&player_2[3]!=0&&player_2[4]!=0)||(lives!=0));
}

#endif
