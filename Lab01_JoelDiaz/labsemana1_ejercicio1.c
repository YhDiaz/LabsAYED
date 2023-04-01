#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

//Codigo creado en DevC++ (Lenguaje de programacion: C)
//Instruccion system("cls") disponible solo desde Windows (Linea 28)

int main()
{
	int dataType_int = 0;
	float dataType_float = 0;
	char dataType_char;
	bool dataType_bl = false;
	
	int arrInt[2];
	float arrFloat[2];
	char arrChar[10] = {'H', 'O', 'L', 'A', ' ', 'M', 'U', 'N', 'D', 'O'};
	
	//arrChar = {'H', 'O', 'L', 'A'};
	
	int spValue = 0;
	int textVel = 0;
	int aux = 0;
	int i = 0;
	
	printf("---------- Antes de empezar ----------\n");
	printf("\n\tSeleccione la velocidad del despliegue de texto;\n\n\t* Presione <0> para un despliegue de texto rapido\n\t* Presione <1> para un despliegue de texto lento\n\n\t* Su opcion: ");
	scanf("%d", &textVel);
	system("cls");
	
	Sleep(1000);
	
	if(textVel == 1)
	{
		spValue = 750;
	}
	
	printf("\n-------------------- BIENVENIDO AL PROGRAMA DE USO DE TIPOS DE DATOS --------------------\n");
	Sleep(spValue);
	printf("\n\t* Comenzaremos con los datos de tipo entero (int),\n\tluego con los de tipo decimal (float), despues con\n\tlos de tipo boolean y finalmente\n\t con los de tipo caracter (char)\n\n\t* IMPORTANTE: El programa no contiene validaciones de datos,\n\tpor favor, ingrese los datos solicitados\n");
	Sleep(spValue);
	
	//Multiplicacion de enteros
	printf("\n---------- MULTIPLICACION DE ENTEROS ----------\n");
	Sleep(spValue);
	printf("\n* Ingrese dos numeros enteros para multiplicarlos;\n\n\t* Ingrese el primer numero: ");
	scanf("%d", &dataType_int);
	
	arrInt[0] = dataType_int;
	Sleep(spValue);
	
	printf("\t* Ingrese el segundo numero: ");
	scanf("%d", &dataType_int);
	
	arrInt[1] = dataType_int;
	Sleep(spValue);
	
	printf("\n\t***** El producto entre %d y %d es %d *****\n", arrInt[0], arrInt[1], arrInt[0] * arrInt[1]);
	Sleep(spValue);
	
	printf("\n\tEl tipo de dato \"int\" permite declarar variables que\n\talmacenaran datos con valor numerico de tipo entero\n");
	Sleep(spValue);
	
	//Adicion de decimales
	printf("\n---------- ADICION DE DECIMALES ----------\n");
	Sleep(spValue);
	printf("\n* Ingrese dos numeros decimales para sumarlos\n(utilice un punto para separar la parte entera de la decimal,\nsolo se consideraran los primeros dos decimales);\n\n\t* Ingrese el primer numero: ");
	scanf("%f", &dataType_float);
	
	arrFloat[0] = dataType_float;
	Sleep(spValue);
	
	printf("\t* Ingrese el segundo numero: ");
	scanf("%f", &dataType_float);
	
	arrFloat[1] = dataType_float;
	Sleep(spValue);
	
	printf("\n\t***** La suma entre %.2f y %.2f es %.2f *****\n", arrFloat[0], arrFloat[1], arrFloat[0] + arrFloat[1]);
	Sleep(spValue);
	
	printf("\n\tEl tipo de dato \"float\" permite declarar variables que\n\talmacenaran datos con valor numerico de tipo decimal.\n\tAdemas del tipo \"float\", podemos encontrar el tipo de\n\tdato \"double\". Tienen la misma funcionalidad, con la\n\tdiferencia de que el \"double\" permite almacenar una\n\tmayor cantidad de decimales");
	Sleep(spValue);
	
	//Cambio de valor bool
	printf("\n\n---------- CAMBIO DE VALOR BOOLEANO ----------\n");
	Sleep(spValue);
	printf("\n* Para evidenciar el uso de este tipo de dato, debera responder un enunciado con:\n\n\t* <0>, si el enunciado es FALSO\n\t* <1>, si el enunciado es VERDADERO\n\n\tENUNCIADO: El usuario de este programa esta usando una maquina de escribir\n\n\t* Ingrese su respuesta: ");
	scanf("%d", &aux);
	Sleep(spValue);
	
	if(aux == 1)
	{
		dataType_bl = true;
		printf("\n\tEl valor del boolean es: VERDADERO\n");
	}
	else
	{
		printf("\n\tEl valor del boolean es: FALSO\n");
	}
	
	if(dataType_bl)
	{
		printf("\n\t***** El usuario SI esta usando una maquina de escribir *****");
	}
	else
	{
		printf("\n\t***** El usuario NO esta usando una maquina de escribir *****");
	}
	
	Sleep(spValue);
	printf("\n\n\tEl tipo de dato \"bool\" almacena valores de verdad, es decir,\n\tsi algo es verdadero o falso. Es usado (muchas veces) como\n\tuna especie de interruptor, ya que su valor de \"si\"\n\to \"no\" facilita la toma de decisiones frente a una condicional");
	Sleep(spValue);
	
	//Print: Hola mundo
	printf("\n\n---------- HOLA MUNDO: USO DE CARACTERES ----------");
	Sleep(spValue);
	printf("\n\n* El uso de caracteres es mas extenso que los demas tipos de datos,\npues abarca desde los caracteres de un teclado alfanumerico\nhasta simbolos basicos. Todos estos caracteres tienen un codigo\nASCII que permite su identificacion interna.\n\n* A continuacion, se muestra un ejemplo del uso de caracteres para formar una frase:\n");
	Sleep(spValue);
	
	for(i = 0; i < 10; i++)
	{
		printf("\n\t* Posicion %d (%d internamente): %c", i + 1, i, arrChar[i]);
	}
	
	Sleep(spValue);
	printf("\n\n\t* Frase formada: ");
	Sleep(spValue);
	
	for(i = 0; i < 10; i++)
	{
		printf("%c", arrChar[i]);
	}
	
	aux = 0;
	
	printf("\n\n\t* Si desea ver un listado de los valores presentes en la tabla ASCII presione <1>\n\t* Para terminar presione cualquier otro numero\n\n\t* Ingrese su opcion: ");
	scanf("%d", &aux);
	
	if(aux == 1)
	{
		printf("\n\t* Listado de los valores de los primeros 250 caracteres del codigo ASCII\n\t(es posible que algunos no se vean):\n");
		
		for(i = 0; i <= 200; i++)
		{
			printf("\n\t\t* Caracter %d: %c", i, i);
			Sleep(25);
		}
	}
	
	Sleep(spValue);
	printf("\n\n\t\t---------- FIN DEL CODIGO ----------");
	
	return 0;
}

