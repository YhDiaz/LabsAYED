#include<stdio.h>
#include<stdlib.h>

//Codigo creado en DevC++ (Lenguaje de programacion: C)

int main()
{
	srand(time(NULL));
	
	//Longitud de la matriz
	int colMtx = 3, rowMtx = 3;
	
	//Variables
	int i = 0, j = 0, emptyPlace = colMtx * rowMtx, posicion = 0, turn = 0;
	
	//Arreglo con posiciones ocupadas
	int arrBusyPlaces[colMtx * rowMtx];
	
	//Matriz de almacenamiento de las jugadas
	int mtxJugadas[rowMtx][colMtx];
	
	//Inicializacion del array
	for(i = 0; i < 9; i++)
	{
		arrBusyPlaces[i] = -1;
	}
	
	//Inicializacion de la matriz
	for(i = 0; i < rowMtx; i++)
	{
		for(j = 0; j < colMtx; j++)
		{
			mtxJugadas[i][j] = -1;
		}
	}

	printf("------------------------- BIENVENIDO AL GRAN GATO -------------------------\n\n");
	Sleep(200);
	printf("\t* El programa utiliza una matriz para almacenar datos y un array\n\tauxiliar para verificar que posiciones estan vacias u ocupadas.\n\tAdemas, la seleccion de posiciones es al azar (utilizando numeros\n\taleatorios).En caso de victoria, se indicara el ganador y la\n\tubicacion de su conjunto ganador (fila, columna o diagonal)\n\n");
	Sleep(1000);
	
	printf("***** Tablero inicial *****\n");
	Sleep(250);
	
	for(i = 0; i < rowMtx; i++)
	{
		printf("\t");
		
		for(j = 0; j < colMtx; j++)
		{
			printf("- ");
		}
		
		printf("\n");
	}

	printf("\n");

	while(emptyPlace > 0)
	{
		printf("Jugada %d, Turno del jugador %d\n\n", turn + 1, (turn % 2) + 1);
		
		posicion = rand() % 9 + 1;
		
		while(arrBusyPlaces[posicion - 1] != -1)
		{
			posicion = rand() % 9 + 1;
		}
		
		if(turn % 2 == 0)
		{
			arrBusyPlaces[posicion - 1] = 0;
		}
		else
		{
			arrBusyPlaces[posicion - 1] = 1;
		}
		
		if(posicion % 3 == 0)
		{
			if(turn % 2 == 0)
			{
				mtxJugadas[(posicion / 3) - 1][2] = 0;
			}
			else
			{
				mtxJugadas[(posicion / 3) - 1][2] = 1;
			}
		}
		else
		{
			if(turn % 2 == 0)
			{
				mtxJugadas[posicion / 3][(posicion % 3) - 1] = 0;
			}
			else
			{
				mtxJugadas[posicion / 3][(posicion % 3) - 1] = 1;
			}
		}
		
		for(i = 0; i < rowMtx; i++)
		{
			printf("\t");
			
			for(j = 0; j < colMtx; j++)
			{
				switch(mtxJugadas[i][j])
				{
					case 0:
						printf("X ");
						break;
						
					case 1:
						printf("O ");
						break;
						
					default:
						printf("- ");
						break;
				}
			}
			
			printf("\n\n");
		}
		
		Sleep(500);
		
		//Jugador 1
		if(mtxJugadas[0][0] == 0 && mtxJugadas[1][1] == 0 && mtxJugadas[2][2] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Diagonal 1) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][2] == 0 && mtxJugadas[1][1] == 0 && mtxJugadas[2][0] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Diagonal 2) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][0] == 0 && mtxJugadas[0][1] == 0 && mtxJugadas[0][2] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Fila 1) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[1][0] == 0 && mtxJugadas[1][1] == 0 && mtxJugadas[1][2] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Fila 2) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[2][0] == 0 && mtxJugadas[2][1] == 0 && mtxJugadas[2][2] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Fila 3) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][0] == 0 && mtxJugadas[1][0] == 0 && mtxJugadas[2][0] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Columna 1) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][1] == 0 && mtxJugadas[1][1] == 0 && mtxJugadas[2][1] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Columna 2) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][2] == 0 && mtxJugadas[1][2] == 0 && mtxJugadas[2][2] == 0)
		{
			printf("\n\t***** El jugador 1 ha ganado (Columna 3) *****");
			emptyPlace = 0;
		}
		
		//Jugador 2
		else if(mtxJugadas[0][0] == 1 && mtxJugadas[1][1] == 1 && mtxJugadas[2][2] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Diagonal 1) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][2] == 1 && mtxJugadas[1][1] == 1 && mtxJugadas[2][0] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Diagonal 2) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][0] == 1 && mtxJugadas[0][1] == 1 && mtxJugadas[0][2] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Fila 1) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[1][0] == 1 && mtxJugadas[1][1] == 1 && mtxJugadas[1][2] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Fila 2) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[2][0] == 1 && mtxJugadas[2][1] == 1 && mtxJugadas[2][2] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Fila 3) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][0] == 1 && mtxJugadas[1][0] == 1 && mtxJugadas[2][0] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Columna 1) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][1] == 1 && mtxJugadas[1][1] == 1 && mtxJugadas[2][1] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Columna 2) *****");
			emptyPlace = 0;
		}
		else if(mtxJugadas[0][2] == 1 && mtxJugadas[1][2] == 1 && mtxJugadas[2][2] == 1)
		{
			printf("\n\t***** El jugador 2 ha ganado (Columna 3) *****");
			emptyPlace = 0;
		}
		
		turn++;
		emptyPlace--;
	}
	
	return 0;
}
