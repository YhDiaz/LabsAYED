#include<stdio.h>
#include<stdlib.h>

//Codigo creado en DevC++ (Lenguaje de programacion: C)
//Instruccion system("cls") disponible solo desde Windows (Lineas 13, 28)

int main()
{
	int i = 0, j = 0;
	
	for(i = 0; i <= 100; i++)
	{
		system("cls");
		printf("Loading %d%%...  ", i);
		
		for(j = 0; j < i; j++)
		{
			if(j % 5 == 0)
			{
				printf("|");
			}
		}
		
		Sleep(100);
	}
	
	Sleep(1000);
	system("cls");
	
	printf("\n\n\t Comienza el juego\n\n");
	Sleep(1000);
	
	return 0;
}
