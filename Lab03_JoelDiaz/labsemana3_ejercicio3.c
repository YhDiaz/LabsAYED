#include<stdio.h>
#include<stdlib.h>
#define n 5
#define maxName 25
#define sizeName 20
#define teams 2

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
		
		while(permit < 0 || permit > 1)
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
	
	for(i = 0; i < teams; i++)
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

//Modo: Arena de batalla (Inicio)

//Cantidad maxima de jugadores que pueden ir a la arena
void cantWarriors(int *num, Player tm1[], Player tm2[], int cantPlayers[])
{
	int i = 0, j = 0, warrTm1 = 0, warrTm2 = 0;
	
	for(i = 0; i < teams; i++)
	{
		for(j = 0; j < cantPlayers[i]; j++)
		{
			if(i == 0)
			{
				if(tm1[j].canFight)
				{
					warrTm1++;
				}					
			}
			else
			{
				if(tm2[j].canFight)
				{
					warrTm2++;
				}	
			}
		}
	}
	
	if(warrTm1 < warrTm2)
	{
		*num = warrTm1;
	}
	else
	{
		*num = warrTm2;
	}
	
	printf("\n\n\t***** Cantidad de guerreros por equipo: %d *****", *num);
}

//Seleccion de guerreros por equipo
void warriorsSelect(int max, Player tm1[], Player tm2[], Player warrTm1[], Player warrTm2[], int numPlayers[])
{
	srand(time(NULL));
	int warrior = 0, i = 0, j = 0, k = 0, posTm1[n], posTm2[n];
	
	for(i = 0; i < n; i++)
	{
		posTm1[i] = -1;
		posTm2[i] = -1;
	}
	
	for(i = 0; i < teams; i++)
	{
		printf("\n\n\tGuerreros del equipo %d:\n", i + 1);
		
		for(j = 0; j < max; j++)
		{
			if(i == 0)
			{
				warrior = rand() % numPlayers[i];
				
				for(k = 0; k < n; k++)
				{
					//El jugador seleccionado debe tener permiso para combatir y no haber sido seleccionado antes
					while(tm1[warrior].canFight == 0 || warrior == posTm1[k])
					{
						warrior = rand() % numPlayers[i];
						k = 0;
					}
				}
				
				//Se muestran los nombres de los jugadores seleccionados y se almacenan en un array de jugadores guerreros
				printf("\n\t%d. %s", j + 1, tm1[warrior].name);
				warrTm1[j] = tm1[warrior];
				posTm1[j] = warrior;
			}
			else
			{
				warrior = rand() % numPlayers[i];
				
				for(k = 0; k < n; k++)
				{
					while(tm2[warrior].canFight == 0 || warrior == posTm2[k])
					{
						warrior = rand() % numPlayers[i];
						k = 0;
					}
				}				
				
				printf("\n\t%d. %s", j + 1, tm2[warrior].name);
				warrTm2[j] = tm2[warrior];
				posTm2[j] = warrior;
			}
		}
	}
}

//Ataque basico de cada jugador
void basicAttack(Player tm[], int p, Player tmEnemy[], int max)
{
	int num = 0, basicEnergy = 2, scoreMin = 5, scoreMax = 10, score = 0;
	
	num = rand() % max;
	score = rand() % (scoreMin + 1) + (scoreMax - scoreMin);
	
	tmEnemy[num].health -= score;
	tm[p].score += score;
	tm[p].energy -= basicEnergy;
	
	printf("\n\n\t\t* %s acaba de atacar (ataque basico) a %s", tm[p].name, tmEnemy[num].name);
	
	printf("\n\n\t\tActualizacion de estadisticas:\n\n\t\t%s:\n\t\t\t* Puntaje: %d\n\t\t\t* Energia: %d\n\n\t\t%s:\n\t\t\t* Salud: %d\n", tm[p].name, tm[p].score, tm[p].energy, tmEnemy[num].name, tmEnemy[num].health);
}

