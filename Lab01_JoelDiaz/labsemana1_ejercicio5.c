#include<stdio.h>
#include<stdlib.h>

//Codigo creado en DevC++ (Lenguaje de programacion: C)

int main()
{
	srand(time(NULL));
	
	int figure = 0, lastFigure = 0, opcion = 0;
	
	printf("------------------------- BIENVENIDO A VRVTetrix -------------------------\n");
	Sleep(1000);
	
	do
	{
		figure = rand() % 7 + 1;
		
		while(figure == lastFigure)
		{
			figure = rand() % 7 + 1;
		}
		
		if(lastFigure == 0)
		{
			printf("\n\t***** Generando la figura %d *****", figure);
			Sleep(500);
		}
		else
		{
			printf("\n\t***** Generando la figura %d (Figura anterior: %d) *****", figure, lastFigure);
			Sleep(500);
		}
		
		lastFigure = figure;
		
		printf("\n\n\t\t Si desea salir presione <0>. De lo contrario, presione cualquier NUMERO.\n\n\t\t* Ingrese su opcion: ");
		scanf("%d", &opcion);
	}
	while(opcion != 0);
	
	Sleep(500);
	printf("\n\n\t\t---------- FIN DEL PROGRAMA ----------");
	Sleep(500);
	
	return 0;
}
