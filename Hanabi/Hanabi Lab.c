#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>
#include "hanabi_model.h"
#include "hanabi_controller.c"
#include "hanabi_view.c"
#include "lab.h"
					//NOTA: CASO DESEJE DESABILITAR A FUNÇÃO DE DELAY PERMANENTEMENTE DEFINA A VARIAVEL <NO_DELAY> COMO 1
void main(void)			
{
	a:
	deck_reset();	//utilizado caso o utilizador volte ao menu principal e volte a criar um jogo novo o deck nao tem cartas em falta 
	system("cls");
	menu_all();
	menu_control();
	system("cls");
		if (menu_p=='1')
		{
			lernome_view();
			lernome();
			shuffle_deck();
			gotoxy(0,100);
			print_hands();
			gotoxy(0,110);
			print_deck();
			gotoxy(0,125);
			system("pause");
			deal();
			gotoxy(0,35);
			print_hands();
			gotoxy(0,40);
			print_deck();
			gotoxy(0,55);
			system("pause");
			game_table();
			game_repeater();
			if (menu=='m') goto a;
		}
		if (menu_p=='2')
		{
			gameload();
			game_repeater();
			if (menu=='m') goto a;
		}
		if (menu_p=='3')
		{
			intructionsheader();
			viewinstructions();
			goto a;
		}
		if (menu_p=='4')
		{
			end();
		}
		if (menu_p=='5')
		{
			delay_settings();
			delay_control();
			if (menu==13)
			{
				if (NO_DELAY==1) NO_DELAY=0;
				else NO_DELAY=1;
			}
			goto a;
		}	
}

