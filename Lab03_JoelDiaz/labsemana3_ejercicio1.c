#include<stdio.h>
#include<stdlib.h>
#define n 10
#define maxName 25
#define sizeName 20

//Estructura del player
typedef struct
{
	char name[25];
	int level, health, score;
} Player;

//Registro de datos (Inicio)

//Verificacion 1: Extension del nombre y los caracteres usados
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

//Verificacion 2: Datos enteros
void verifIntegers(int *value, int min, int max)
{
	while(*value < min || *value > max)
	{
		printf("\n\t\t* (Error: Dato invalido) Por favor, ingrese un numero valido: ");
		scanf("%d", value);
		getchar();
	}
}

//Ingreso del nombre del jugador
void enterData_name(Player *p)
{
	int j = 0;
	
	printf("\n\t* Ingrese el nombre del jugador (minimo de caracteres: 1, maximo de caracteres: 20; SOLO LETRAS): ");
	scanf("%s", p->name);
	
	while(verifName(p->name) == 0)
	{
		printf("\n\t\t* (Error: Extension o caracter invalido) Por favor, intente nuevamente: ");
		scanf("%s", p->name);
	}
	
	//Se escribe el nombre con mayusculas
	for(j = 0; j < sizeName; j++)
	{
		//Si se termina el nombre, sale del bucle
		if(p->name[j] == '\0')
		{
			break;
		}
		//Si el codigo ASCII de la letra es mayor a 90 ('Z'), entonces esta escrito en minusculas
		else if(p->name[j] > 90)
		{
			p->name[j] -= 32;
		}
	}
}

//Ingreso del nivel del jugador
void enterData_level(Player *p)
{
	int value = 0;
	
	printf("\n\t* Ingrese el nivel del jugador (minimo: 1, maximo 5): ");
	scanf("%d", &value);
	getchar();
	
	verifIntegers(&value, 1, 5);
	
	p->level = value;
}

//Ingreso de la vida del jugador
void enterData_health(Player *p)
{
	int value = 0;
	
	printf("\n\t* Ingrese la vida del jugador (minimo: 1, maximo 100): ");
	scanf("%d", &value);
	getchar();
	
	verifIntegers(&value, 1, 100);
	
	p->health = value;
}

//Ingreso del puntaje del jugador
void enterData_score(Player *p)
{
	int value = 0;
	
	printf("\n\t* Ingrese el puntaje del jugador (minimo: 1, maximo 10): ");
	scanf("%d", &value);
	getchar();
	
	verifIntegers(&value, 1, 10);
	
	p->score = value;
}

//Ingreso de datos
void enterData(Player arr[], int *cantPlayers)
{
	int i = 0;
	
	printf("------------------------- BIENVENIDO AL PROGRAMA DE DESARROLLO Y ALMACENAMIENTO DE ESTADISTICAS -------------------------\n");
	printf("\n* Indique la cantidad de jugadores que desea ingresar (minimo: 1, maximo: 10): ");
	scanf("%d", cantPlayers);
	getchar();
	
	while(*cantPlayers < 1 || *cantPlayers > 10)
	{
		printf("\n\t* (Error: Cantidad fuera de rango) Por favor, ingrese una cantidad valida: ");
		scanf("%d", cantPlayers);
		getchar();
	}
	
	//Asignacion de datos de cada jugador a traves de un jugador generico. Luego de la asignacion, el jugador se almacena en un array de jugadores
	for(i = 0; i < *cantPlayers; i++)
	{
		Player *generic = malloc(sizeof(Player));
		
		printf("\n\t---------- Datos del jugador %d ----------\n", i + 1);
		
		enterData_name(generic);
		enterData_level(generic);
		enterData_health(generic);
		enterData_score(generic);
		
		arr[i] = *generic;
	}
}

//Registro de datos (Fin)

//Se muestran los datos
void showData(Player arr[], int *cantPlayers)
{
	int i = 0;
	
	printf("\n\n-------------------- ESTADISTICAS --------------------\n");
	
	for(i = 0; i < *cantPlayers; i++)
	{
		printf("\n\t* Jugador %d\n\n\t\t- Nombre: %s\n\t\t- Nivel: %d\n\t\t- Salud: %d\n\t\t- Puntaje: %d\n", i + 1, arr[i].name, arr[i].level, arr[i].health, arr[i].score);
	}
}

int main()
{
	int cantPlayers = 0;
	Player arrPlayers[n];

	enterData(arrPlayers, &cantPlayers);
	
	showData(arrPlayers, &cantPlayers);
	
	return 0;
}
