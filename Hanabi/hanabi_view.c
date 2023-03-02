#ifndef _hanabi_view_ 
#define _hanabi_view_
#include <stdio.h>
#include "lab.h"
#include "hanabi_model.h"
#include <time.h>
#include <locale.h>
#define PLAYX 50
#define PLAYY 14
#define RULESX 50
#define RULESY 20
#define LEAVEX 50
#define LEAVEY 23
#define MENUX 40
#define MENUY 11
#define LOADX 50
#define LOADY 17
#define CARDL 19
#define CARDA 2
#define CARDZ 40
#define CARDN 2
#define ACOESX 70
#define ACOESY 20
#define CARDC 54
#define CARDD 4
#define MSGX 60
#define MSGY 25


#define PLAYER1HX 10
#define PLAYER1HY 1

#define PLAYER2HX 10
#define PLAYER2HY 20

#define TABLEX  10
#define TABLEY 	10

#define DECKX 60
#define DECKY 1

#define TIPSX 90
#define TIPSY 10

#define LIVESX 90
#define LIVESY 3

#define DISCARDX 
#define DISCARDY 

#define CARDW 6		
#define CARDH 4

#define GAP 2
#include <stdio.h>
#include <stdlib.h>

# define INSTRUCTION_HEADER_WIDTH 100
# define INSTRUCTION_HEADER_HEIGHT 3
# define CONSOLE_HEIGHT 20

#define MY_COLOR_BLACK			0
#define MY_COLOR_DARK_BLUE		1
#define MY_COLOR_SOFT_GREEN		2
#define MY_COLOR_SOFT_BLUE		3
#define MY_COLOR_DARK_RED		4
#define MY_COLOR_PURPLE			5
#define MY_COLOR_DARK_YELLOW	6
#define MY_COLOR_GRAY			7
#define MY_COLOR_DARK_GRAY		8
#define MY_COLOR_CYAN			9
#define MY_COLOR_LIGHT_GREEN	10
#define MY_COLOR_LIGHT_BLUE		11
#define MY_COLOR_LIGHT_RED		12
#define MY_COLOR_PINK			13
#define MY_COLOR_LIGHT_YELLOW	14
#define MY_COLOR_WHITE			15

