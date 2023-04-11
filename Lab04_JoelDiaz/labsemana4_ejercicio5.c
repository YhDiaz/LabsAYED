#include <stdio.h>
#include <stdlib.h>
#define nameMax 51

//Estructura del tipo Paciente
typedef struct Patient
{
	char name[nameMax];
	int age;
	int room;
	float temp;	
	struct Patient *next;
} Patient;

//Funcion para desplegar el menu de opciones
void menu(int *option, Patient *head)
{
	printf("\n---------- MENU DE ACCIONES ----------\n");
	
	printf("\n\t* Presione <0> para terminar el programa\n\t* Presione <1> para agregar un paciente a la cola");
	
	if(head != NULL)
	{
		printf("\n\t* Presione <2> para quitar un paciente de la cola\n\t* Presione <3> para conocer cuantos paciente faltan por atender\n\t* Presione <4> para saber cuantos pacientes estan antes de un paciente especifico (cuantos turnos faltan)\n\t* Presione <5> para conocer los datos del proximo paciente en salir\n\t* Presione <6> para ver la lista de pacientes\n");	
	}
	
	printf("\n\t* Ingrese su opcion: ");
	scanf("%d", option);
	
	while(*option < 0 || *option > 6)
	{
		printf("\n\t\t* (Error: Valor no definido) Por favor, seleccione una accion definida: ");
		scanf("%d", option);
		
		while(head == NULL && *option != 0 && *option != 1)
		{
			printf("\n\t\t* (Error: La opcion seleccionada esta definida pero no aun no esta habilitada, ya que la cola esta vacia) Por favor, seleccione otra opcion: ");
			scanf("%d", option);
		}
	}
	
	while(head == NULL && *option != 0 && *option != 1)
	{
		printf("\n\t\t* (Error: La opcion seleccionada esta definida pero no aun no esta habilitada, ya que la cola esta vacia) Por favor, seleccione otra opcion: ");
		scanf("%d", option);
		
		while(*option < 0 || *option > 6)
		{
			printf("\n\t\t* (Error: Valor no definido) Por favor, seleccione una accion definida: ");
			scanf("%d", option);
		}
	}
}

//Funcion para agregar pacientes a la cola
void enqueue(Patient **head, Patient **last, int *size)
{
	Patient *newPatient = malloc(sizeof(Patient));
	
	printf("\n\t----- DATOS DEL PACIENTE -----\n");
	printf("\n\t* Ingrese el nombre del paciente: ");
	scanf("%s", &newPatient->name);
	
	printf("\n\t* Ingrese la edad del paciente: ");
	scanf("%d", &newPatient->age);
	
	printf("\n\t* Ingrese la habitacion del paciente: ");
	scanf("%d", &newPatient->room);
	
	printf("\n\t* Ingrese la temperatura del paciente: ");
	scanf("%f", &newPatient->temp);
	
	newPatient->next = NULL;
	
	if(*head == NULL)
	{
		*head = newPatient;
		*last = newPatient;
	}
	else
	{
		Patient *current = *head;
		
		while(current->next != NULL)
		{
			current = current->next;
		}
		
		current->next = newPatient;
		*last = newPatient;
	}
	
	*size += 1;
}

void dequeue(Patient **head, Patient **last, int *size)
{
	if(*size == 1)
	{
		Patient *lastHead = *head;
		
		printf("\n\t***** %s ha sido removida(o) de la cola *****\n", lastHead->name);
		
		free(lastHead);
		*head = NULL;
		*last = NULL;
	}
	else
	{
		Patient *lastHead = *head;
		*head = lastHead->next;
		
		printf("\n\t***** %s ha sido removida(o) de la cola *****\n", lastHead->name);
		
		free(lastHead);
	}
	
	*size -= 1;
	
	if(*size == 0)
	{
		printf("\n\t\t***** No quedan pacientes en la cola *****\n");
	}
}

//Funcion para mostrar la lista de pacientes
void printPatients(Patient *head)
{
	int i = 1;
	Patient *aux = head;
	
	while(aux != NULL)
	{
		printf("\n\tPaciente %d\n\n\t- Nombre: %s\n\t- Edad: %d\n\t- Habitacion: %d\n\t- Temperatura: %.1f%cC\n", i, aux->name, aux->age, aux->room, aux->temp, 167);
		
		i++;
		aux = aux->next;
	}
}

//Funcion para obtener la cantidad de pacientes restantes
void getQueueSize(int *queueSize, Patient *head)
{
	Patient *current = head;
	*queueSize = 0;
	
	while(current != NULL)
	{
		*queueSize += 1;
		current = current->next;
	}
	
	printf("\n\t***** Quedan %d pacientes en la cola *****\n", *queueSize);
}

//Funcion para saber cuantos pacientes faltan para llegar a un paciente especifico
void getLeftPatients(Patient *head)
{
	int i = 1, option = 0;
	Patient *aux = head;
	
	printf("\n\tCola de pacientes:\n");
	
	while(aux != NULL)
	{
		printf("\n\t%d. %s", i, aux->name);
		i++;
		aux = aux->next;
	}
	
	printf("\n\n\t* Ingrese el numero de un paciente para saber cuantas personas hay antes: ");
	scanf("%d", &option);
	
	while(option < 1 || option > i - 1)
	{
		printf("\n\t\t* (Error: El numero ingresado esta fuera del rango) Por favor, indique otro numero: ");
		scanf("%d", &option);
	}
	
	aux = head;
	
	for(i = 0; i < option; i++)
	{
		if(i < option - 1)
		{	
			aux = aux->next;
		}
	}
	
	if(option - 1 == 0)
	{
		printf("\n\t***** El proximo turno es de %s *****\n", aux->name);
	}
	else
	{
		printf("\n\t***** Hay %d persona(s) antes que %s *****\n", option - 1, aux->name);
	}
	
}

//Funcion para saber los datos del proximo paciente en salir de la cola
void getNextPatient(Patient *head)
{
	printf("\n\t***** El proximo paciente en salir de la cola es %s (Edad: %d, Temperatura: %.1f, Habitacion: %d) *****\n", head->name, head->age, head->temp, head->room);
}

//Funcion para liberar el espacio de memoria reservado para el programa
void freePatients(Patient *head)
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
	int option = 0, numPatients = 0, queueSize = 0;
	Patient *head = NULL, *last = NULL;
	
	do
	{
		menu(&option, head);
		
		switch(option)
		{
			case 1:
				enqueue(&head, &last, &queueSize);
				break;
				
			case 2:
				dequeue(&head, &last, &queueSize);
				break;
				
			case 3:
				getQueueSize(&queueSize, head);
				break;
				
			case 4:
				getLeftPatients(head);
				break;
				
			case 5:
				getNextPatient(head);
				break;
				
			case 6:
				printPatients(head);
				break;
		}
	}
	while(option != 0);
	
	freePatients(head);
	
	return 0;
}
