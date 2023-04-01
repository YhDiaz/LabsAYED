#include<stdio.h>
#include<stdlib.h>

//Codigo creado en DevC++ (Lenguaje de programacion: C)

void suma(int num, int random)
{
	printf("\n\t***** La suma entre %d y %d es %d *****\n", num, random, num + random);
}

void resta(int num, int random)
{
	printf("\n\t***** Al restarle %d a %d se obtiene %d *****\n", random, num, num - random);
}

void multiplicacion(int num, int random)
{
	printf("\n\t***** El producto entre %d y %d es %d *****\n", num, random, num * random);
}

void division(int num, int random)
{
	printf("\n\t***** Al dividir %d entre %d se obtiene %d (truncado a la unidad) *****\n", num, random, num / random);
}

void plusHalf(int num)
{
	printf("\n\t***** La suma entre %d y su mitad es %d (truncado a la unidad) *****\n", num, num + (num / 2));
}

void squared(int num)
{
	printf("\n\t***** El cuadrado de %d es %d *****\n", num, num * num);
}

int main()
{
	int num = 0, opcion = 0;
	
	printf("-------------------- BIENVENIDO A LA CALCULADORA MULTIFUNCIONES --------------------\n");
	
	do
	{
		printf("\n\t* Ingrese un numero entero: ");
		scanf("%d", &num);
		
		printf("\n\tSeleccione la operacion que desea realizar con el numero ingresado;\n\n\t* Presione <1> para sumarle un numero,\n\t* Presione <2> para restarle un numero,\n\t* Presione <3> para multiplicarlo por un numero,\n\t* Presione <4> para dividirlo por un numero,\n\t* Presione <5> para sumarle su mitad,\n\t* Presione <6> para elevarlo al cuadrado,\n\t* Presione cualquier otro numero para terminar el programa\n\n\t* Ingrese su opcion: ");
		scanf("%d", &opcion);
		
		switch(opcion)
		{
			case 1:
				suma(num, 3);
				break;
				
			case 2:
				resta(num, 3);
				break;
				
			case 3:
				multiplicacion(num, 3);
				break;
				
			case 4:
				division(num, 2);
				break;
				
			case 5:
				plusHalf(num);
				break;
				
			case 6:
				squared(num);
				break;
				
			default:
				printf("\n\n\t\tFinalizando el programa...");
		}
	}
	while(opcion > 0 && opcion <= 6);
	
	printf("\n\n\t\t---------- FIN DEL PROGRAMA ----------");
	
	return 0;
}
