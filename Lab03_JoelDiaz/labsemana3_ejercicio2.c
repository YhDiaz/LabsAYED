#include<stdio.h>
#include<stdlib.h>
#define n 5
#define maxName 25
#define sizeName 20

//Estructura del player
typedef struct
{
	//El atributo name almacenara el nombre o alias del jugador
	char name[25];
	
	/*El atributo level almacena el nivel del jugador; health, la vida; score, el puntaje; energy, la energia para combatir;
	y canFight, la habilitacion para estar en el combate*/
	int level, health, score, energy, canFight;
} Player;

//Registro de datos (Inicio)

//Verificacion 1: Numero de jugadores
void verifNumPlayers(int *num, int i, int cantPlayers[])
{
	printf("\n\n\t* Indique la cantidad de jugadores que tiene el equipo (minimo: 1, maximo: 5): ");
	scanf("%d", num);
	getchar();
	
	while(*num < 1 || *num > 5)
	{
		printf("\n\t\t* (Error: Dato invalido) Por favor, ingrese un valor que este dentro del rango: ");
		scanf("%d", num);
		getchar();
	}
	
	cantPlayers[i] = *num;
}

//Verificacion 2: Nombre del jugador
int verifName(char name[])
{
	int i = 0, nameLength = 0;
	
	//Extension del nombre
	for(i = 0; i < maxName; i++)
	{
		if(name[i] == '\0')
		{
			if(i <= 20)
			{
				nameLength = i;
				break;
			}
		}
		else if(i == sizeName + 1)
		{
			return 0;
		}
	}
	
	//Caracteres
	for(i = 0; i < nameLength; i++)
	{
		//ASCII 65: 'A'; ASCII 90: 'Z'; ASCII 97: 'a'; ASCII 122: 'z'
		if(name[i] < 65 || (name[i] > 90 && name[i] < 97) || name[i] > 122)
		{
			return 0;
		}
		else if(name[i] == '\0')
		{
			return 1;
		}
	}
}

//Asignacion del nombre o alias del jugador
void name(Player *generic)
{
	int j = 0;
	
	printf("\n\n\t\t* Ingrese su nombre o alias (minimo de caracteres: 1, maximo de caracteres: 20; SOLO LETRAS): ");
	scanf("%s", generic->name);
	
	while(verifName(generic->name) == 0)
	{
		printf("\n\t\t* (Error: Extension o caracter invalido) Por favor, intente nuevamente: ");
		scanf("%s", generic->name);
	}
		
	//Se escribe el nombre con mayusculas
	for(j = 0; j < sizeName; j++)
	{
		//Si se termina el nombre, sale del bucle
		if(generic->name[j] == '\0')
		{
			break;
		}
		//Si el codigo ASCII de la letra es mayor a 90 ('Z'), entonces esta escrito en minusculas
		else if(generic->name[j] > 90)
		{
			generic->name[j] -= 32;
		}
	}
}

//Permiso de combate
int combatPermit(int num)
{
	int permit = 0;
	
	if(num == 0)
	{
		return 1;
	}
	else
	{
		printf("\n\t\t* Indique si el jugador puede combatir (<0>: No, <1>: Si): ");
		scanf("%d", &permit);
		getchar();
		
		while(permit != 0 && permit != 1)
		{
			printf("\n\t\t\t* (Error: Dato invalido) Por favor, seleccione una opcion definida: ");
			scanf("%d", &permit);
			getchar();
		}
		
		return permit;
	}
}

//Datos de cada jugador
void playerData(Player tm[], int pos)
{
	Player *generic = malloc(sizeof(Player));
	
	name(generic);
	
	generic->level = 1;
	generic->health = 100;
	generic->score = 0;
	generic->energy = 10;
	
	generic->canFight = combatPermit(pos);
	
	tm[pos] = *generic;
}

//Datos de cada equipo
void teamData(Player tm[], int numTm, int cantPlayers[])
{
	int i = 0, num = 0;
	
	verifNumPlayers(&num, numTm, cantPlayers);
	
	for(i = 0; i < num; i++)
	{
		printf("\n\t\t----- Datos del jugador %d -----", i + 1);
		
		playerData(tm, i);
	}
}

//Ingreso de datos de los equipos
void enterData(Player tm1[], Player tm2[], int cantPlayers[])
{
	int i = 0;
	
	printf("------------------------- BIENVENIDO AL MODO: ARENA DE BATALLA -------------------------\n");
	
	for(i = 0; i < 2; i++)
	{
		printf("\n\t---------- Datos del equipo %d ----------", i + 1);
		
		if(i == 0)
		{
			teamData(tm1, i, cantPlayers);
		}
		else
		{
			teamData(tm2, i, cantPlayers);
		}
	}
}

//Registro de datos (Fin)

//Se muestran los datos
void showData(Player tm1[], Player tm2[], int cantPlayers[])
{
	int i = 0, j = 0;
	
	printf("\n\n--------------- DATOS DE LOS EQUIPOS ---------------\n");
	
	for(i = 0; i < 2; i++)
	{
		printf("\n\t---------- EQUIPO %d ----------\n", i + 1);
		
		for(j = 0; j < cantPlayers[i]; j++)
		{
			printf("\n\t\t* Jugador %d\n", j + 1);
			
			if(i == 0)
			{
				if(tm1[j].canFight)
				{
					printf("\n\t\t- Nombre/Alias: %s\n\t\t- Nivel: %d\n\t\t- Salud: %d\n\t\t- Puntaje: %d\n\t\t- Energia: %d\n\t\t- Permiso para combatir: Si\n", tm1[j].name, tm1[j].level, tm1[j].health, tm1[j].score, tm1[j].energy);
				}
				else
				{
					printf("\n\t\t- Nombre/Alias: %s\n\t\t- Nivel: %d\n\t\t- Salud: %d\n\t\t- Puntaje: %d\n\t\t- Energia: %d\n\t\t- Permiso para combatir: No\n", tm1[j].name, tm1[j].level, tm1[j].health, tm1[j].score, tm1[j].energy);					
				}
			}
			else
			{
				if(tm2[j].canFight)
				{
					printf("\n\t\t- Nombre/Alias: %s\n\t\t- Nivel: %d\n\t\t- Salud: %d\n\t\t- Puntaje: %d\n\t\t- Energia: %d\n\t\t- Permiso para combatir: Si\n", tm2[j].name, tm2[j].level, tm2[j].health, tm2[j].score, tm2[j].energy);
				}
				else
				{
					printf("\n\t\t- Nombre/Alias: %s\n\t\t- Nivel: %d\n\t\t- Salud: %d\n\t\t- Puntaje: %d\n\t\t- Energia: %d\n\t\t- Permiso para combatir: No\n", tm2[j].name, tm2[j].level, tm2[j].health, tm2[j].score, tm2[j].energy);
				}
			}
		}
	}
}

int main()
{
	int cantPlayers[2];
	Player team1[n], team2[n];
	
	enterData(team1, team2, cantPlayers);
	
	showData(team1, team2, cantPlayers);

	return 0;
}
