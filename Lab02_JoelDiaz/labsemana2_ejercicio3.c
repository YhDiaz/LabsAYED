#include<stdio.h>
#include<stdlib.h>
#define n 100

//Parte 3 (Inicio): Declaracion de funciones

void agregar(int arrPlayerInv[], int arrMainInv[])
{
	int id = 0, i = 0;
	
	printf("\n---------- AGREGAR UN ITEM ----------");
	
	printf("\n\n\tInventario:\n");
	
	for(i = 0; i < n; i++)
	{
		if(arrPlayerInv[i] != 0)
		{
			printf("\n\t- Item %d: %d", i + 1, arrPlayerInv[i]);
		}
	}
	
	printf("\n\n\t* Ingrese el identificador del item que desea incrementar (minimo: 1, maximo: %d): ", n);
	scanf("%d", &id);
	getchar();
	
	while(id < 1 || id > n)
	{
		printf("\n\t\t* (Error: Identificador indefinido) Por favor, ingrese un identificador valido: ");
		scanf("%d", &id);
		getchar();
		
		while(arrMainInv[id - 1] == 0)
		{
			printf("\n\t* Lo siento, no quedan unidades disponibles del item que deseas ingresar. Por favor, ingresa otro identificador: ");
			scanf("%d", &id);
			getchar();
		}
	}
	
	while(arrMainInv[id - 1] == 0)
	{
		printf("\n\t* Lo siento, no quedan unidades disponibles del item que deseas ingresar. Por favor, ingresa otro identificador: ");
		scanf("%d", &id);
		getchar();
		
		while(id < 1 || id > n)
		{
			printf("\n\t\t* (Error: Identificador indefinido) Por favor, ingrese un identificador valido: ");
			scanf("%d", &id);
			getchar();
		}
	}
	
	arrPlayerInv[id - 1]++;
	printf("\n\t* El item %d se ha incrementado en una unidad (Cantidad actual: %d)", id, arrPlayerInv[id - 1]);
	
	printf("\n\n\tInventario actualizado:\n");
	
	for(i = 0; i < n; i++)
	{
		if(arrPlayerInv[i] != 0)
		{
			printf("\n\t- Item %d: %d", i + 1, arrPlayerInv[i]);
		}
	}
}

void eliminar(int arrPlayerInv[], int arrMainInv[])
{
	int id = 0, i = 0;
	
	printf("\n---------- ELIMINAR UN ITEM ----------");
	
	printf("\n\n\tInventario:\n");
	
	for(i = 0; i < n; i++)
	{
		if(arrPlayerInv[i] != 0)
		{
			printf("\n\t- Item %d: %d", i + 1, arrPlayerInv[i]);
		}
	}
	
	printf("\n\n\t* Ingrese el identificador del item del que desea quitar una unidad (minimo: 1, maximo: %d): ", n);
	scanf("%d", &id);
	getchar();
	
	while(id < 1 || id > n)
	{
		printf("\n\t\t* (Error: Identificador indefinido) Por favor, ingrese un identificador valido: ");
		scanf("%d", &id);
		getchar();
		
		while(arrPlayerInv[id - 1] == 0)
		{
			printf("\n\t* El item indicado no tiene unidades, por lo que no se le pueden eliminar mas. Por favor, ingresa otro identificador: ");
			scanf("%d", &id);
			getchar();
		}
	}
	
	while(arrPlayerInv[id - 1] == 0)
	{
		printf("\n\t* El item indicado no tiene unidades, por lo que no se le pueden eliminar mas. Por favor, ingresa otro identificador: ");
		scanf("%d", &id);
		getchar();
		
		while(id < 1 || id > n)
		{
			printf("\n\t\t* (Error: Identificador indefinido) Por favor, ingrese un identificador valido: ");
			scanf("%d", &id);
			getchar();
		}
	}
	
	arrPlayerInv[id - 1]--;
	
	if(arrPlayerInv[id - 1] > 0)
	{
		printf("\n\t* El item %d se ha incrementado en una unidad (Cantidad actual: %d)", id, arrPlayerInv[id - 1]);
	}
	else
	{
		printf("\n\t* Se elimino la ultima unidad del item seleccionado, por lo que se ha quitado del inventario");
	}
	
	printf("\n\n\tInventario actualizado:\n");
	
	for(i = 0; i < n; i++)
	{
		if(arrPlayerInv[i] != 0)
		{
			printf("\n\t- Item %d: %d", i + 1, arrPlayerInv[i]);
		}
	}
}

