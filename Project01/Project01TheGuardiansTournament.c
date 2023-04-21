#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define strLength 20

/*CONSIDERAR

	LA EXISTENCIA DE AL MENOS 3 GUARDIANES EN LA LISTA PARA PODER JUGAR EN MODO PRICIPIANTE
	Y LAS VERIFICACIONES DE CANTIDAD DE GUARDIANES ANTES DE ELEGIR UNA DIFICULTAD
	*NO PUEDE ELEGIRSE LA DIFICULTAD INTERMEDIA SI HAY SOLO 4 GUARDIANES
	
	SI SE SELECCIONA LA DIFICULTAD INTERMEDIA, DEBE DERROTAR 5 GUARDIANES? O DEBE DERROTAR PRIMERO LOS 3 DE PRINCIPIANTE Y LUEGO 5 MAS DE INTERMEDIA
	LO MISMO AL COMPLETAR UN NIVEL DE DIFICULTAD, SI SE QUIERE PASAR AL SIGUIENTE NIVEL, SE COMIENZA DESDE 0 EL CONTADOR O SOLO TIENE QUE DERROTAR
	2 GUARDIANES MAS EN CASO DE PASAR DESDE PRINCIPIANTE A INTERMEDIO?

*/

/*CODIGO DEBUG

	Guardian *current = head;
	while(current != NULL)
	{
		printf("\n\tGuardian %d\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", i, current->name, current->type, current->life, current->attackPoints, current->defensePoints);
		current = current->next;
		i++;
	}
	
	Guardian *aux = head;
	int i = 1;
	
	printf("\n\t---------- LISTA DE GUARDIANES ----------\n");
	
	while(aux != NULL)
	{
		printf("\n\tGuardian %d\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", i, aux->name, aux->type, aux->life, aux->attackPoints, aux->defensePoints);
		aux = aux->next;
		
		if(aux != NULL)
		{
			i++;
		}
	}

*/

//Estructuras

//Guardian
typedef struct guardian
{
	//Cada guardian tiene los datos: nombre, tipo, cantidad de vida, puntos de ataque y puntos de defensa
	char name[strLength + 1];
	char type[strLength];
	int life;
	int attackPoints;
	int defensePoints;
	
	//La variable status indica si el guardian ya participo en un combate o no:
	//0: Participo, es decir, no puede volver a combatir; 1: No ha participado, es decir, puede combatir
	int status;
	
	struct guardian *next;
} Guardian;

//Funciones

//Cargar archivo
int loadFile(int argc, char *argv[], Guardian **head);

//Crear guardian/jugador
void createCharacter(Guardian *guardian, Guardian *head);

//Seleccionar guardian
void selectCharacter(Guardian **guardian, Guardian **head);

//Seleccionar dificultad
void selectTournament(int *difficulty);

//Menu
void menuOptions(Guardian *myGuardian, Guardian *head, int *difficulty);

//Mostrar status de un guardian
void printCharacterStatus(Guardian *guardian);

//
//
//

//Funcion para saber el estado de un guardian
void printCharacterStatus(Guardian *guardian)
{
	printf("\n\t---------- GUARDIAN STATUS ----------\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", guardian->name, guardian->type, guardian->life, guardian->attackPoints, guardian->defensePoints);	
}

