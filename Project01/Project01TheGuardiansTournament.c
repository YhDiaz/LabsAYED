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

//Datos del torneo
typedef struct tournament
{
	int totalGuardians;
	int defeatedGuardians;
	int remainingGuardians;
} Tournament;

//Historial de batalla
typedef struct history
{
	char name[strLength];
	char type[strLength];
	int life;
	int attackPoints;
	int defensePoints;
	
	//Resultado del enfrentamiento contra el player
	//1: Ganador; 2: Perdedor
	int resultVsPlayer;
	
	//Cantidad de turnos que duro el enfrentamiento
	int turns;
	
	struct history *next;
} History;

//Funciones

//Cargar archivo
int loadFile(int argc, char *argv[], Guardian **head, Tournament *data);

//Crear guardian/jugador
void createCharacter(Guardian *guardian, Guardian *head);

//Seleccionar guardian
void selectCharacter(Guardian **guardian, Guardian **head, Tournament *data);

//Seleccionar dificultad
void selectTournament(int *difficulty);

//Menu
void menuOptions(Guardian **myGuardian, Guardian **head, int *difficulty, Tournament *data);

//Mostrar status de un guardian
void printCharacterStatus(Guardian *guardian);

//Lanzar un dado
int getRollResult(int diceSize);

//Historial de batalla
void getResult(History *head, Guardian *myGuardian);

//Mecanica de pelea
void startFight(int *difficulty, int *end, Guardian *local, Guardian *headEnemies, History **headHistory, Tournament *data);

int main(int argc, char *argv[])
{
	//Precarga de datos
	Guardian *headGuardians = NULL;
	Tournament *data = (Tournament*)malloc(sizeof(Tournament));
	
	//Si la variable endMain almacena un 1, entonces algo fallo en la carga del archivo
	int endMain = loadFile(argc, argv, &headGuardians, data);
	
	//Si la variable endMain almacena un 1, se termina el programa
	if(endMain == 1)
	{
		return 1;
	}
	
	//Mecanica de juego
	int end = 0, difficulty = 0;
	Guardian *myGuardian = malloc(sizeof(Guardian));
	History *headHistory = NULL;
	
	//Menu
	menuOptions(&myGuardian, &headGuardians, &difficulty, data);

	//Pelea
	do
	{
		startFight(&difficulty, &end, myGuardian, headGuardians, &headHistory, data);
	}
	while(end == 0);
	
	//Historial de batalla
	getResult(headHistory, myGuardian);
	
	return 0;
}

//Funcion para cargar un archivo de texto con los guardianes
int loadFile(int argc, char *argv[], Guardian **head, Tournament *data)
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
	
	//Inicializacion del total de guardianes para comenzar el conteo
	data->totalGuardians = 0;
	
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
		
		//Contador de guardianes
		data->totalGuardians++;
	}
	
	//Inicializacion de los contadores para guardianes restantes y guardianes derrotados
	data->remainingGuardians = data->totalGuardians;
	data->defeatedGuardians = data->totalGuardians - data->remainingGuardians;
	
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
	printf("\n\tIndique el nombre del guardian (minimo: 1 caracter, maximo: 20 caracteres): ");
	scanf("%s", &guardian->name);
	
	//Verificacion
	do
	{
		//Como la variable i esta inicializada en 0, si es distinta de este valor significa que no supero el proceso de verificacion
		if(i != 0)
		{
			printf("\n\t\t* (Error: Longitud invalida) Por favor, ingrese una cantidad de caracteres valida: ");
			scanf("%s", &guardian->name);
		}
		
		//Se busca la posicion en la que se ubica la instruccion de fin del array y se verifica que este dentro del rango
		for(i = 0; i < strLength + 1; i++)
		{
			if(i <= strLength)
			{
				if(guardian->name[i] == '\0')
				{
					i = strLength + 2;
				}
			}
		}		
	}
	while(i == strLength + 1);
	
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
			//Asignacion de puntos de vida
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
			//Asignacion de puntos de ataque
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
			//Asignacion de puntos de defensa
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
	guardian->status = 1;
	guardian->next = NULL;	
}

//Funcion para que el jugador pueda seleccionar un guardian creado
void selectCharacter(Guardian **guardian, Guardian **head, Tournament *data)
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
		//Si el guardian seleccionado era el primer elemento de la lista, entonces el primer elemento de la lista sera su sucesor
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
	
	//El guardian seleccionado como jugador ya no pertenece al total de guardianes
	data->totalGuardians--;
	data->remainingGuardians--;
}