//Parte 3 (Fin): Declaracion de funciones

int main()
{
	//Parte 2 (Inicio): Preliminar
	
	srand(time(NULL));
	
	int itemsMax[n] = {0}, gameInventory[n] = {0}, limit = 0, i = 0;
	
	printf("***** Actualizacion del juego: Se ha definido un maximo de items dentro del juego *****\n\n* Inventario del juego:\n\n");
	
	for(i = 0; i < n; i++)
	{
		limit = rand() % 20 + 5;
		
		itemsMax[i] = limit;
		gameInventory[i] = itemsMax[i];
		printf("\t- Item %d = %d\n", i + 1, itemsMax[i]);
		Sleep(10);
	}
	
	//Parte 2 (Fin): Preliminar
	
	//Parte 1 (Inicio)
	
    int player01Inventory[n] = {0}, cantItems = 0, id = 0, itemFreq = 0, player = 1;
    
    printf("\n* Bienvenido jugador %d, indica cuantos items quieres ingresar (minimo: 1, maximo: 100): ", player);
    scanf("%d", &cantItems);
    getchar();
    
    while(cantItems < 1 || cantItems > n)
    {
    	printf("\n\t* (Error: Cantidad de Items fuera de rango) Por favor, ingrese una cantidad valida: ");
    	scanf("%d", &cantItems);
    	getchar();
	}
    
    for(i = 0; i < cantItems; i++)
    {
    	itemFreq = 0;
    	
    	printf("\n\t* Indica el identificador del elemento cuya cantidad deseas ingresar (minimo: 1, maximo: 100): ");
    	scanf("%d", &id);
    	getchar();
    	
    	while(id < 1 || id > n)
    	{
    		printf("\n\t\t* (Error: ID fuera de rango) Por favor, ingrese un identificador valido: ");
    		scanf("%d", &id);
    		getchar();
		}
		
		printf("\n\t* Indica la frecuencia del item %d (minimo: 1, maximo: %d): ", id, gameInventory[id - 1]);
		scanf("%d", &itemFreq);
		getchar();
		
		while(itemFreq < 1 || itemFreq > gameInventory[id - 1])
		{
			printf("\n\t\t* (Error: Frecuencia fuera de rango) Por favor, ingrese una frecuencia valida: ");
    		scanf("%d", &itemFreq);
    		getchar();
		}
		
		player01Inventory[id - 1] += itemFreq;
		gameInventory[id- 1] -= itemFreq;
	}
	
	printf("\n* Inventario del jugador %d:\n\n", player);
	
	for(i = 0; i < n; i++)
	{
		if(player01Inventory[i] != 0)
		{
			printf("\t- Item %d: %d\n", i + 1, player01Inventory[i]);
		}
	}
	
	printf("\n\t--------------- IMPORTANTE: Los items que no aparecen en la lista tienen una cantidad igual a 0 ---------------\n");
	
	player++;
	
	//Parte 1 (Fin)
	
	//Parte 2 (Inicio)
	
	int player02Inventory[n] = {0};
	
	printf("\n* Bienvenido jugador %d, indica cuantos items quieres ingresar (minimo: 1, maximo: 100): ", player);
    scanf("%d", &cantItems);
    getchar();
    
    while(cantItems < 1 || cantItems > n)
    {
    	printf("\n\t* (Error: Cantidad de Items fuera de rango) Por favor, ingrese una cantidad valida: ");
    	scanf("%d", &cantItems);
    	getchar();
	}
    
    for(i = 0; i < cantItems; i++)
    {
    	itemFreq = 0;
    	
    	printf("\n\t* Indica el identificador del elemento cuya cantidad deseas ingresar (minimo: 1, maximo: 100): ");
    	scanf("%d", &id);
    	getchar();
    	
    	while(gameInventory[id - 1] == 0 && id >= 1 && id <= n)
    	{
    		printf("\n\t\t* Lo siento, no quedan unidades disponibles del item que deseas ingresar. Por favor, ingresa otro identificador: ");
    		scanf("%d", &id);
    		getchar();
    		
    		while(id < 1 || id > n)
		   	{
		   		printf("\n\t\t* (Error: ID fuera de rango) Por favor, ingrese un identificador valido: ");
		   		scanf("%d", &id);
		   		getchar();
			}
		}
		
		while(id < 1 || id > n)
    	{
    		printf("\n\t\t* (Error: ID fuera de rango) Por favor, ingrese un identificador valido: ");
    		scanf("%d", &id);
    		getchar();
    		
    		while(gameInventory[id - 1] == 0)
    		{
    			printf("\n\t\t* Lo siento, no quedan unidades disponibles del item que deseas ingresar. Por favor, ingresa otro identificador: ");
    			scanf("%d", &id);
    			getchar();
			}
		}	
    			
		printf("\n\t* Indica la frecuencia del item %d (minimo: 1, maximo: %d): ", id, gameInventory[id - 1]);
		scanf("%d", &itemFreq);
		getchar();
		
		while(itemFreq < 1 || itemFreq > gameInventory[id - 1])
		{
			printf("\n\t\t* (Error: Frecuencia fuera de rango) Por favor, ingrese una frecuencia valida: ");
    		scanf("%d", &itemFreq);
    		getchar();
		}
		
		player02Inventory[id - 1] += itemFreq;
		gameInventory[id - 1] -= itemFreq;
	}
	
	printf("\n* Inventario del jugador %d:\n\n", player);
	
	for(i = 0; i < n; i++)
	{
		if(player02Inventory[i] != 0)
		{
			printf("\t- Item %d: %d\n", i + 1, player02Inventory[i]);
		}
	}
	
	//Parte 2 (Fin)
	
	//Parte 3 (Inicio): Llamada de funciones
	
	int funcSelected = -1, endProgram = 0;
	
	do
	{
		funcSelected = -1;
		endProgram = -1;
		
		printf("\n--------------- FUNCIONALIDADES ADICIONALES ---------------");
		printf("\n\n\tSeleccione una de las siguientes opciones para continuar:\n\n\t* Presione <0> para finalizar el programa\n\t* Presione <1> para agregar un item\n\t* Presione <2> para eliminar un item\n\n\t* Ingrese su opcion: ");
		scanf("%d", &funcSelected);
		getchar();
		
		while(funcSelected < 0 || funcSelected > 2)
		{
			printf("\n\t\t* (Error: Opcion indefinida) Por favor, seleccione una opcion valida: ");
			scanf("%d", &funcSelected);
			getchar();
		}
		
		if(funcSelected != 0)
		{
			switch(funcSelected)
			{
				case 1:
					agregar(player01Inventory, gameInventory);
					break;
					
				case 2:
					eliminar(player01Inventory, gameInventory);
					break;
			}
			
			printf("\n\n\t---------- CONTINUAR PROGRAMA ----------");
			printf("\n\n\tSeleccione una de las siguientes opciones para continuar:\n\n\t* <0> para finalizar\n\t* <1> para realizar otra operacion\n\n\t* Ingrese su opcion: ");
			scanf("%d", &endProgram);
			getchar();
			
			while(endProgram != 0 && endProgram != 1)
			{
				printf("\n\t\t* (Error: Opcion indefinida) Por favor, ingrese una opcion valida: ");
				scanf("%d", &endProgram);
				getchar();
			}
		}
		else
		{
			endProgram = 0;
		}
	}
	while(endProgram == 1);
	
	//Parte 3 (Fin): Llamada de funciones
	
	printf("\n\n\t\t-------------------- FIN DEL PROGRAMA --------------------\n");

    return 0;
}