void delay(float secs) 												//função de delay
{
	if (NO_DELAY==1)
	{
		goto a;
	}
    int m_secs = 1000 * secs; 
    clock_t start_time = clock(); 
    while (clock() < start_time + m_secs); 
    a:
    return;
} 
void print_gametable()
{
	gotoxy(0,100);
	for (i=0;i<5;i++)
	{
		if(i==0) printf("R_table: ");
		printf("%i ",r_table[i]);
		if(i==5) printf("\n");
	}
		for (i=0;i<5;i++)
	{
		if(i==0) printf("G_table: ");
		printf("%i ",g_table[i]);
		if(i==5) printf("\n");
	}
		for (i=0;i<5;i++)
	{ 
		if(i==0) printf("B_table: ");
		printf("%i ",b_table[i]);
		if(i==5) printf("\n");
	}
		for (i=0;i<5;i++)
	{
		if(i==0) printf("Y_table: ");
		printf("%i ",y_table[i]);
		if(i==5) printf("\n");
	}
		for (i=0;i<5;i++)
	{
		if(i==0) printf("W_table:");
		printf("%i ",w_table[i]);
		if(i==5) printf("\n");
	}
}
void print_hands()											//FUNÇÃO TESTE 
{															//Da printf ambas as mãos dos players 
	int i;
    printf("\n\n PLAYER 1:");
    for(i=0;i<5;i++)
        {
        	printf("%s ",deck_char[player_1[i]-1]);
        }
    printf("\n\n PLAYER 2:");
    for(i=0;i<5;i++)
        {
        	printf("%s ",deck_char[player_2[i]-1]);
        }
    printf("\n");
	printf("\n");
	printf("\n");
}
void print_deck()											//FUNÇÃO TESTE
{															//Imprime o baralho utilizando o <int deck> baralhado como ordem do vetor <char deck_char>
	printf("\n\n");
	int i,n;
	for (i=0;i<DECK_SIZE;i++)
	{
		printf("%s ",deck_char[deck[i]-1]);
		if (i==9||i==19||i==29||i==39||i==49)
		{
			printf("\n");
			printf("\n");
		}
	}
	printf("\n");
	printf("\n");
}
void intructionsheader()
{
	// Limpa o ecra e cores
	system("cls");
	resetColor();
	
	// Desenha o rectangulo e escreve o titulo
	showRectAt(0, 0, INSTRUCTION_HEADER_WIDTH, INSTRUCTION_HEADER_HEIGHT);
	printfAt(INSTRUCTION_HEADER_WIDTH/2 -6 , INSTRUCTION_HEADER_HEIGHT/2 +1 , "INSTRUCOES");
	gotoxy(0,INSTRUCTION_HEADER_HEIGHT+1);														// Posicionamos o cursor depois do retangulo		
}
void viewinstructions()	
{
	intructionsheader();
	
	// Imprime instrucoes de um ficheiro...
	FILE *fptr;
	char c;
	int column_counter = 0;
	int line_counter = 0;
	
	fptr = fopen("instructions_pt.txt", "r"); 			// este ficheiro de texto esta na mesma pasta que o codigo
	
	
	
	c = fgetc(fptr); 									// Obtem o primeiro caracter do ficheiro
    while (c != EOF) 									// Imprime o ficheiro caracter a caracter
    {
    	delay (0.01);
        printf ("%c", c); 								// imprime o caracter actual
		column_counter++; 								// para sabermos em que coluna vamos
		
		
		
		if(c == '\n'){									// reset ao contador no inicio de linha do ficheiro
			column_counter = 0;							
			line_counter++;								// incrementa contador de linhas
		}
		
		if(column_counter == INSTRUCTION_HEADER_WIDTH){ // se vamos sair do ecra por causa de linha grande
			printf("\n");								// salta de linha
			column_counter = 0;						    // faz reset ao contador de colunas
			line_counter++;       						// incrementa contador de linhas
		}
		
		if (line_counter == CONSOLE_HEIGHT){			// refresh ecra 
			puts("\nPress ENTER Key to Continue");
			getch();
			intructionsheader();						// reescreve o cabecalho
			line_counter = 0;							// reanicializa o contador de linhas
		}
        c = fgetc(fptr);								// obtem proximo caracter do ficheiro
    } 
    fclose(fptr);
	
	
	puts("\nPress ENTER Key to Continue");
	getch();
	system("cls");							// limpa o ecra para desenhar o menu 
}
void viewintro()							// Escreve o o nome de que realizou o trabalho numa determinada posição 
{
	gotoxy(93,22);
	delay(0.5);
	printf("realizado pelos alunos:");
	gotoxy(93,23);
	delay(0.5);
	printf("Claudia Silva n:70759");
	delay(0.5);
	gotoxy(93,24);
	printf("Pedro Barroso n:71134");
	gotoxy(93,25);
	delay(0.5);
	printf("Aurea Laranja n:70790");
	delay(0.5);
}
void viewplayer1h (void)								//desenha e mostra as cartas do player 1 (Computadar)
{
	int i;
	delay(0.1);
	gotoxy (PLAYER1HX,PLAYER1HY-1); 					//escreve computador acima das cartas do BOT de modo ao utilizador saber que são as cartas do outro jogador
	printf ("COMPUTER");						
	for (i=0; i<5; i++)									
	{
		switch (deck_char[player_1[i]-1][1])				//ve que letra que esta na segunda posição do vector nas posições <char deck_char[player_1[i]-1][1]>
		{													//estas posições que varia de acordo com o i são as 5 cartas do player_1 (computador)
			case'B':
			setColor(1,0);
			break;
			case'W':
			setColor(15,0);
			break;
			case'G':										//define uma cor depedendo da cor das cartas que o deck do computador tem
			setColor(10,0);
			break;
			case'R':
			setColor(4,0);
			break;
			case'Y':
			setColor(6,0);
			break;
		}
		delay(0.1);
		showRectAt (PLAYER1HX+(i*(CARDW+GAP)), PLAYER1HY, CARDW, CARDH);							//desenha as 5 cartas do Bot 
		printfAt (PLAYER1HX+(i*(CARDW+GAP))+2, PLAYER1HY+2, deck_char[player_1[i]-1]);				//com o numero e cor de cada
		resetColor();
	}
	
}
void viewplayer1h_info (void)								//desenha e mostra as cartas do player 1 (Computadar)
{
	int i,k;				
	for (i=0; i<5; i++)									
	{
		switch (player_1_info[i][1])				//ve que letra que esta na segunda posição do vector nas posições <char deck_char[player_1[i]-1][1]>
		{													//estas posições que varia de acordo com o i são as 5 cartas do player_1 (computador)
			case'B':
			setColor(1,0);
			break;
			case'W':
			setColor(15,0);
			break;
			case'G':										//define uma cor depedendo da cor das cartas que o deck do computador tem
			setColor(10,0);
			break;
			case'R':
			setColor(4,0);
			break;
			case'Y':
			setColor(6,0);
			break;
		}
		delay(0.1);
		gotoxy(PLAYER1HX+(i*(CARDW+GAP))+2,PLAYER1HY+3);
		printf("%c",player_1_info[i][0]);
		gotoxy(PLAYER1HX+(i*(CARDW+GAP))+3,PLAYER1HY+3);
		printf("%c",player_1_info[i][1]);			//com o numero e cor de cada
		resetColor();
	}
}
void viewplayer2h (void)																			
{
	int i;
	delay(0.1);
	gotoxy (PLAYER2HX,PLAYER2HY-6);												// Escreve o nome do jogador previamente escollhido
	printf ("%s",player_name);
	for (i=0; i<5; i++)									
	{
		switch (player_2_info[i][1])				//ve que letra que esta na segunda posição do vector nas posições <char deck_char[player_1[i]-1][1]>
		{													//estas posições que varia de acordo com o i são as 5 cartas do player_1 (computador)
			case'B':
			setColor(1,0);
			break;
			case'W':
			setColor(15,0);
			break;
			case'G':										//define uma cor depedendo da cor das cartas que o deck do computador tem
			setColor(10,0);
			break;
			case'R':
			setColor(4,0);
			break;
			case'Y':
			setColor(6,0);
			break;
		}
		delay(0.1);
		showRectAt (PLAYER2HX+(i*(CARDW+GAP)),PLAYER2HY-5,CARDW,CARDH);							//desenha as cartas do untilizador (so as bordas, sem que este veja quais sao)
		gotoxy(PLAYER2HX+(i*(CARDW+GAP))+3,PLAYER2HY+2-5);
		printf("%c",player_2_info[i][1]);
		gotoxy(PLAYER2HX+(i*(CARDW+GAP))+2,PLAYER2HY+2-5);
		printf("%c",player_2_info[i][0]);
		resetColor();
	}
}
void viewtable (void)				
{
	char table;
	int i,j;
	delay(0.1);
	gotoxy (TABLEX,TABLEY-3);													//escreve Table (que representa a mesa de jogo)
	printf ("TABLE");															
	for (i=0; i<5;i++)
	{
		switch (i)
		{
			case 2:
			setColor(1,0);
			showRectAt (TABLEX+(i*(CARDW+GAP)),TABLEY-2,CARDW,CARDH);										//deseja os 5 lugares para cada cor de jogo 
			for (j=0;j<5;j++)
			{
				if (b_table[j]!=0) printfAt (TABLEX+(i*(CARDW+GAP))+2,TABLEY, deck_char[b_table[j]-1]);
			}
			break;
			case 0:
			setColor(15,0);
			showRectAt (TABLEX+(i*(CARDW+GAP)),TABLEY-2,CARDW,CARDH);										//deseja os 5 lugares para cada cor de jogo 
			for (j=0;j<5;j++)
			{
				if (w_table[j]!=0) printfAt (TABLEX+(i*(CARDW+GAP))+2,TABLEY, deck_char[w_table[j]-1]);
			}
			break;
			case 3:										//define uma cor diferente para cada carta da mesa de jogo
			setColor(10,0);
			showRectAt (TABLEX+(i*(CARDW+GAP)),TABLEY-2,CARDW,CARDH);										//deseja os 5 lugares para cada cor de jogo 
			for (j=0;j<5;j++)
			{
				if (g_table[j]!=0) printfAt (TABLEX+(i*(CARDW+GAP))+2,TABLEY, deck_char[g_table[j]-1]);
			}
			break;
			case 4:
			setColor(4,0);
			showRectAt (TABLEX+(i*(CARDW+GAP)),TABLEY-2,CARDW,CARDH);										//deseja os 5 lugares para cada cor de jogo 
			for (j=0;j<5;j++)
			{
				if (r_table[j]!=0) printfAt (TABLEX+(i*(CARDW+GAP))+2,TABLEY, deck_char[r_table[j]-1]);
			}
			break;
			case 1:
			setColor(6,0);
			showRectAt (TABLEX+(i*(CARDW+GAP)),TABLEY-2,CARDW,CARDH);										//deseja os 5 lugares para cada cor de jogo 
			for (j=0;j<5;j++)
			{
				if (y_table[j]!=0) printfAt (TABLEX+(i*(CARDW+GAP))+2,TABLEY, deck_char[y_table[j]-1]);
			}
			break;
		}
	delay(0.1);
	resetColor();																								//da reset as cores
	}
}
void viewdeck (void)															
{
	printfAt (DECKX+2,DECKY+2,"  ");
	char buf[5];
	itoa(decksize(deck,50),buf,10);												//transforma o que retorna da função decksize que é um inteiro numa string 							
	showRectAt (DECKX,DECKY,CARDW,CARDH);										//desenha um retandulo
	printfAt (DECKX+2,DECKY+2,buf);												//print da string que foi guardada no buf
	gotoxy (DECKX,DECKY-1);
	printf ("DECK");															//da print de 'DECK'
}
void viewlives (void)															//mostra as vidas restantes 
{
	
	int i;
	gotoxy (LIVESX,LIVESY);
	delay(0.1);
	setColor(4,0);																//define aa cor para da letra para vermelho
	printf ("Lives:%i",lives);
	resetColor();
}
void settings()																	//função que desenha a caixa de saida do jogo (LEAVE) do menu principal
{
int i;
	setColor(5,0);															//define a cor da letra para verde
	showRectAt (LEAVEX,LEAVEY+3,CARDL,CARDA);									//desenha um retangulo
	gotoxy (56,27);																//escreve '5-SETTINGS' dentro dentro do retangulo 
	printf ("5-SETTINGS");		
	resetColor();																//reset da cor da letra para branco
}
void viewtips (void)															//mostra as dicas restantes 
{
	int i;
	gotoxy (LIVESX,LIVESY+1);
	delay(0.1);
	setColor(1,0);																//define aa cor para da letra para azul
	printf ("Tips:%i",tips);
	resetColor();
}
void viewpoints (void)															//mostra as dicas restantes 
{
	int i;
	gotoxy (LIVESX,LIVESY+2);
	delay(0.1);
	setColor(1,0);																//define aa cor para da letra para azul
	printf ("Points:%i",points);
	resetColor();
}
void play1()																	//função que desenha a caixa de 'NEW GAME' do menu principal
{
int i;
	setColor(1,0);																//define a cor da letra para vermelho
	showRectAt (PLAYX,PLAYY,CARDL,CARDA);										//desenha um retangulo
	gotoxy (56,15);																//escreve '1-NEW GAME' dentro dentro do retangulo 
	printf ("1-NEW GAME");															
	resetColor();																//reset da cor da letra para branco
}
void rules1()																	//função que desenha a caixa de regras do menu principal
{
int i;																	
     setColor(6,0);																//define a cor da letra para amarelo	
		showRectAt (RULESX,RULESY,CARDL,CARDA);									//desenha um retangulo
	gotoxy (56,21);																//escreve '3-RULES' dentro dentro do retangulo 
	printf ("3-RULES");
	resetColor();																//reset da cor da letra para branco
}
void leave1()																	//função que desenha a caixa de saida do jogo (LEAVE) do menu principal
{
int i;
		setColor(10,0);															//define a cor da letra para verde
		showRectAt (LEAVEX,LEAVEY,CARDL,CARDA);									//desenha um retangulo
	gotoxy (56,24);																//escreve '4-Leave' dentro dentro do retangulo 
	printf ("4-LEAVE");		
	resetColor();																//reset da cor da letra para branco
}
void menu1()																	//função que desenha a caixa de Menu do menu principal
{
int i;
		showRectAt (MENUX,MENUY,CARDZ,CARDN);									//desenha um retangulo
	gotoxy (58,12);																//escreve 'Menu' dentro dentro do retangulo 
	printf ("MENU");
} 
void load1()																	//função que desenha a caixa de load do menu principal
{
	setColor(4,0);																//define a cor da letra para vermelho	
		showRectAt (LOADX,LOADY,CARDL,CARDA);									//desenha um retangulo 
	
	gotoxy (56,18);
	printf ("2-LOAD GAME");														//escreve '2-LOAD GAME' dentro do retangulo
	resetColor();																//reset da cor da letra para branco
}
void titulo()																	//escreve HANABI no MENU principal
{
 setForeColor(4);																//define a cor para vermelho 
	printf("\n\n	**** 	****           ***            ****       ***           ***            *********      **************\n");
	printf("	****  	****          ******         *** **      ***          ******          ***    ***           **\n");
	printf("	****    ****        **     **        ***   **    ***        **     **         ***    ***           **\n");
	printf("	************       ***     ***       ***    **   ***       ***     ***        ********             **\n");
	printf("	****  	****      *************      ***     **  ***      *************       ***    ***           **\n");
	printf("	****  	****     ***         ***     ***      ******      ***        ***      ***    ***           **\n"); 
	printf("	****  	****     ***         ***     ***       ****       ***        ***      *********      **************\n");
	resetColor();
gotoxy (8,27);
}
void menu_all()																	//função que chama todos os elementos do MENU principal
{
	titulo();		
	delay(0.5);
	menu1();
	delay(0.5);
	play1();
	delay(0.5);
	load1();	
	delay(0.5);
	rules1();
	delay(0.5);
	leave1();
	delay(0.5);
	settings();
	delay(0.5);
	viewintro();
}
void end()																		//animação foguetes
{
	int i,j,k,n,p,c;
	setlocale(LC_ALL, "C");
	for(j=0;j<10;j++)															//for para 10 foguetes
	{
		n=rand()%120;
		if (n<10) n=n+20;
		if (n>100) n=n-20;
		setColor(15,0);
		for(i=0;i<20;i++)														//ciclo for para o movimento vertical do caracter 186 do ASCII
			{
				system("cls");
				gotoxy(n,30-i);
				printf("%c",186);
				delay(0.001);
				if (i==19)for(k=1;k<5;k++)										//na ultima vez do ciclo cuja variavel de contagem é o 'i' (ou seja o ponto mais alto dofoguete)
				{																//ocorre a explosão que se espalha nas 8 direções escritas abaixo
					if (k==1)
					{
						c=rand()%15;											//seleçao de cor aleatoria da explosão
						setColor(c,0);
					}
					gotoxy(n,30-1-i);
					if (i==0) printf("*");
					gotoxy(n,30-1-i-k); //cima
					printf("*");
					gotoxy(n,30-1-i+k); //baixo
					printf("*");
					gotoxy(n-2*k,30-1-i); //esquerda 
					printf("*");
					gotoxy(n+2*k,30-1-i); //direita
					printf("*");
					gotoxy(n-2*k,30-1-i-k); //superior esquerdo
					printf("*");
					gotoxy(n+2*k,30-1-i-k); //superior direito
					printf("*");
					gotoxy(n-2*k,30-1-i+k); //inferior esquerdo
					printf("*");
					gotoxy(n+2*k,30-1-i+k); //inferior direito
					printf("*");
					delay(0.25);	
				} 
			}
		if (j==9)
		{
			system("cls"); 
			printf("Obrigado por jogar!");										//Mensagem final
		}	
	}

}
void viewacoes()																//interface de ações possiveis ao utilizador 
{
	gotoxy(70,20);
	printf("\n    PRESS\n P and (1,2,3,4,5)- to play a card\n D and (1,2,3,4,5) to discard a card\n N and (1,2,3,4,5)- to give a number tip\n C and (W,B,R,G,Y)- to give a color tip\n\n M- to return to MENU\n S- to save and leave the game\n L- to give up");
}
void msg_box()
{	
	showRectAt (MSGX,MSGY,CARDC,CARDD);
	gotoxy (62,24	);
	printf ("MESSAGES:");	
}
void msg_inicial()																		//caixa de mensagens para o utilizador
{

		
	gotoxy (62,26	);
	printf ("The game has began have fun!!!");


}
void lernome_view()																//caixa de mensagem que pede ao utilizador para escolher um nome de jogo
{
	gotoxy(50,10);
	printf("Escolha um nome: \n");
	showRectAt (49,9,17,3);
}
void viewdiscarded()
{
    int j=0,i=0,discarded_start_y,discarded_start_x;
    discarded_start_x = LIVESX;
    discarded_start_y = 16;
    int pos=discarded_start_y-1;
    for(i=0;i<5;i++)
    {
        pos+=1;
        gotoxy(90,pos);
        for(j=0;j<5;j++)
        {
            switch (i)
        {
            case 0:
            setForeColor(15);
            break;
            case 1:
             setForeColor(6);
            break;
            case 2:
            setForeColor(1);
            break;
            case 3 :
            setForeColor(10);
            break;
            case 4:
            setForeColor(4);
            break;
        }
            printf("%d", discarded_table[i][j]);
            printf("  ");
        }
    }
    resetColor();                                                            //para nao afetar retangulo
    showRectAt(discarded_start_x -1, discarded_start_y -1, 15,6 );            //retangulo dos numeros
    printfAt(discarded_start_x -1, discarded_start_y -3, "DISCARD");        //titulo
    printfAt(discarded_start_x, discarded_start_y-2,"1  2  3  4  5");
}
void delay_settings()
{
	system("cls");
	if (NO_DELAY!=1) 
	{
		printf("DELAY_ON");
		printf("\n prima 'ENTER' para DESLIGAR o DELAY.\n Prima m para retornar ao menu.");
	}
	else
	{
		setColor (4,0);
		printf("DELAY_OFF");
		printf("\n prima 'ENTER' para LIGAR o DELAY.\n Prima m para retornar ao menu.");
	}
}
void starter_view()
{
	gotoxy (62,27);
	if (plays==1) printf("it's your turn to play");
	if (plays==0) printf("agora esperas, é lidar");
	//escrever na caixa de msg a dizer quem ganhou o sorteio
}
void clear_msgbox()
{
    int i;
    int j;
    for (i=26;i<29;i++)
    {
        for (j=62;j<114;j++)
        {
            gotoxy(j,i);
            printf(" ");
        }
    }
}
void mensagens()
{
	switch(menu)
	{
		case 'p':
		case 'P':
			clear_msgbox();
			gotoxy (62,26);
			printf( " Escolha o numero da carta que quer jogar:");
		break;
		
		case 'c':
		case 'C':
			clear_msgbox();
			gotoxy (62,26);
			printf(" Escolha a cor que quer dar a dica:");
		break;
		
		case 'n':
		case 'N':
			clear_msgbox();
			gotoxy (62,26);
			printf(" Escolha o numero que quer dar a dica:");
		break;
		
		case 'd':
		case 'D':
			clear_msgbox();
			gotoxy (62,26);
			printf(" Escolha o numero da carta que quer descartar:");
		break;
	}
}
void mensagem_selec()
{
	gotoxy (62,27);
	printf("selecione uma opcao do menu:");
}
void game_table()
{
	system("cls");
	gotoxy(60,10);
	printf("plays: %i",plays);
	gotoxy(0,35);
	print_hands();
	gotoxy(0,40);
	print_deck();
	msg_box();
	viewdiscarded ();
	viewacoes();
	viewplayer1h();
	viewplayer1h_info();
	viewtable ();
	viewplayer2h();
	viewdeck();
	viewlives();
	viewtips();
	viewpoints();
	print_gametable();
	gotoxy(0,55);
	system("pause");
}
#endif
