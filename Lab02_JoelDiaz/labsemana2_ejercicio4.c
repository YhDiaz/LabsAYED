#include<stdio.h>

//Variables globales
#define n 10

//Preliminares (Inicio)

//Verificacion 1: Unidad de medida de la temperatura	
int ver01TempUnit(void)
{
	int tempUnit = 0;
	
	printf("\n\n\t* Ingrese su eleccion: ");
	scanf("%d", &tempUnit);
	getchar();

	while(tempUnit != 1 && tempUnit != 2)
	{
		printf("\n\t\t* (Error: Valor indefinido) Por favor, seleccione una opcion valida: ");
		scanf("%d", &tempUnit);
		getchar();
	}
	
	if(tempUnit == 1)
	{
		printf("\n\t***** La temperatura sera medida en grados Celsius (%cC) *****", 167);
	}
	else
	{
		printf("\n\t***** La temperatura sera medida en grados Fahrenheit (%cF) *****", 167);
	}
	
	return tempUnit;
}

//Verificacion 2: Numero de pacientes
int ver02NumPatients(int availableRooms)
{
	int cantPatients = 0;
	
	printf("\n\n--------------- NUMERO DE PACIENTES ---------------");
	printf("\n\n\t* Indique la cantidad de pacientes cuyos datos desea ingresar (minimo: 1, maximo: %d): ", availableRooms);
	scanf("%d", &cantPatients);
	getchar();
	
	while(cantPatients < 1 || cantPatients > availableRooms)
	{
		printf("\n\t\t* (Error: Numero de pacientes fuera de rango) Por favor, ingrese un numero valido: ");
		scanf("%d", &cantPatients);
		getchar();
	}
	
	return cantPatients;
}

//Preliminares (Fin)

//Datos del paciente (Inicio)

//Habitacion (Inicio)

//Habitaciones disponibles
void availableRooms(int roomForPatients[])
{
	int j = 0;
	
	printf("\n\n\t----- HABITACION -----\n\n\tHabitaciones disponibles:\n");
	
	for(j = 0; j < n; j++)
	{
		if(roomForPatients[j] == 0)
		{
			printf("\n\t\t* Habitacion %d", j + 1);
		}
	}
}

//Verificacion 3: Numero de habitacion del paciente
int roomNum(int roomForPatients[], int patient)
{
	int room = -1;
	
	printf("\n\n\t* Ingrese el numero de habitacion que se le asignara al paciente %d: ", patient);
	scanf("%d", &room);
	getchar();
			
	while(room < 1 || room > n)
	{
		printf("\n\t\t* (Error: La habitacion ingresada no existe) Por favor, ingrese un numero de habitacion valido: ");
		scanf("%d", &room);
		getchar();
				
		while(roomForPatients[room - 1] != 0)
		{
			printf("\n\t\t* (Error: La habitacion no esta disponible) Por favor, seleccione una habitacion disponible (mirar lista de arriba): ");
			scanf("%d", &room);
			getchar();
		}
	}
		
	while(roomForPatients[room - 1] != 0)
	{
		printf("\n\t\t* (Error: La habitacion no esta disponible) Por favor, seleccione una habitacion disponible (mirar lista de arriba): ");
		scanf("%d", &room);
		getchar();
			
		while(room < 1 || room > n)
		{
			printf("\n\t\t* (Error: La habitacion ingresada no existe) Por favor, ingrese un numero de habitacion valido: ");
			scanf("%d", &room);
			getchar();
		}
	}
	
	return room;
}

//Asignacion de habitacion
void roomAssignment(int roomForPatients[], int patient)
{
	int room = 0;
	
	availableRooms(roomForPatients);
	
	room = roomNum(roomForPatients, patient);
	
	roomForPatients[room - 1] = patient;
}

//Habitacion (Fin)

//Edad (Inicio)

//Registro de edad del paciente
void patientAge(int ages[], int patient)
{
	int age = 0;
	
	printf("\n\t----- EDAD -----\n\n\t* Ingrese la edad del paciente %d: ", patient);
	scanf("%d", &age);
	getchar();
	
	while(age < 0 || age > 100)
	{
		printf("\n\t\t* (Error: Edad fuera del rango humano) Por favor, ingrese una edad razonable: ");
		scanf("%d", &age);
		getchar();
	}
	
	ages[patient - 1] = age;
}

//Edad (Fin)

//Temperatura (Inicio)

//Informacion sobre la seccion de registro de temperatura
void infoTemps(int patient, int tempUnit)
{
	printf("\n\t----- REGISTRO DE TEMPERATURA DIARIA Y TEMPERATURA MEDIA DEL PACIENTE %d (EN UNA SEMANA) -----\n\n\tIndicaciones:\n\n\t- 1. Utilice el punto para separar las cifras enteras de las decimales, de lo contrario, no se asignara la parte decimal y el seguimiento sera inexacto\n\t- 2. Recuerde la unidad de temperatura que eligio al inicio para ingresar temperaturas que sean razonables ", patient);

	if(tempUnit == 1)
	{
		printf("(La unidad de medida actual de la temperatura es: %cC)\n", 167);
	}
	else
	{
		printf("(La unidad de medida actual de la temperatura es: %cF)\n", 167);
	}
}