//Funcion para comenzar la pelea
void startFight(int *difficulty, int *end, Guardian *local, Guardian *headEnemies)
{
	srand(time(NULL));
	
//SE ASUME QUE LA LISTA CONTIENE LA CANTIDAD MINIMA DE GUARDIANES PARA LA DIFICULTAD ESCOGIDA
//REALIZAR VERIFICACION ANTES DE LLEGAR AQUI
	Guardian *aux = headEnemies;
	int guardiansCount = 1;
	
	//Se cuentan los guardianes de la lista
	while(aux != NULL)
	{
		aux = aux->next;
		
		//Como se cambio el valor de aux, se comprueba si es nulo antes de incrementar el contador
		if(aux != NULL)
		{
			guardiansCount++;
		}
	}
	
	//Inicio de la lista (convertir en cola) de guardianes que van a combatir con el jugador
	Guardian *headContenders = NULL;
	
	int guardiansSelection = 0, numContenders = 0, currentContenders = 0;
	
	//Cantidad de guardianes que el jugador debe derrotar dependiendo del nivel de dificultad
	if(*difficulty == 1)
	{
		numContenders = 3;
	}
	else if(*difficulty == 2)
	{
		numContenders = 5;
	}
	else
	{
		numContenders = 7;
	}
	
	//Se agregan guardianes a la lista de contendientes del jugador hasta que se alcance la cantidad de guardianes correspondiente al nivel
	while(currentContenders < numContenders)
	{
		//Se selecciona un guardian de la lista
		guardiansSelection = rand() % guardiansCount + 1;
		int guardianSelected = 1;
		
		//Si la lista de contendientes esta vacia, el guardian seleccionado aleatoriamente se agrega como primer elemento
		if(headContenders == NULL)
		{
			aux = headEnemies;
			
			//Busqueda del guardian seleccionado aleatoriamente
			while(guardianSelected != guardiansSelection)
			{
				aux = aux->next;
				guardianSelected++;
			}
			
			//Asignacion del guardian seleccionado como primer elemento de la lista de contendientes
			headContenders = aux;
			
			//Se quita el guardian de la lista principal
			if(headContenders == headEnemies)
			{
				aux = headEnemies;
				headEnemies = headEnemies->next;
			}
			else
			{
				aux = headEnemies;
				
				while(aux->next != headContenders)
				{
					aux = aux->next;
				}
				
				//Se usa headContenders para pasar la direccion de memoria del siguiente elemento en la lista original
				aux->next = headContenders->next;
			}
			
			//Como el guardian agregado es el ultimo de la lista, apunta a NULL
			headContenders->next = NULL;
		}
		else
		{
			aux = headEnemies;
			
			//Busqueda del guardian seleccionado aleatoriamente
			while(guardianSelected != guardiansSelection)
			{
				aux = aux->next;
				guardianSelected++;
			}
			
			Guardian *current = headContenders;
			
			while(current->next != NULL)
			{
				current = current->next;
			}
			
			//Asignacion del guardian seleccionado como ultimo elemento de la lista de contendientes
			current->next = aux;
			
			//La variable current ahora corresponde al ultimo elemento agregado con el objetivo de un mejor manejo posterior
			current = current->next;
			
			//Se quita el guardian de la lista principal
			if(current == headEnemies)
			{
				aux = headEnemies;
				headEnemies = headEnemies->next;
			}
			else
			{
				aux = headEnemies;
				
				while(aux->next != current)
				{
					aux = aux->next;
				}
				
				//Se usa headContenders para pasar la direccion de memoria del siguiente elemento en la lista original
				aux->next = current->next;
			}
			
			//Como el guardian agregado es el ultimo de la lista, apunta a NULL
			current->next = NULL;
		}
		
		//Se incrementa el contador de contendientes agregados a la lista
		currentContenders++;
		
		//Se decrementa el contador de guardianes restantes en la lista original
		guardiansCount--;
	}
	
	Guardian *aux1 = headContenders;
	int i = 1;
	
	printf("\n\t---------- LISTA DE GUARDIANES ----------\n");
	
	while(aux1 != NULL)
	{
		printf("\n\tGuardian %d\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", i, aux1->name, aux1->type, aux1->life, aux1->attackPoints, aux1->defensePoints);
		aux1 = aux1->next;
		
		if(aux1 != NULL)
		{
			i++;
		}
	}
	
	aux1 = headEnemies;
	i = 1;
	
	printf("\n\t---------- LISTA ORIGINAL (ACTUALIZADA) ----------\n");
	
	while(aux1 != NULL)
	{
		printf("\n\tGuardian %d\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", i, aux1->name, aux1->type, aux1->life, aux1->attackPoints, aux1->defensePoints);
		aux1 = aux1->next;
		
		if(aux1 != NULL)
		{
			i++;
		}
	}
	
	*end = 1;
}

int main(int argc, char *argv[])
{
	//Precarga de datos
	Guardian *headGuardians = NULL, *myGuardian = malloc(sizeof(Guardian));
	
	//Si la variable endMain almacena un 1, entonces algo fallo en la carga del archivo
	int endMain = loadFile(argc, argv, &headGuardians);
	
	//Si la variable endMain almacena un 1, se termina el programa
	if(endMain == 1)
	{
		return 1;
	}
	
	//Mecanica de juego
	int end = 0, difficulty = 0;
	
	menuOptions(myGuardian, headGuardians, &difficulty);

	do
	{
		startFight(&difficulty, &end, myGuardian, headGuardians);
	}
	while(end == 0);
	
	return 0;
}