//Funcion para elegir el nivel de dificultad del torneo
void selectTournament(int *difficulty)
{
	//Indicaciones y entrada del dato
	printf("\n\t---------- SELECCIONAR DIFICULTAD ----------\n\n\tNiveles de dificultad:\n\n\t\t* Principiante: Debe derrotar a 3 guardianes\n\t\t* Intermedio: Debe derrotar a 5 guardianes\n\t\t* Experto: Debe derrotar a 7 guardianes\n\n\tSeleccione el nivel de dificultad que desea\n\n\t* Presione <1> para seleccionar la dificultad Principiante\n\t* Presione <2> para seleccionar la dificultad Intermedio\n\t* Presione <3> para seleccionar la dificultad Experto\n\n\t* Ingrese su opcion: ");
	scanf("%d", difficulty);
	
	//Verificacion
	while(*difficulty < 1 || *difficulty > 3)
	{
		printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
		scanf("%d", difficulty);
	}
	
	//Informacion relacionada con la dificultad escogida
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

//Funcion que contiene el menu de inicio del juego (Crear/seleccionar un guardian y seleccionar dificultad de juego)
void menuOptions(Guardian **myGuardian, Guardian **head, int *difficulty, Tournament *data)
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
		createCharacter(*myGuardian, *head);
	}
	else
	{
		selectCharacter(myGuardian, head, data);
	}
	
	action = 0;
	
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

//Funcion para saber el estado de un guardian durante el enfrentamiento
void printCharacterStatus(Guardian *guardian)
{
	printf("\n\t---------- GUARDIAN STATUS: %s ----------\n\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", guardian->name, guardian->life, guardian->attackPoints, guardian->defensePoints);
}

//Funcion para saber el resultado del lanzamiento de un dado
int getRollResult(int diceSize)
{
	srand(time(NULL));
	
	//La variable diceSize indicara la cantidad de numeros del dado. Con un dado tradicional, diceSize tendria el valor 6
	return rand() % diceSize + 1;
}

//Funcion para ver el historial de batalla del jugador una vez que termine su participacion en el torneo
void getResult(History *head, Guardian *myGuardian)
{
	History *current = head;
	int i = 1;
	
	printf("\n\t---------- HISTORIAL DE	ENFRENTAMIENTOS ----------\n");
	
	//Se muestran los datos del historial
	while(current != NULL)
	{
		printf("\n\t---------- ENFRENTAMIENTO %d ----------\n", i);
		printf("\n\tDatos del Guardian\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", current->name, current->type, current->life, current->attackPoints, current->defensePoints);
		
		if(current->resultVsPlayer == 1)
		{
			printf("\n\t* Resultado del enfrentamiento:\n\n\t\t%s (Guardian): Ganador\n\t\t%s (Jugador): Perdedor\n", current->name, myGuardian->name);
		}
		else
		{
			printf("\n\t* Resultado del enfrentamiento:\n\n\t\t%s (Guardian): Perdedor\n\t\t%s (Jugador): Ganador\n", current->name, myGuardian->name);
		}
		
		printf("\n\t* El enfrentamiento termino luego de %d turnos\n", current->turns);
		
		current = current->next;
		
		if(current != NULL)
		{
			i++;
		}
	}
}