//Almacenamiento de temperaturas y calculos relacionados
int storageTemps(float mtxTemps[n][8], float temp, int j, int patient, float averageTemp, int tempUnit)
{
	int feverThresholdCelsius = 375, feverThresholdFahrenheit = 995, daysWithFever = 0, fever3Days = 0, i = 0;
	
	mtxTemps[patient - 1][j] = temp;
	
	if(j == 6)
	{
		for(i = 0; i < 7; i++)
		{
			if(tempUnit == 1)
			{
				if(mtxTemps[patient - 1][i] * 10 >= feverThresholdCelsius)
				{
					daysWithFever++;
					
					if(daysWithFever >= 3)
					{
						fever3Days = 1;
					}
				}
				else
				{
					daysWithFever = 0;
				}
			}
			else
			{
				if(mtxTemps[patient - 1][i] * 10 >= feverThresholdFahrenheit)
				{
					daysWithFever++;
					
					if(daysWithFever >= 3)
					{
						fever3Days = 1;
					}
				}
				else
				{
					daysWithFever = 0;
				}
			}			
		}		
		
		averageTemp /= 7;
		mtxTemps[patient - 1][7] = averageTemp;
	}
		
	return fever3Days;
}

//Verificacion 4: Ingreso de temperaturas diarias
int dailyTemps(int patient, int tempUnit, float mtxTemps[n][8])
{
	int j = 0, tempsCol = 8, fever3Days = 0;
	float temp = 0, averageTemp = 0;
	
	for(j = 0; j < tempsCol - 1; j++)
	{
		printf("\n\t* Ingrese la temperatura que el paciente %d tuvo el dia %d: ", patient, j + 1);
		scanf("%f", &temp);
		getchar();
		
		if(tempUnit == 1)
		{
			while(temp < 33 || temp > 43)
			{
				printf("\n\t\t* (Error: Temperatura ingresada fuera del rango que puede soportar un humano) Por favor, ingrese un valor razonable: ");
				scanf("%f", &temp);
				getchar();
			}
			
			averageTemp += temp;
		}
		else
		{
			while(temp * 10 < 914 || temp * 10 > 1094)
			{
				printf("\n\t\t* (Error: Temperatura ingresada fuera del rango que puede soportar un humano) Por favor, ingrese un valor razonable: ");
				scanf("%f", &temp);
				getchar();
			}
			
			averageTemp += temp;
		}
		
		fever3Days = storageTemps(mtxTemps, temp, j, patient, averageTemp, tempUnit);			
	}
	
	return fever3Days;
}

//Registro de temperatura del paciente
int patientTemps(int patient, int tempUnit, float mtxTemps[n][8])
{
	int fever3Days = 0;
	
	infoTemps(patient, tempUnit);
			
	fever3Days = dailyTemps(patient, tempUnit, mtxTemps);
			
	return fever3Days;
}

//Temperatura (Fin)

//Registro de datos del paciente
void patientData(int patient,int roomForPatients[], int ages[], int tempUnit, float mtxTemps[n][8], int fever3Days)
{
	int j = 0, tempsCol = 8;
	
	printf("\n\n\t\tPlanilla de datos del paciente %d:", patient);
	
	for(j = 0; j < n; j++)
	{
		if(roomForPatients[j] == patient)
		{
			printf("\n\n\t\t* Habitacion asignada: %d", j + 1);
		}
	}
	
	printf("\n\t\t* Edad: %d", ages[patient - 1]);
	printf("\n\t\t* Registro de temperatura diaria:\n");
	
	for(j = 0; j < tempsCol - 1; j++)
	{
		if(tempUnit == 1)
		{
			printf("\n\t\t\t- Dia %d: %.1f%cC", j + 1, mtxTemps[patient - 1][j], 167);
		}
		else
		{
			printf("\n\t\t\t- Dia %d: %.1f%cF", j + 1, mtxTemps[patient - 1][j], 167);
		}
	}
	
	if(tempUnit == 1)
	{
		printf("\n\n\t\t\t* Temperatura promedio: %.1f%cC\n", mtxTemps[patient - 1][7], 167);
	}
	else
	{
		printf("\n\n\t\t\t* Temperatura promedio: %.1f%cF\n", mtxTemps[patient - 1][7], 167);
	}
	
	if(fever3Days == 1)
	{
		printf("\n\t\t* IMPORTANTE: El paciente tuvo fiebre por 3 o mas dias consecutivos\n");
	}
}