//Funcion para cargar un archivo de texto con los guardianes
int loadFile(int argc, char *argv[], Guardian **head)
{
	//Verificaciones de argumentos
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
		return 1;
	}
	
	char *file_name = argv[1];
	FILE *file = fopen(file_name, "r");
	
	if(file == NULL)
	{
		fprintf(stderr, "Error: Could not open file %s\n", file_name);
		return 1;
	}
	
	char line[100];
	
	printf("\n\tCargando datos...\n");
	Sleep(500);
	
	//Asignacion de valores
	while(fgets(line, 100, file) != NULL)
	{
		Guardian *aux = (Guardian*)malloc(sizeof(Guardian));
		
		strcpy(aux->name, strtok(line, ","));
		strcpy(aux->type, strtok(NULL, ","));
		aux->life = atoi(strtok(NULL, ","));
		aux->attackPoints = atoi(strtok(NULL, ","));
		aux->defensePoints = atoi(strtok(NULL, ","));
		aux->status = 1;
		aux->next = NULL;		
		
		if(*head == NULL)
		{
			*head = aux;
		}
		else
		{
			Guardian *current = *head;
			
			while(current->next != NULL)
			{
				current = current->next;
			}
			
			current->next = aux;
		}
	}
	
	fclose(file);
	printf("\n\tDatos cargados exitosamente\n\n");
	
	return 0;
}

//Funcion para que el jugador pueda crear un guardian
void createCharacter(Guardian *guardian, Guardian *head)
{
	srand(time(NULL));
	int option = 0, min = 0, max = 0, i = 0;
	
	printf("\n\t--------------- CREACION DE UN GUARDIAN ---------------\n");
	
	//Nombre
	
	//Indicaciones
	printf("\n\tIndique el nombre del guardian: ");
	scanf("%s", &guardian->name);
	
	//Tipo de guardian
	
	//Indicaciones
	printf("\n\tIndique el tipo del guardian;\n\n\t* Presione <1> para elegir el tipo MAGO\n\t* Presione <2> para elegir el tipo VIKINGO\n\t* Presione <3> para elegir el tipo NIGROMANTE\n\t* Presione <4> para elegir el tipo BESTIA\n\n\t* Ingrese su eleccion: ");
	scanf("%d", &option);
	
	//Verificacion del tipo de guardian
	while(option < 1 || option > 4)
	{
		printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
		scanf("%d", &option);
	}
	
	//Asignacion del tipo de guardian
	switch(option)
	{
		case 1:
			strcpy(guardian->type, "Mago");
			break;
			
		case 2:
			strcpy(guardian->type, "Vikingo");
			break;
			
		case 3:
			strcpy(guardian->type, "Nigromante");
			break;
			
		case 4:
			strcpy(guardian->type, "Bestia");
			break;
	}
	
	//Vida, puntos de ataque y puntos de defensa
	for(i = 0; i < 3; i++)
	{
		Guardian *aux = head->next;
		
		//Se obtienen los valores minimos y maximos de los guardianes, correspondientes a: vida (i = 0), puntos de ataque (i = 1)
		//y puntos de defensa (i = 2). Luego, se genera un numero random que se encuentre dentro de cada rango y se asigna al jugador.
		//La formula de generacion del numero random devolvera un numero dentro del rango, pero nunca sera igual al limite inferior
		if(i == 0)
		{
			min = head->life;
			max = head->life;
			
			while(aux != NULL)
			{
				if(aux->life < min)
				{
					min = aux->life;
				}
				
				if(aux->life > max)
				{
					max = aux->life;
				}
				
				aux = aux->next;
			}
			
			guardian->life = rand() % (max - min + 1) + min;
		}
		else if(i == 1)
		{
			min = head->attackPoints;
			max = head->attackPoints;
			
			while(aux != NULL)
			{
				if(aux->attackPoints < min)
				{
					min = aux->attackPoints;
				}
				
				if(aux->attackPoints > max)
				{
					max = aux->attackPoints;
				}
				
				aux = aux->next;
			}
			
			guardian->attackPoints = rand() % (max - min + 1) + min;
		}
		else
		{
			min = head->defensePoints;
			max = head->defensePoints;
			
			while(aux != NULL)
			{
				if(aux->defensePoints < min)
				{
					min = aux->defensePoints;
				}
				
				if(aux->defensePoints > max)
				{
					max = aux->defensePoints;
				}
				
				aux = aux->next;
			}
			
			guardian->defensePoints = rand() % (max - min + 1) + min;
		}
	}
	
	//Variables extras
	guardian->next = NULL;
	guardian->status = 1;	
}

