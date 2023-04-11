#include <stdio.h>
#include <stdlib.h>
#define n 10
#define nameMax 51

//Estructura del tipo Paciente
typedef struct
{
	char name[nameMax];
	int age;
	int room;
	float temperature;
} Patient;

//Funcion que agrega pacientes al array mientras no se alcance el limite "n"
void addPatients (Patient patients[], int *index, int rooms[])
{
	int i = nameMax + 1, firstTime = 1;
	
	//Si aun no se alcanza el maximo de pacientes, se ejecuta el bloque
	if(*index < n)
	{
		//Se piden los datos y se verifican
		printf("\n\n\t--------------- AGREGAR PACIENTE ---------------\n");
		
		Patient *generic = malloc(sizeof(Patient));
		
		//Nombre
		while(i == (nameMax + 1))
		{
			if(firstTime == 1)
			{
				printf("\n\t* Ingrese el nombre del paciente (minimo: 1 caracter, maximo: 50 caracteres): ");
			}
			else
			{
				printf("\n\t\t* (Error: Extension invalida) Por favor, ingrese una cantidad de caracteres dentro del rango: ");
			}
			
			scanf("%s", &generic->name);
			
			for(i = 0; i < nameMax; i++)
			{
				if(i < nameMax - 1)
				{
					if(generic->name[i] == '\0')
					{
						i = nameMax - 1;
					}
				}
				else
				{
					i = nameMax;
				}
				
			}
			
			firstTime = 0;
		}		
		
		//Edad
		printf("\n\t* Ingrese la edad del paciente: ");
		scanf("%d", &generic->age);
		
		while(generic->age < 1 || generic->age > 100)
		{
			printf("\n\t\t* (Error: Edad fuera de rango) Por favor, ingrese una edad razonable: ");
			scanf("%d", &generic->age);
		}
		
		//Habitacion
		printf("\n\t* Ingrese el numero de la habitacion del paciente: ");
		scanf("%d", &generic->room);
		
		while(generic->room < 1 || generic->room > n)
		{
			printf("\n\t\t* (Error: La habitacion no existe) Por favor, ingrese un numero de habitacion valido: ");
			scanf("%d", &generic->room);
			
			while(rooms[generic->room - 1] != 0)
			{
				printf("\n\t\t* (Error: La habitacion esta ocupada) Por favor, ingrese otro numero de habitacion: ");
				scanf("%d", &generic->room);
			}
		}
		
		while(rooms[generic->room - 1] != 0)
		{
			printf("\n\t\t* (Error: La habitacion esta ocupada) Por favor, ingrese otro numero de habitacion: ");
			scanf("%d", &generic->room);
			
			while(generic->room < 1 || generic->room > n)
			{
				printf("\n\t\t* (Error: La habitacion no existe) Por favor, ingrese un numero de habitacion valido: ");
				scanf("%d", &generic->room);
			}
		}
		
		//Temperatura
		printf("\n\t* Ingrese la temperatura del paciente (en grados Celsius): ");
		scanf("%f", &generic->temperature);
		
		while(generic->temperature * 10 < 330 || generic->temperature * 10 > 430)
		{
			printf("\n\t\t* (Error: Temperatura fuera de rango) Por favor, ingrese una temperatura valida: ");
			scanf("%f", &generic->temperature);
		}
		
		//Se agrega el paciente al array de pacientes, se incrementa el indice y se indica que la habitacion esta ocupada
		patients[*index] = *generic;		
		*index += 1;
		rooms[generic->room - 1] = 1;
		
		if(*index == n)
		{
			printf("\n\n\t***** Maximo de pacientes alcanzado (%d) *****", *index);
		}
	}
}

//Funcion que muestra en pantalla la informacion de todos los pacientes
void printPatients (Patient patients[], int index)
{
	int i = 0;
	
	printf("\n\n---------- LISTA DE PACIENTES ----------\n");
	
	for(i = 0; i < index; i++)
	{
		printf("\n\tPaciente %d\n\n\t* Nombre: %s\n\t* Edad: %d\n\t* Habitacion: %d\n\t* Temperatura: %.1f%cC\n", i + 1, patients[i].name, patients[i].age, patients[i].room, patients[i].temperature, 167);
	}
}

//Funcion para continuar el programa
void keepAdding (int *exit)
{
	printf("\n\t---------- CONTINUAR PROGRAMA ----------\n\n\t* Presione <0> para salir\n\t* Presione <1> para continuar\n\n\t* Ingrese su opcion: ");
	scanf("%d", exit);
	
	while(*exit != 0 && *exit != 1)
	{
		printf("\n\t\t* (Error: Valor indefinido) Por favor, ingrese una opcion definida: ");
		scanf("%d", exit);
	}
}

int main ()
{
	int exit = 0, index = 0, rooms[n] = {0};
	Patient patients[n];
	
	do
	{
		addPatients(patients, &index, rooms);
		
		if(index < n)
		{
			keepAdding(&exit);	
		}
		else
		{
			exit = 0;
		}		
	}
	while(exit != 0);
	
	printPatients(patients, index);
	
	return 0;
}