//Algoritmo general de registro de datos
int generalData(int cantPatients, int patient, int roomForPatients[], int ages[], int tempUnit, float mtxTemps[n][8])
{
	int i = 0, fever3Days = 0, averageTemp = 0;
	
	for(i = 0; i < cantPatients; i++)
	{
		fever3Days = 0;
		averageTemp = 0;
		patient++;
		
		printf("\n---------- DATOS PACIENTE %d ----------", patient);
		printf("\n\n* Por favor, ingrese los datos solicitados del paciente %d;", patient);
		
		//Habitacion			
		roomAssignment(roomForPatients, patient);
		
		//Edad
		patientAge(ages, patient);
		
		//Temperaturas
		fever3Days = patientTemps(patient, tempUnit, mtxTemps);
		
		//Datos del paciente
		patientData(patient, roomForPatients, ages, tempUnit, mtxTemps, fever3Days);
	}
	
	return patient;
}

//Datos del paciente (Fin)

//Funcionamiento del programa (Inicio)

//Seguir/finalizar programa
int endProgram(void)
{
	int continueProgram = 1;
	
	printf("\n\t\t---------- CONTINUAR PROGRAMA ----------\n\n\t\tSeleccione una de las opciones que siguen;\n\n\t\t* Presione <1> si desea registrar mas pacientes\n\t\t* Presione <0> si desea terminar el proceso de registro, ver los datos y finalizar el programa\n\n\t\t* Ingrese su opcion: ");
	scanf("%d", &continueProgram);
	getchar();
	
	while(continueProgram != 0 && continueProgram != 1)
	{
		printf("\n\t\t\t* (Error: Opcion indefinida) Por favor, seleccione una opcion valida: ");
		scanf("%d", &continueProgram);
		getchar();
	}
}

//Resultados del seguimiento
void results(int patient,int roomForPatients[], int ages[], int tempUnit, float mtxTemps[n][8])
{
	int i = 0, j = 0, tempsCol = 8;
	
	printf("\n\n------------------------------ DATOS DE LOS PACIENTES ------------------------------");
	
	for(i = 0; i < patient; i++)
	{
		printf("\n\n-------------------- PACIENTE %d --------------------", i + 1);
	
		printf("\n\n\t\tPlanilla de datos del paciente %d:", i + 1);
		
		for(j = 0; j < n; j++)
		{
			if(roomForPatients[j] == i + 1)
			{
				printf("\n\n\t\t* Habitacion asignada: %d", j + 1);
			}
		}
		
		printf("\n\t\t* Edad: %d", ages[i]);
		printf("\n\t\t* Registro de temperatura diaria:\n");
		
		for(j = 0; j < tempsCol - 1; j++)
		{
			if(tempUnit == 1)
			{
				printf("\n\t\t\t- Dia %d: %.1f%cC", j + 1, mtxTemps[i][j], 167);
			}
			else
			{
				printf("\n\t\t\t- Dia %d: %.1f%cF", j + 1, mtxTemps[i][j], 167);
			}
		}
		
		if(tempUnit == 1)
		{
			printf("\n\n\t\t\t* Temperatura promedio: %.1f%cC", mtxTemps[i][7], 167);
		}
		else
		{
			printf("\n\n\t\t\t* Temperatura promedio: %.1f%cF", mtxTemps[i][7], 167);
		}
	}
}

//Funcionamiento del programa (Fin)

int main()
{
	int tempUnit = 0, availableRooms = n, continueProgram = 0, cantPatients, roomForPatients[n] = {0}, patient = 0, ages[n] = {0};
	float mtxTemps[n][8] = {0}, temp = 0, averageTemp = 0;
	
	//Informacion	
	printf("-------------------- SEGUIMIENTO DE PACIENTES DURANTE LA PANDEMIA DE COVID-19 --------------------");
	printf("\n\nEl siguiente programa permite realizar el seguimiento de un maximo de 100 pacientes durante la\npandemia de Covid-19. Podra registrar la temperatura corporal de cada uno durante 7 dias (minimo).\nEl programa determinara la temperatura media de cada paciente y alertara en caso de que alguno\ntuviera fiebre por 3 o mas dias consecutivos. Se considereara que un paciente tiene fiebra si su\ntemperatura corporal es mayor o igual a 37.5%cC o 99.5%cF. Para efectos practicos, por favor indique\nla unidad de medicion de la temperatura que desea;\n\n\t* Presione <1> para medir la temperatura en grados Celsius (%cC)\n\t* Presione <2> para medir la temperatura en grados Fahrenheit (%cF)", 167, 167, 167,167);
	
	//Medicion de la temperatura
	tempUnit = ver01TempUnit();
	
	do
	{
		//Cantidad de pacientes que se van a ingresar al sistema
		cantPatients = ver02NumPatients(availableRooms);
		
		//Registro de datos
		patient = generalData(cantPatients, patient, roomForPatients, ages, tempUnit, mtxTemps);
		
		//Habitaciones restantes luego de asignarle una a cada paciente
		availableRooms -= cantPatients;
		
		//Seguir/finalizar programa
		continueProgram = endProgram();
	}
	while(availableRooms > 0 && continueProgram == 1);
	
	//Resultados del seguimiento
	results(patient, roomForPatients, ages, tempUnit, mtxTemps);
	
	printf("\n\n\t\t-------------------- FIN DEL PROGRAMA --------------------\n");
	
	return 0;
}