//Funcion para comenzar la pelea
void startFight(int *difficulty, int *end, Guardian *local, Guardian *headEnemies, History **headHistory, Tournament *data)
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
	
	//Inicio de la cola de guardianes que van a combatir con el jugador
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
	
	//Se agregan guardianes a la cola de contendientes del jugador hasta que se alcance la cantidad de guardianes correspondiente al nivel
	while(currentContenders < numContenders)
	{
		//Se selecciona un guardian de la lista
		guardiansSelection = rand() % guardiansCount + 1;
		int guardianSelected = 1;
		
		//Si la cola de contendientes esta vacia, el guardian seleccionado aleatoriamente se agrega como primer elemento
		if(headContenders == NULL)
		{
			aux = headEnemies;
			
			//Busqueda del guardian seleccionado aleatoriamente
			while(guardianSelected != guardiansSelection)
			{
				aux = aux->next;
				guardianSelected++;
			}
			
			//Asignacion del guardian seleccionado como primer elemento de la cola de contendientes
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
			
			//Como el guardian agregado es el unico de la cola, apunta a NULL
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
			
			//Asignacion del guardian seleccionado como ultimo elemento de la cola de contendientes
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
			
			//Como el guardian agregado es el ultimo de la cola, apunta a NULL
			current->next = NULL;
		}
		
		//Se incrementa el contador de contendientes agregados a la cola de contendientes
		currentContenders++;
		
		//Se decrementa el contador de guardianes restantes en la lista original
		guardiansCount--;
	}
	
	//Lista de guardianes seleccionados para combatir contra el jugador
	Guardian *aux1 = headContenders;
	int i = 1;
	
	printf("\n\t---------- LISTA DE CONTENDIENTES ----------\n\n\tLa siguiente lista contiene a los guardianes a los que deberas enfrentarte:\n");
	
	while(aux1 != NULL)
	{
		printf("\n\tGuardian %d\n\n\t* Nombre: %s\n\t* Tipo: %s\n\t* Vida: %d\n\t* Puntos de ataque: %d\n\t* Puntos de defensa: %d\n", i, aux1->name, aux1->type, aux1->life, aux1->attackPoints, aux1->defensePoints);
		aux1 = aux1->next;
		
		if(aux1 != NULL)
		{
			i++;
		}
	}
	
	//Pelea
	
	//Copia manipulable del player
	Guardian *myGuardian = local;
	
	int dice = 0, turnPlayer = 0;
	
	printf("\n\t------------------------- COMIENZAN LOS ENFRENTAMIENTOS -------------------------\n");
	
	//Indicaciones de juego
	printf("\n\tAntes de comenzar, se indican algunos puntos relacionados con el modo de juego;\n\n\t1. Si el jugador de turno desea atacar:\n\n\t\ta. Obteniendo 1 al lanzar el dado, sus puntos de ataque se multiplicaran por 0.8\n\t\tb. Obteniendo 3 al lanzar el dado, sus puntos de ataque se multiplicaran por 1\n\t\tc. Obteniendo 5 al lanzar el dado, sus puntos de ataque se multiplicaran por 1.3\n\t\td. Obteniendo un numero para al lanzar el dado, el ataque sera bloqueado por el rival\n\n\t2. Si el jugador de turno desea defender:\n\n\t\ta. Obteniendo 2 al lanzar el dado, sus puntos de defensa se multiplicaran por 0.5\n\t\tb. Obteniendo 4 al lanzar el dado, sus puntos de defensa se multiplicaran por 1\n\t\tc. Obteniendo 6 al lanzar el dado, sus puntos de defensa se multiplicaran por 1.2\n\t\td. Obteniendo un numero impar, sus puntos de defensa se desgastaran un 5% mientras esten sobre 30 puntos\n\n\t3. Obteniendo 6 al lanzar el dado, se vuelve a lanzar el dado (Maximo 1 vez acumulada por turno)\n");
	
	//Los enfrentamientos terminan cuando el jugador es derrotado o el jugador derrota a todos sus contrincantes
	do
	{
		//Contador de turnos
		int turns = 0;
		
		printf("\n\t--------------- ENFRENTAMIENTO %d: %s (Jugador) V/S %s (Guardian) ---------------\n", numContenders - currentContenders + 1, myGuardian->name, headContenders->name);
		
		//Se lanza un dado para saber quien inicia
		//1: Jugador; 2: Contendiente
		dice = getRollResult(2);
		
		//Si el dado arroja un 1, el primer turno es del jugador
		if(dice == 1)
		{
			turnPlayer = 1;
			printf("\n\t***** El primer turno del enfrentamiento es para %s *****\n", myGuardian->name);
		}
		else
		{
			printf("\n\t***** El primer turno del enfrentamiento es para %s *****\n", headContenders->name);
		}
		
		//El enfrentamiento actual termina cuando uno de los dos participantes muere
		do
		{
			int action = 0, again = 0;
			
			//Se detecta el jugador de turno
			if(turnPlayer)
			{
				//Cada jugador tiene como minimo un turno por ronda
				do
				{
					//Incrementacion del contador de turnos
					turns++;
					
					printf("\n\t%s (Turno %d)\n", myGuardian->name, turns);
					
					//Ataca o defiende
					printf("\n\tMenu de acciones\n\n\t* Presiona <1> si desea atacar\n\t* Presiona <2> si desea defenderse\n\n\t* Ingrese su opcion: ");
					scanf("%d", &action);
					
					//Verificacion de input
					while(action != 1 && action != 2)
					{
						printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
						scanf("%d", &action);
					}
					
					//Se lanza el dado
					dice = getRollResult(6);
					printf("\n\t***** Se obtuvo %d al lanzar el dado *****\n", dice);
					
					//Dependiendo del valor del dado, se completa la accion
					if(action == 1)
					{
						//Se multiplica la vida para operar mejor los valores
						headContenders->life *= 10;
						
						switch(dice)
						{
							//Se quita vida al enemigo en los casos 1, 3 y 5
							case 1:								
								headContenders->life -= myGuardian->attackPoints * 8;
								break;
								
							case 3:
								headContenders->life -= myGuardian->attackPoints * 10;
								break;
								
							case 5:
								//Se quita vida al enemigo
								headContenders->life -= myGuardian->attackPoints * 13;
								break;
								
							//Si se obtiene un numero par al lanzar el dado, no se le quita vida al enemigo
							default:
								printf("\n\t***** %s bloqueo el ataque *****\n", headContenders->name);
								break;
						}
						
						//Se reestablece la magnitud normal de la vida, actualizada luego de aplicar los calculos
						headContenders->life /= 10;
						
						//Se muestra la actualizacion
						printCharacterStatus(headContenders);
					}
					else
					{
						//Se multiplica la vida para operar mejor los valores
						myGuardian->life *= 10;
						
						switch(dice)
						{
							//Se aumenta la vida del jugador en los casos 2, 4 y 6
							case 2:
								myGuardian->life += myGuardian->defensePoints * 5;
								break;
								
							case 4:
								myGuardian->life += myGuardian->defensePoints * 10;
								break;
								
							case 6:
								myGuardian->life += myGuardian->defensePoints * 12;
								break;
								
							//Se desgastan los puntos de vida en caso de que tenga mas de 30
							default:
								
								//Calculo del 5% de los puntos de defensa y descuento del total
								if(myGuardian->defensePoints > 30)
								{
									int discount = myGuardian->defensePoints * 5;
									
									myGuardian->defensePoints *= 100;
																		
									myGuardian->defensePoints -= discount;
									
									myGuardian->defensePoints /= 100;
									
									//El jugador no puede tener menos de 30 puntos de defensa
									if(myGuardian->defensePoints < 30)
									{
										myGuardian->defensePoints = 30;
									}
								}
								else
								{
									printf("\n\t***** El jugador (%s) alcanzo el limite inferior de puntos de defensa (30) *****\n", myGuardian->name);
								}
								
								break;
						}
						
						//Se reestablece la magnitud normal de la vida, actualizada luego de aplicar los calculos
						myGuardian->life /= 10;
						
						//Se muestra la actualizacion
						printCharacterStatus(myGuardian);
					}
					
					//Si es el primer turno acumulado y se obtuvo 6 al lanzar el dado, se tiene un turno extra
					if(again != 1 && dice == 6)
					{
						printf("\n\t***** Tienes un turno extra!! *****\n");
						again = 1;
					}
					else
					{
						again = 0;
						
						//Termina el turno del player
						turnPlayer = 0;
					}
				}
				while(again != 0);
			}
			else
			{
				//Cada jugador tiene como minimo un turno por ronda
				do
				{
					//Incrementacion del contador de turnos
					turns++;
					
					printf("\n\t%s (Turno %d)\n", headContenders->name, turns);
					
					//Ataca o defiende
					//Al igual que el jugador, si se obtiene 1, el guardian ataca, mientras que obteniendo 2, se defiende
					action = getRollResult(2);
					
					if(action == 1)
					{
						printf("\n\t***** %s ha decidido atacar *****\n", headContenders->name);
					}
					else
					{
						printf("\n\t***** %s ha decidido defenderse *****\n", headContenders->name);
					}
					
					//Se lanza el dado
					dice = getRollResult(6);
					printf("\n\t***** Se obtuvo %d al lanzar el dado *****\n", dice);
					
					//Dependiendo del valor del dado, se completa la accion
					if(action == 1)
					{
						//Se multiplica la vida para operar mejor los valores
						myGuardian->life *= 10;
						
						switch(dice)
						{
							//Se quita vida al jugador en los casos 1, 3 y 5
							case 1:								
								myGuardian->life -= headContenders->attackPoints * 8;
								break;
								
							case 3:
								myGuardian->life -= headContenders->attackPoints * 10;
								break;
								
							case 5:
								//Se quita vida al enemigo
								myGuardian->life -= headContenders->attackPoints * 13;
								break;
								
							//Si se obtiene un numero par al lanzar el dado, no se le quita vida al enemigo
							default:
								printf("\n\t***** %s bloqueo el ataque *****\n", myGuardian->name);
								break;
						}
						
						//Se reestablece la magnitud normal de la vida, actualizada luego de aplicar los calculos
						myGuardian->life /= 10;
						
						//Se muestra la actualizacion
						printCharacterStatus(myGuardian);
					}
					else
					{
						//Se multiplica la vida para operar mejor los valores
						headContenders->life *= 10;
						
						switch(dice)
						{
							//Se aumenta la vida del jugador en los casos 2, 4 y 6
							case 2:
								headContenders->life += headContenders->defensePoints * 5;
								break;
								
							case 4:
								headContenders->life += headContenders->defensePoints * 10;
								break;
								
							case 6:
								headContenders->life += headContenders->defensePoints * 12;
								break;
								
							//Se desgastan los puntos de vida en caso de que tenga mas de 30
							default:
								
								//Calculo del 5% de los puntos de defensa y descuento del total
								if(headContenders->defensePoints > 30)
								{
									int discount = headContenders->defensePoints * 5;
									
									headContenders->defensePoints *= 100;
																		
									headContenders->defensePoints -= discount;
									
									headContenders->defensePoints /= 100;
									
									//El jugador no puede tener menos de 30 puntos de defensa
									if(headContenders->defensePoints < 30)
									{
										headContenders->defensePoints = 30;
									}
								}
								else
								{
									printf("\n\t***** El guardian (%s) alcanzo el limite inferior de puntos de defensa (30) *****\n", headContenders->name);
								}
								
								break;
						}
						
						//Se reestablece la magnitud normal de la vida, actualizada luego de aplicar los calculos
						headContenders->life /= 10;
						
						//Se muestra la actualizacion
						printCharacterStatus(headContenders);
					}
					
					//Si es el primer turno acumulado y se obtuvo 6 al lanzar el dado, se tiene un turno extra
					if(again != 1 && dice == 6)
					{
						printf("\n\t***** %s tiene un turno extra!! *****\n", headContenders->name);
						again = 1;
					}
					else
					{
						again = 0;
						
						//Es turno del player
						turnPlayer = 1;
					}
				}
				while(again != 0);
			}
		}
		while(myGuardian->life > 0 && headContenders->life > 0);
		
		//Se crea una variable para almacenar un guardian en el historial y se asignan los valores correspondientes
		History *newHistory = (History*)malloc(sizeof(History));
		
		strcpy(newHistory->name, headContenders->name);
		strcpy(newHistory->type, headContenders->type);
		
		//El guardian puede llegar a un minimo de 0 puntos de vida
		if(headContenders->life <= 0)
		{
			newHistory->life = 0;
		}
		else
		{
			newHistory->life = headContenders->life;
		}
		
		newHistory->attackPoints = headContenders->attackPoints;
		newHistory->defensePoints = headContenders->defensePoints;
		newHistory->turns = turns;
		newHistory->next = NULL;
		
		//Si el jugador tiene vida, entonces el guardian murio, es decir, es el perdedor
		if(myGuardian->life > 0)
		{
			newHistory->resultVsPlayer = 2;
		}
		else
		{
			newHistory->resultVsPlayer = 1;
		}
		
		//Se agrega el contendiente al historial de batalla del jugador
		if(*headHistory == NULL)
		{
			*headHistory = newHistory;
		}
		else
		{
			History *current = *headHistory;
			
			//Se ubica el puntero en el ultimo elemento de la lista
			while(current->next != NULL)
			{
				current = current->next;
			}
			
			current->next = newHistory;
		}
		
		//Si se termino la ejecucion del loop y el jugador aun tiene vida, entonces derroto al guardian y debera enfrentarse con el siguiente
		if(myGuardian->life > 0)
		{
			//El jugador debera enfrentarse al siguiente contendiente en la cola
			headContenders = headContenders->next;
			currentContenders--;
			
			//Actualizacion de las estadisticas del torneo
			data->defeatedGuardians++;
			data->remainingGuardians--;
		}
	}
	while(myGuardian->life > 0 && currentContenders > 0);
	
	//Resultados
	if(myGuardian->life <= 0)
	{
		printf("\n\t***** Has sido derrotado por %s *****\n", headContenders->name);
	}
	else
	{
		printf("\n\t***** Felicidades!! Has derrotado a todos tus contrincantes, por lo que has completado la dificultad");
		
		if(*difficulty == 1)
		{
			printf(" Principiante *****\n");
		}
		else if(*difficulty == 2)
		{
			printf(" Intermedio *****\n");
		}
		else
		{
			printf(" Experto *****\n");
		}
	}
	
	*end = 1;
}