//Funcion para que el jugador pueda seleccionar un guardian creado
void selectCharacter(Guardian **guardian, Guardian **head)
{
	Guardian *aux = *head;
	int i = 1, option = 0;
	
	//Se muestra la lista de guardianes
	printf("\n\t---------- LISTA DE GUARDIANES ----------\n");
	
	while(aux != NULL)
	{
		printf("\n\tGuardian %d\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", i, aux->name, aux->type, aux->life, aux->attackPoints, aux->defensePoints);
		aux = aux->next;
		
		//Contador de guardianes
		if(aux != NULL)
		{
			i++;
		}
	}
	
	//Indicaciones para elegir un guardian de la lista
	printf("\n\tIngrese el numero del guardian que desea escoger como su campeon: ");
	scanf("%d", &option);
	
	//Verificacion del input
	while(option < 1 || option > i)
	{
		printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
		scanf("%d", &option);
	}
	
	//Busqueda del guardian seleccionado
	aux = *head;
	i = 1;
	
	while(i < option)
	{
		aux = aux->next;
		i++;
	}
	
	//Asignacion del guardian seleccionado al guardian del jugador
	*guardian = aux;
	
	//Se quita el guardian seleccionado de la lista, cambiando el valor del puntero del guardian que alamacenaba su direccion de memoria
	if(*guardian == *head)
	{
		*head = aux->next;
	}
	else
	{
		//current es la variable Guardian que se quitara de la lista
		Guardian *current = *guardian;
		
		//aux es la varibale Guardian auxiliar que se utilizara para hacer el cambio en el valor del puntero
		aux = *head;
		
		//Se obtiene la variable Guardian que apunta a la direccion de current
		while(aux->next != current)
		{
			aux = aux->next;
		}
		
		//El puntero que apuntaba a current ahora apuntara al Guardian que apuntaba current
		aux->next = current->next;
	}
}

//Funcion para elegir el nivel de dificultad del torneo
void selectTournament(int *difficulty)
{
	printf("\n\t---------- SELECCIONAR DIFICULTAD ----------\n\n\tNiveles de dificultad:\n\n\t\t* Principiante: Debe derrotar a 3 guardianes\n\t\t* Intermedio: Debe derrotar a 5 guardianes\n\t\t* Experto: Debe derrotar a 7 guardianes\n\n\tSeleccione el nivel de dificultad que desea\n\n\t* Presione <1> para seleccionar la dificultad Principiante\n\t* Presione <2> para seleccionar la dificultad Intermedio\n\t* Presione <3> para seleccionar la dificultad Experto\n\n\t* Ingrese su opcion: ");
	scanf("%d", difficulty);
	
	while(*difficulty < 1 || *difficulty > 3)
	{
		printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
		scanf("%d", difficulty);
	}
	
	if(*difficulty == 1)
	{
		printf("\n\t***** Has seleccionado la dificultad Principiante, deberas enfrentarte a 3 guardianes *****\n");
	}
	else if(*difficulty == 2)
	{
		printf("\n\t***** Has seleccionado la dificultad Intermedio, deberas enfrentarte a 5 guardianes *****\n");
	}
	else
	{
		printf("\n\t***** Has seleccionado la dificultad Experto, deberas enfrentarte a 7 guardianes *****\n");
	}
}

//Funcion que contiene el menu de inicio del juego (Crear o seleccionar un guardian y seleccionar dificultad de juego)
void menuOptions(Guardian *myGuardian, Guardian *head, int *difficulty)
{
	int action = 0;
	
	//Indicaciones (Creacion/seleccion de guardian)
	printf("------------------------------ BIENVENIDO AL TORNEO DE GUARDIANES ------------------------------\n\n\tAntes de comenzar, seleccione una de las siguiente opciones\n\n\t* Presione <1> para crear su propio guardian (solo puede indicar el nombre y tipo)\n\t* Presione <2> para seleccionar un guardian ya creado\n\n\t* Ingrese su eleccion: ");
	scanf("%d", &action);
	
	//Verificacion de input
	while(action != 1 && action != 2)
	{
		printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
		scanf("%d", &action);
	}
	
	//Se realiza la accion que desea el jugador
	if(action == 1)
	{
		createCharacter(myGuardian, head);
	}
	else
	{
		selectCharacter(&myGuardian, &head);
	}
	
	printCharacterStatus(myGuardian);	
	
	//Indicaciones (Seleccion de dificultad)
	printf("\n\t-------------------- SELECCIONAR DIFICULTAD --------------------\n\n\tEl juego presenta 3 dificultades: Principiante, Intermedio y Experto\n\t%cDesea seleccionar la dificultad con la que quiere iniciar?\n\t(La dificultad de inicio por defecto es Principiante)\n\n\t* Presione <0> para comenzar con la dificultad por defecto\n\t* Presione <1> para seleccionar dificultad\n\n\t* Ingrese su opcion: ", 168);
	scanf("%d", &action);
	
	//Verificacion de input
	while(action != 0 && action != 1)
	{
		printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
		scanf("%d", &action);
	}
	
	//Se llama a la funcion solamente si el jugador desea seleccionar el nivel de dificultad
	if(action == 1)
	{
		selectTournament(difficulty);
	}
	else
	{
		printf("\n\t***** Se iniciara el juego en la dificultad por defecto: Principiante *****\n");
		*difficulty = 1;
	}
}
