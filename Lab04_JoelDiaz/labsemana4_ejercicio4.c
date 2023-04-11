#include <stdio.h>
#include <stdlib.h>
#define n 10
#define nameMax 51
#define temps 7

//Estructura del tipo Paciente
typedef struct Patient
{
	char name[nameMax];
	int age;
	int room;
	float temperatures[temps];
	
	//Atributo que contabiliza las temperaturas registradas
	int recordedTemps;
	
	struct Patient *next;
} Patient;

//Funcion para preguntar cuantos pacientes se quieren agregar
void howMany (int *numPatients)
{
	int cant = 0;
	
	printf("\n---------- CANTIDAD DE PACIENTES A INGRESAR ----------\n\n\t* Indique la cantidad de pacientes que desea ingresar (minimo: 1, habitaciones restantes: %d): ", n - *numPatients);
	scanf("%d", &cant);
	
	while(cant < 1 || cant + *numPatients > n)
	{
		printf("\n\t\t* (Error: La cantidad de pacientes que se desean ingresar esta fuera del rango permitido) Por favor, ingrese un valor valido: ");
		scanf("%d", &cant);
	}
	
	//Se incrementa el numero total de pacientes desde la direccion de memoria
	*numPatients += cant;
}

//Funcion que agrega pacientes al array mientras no se alcance el limite "n"
void addPatients (int *index, int rooms[], int *totalTemps, Patient **head)
{
	int i = 0, j = nameMax + 1, firstTime = 1, currentNum = *index, k = 0;
	
	//La variable index se recibe en la funcion "addPatients" como puntero, por lo que no se agrega "&" al pasarla a "howMany"
	howMany(index);
	
	printf("\n\t-------------------- AGREGAR PACIENTES --------------------\n");
	
	//Si aun no se alcanza el maximo de pacientes, se ejecuta el bloque
	for(i = 0; i < *index - currentNum; i++)
	{
		//Se piden los datos y se verifican
		printf("\n\t--------------- AGREGAR PACIENTE %d ---------------\n", currentNum + i + 1);
		
		Patient *generic = malloc(sizeof(Patient));
		
		j = nameMax + 1;
		firstTime = 1;
		
		//Nombre
		while(j == (nameMax + 1))
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
			
			//Comprobacion de la extension del nombre
			for(j = 0; j < nameMax; j++)
			{
				if(j < nameMax - 1)
				{
					//Si se indica el termino del array ('\0') antes de que la extension del nombre indique 50 caracteres, la extension es valida
					if(generic->name[j] == '\0')
					{
						j = nameMax - 1;
					}
				}
				else
				{
					j = nameMax;
				}
				
			}
			
			/*La variable firstTime se usa para saber si hay algun error en el ingreso de datos, pues, si el bucle
			se ejecuta 2 o mas veces, significa que hubo un error*/
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
		
		//Se inicializa la variable que contabiliza las temperaturas registradas
		generic->recordedTemps = 0;
		
		printf("\n\t* Indique la cantidad de temperaturas que desea registrar (minimo: 1, maximo: %d): ", temps);
		scanf("%d", &generic->recordedTemps);
		
		while(generic->recordedTemps < 1 || generic->recordedTemps > temps)
		{
			printf("\n\t\t* (Error: La cantidad de temperaturas que se quiere registrar esta fuera del rango) Por favor, ingrese una cantidad dentro del rango: ");
			scanf("%d", &generic->recordedTemps);
		}
		
		//Se incrementa el total de temperaturas
		*totalTemps += generic->recordedTemps;
		
		for(k = 0; k < generic->recordedTemps; k++)
		{
			printf("\n\t* Ingrese la temperatura %d del paciente (en grados Celsius): ", k + 1);
			scanf("%f", &generic->temperatures[k]);
			
			while(generic->temperatures[k] * 10 < 330 || generic->temperatures[k] * 10 > 430)
			{
				printf("\n\t\t* (Error: Temperatura fuera de rango) Por favor, ingrese una temperatura valida: ");
				scanf("%f", &generic->temperatures[k]);
			}
		}
		
		//Next patient
		generic->next = NULL;
		
		//Se indica que la habitacion esta ocupada
		rooms[generic->room - 1] = 1;
		
		//Asignacion del puntero que indica la direccion de memoria del siguiente paciente en la lista
		if(*head == NULL)
		{
			*head = generic;
		}
		else
		{
			Patient *current = *head;
			
			while(current->next != NULL)
			{
				current = current->next;
			}
			
			current->next = generic;
		}
	}
	
	if(*index == n)
	{
		printf("\n\t***** Maximo de pacientes alcanzado (%d) *****\n", *index);
	}
}

