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
int sorteio();
int ingame();
int end(int opc);
//---------------[GLOBAIS]------------------//
int key,ran,players = 2,prize;

char objs[10][9][20]{0};
int lifes[10]{1};
int money[10]{0};
int bet[10]{2};

int balas[8]{0};
int quant,verm;

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
		}while( bet[p]>money[p]);
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
   	ingame();
   	
   	for(int r = 0;r<quant;r++)
   	{
   		balas[r] = 0;
	}

}

int ingame()
{
	for(int p = 1;p<=quant;p++)
	{
		if(lifes[p] == 0)
			continue;
		
		printf("jogador %d: \n",p);
		printf("\nobjetos:");
		for(int i = 1;i<=8;i++)
		{
			printf("\n%d:",i);
			strcpy(objs[p][0],objs[p][i]);
			for(int s = 0;objs[p][i][s] != '\0';s++)
			{
				printf("%c",objs[p][i][s]);
			}
		}
		
		printf("\n\n[revolver]");
		
		printf("vidas:");
		for(int i = 0;i<lifes[p];i++)
		{
			printf("%c",3);
		}
		
		key = getch();
		
		switch(key)
		{
			case 'w':
				
			break;
		}
	}
}
//---------------------------------------[fim do jogo e fim das apostas]-------------------------------------------//
//-Eu n queria deixar uma linha quilométrica nos whiles(pra verificara cada player) ent eu coloquei meus fors aqui
int end(int opc)
{
	switch(opc)
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






