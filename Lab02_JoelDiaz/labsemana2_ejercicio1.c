#include<stdio.h>
#define n 100

int main()
{
    int player01Inventory[n] = {0}, i = 0, cantItems = 0, id = 0, itemFreq = 0, player = 1;
    
    printf("Bienvenido jugador, indica cuantos items quieres ingresar (minimo: 1, maximo: 100): ");
    scanf("%d", &cantItems);
    getchar();
    
    while(cantItems < 1 || cantItems > 100)
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
    	
    	while(id < 1 || id > 100)
    	{
    		printf("\n\t\t* (Error: ID fuera de rango) Por favor, ingrese un identificador valido: ");
    		scanf("%d", &id);
    		getchar();
		}
		
		printf("\n\t* Indica la frecuencia del item %d (minimo: 1): ", id);
		scanf("%d", &itemFreq);
		getchar();
		
		while(itemFreq < 1)
		{
			printf("\n\t\t* (Error: Frecuencia fuera de rango) Por favor, ingrese una frecuencia valida: ");
    		scanf("%d", &itemFreq);
    		getchar();
		}
		
		player01Inventory[id - 1] += itemFreq;
	}
	
	printf("\n* Inventario del jugador %d:\n\n", player);
	
	for(i = 0; i < n; i++)
	{
		if(player01Inventory[i] != 0)
		{
			printf("\t- Item %d: %d\n", i + 1, player01Inventory[i]);
		}		
	}
	
	printf("\n\n\t* IMPORTANTE: Los items que no aparecen en la lista tienen una cantidad igual a 0\n");
	
	player++;

    return 0;
}