//Funcion que muestra en pantalla la informacion de todos los pacientes
void printPatients (Patient *head, int index)
{
	int i = 0, j = 0;
	
	printf("\n\n---------- LISTA DE PACIENTES ----------\n");
	
	Patient *current = head;
	
	for(i = 0; i < index; i++)
	{
		printf("\n\tPaciente %d\n\n\t* Nombre: %s\n\t* Edad: %d\n\t* Habitacion: %d\n\n\t* Temperaturas:\n\n", i + 1, current->name, current->age, current->room);
			
		//Se recorre el array de temperaturas del paciente
		for(j = 0; j < current->recordedTemps; j++)
		{			
			printf("\t- Temperatura %d: %.1f%cC\n", j + 1, current->temperatures[j], 167);
		}
		
		if(current->next != NULL)
		{
			current = current->next;
		}		
	}
	
	if(index == 1)
	{
		printf("\n\n\t***** Se registro 1 paciente *****\n");
	}
	else
	{
		printf("\n\n\t***** Se registraron %d pacientes *****\n", index);
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

//Funcion para registrar mas temperaturas
void recordTemperature (Patient *head, int numPatients, int *totalTemps)
{
	int add = 0, i = 0, patient = 0, cantTemps = 0, j = 0, available = 0, exit = 0;
	Patient patients[numPatients];
	
	printf("\n\t---------- AGREGAR REGISTRO DE TEMPERATURAS ----------\n");
	
	Patient *current = (Patient*)malloc(sizeof(Patient));
	current = head;
	
	//Se busca al menos un paciente al que se le puedan agregar registros de temperatura
	for(i = 0; i < numPatients; i++)
	{
		if(current->recordedTemps < temps)
		{
			available = 1;
			i = numPatients;
		}
		
		current = current->next;
	}
	
	if(available == 1)
	{
		do
		{
			//Instrucciones y comprobacion del dato ingresado
			printf("\n\t* Presione <0> para continuar el programa\n\t* Presione <1> para registrar una nueva temperatura en un paciente\n\n\t* Ingrese su opcion: ");
			scanf("%d", &add);
		
			while(add != 0 && add != 1)
			{
				printf("\n\t\t* (Error: Valor indefinido) Por favor, ingrese una opcion definida: ");
				scanf("%d", &add);
			}
			
			if(add == 1)
			{
				printf("\n\tLista de pacientes:\n");
				
				current = head;
				
				//Se muestra la lista enumerada de pacientes
				for(i = 0; i < numPatients; i++)
				{
					printf("\n\t%d. %s ", i + 1, current->name);
					
					//Se indica si el paciente tiene el registro de temperaturas completo o la cantidad de temperaturas que aun se pueden registrar
					if(current->recordedTemps == temps)
					{
						printf("(Registro completo)");
					}
					else
					{
						printf("(Registros restantes: %d)", temps - current->recordedTemps);
					}
					
					current = current->next;
				}
				
				//Instrucciones y comprobacion del dato ingresado
				printf("\n\n\t* Indique el numero del paciente al que desea registrarle la(s) temperatura(s) (SOLO EL NUMERO): ");
				scanf("%d", &patient);
				
				//Se hacen las comprobaciones respectivas al paciente en cuestion
				do
				{
					while(patient < 1 || patient > numPatients)
					{
						printf("\n\t\t* (Error: El numero ingresado esta fuera del rango) Por favor, ingrese un numero valido: ");
						scanf("%d", &patient);
					}
					
					current = head;
					
					//Se detecta el paciente escogido
					for(i = 1; i < patient; i++)
					{
						current = current->next;
					}
					
					if(current->recordedTemps >= temps)
					{
						exit = -1;
						printf("\n\t\t* (Error: El paciente ya tiene un registro completo) Por favor, seleccione un paciente que tenga espacios disponibles para mas registros: ");
						scanf("%d", &patient);
					}
					
					if(exit != -1)
					{
						exit = 1;
					}					
				}
				while(exit != 1);
				
				//Se pide la cantidad de temperaturas que se quieren registrar y se comprueba el dato ingresado
				printf("\n\t* Indique la cantidad de temperaturas que desea registrar de %s (minimo: 1, maximo: %d): ", current->name, temps - current->recordedTemps);
				scanf("%d", &cantTemps);
				
				while(cantTemps < 1 || cantTemps > temps - current->recordedTemps)
				{
					printf("\n\t\t* (Error: Cantidad de temperaturas fuera del rango establecido) Por favor, indique una cantidad valida: ");
					scanf("%d", &cantTemps);
				}
				
				for(j = 0; j < cantTemps; j++)
				{
					printf("\n\t\t* Ingrese la temperatura %d (temperatura %d en el registro): ", j + 1, current->recordedTemps + 1);
					scanf("%f", &current->temperatures[current->recordedTemps]);
					
					//Comprobacion de rango
					while(current->temperatures[current->recordedTemps] * 10 < 330 || current->temperatures[current->recordedTemps] * 10 > 430)
					{
						printf("\n\t\t* (Error: Temperatura fuera de rango) Por favor, ingrese una temperatura valida: ");
						scanf("%f", &current->temperatures[current->recordedTemps]);
					}
					
					current->recordedTemps++;
				}
				
				//Se incrementa la cantidad total de temperaturas
				*totalTemps += cantTemps;
			}
			
			//Se comprueba nuevamente si queda al menos un paciente al que se le puede registrar una temperatura
			available = 0;
			
			current = head;
			
			for(i = 0; i < numPatients; i++)
			{
				if(current->recordedTemps < temps)
				{
					available = 1;
					i = numPatients;
				}
				
				current = current->next;
			}
			
			if(available == 0)
			{
				printf("\n\t***** Todos los pacientes tienen el registro de temperaturas completo *****\n");
				add = 0;
			}
		}
		while(add == 1);
	}
	else
	{
		printf("\n\t***** Todos los pacientes tienen el registro de temperaturas completo *****\n");
	}
}

//Funcion para dar de alta a un paciente
void dischargePatient (Patient *head, int *numPatients)
{
	int option = 0, i = 0, patient = 0;
	
	printf("\n\t---------- DAR DE ALTA A UN PACIENTE ----------\n");

	printf("\n\t* Presione <0> para continuar el programa\n\t* Presione <1> para dar de alta a un paciente\n\n\t* Ingrese su opcion: ");
	scanf("%d", &option);
	
	while(option != 0 && option != 1)
	{
		printf("\n\t\t (Error: El valor ingresado no esta definido) Por favor, ingrese un valor valido: ");
		scanf("%d", &option);
	}
	
	if(option == 1)
	{
		Patient *current = malloc(sizeof(Patient));
		
		printf("\n\tLista de pacientes:\n");
		
		current = head;
		
		for(i = 0; i < *numPatients; i++)
		{
			printf("\n\t%d. %s", i + 1, current->name);
			
			current = current->next;
		}
		
		printf("\n\n\t* Indique el numero del paciente al que desea registrarle la(s) temperatura(s) (SOLO EL NUMERO): ");
		scanf("%d", &patient);
	
		while(patient < 1 || patient > *numPatients)
		{
			printf("\n\t\t* (Error: El numero ingresado esta fuera del rango) Por favor, ingrese un numero valido: ");
			scanf("%d", &patient);
		}
		
		Patient *aux = malloc(sizeof(Patient));
		//Patient *next = malloc(sizeof(Patient));
		
		current = head;
			
		//Se detecta el paciente escogido
		for(i = 1; i < patient; i++)
		{
			if(i == patient - 1)
			{
				aux = current;
			}
			
			current = current->next;
		}
		
		printf("\n\t\t***** %s ha sido dada(o) de alta *****\n", current->name);
		
		aux->next = current->next;
		
		free(current);
		
		//Se disminuye el contador de pacientes
		*numPatients -= 1;
	}
}

//Funcion para liberar el espacio de memoria reservado para el programa
void freePatients (Patient *head)
{
	Patient *current = head;
	
	while(current != NULL)
	{
		//Se almacena el siguiente elemento de la lista
		Patient *next = current->next;
		
		//Se libera el espacio de memoria reservado para el elemento actual
		free(current);
		
		//Se asigna el siguiente elemento de la lista como el elemento actual
		current = next;
	}
}

int main ()
{
	int exit = 0, numPatients = 0, rooms[n] = {0}, tempsEntered = 0;
	Patient *head = NULL;
	
	do
	{
		//Se llama a la funcion para agregar pacientes, luego a la funcion para agregar mas temperaturas y finalmente a la funcion para dar de alta un paciente
		if(numPatients < n)
		{
			addPatients(&numPatients, rooms, &tempsEntered, &head);
		}
		
		if(tempsEntered < temps * n)
		{
			recordTemperature(head, numPatients, &tempsEntered);
		}
		
		if(numPatients > 0)
		{
			dischargePatient(head, &numPatients);
		}
		
		if(numPatients < n || tempsEntered < temps * n)
		{
			keepAdding(&exit);
		}
		else
		{
			exit = 0;
		}		
	}
	while(exit != 0);
	
	printPatients(head, numPatients);
	
	freePatients(head);
	
	return 0;
}