//Ataque especial de cada jugador
void specialAttack(Player tm[], int p, Player tmEnemy[], int max)
{
	int num = 0, specialEnergy = 5, scoreMin = 10, scoreMax = 20, score = 0;
	
	num = rand() % max;
	score = rand() % (scoreMin + 1) + (scoreMax - scoreMin);
	
	tmEnemy[num].health -= score;
	tm[p].score += score;
	tm[p].energy -= specialEnergy;
	
	printf("\n\n\t\t* %s acaba de atacar (ataque especial) a %s", tm[p].name, tmEnemy[num].name);
	
	printf("\n\n\t\tActualizacion de estadisticas:\n\n\t\t%s:\n\t\t\t* Puntaje: %d\n\t\t\t* Energia: %d\n\n\t\t%s:\n\t\t\t* Salud: %d\n", tm[p].name, tm[p].score, tm[p].energy, tmEnemy[num].name, tmEnemy[num].health);

}

//Curacion
void healing(Player tm[], int p)
{
	int num = 0, healPower = 25, score = 1;
	
	num = rand() % (healPower - 15) + 16;
	
	if(tm[p].health + num > 100)
	{
		tm[p].health = 100;
	}
	else
	{
		tm[p].health += num;
	}
	
	printf("\n\n\t\t* %s se acaba de curar", tm[p].name);
	
	printf("\n\n\t\tActualizacion de estadisticas:\n\n\t\t%s:\n\t\t\t* Salud: %d\n", tm[p].name, tm[p].health);
}

//Recarga de energia
void chargeEnergy(Player tm[], int p)
{
	int num = 0, powerCharEnergy = 5, score = 1;
	
	num = rand() % (powerCharEnergy - 2) + 3;
	
	if(tm[p].energy + num > 10)
	{
		tm[p].energy = 10;
	}
	else
	{
		tm[p].energy += num;
	}
	
	printf("\n\n\t\t* %s acaba de recargar su energia de combate", tm[p].name);
	
	printf("\n\n\t\tActualizacion de estadisticas:\n\n\t\t%s:\n\t\t\t* Energia: %d\n", tm[p].name, tm[p].energy);
}

//Menu de acciones que pueden hacer los jugadores
void selectOption(int op, Player tm[], Player tmEnemy[], int p, int max)
{
	int num = 0;
	
	num = rand() % op + 1;
	
	//Para poder realizar una accion se deben cumplir ciertos requisitos
	//Accion 1: Ataque basico. Requisito: Tener minimo 2 unidades de energia
	//Accion 2: Ataque especial. Requisito: Tener minimo 5 unidades de energia
	//Accion 3: Curarse. Requisito: No tener la salud al maximo
	//Accion 4: Recargar energia de combate. Requisito: No tener la barra de energia al maximo
	while((num == 1 && tm[p].energy < 2) || (num == 2 && tm[p].energy < 5) || (num == 3 && tm[p].health == 100) || (num == 4 && tm[p].energy == 10))
	{
		num = rand() % op + 1;
	}
	
	printf("\n\n\t\t* %s ha seleccionado la opcion %d", tm[p].name, num);
	
	switch(num)
	{
		case 1:
			basicAttack(tm, p, tmEnemy, max);
			break;
			
		case 2:
			specialAttack(tm, p, tmEnemy, max);
			break;
			
		case 3:
			healing(tm, p);
			break;
			
		case 4:
			chargeEnergy(tm, p);
			break;
	}
}

//Contador de experiencia por equipo
void totalXP(int *xp1, int *xp2, Player tm1[], Player tm2[], int max)
{
	int i = 0, j = 0;
	
	for(i = 0; i < teams; i++)
	{
		for(j = 0; j < max; j++)
		{
			if(i == 0)
			{
				*xp1 += tm1[j].score;
			}
			else
			{
				*xp2 += tm2[j].score;
			}
		}
	}
}

