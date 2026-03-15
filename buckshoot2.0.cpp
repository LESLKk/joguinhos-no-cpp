#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
//---------------[EVENTOS]------------------//
int game();
int bets();
int sorteio();
int objs(int p);
int ingame();
int end(int f);
//---------------[GLOBAIS]------------------//
int key,ran,players = 2,prize;

char objetos[11][20]{
"",
"serra",
"pilula",
"algema",
"seila",
"c",
"s",
"d",
"f",
"g",
"h"
};
int obj[10][8]{0};
int lifes[10]{1};
int money[10]{0};
int bet[10]{2};

int balas[8]{0};
int quant,verm;

int opc = 0;
bool sort[10] = {false};

char frase[50] = "Buckshot roullete";//uma frase pra escrever aos poucos quando eu quiser

HANDLE hc = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	//---------------------------------------------[tela inicial]------------------------------------------------//
	
	
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
		printf("\nvidas:%c[%d]%c",17,lifes[0],16);
		
		switch(r)
		{
			case 0:
				printf("\033[3;11H");
				key = getch();
				switch(key)
				{
					case 'd':players==9?:players++;
						break;
						
					case 'a':players==2?:players--;
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
					case 'd':lifes[0]==9?:lifes[0]++;
						break;
						
					case 'a':lifes[0]==1?:lifes[0]--;
						break;
						
					case 13:r++;
						break;
				}
			break;
		}
		for(int p = 1;p<=players;p++)
		{
			lifes[p] = lifes[0];
		}
		system("cls");
	}
	
	game();
}
//--------------------------[jogo]---------------------------------//

int game()
{
	while(end(1) != 1)
	{
		bets();
		
		strcpy(frase,"que os jogos comecem!!");
		printf("		");
		for (int i = 0; frase[i] != '\0'; i++) 
		{
    	    printf("%c", frase[i]);
    	   	fflush(stdout);  // Garante que o caractere seja impresso imediatamente
    	    Sleep(100);      // Pausa de 100 milissegundos entre cada caractere
    	}
    	
    	while(end(2) != 1)
    	{
    		sorteio();
		}
	}
}

//-------------------------[apostas]-------------------------------//

int bets()
{
	for(int p = 1;p<=players;p++)
	{
		printf("narrador:\"jogador %d, fa%ca a sua aposta\"",p,135);
		printf("\nseu saldo:%d",money[p]);
		printf("\n\naposta:R$");
		do
		{
			printf("\033[4;10H");
			scanf("%d",&bet[p]);
		}while( bet[p]>money[p] || bet[p] <= 0);
		prize+=bet[p];
		money[p] -= bet[p];
		system("cls");
	}
}

//-----------------------------------[dentro do jogo]-------------------------------------//
//-n quis fazer tudo dentro de um evento pq eu to ficando louco LALALALALALALLALA

int sorteio()
{
	system("cls");
	srand(time(NULL));
   	quant = rand()%5+3;
   	srand(time(NULL));
   	verm = rand()%(quant/2+1)+1;
   	
   	
   	for(int i = 0;i<verm;i++)
   	{
   		do
   		{
   			srand(time(NULL));
		   	ran = rand()%quant;
		}while(balas[ran] == 1);
		balas[ran] = 1;
	}
   	
   	printf("%d blanks\n%d lives\n",quant-verm,verm);
   	Sleep(5000);
   	system("cls");
   	ingame();
   	
   	for(int r = 0;r<quant;r++)
   	{
   		balas[r] = 0;
	}

}

int ingame()
{
	int acabou = 0;
	opc = 1;
	for(int p = 1;p<=quant;p++)
	{
		system("cls");
		if(lifes[p] == 0)
			continue;
		
		printf("jogador %d: \n",p);
		
		if(sort[p] == false)
		{
			objs(p);
		}
		printf("\nobjetos:");
		for(int i = 1;i<=8;i++)
		{
			if(opc == i)
			{
				SetConsoleTextAttribute(hc,16+7);
			}
			else
			{
				SetConsoleTextAttribute(hc,7);
			}

			printf("\n%d:",i);
			strcpy(frase,objetos[obj[p][i]]);
			printf("%s",frase);
		}
		
		if(opc == 9)
		{
			SetConsoleTextAttribute(hc,16+7);
		}
		else
		{
			SetConsoleTextAttribute(hc,7);
		}
		printf("\n\n[revolver]");
		SetConsoleTextAttribute(hc,7);
		printf("\n\nvidas: ");
		for(int i = 0;i<lifes[p];i++)
		{
			printf("%c",3);
		}
		
		key = tolower(getch());
		
		switch(key)
		{
			case 's':
				if(opc < 9)
					opc++;
			break;
			
			case 'w':
				if(opc > 1)
					opc--;
			break;
			
			case 13:
				switch(opc)
				{
					case 1 ... 8:
						
					break;
					
					case 9:
						
					break;
				}
			break;
		}
		
		
		
		if(acabou == 1)
		{
			acabou = 0;
			continue;
		}
		else
		{
			p--;
		}
	}
}

int objs(int p)
{
	
	for(int i = 0; i<4;i++)
	{
		ran = 0;
		for(int j = 1;j<=8;j++)
		{
			if(obj[p][j] == 0)
			{
				srand(time(NULL)* sqrt(i*j));
				obj[p][j] = rand()%10+1;
				printf("\nrecebeu: %s",objetos[obj[p][j]]);
				break;
			}
			
			else
			{
				ran++;
			}
		}
		
		key = getch();
	}
	sort[p] = true;
	system("cls");
}


//---------------------------------------[fim do jogo e fim das apostas]-------------------------------------------//
//-Eu n queria deixar uma linha quilométrica nos whiles(pra verificara cada player) ent eu coloquei meus fors aqui
int end(int f)
{
	switch(f)
	{
		case 1:
			for(int i = 1;i<=players;i++)
			{
				if(money[i] <= 0)
					return 1;
				
				else
					return 0;
			}
		break;
		
		case 2:
			int q = 0;
			for(int i = 1;i<=players;i++)
			{
				if(lifes[i] > 0)
				{
					q++;
				}
			}
			
			if(q <= 1)
				return 1;
				
			else
				return 0;
		break;
	}
}





//369
