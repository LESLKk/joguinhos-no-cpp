#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
//---------------[EVENTOS]------------------//
int game();
int bets();

//---------------[GLOBAIS]------------------//
int key,players = 1,lifes = 1,prize,end;
int money[10]{0};
int bet[10]{2};
HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	//---------------------------------------------[tela inicial]------------------------------------------------//
	
	char frase[50] = "Buckshot roullete";//uma frase pra escrever aos poucos quando eu quiser
	
	printf("		");
	for (int i = 0; frase[i] != '\0'; i++) 
	{
        printf("%c", frase[i]);
        fflush(stdout);  // Garante que o caractere seja impresso imediatamente
        Sleep(100);      // Pausa de 100 milissegundos entre cada caractere
    }
    printf("\n\n\n\n		     [jogar]");
    
    do
	{
		key = getch();	
	}while(key != 13);
	system("cls");
	for(int r = 0;r<3;)
	{
		printf("----------[configura%c%ces de jogo]----------\n",135,228);
		printf("\nplayers:%c[%d]%c",17,players,16);
		printf("\ndinheiro:R$%d",money[0]);
		printf("\nvidas:%c[%d]%c",17,lifes,16);
		
		switch(r)
		{
			case 0:
				printf("\033[3;11H");
				key = getch();
				switch(key)
				{
					case 'd':players==9?:players++;
						break;
						
					case 'a':players==1?:players--;
						break;
						
					case 13:r++;
						break;
				}
			break;
			
			case 1:
				do
				{
					printf("\033[4;12H");
					scanf("%d",&money[0]);
				}while(money[0]<1);
				
				for(int p = 1;p<=players;p++)
				{
					money[p] = money[0];
				}
				r++;
			break;
			
			case 2:
				printf("\033[5;9H");
				key = getch();
				switch(key)
				{
					case 'd':lifes==9?:lifes++;
						break;
						
					case 'a':lifes==1?:lifes--;
						break;
						
					case 13:r++;
						break;
				}
			break;
		}
		
		system("cls");
	}
	
	game();
}
//--------------------------[jogo]---------------------------------//

int game()
{
	do
	{
		
	}while(end == 1);
}

//-------------------------[apostas]-------------------------------//

int bets()
{
	for(int p = 1;p<=players;p++)
	{
		printf("narrador:\"jogador %d, fa%ca a sua aposta, ela deve ser maior que a metade da aposta anterior\"",p,135);
		printf("seu saldo:%d",money[p]);
		printf("\n\naposta:R$");
		do
		{
			printf("\033[3;10H");
			scanf("%d",&bet[p]);
		}while(bet[p]<bet[p-1]/2 && bet[p]>money[p]);
		prize+=bet[p];
		system("cls");
	}
}