//Estadisticas finales
void stats(int xp1, int xp2, Player tm1[], Player tm2[], int max)
{
	int i = 0, j = 0;
	
	printf("\n\n--------------- ESTADISTICAS ---------------\n");
	
	for(i = 0; i < teams; i++)
	{
		printf("\n\t---------- EQUIPO %d ----------\n", i + 1);
		
		for(j = 0; j < max; j++)
		{
			printf("\n\t\t* Jugador %d\n", j + 1);
			
			if(i == 0)
			{
				printf("\n\t\t- Nombre/Alias: %s\n\t\t- Nivel: %d\n\t\t- Salud: %d\n\t\t- Puntaje: %d\n\t\t- Energia: %d\n\t\t- Permiso para combatir: Si\n", tm1[j].name, tm1[j].level, tm1[j].health, tm1[j].score, tm1[j].energy);
			}
			else
			{
				printf("\n\t\t- Nombre/Alias: %s\n\t\t- Nivel: %d\n\t\t- Salud: %d\n\t\t- Puntaje: %d\n\t\t- Energia: %d\n\t\t- Permiso para combatir: Si\n", tm2[j].name, tm2[j].level, tm2[j].health, tm2[j].score, tm2[j].energy);
			}
		}
	}
	
	printf("\n\n\t* Puntos de experiencia del equipo 1: %d\n\t* Puntos de experiencia del equipo 2: %d", xp1, xp2);
	
	if(xp1 > xp2)
	{
		printf("\n\n\t--------------- EL EQUIPO 1 ES EL GANADOR ---------------");
	}
	else
	{
		printf("\n\n\t--------------- EL EQUIPO 2 ES EL GANADOR ---------------");
	}
}

//Mecanica de combate por turnos
void mechFight(Player tm1[], Player tm2[], int max)
{
	int turn = 1, turnTeam1 = 1, turnTeam2 = 1, i = 0, options = 4, tm1XP = 0, tm2XP = 2;
	
	printf("\n\n---------------- COMIENZA LA BATALLA ---------------");
	
	for(i = 0; i < 10; i++)
	{
		printf("\n\n\tTurno %d", i + 1);
		
		if(i % 2 == 0)
		{
			//Si el jugador tiene mas de 10 puntos, sube de nivel en su proximo turno
			if(tm1[turnTeam1 - 1].score >= 10)
			{
				tm1[turnTeam1 - 1].level++;
			}
			
			selectOption(options, tm1, tm2, turnTeam1 - 1, max);
						
			if(turnTeam1 == max)
			{
				turnTeam1 = 1;
			}
			else
			{
				turnTeam1++;
			}
		}
		else
		{
			if(tm2[turnTeam2 - 1].score >= 10)
			{
				tm2[turnTeam2 - 1].level++;
			}
			
			selectOption(options, tm2, tm1, turnTeam2 - 1, max);
			
			if(turnTeam2 == max)
			{
				turnTeam2 = 1;
			}
			else
			{
				turnTeam2++;
			}
		}
	}
	
	//Calculador de puntos de experiencia por equipo y estadisticas finales
	totalXP(&tm1XP, &tm2XP, tm1, tm2, max);
	stats(tm1XP, tm2XP, tm1, tm2, max);
}

//Modo de arena de combate
void battleMode(Player tm1[], Player tm2[], int cantPlayers[])
{
	int maxWarriors = 0, i = 0, warrPerTm = 0;
	Player warriorsTm1[n], warriorsTm2[n];
	
	printf("\n\n--------------- SIMULACION DE LA ARENA DE BATALLA ---------------\n");
	
	cantWarriors(&maxWarriors, tm1, tm2, cantPlayers);
	
	warriorsSelect(maxWarriors, tm1, tm2, warriorsTm1, warriorsTm2, cantPlayers);
	
	mechFight(warriorsTm1, warriorsTm2, maxWarriors);
}

//Modo: Arena de batalla (Fin)

int main()
{
	srand(time(NULL));
	int cantPlayers[teams];
	Player team1[n], team2[n];
	
	enterData(team1, team2, cantPlayers);
	
	battleMode(team1, team2, cantPlayers);

	return 0;
}
