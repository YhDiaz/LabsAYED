#include <stdio.h>
#include <stdlib.h>
#define n 10
#define nameMax 51
#define temps 7

//Estructura del tipo Paciente
typedef struct
{
	char name[nameMax];
	int age;
	int room;
	float temperatures[temps];
	
	//Atributo que contabiliza las temperaturas registradas
	int recordedTemps;
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
void addPatients (Patient patients[], int *index, int rooms[], int *totalTemps)
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
		
		//Se agrega el paciente al array de pacientes y se indica que la habitacion esta ocupada
		patients[currentNum + i] = *generic;
		rooms[generic->room - 1] = 1;
	}
	
	if(*index == n)
	{
		printf("\n\t***** Maximo de pacientes alcanzado (%d) *****\n", *index);
	}
}

//Funcion que muestra en pantalla la informacion de todos los pacientes
void printPatients (Patient patients[], int index)
{
	int i = 0, j = 0;
	
	printf("\n\n---------- LISTA DE PACIENTES ----------\n");
	
	for(i = 0; i < index; i++)
	{
		printf("\n\tPaciente %d\n\n\t* Nombre: %s\n\t* Edad: %d\n\t* Habitacion: %d\n\n\t* Temperaturas:\n\n", i + 1, patients[i].name, patients[i].age, patients[i].room);
		
		//Se recorre el array de temperaturas del paciente
		for(j = 0; j < patients[i].recordedTemps; j++)
		{
			printf("\t- Temperatura %d: %.1f%cC\n", j + 1, patients[i].temperatures[j], 167);
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
void recordTemperature (Patient patients[], int numPatients, int *totalTemps)
{
	int add = 0, i = 0, patient = 0, cantTemps = 0, j = 0, available = 0;
	
	printf("\n\t---------- AGREGAR REGISTRO DE TEMPERATURAS ----------\n");
	
	//Se busca al menos un paciente al que se le puedan agregar registros de temperatura
	for(i = 0; i < numPatients; i++)
	{
		if(patients[i].recordedTemps < temps)
		{
			available = 1;
			i = numPatients;
		}
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
				
				//Se muestra la lista enumerada de pacientes
				for(i = 0; i < numPatients; i++)
				{
					printf("\n\t%d. %s ", i + 1, patients[i].name);
					
					//Se indica si el paciente tiene el registro de temperaturas completo o la cantidad de temperaturas que aun se pueden registrar
					if(patients[i].recordedTemps == temps)
					{
						printf("(Registro completo)");
					}
					else
					{
						printf("(Registros restantes: %d)", temps - patients[i].recordedTemps);
					}
				}
				
				//Instrucciones y comprobacion del dato ingresado
				printf("\n\n\t* Indique el numero del paciente al que desea registrarle la(s) temperatura(s) (SOLO EL NUMERO): ");
				scanf("%d", &patient);
				
				while(patient < 1 || patient > numPatients)
				{
					printf("\n\t\t* (Error: El numero ingresado esta fuera del rango) Por favor, ingrese un numero valido: ");
					scanf("%d", &patient);
					
					while(patients[patient - 1].recordedTemps == temps)
					{
						printf("\n\t\t* (Error: El paciente ya tiene un registro completo) Por favor, seleccione un paciente que tenga espacios disponibles para mas registros: ");
						scanf("%d", &patient);
					}
				}
				
				while(patients[patient - 1].recordedTemps == temps)
				{
					printf("\n\t\t* (Error: El paciente ya tiene un registro completo) Por favor, seleccione un paciente que tenga espacios disponibles para mas registros: ");
					scanf("%d", &patient);
					
					while(patient < 1 || patient > numPatients)
					{
						printf("\n\t\t* (Error: El numero ingresado esta fuera del rango) Por favor, ingrese un numero valido: ");
						scanf("%d", &patient);
					}
				}
				
				//Se pide la cantidad de temperaturas que se quieren registrar y se comprueba el dato ingresado
				printf("\n\t* Indique la cantidad de temperaturas que desea registrar de %s (minimo: 1, maximo: %d): ", patients[patient - 1].name, temps - patients[patient - 1].recordedTemps);
				scanf("%d", &cantTemps);
				
				while(cantTemps < 1 || cantTemps > temps - patients[patient - 1].recordedTemps)
				{
					printf("\n\t\t* (Error: Cantidad de temperaturas fuera del rango establecido) Por favor, indique una cantidad valida: ");
					scanf("%d", &cantTemps);
				}
				
				//Para registrar las temperaturas se utiliza la variable "patient" para acceder a la posicion en la lista de pacientes
				/*patients[patient - 1] (como la lista enumerada de pacientes comienza desde 1, se debe restar al momento de acceder
				a la posicion en el array de pacientes)*/
				
				/*Para acceder a la posicion que corresponde en el array de temperaturas, se usa la cantidad de temperaturas registradas. Dado que
				esta variable se incrementa posterior al ingreso de temperaturas, su valor coincide con la posicion actual a la que se quiere acceder*/
				//temperatures[ *****recordedTemps***** ]
				
				//Sin embargo, la variable recordedTemps tambien pertenece al paciente en cuestion, por lo que se debe reemplazar;
				//temperatures[ *****patients[patient - 1].recordedTemps***** ]
				
				//La expresion final para acceder a la posicion de la temperatura que se quiere ingresar es:
				//patients[patient - 1].temperatures[patients[patient - 1].recordedTemps]
				
				for(j = 0; j < cantTemps; j++)
				{
					printf("\n\t\t* Ingrese la temperatura %d (temperatura %d en el registro): ", j + 1, patients[patient - 1].recordedTemps + 1);
					scanf("%f", &patients[patient - 1].temperatures[patients[patient - 1].recordedTemps]);
					
					//Comprobacion de rango
					while(patients[patient - 1].temperatures[patients[patient - 1].recordedTemps] * 10 < 330 || patients[patient - 1].temperatures[patients[patient - 1].recordedTemps] * 10 > 430)
					{
						printf("\n\t\t* (Error: Temperatura fuera de rango) Por favor, ingrese una temperatura valida: ");
						scanf("%f", &patients[patient - 1].temperatures[patients[patient - 1].recordedTemps]);
					}
					
					patients[patient - 1].recordedTemps++;
				}
				
				//Se incrementa la cantidad total de temperaturas
				*totalTemps += cantTemps;
			}
			
			//Se comprueba nuevamente si queda al menos un paciente al que se le puede registrar una temperatura
			available = 0;
			
			for(i = 0; i < numPatients; i++)
			{
				if(patients[i].recordedTemps < temps)
				{
					available = 1;
					i = numPatients;
				}
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

int main ()
{
	int exit = 0, numPatients = 0, rooms[n] = {0}, tempsEntered = 0;
	Patient patients[n];
	
	do
	{
		//Se llama a la funcion para agregar pacientes y luego a la funcion para agregar mas temperaturas
		
		if(numPatients < n)
		{
			addPatients(patients, &numPatients, rooms, &tempsEntered);
		}
		
		if(tempsEntered < temps * n)
		{
			recordTemperature(patients, numPatients, &tempsEntered);
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
	
	printPatients(patients, numPatients);
	
	return 0;
}
