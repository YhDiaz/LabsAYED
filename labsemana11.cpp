#include <iostream>
#include <vector>
using namespace std;

//Clases
class Graph
{
	public:
		
		//Constructores
		Graph();
		
		//Destructor
		~Graph();
	
		//Metodos
		void createMatrix();
		void addEdge(int, int);
		void printGraphs();
		bool areAdjacent(int, int);
		int getSize();
		void thereIsPath(int, int);
	
	//Atributos
	private:
		vector<vector<int>> graphs_;
		int size_;
};

//Definiciones

	//Constructores
	Graph::Graph()
	{
		
	}
	
	Graph::~Graph()
	{
		cout << "\n\t***** Destruyendo clase *****";
	}
	
	//Metodos
	void Graph::createMatrix()
	{
		int size = 0;
		bool stop = true;
		
		do
		{
			if(stop)
			{
				cout << "\t* Indique la medida de la matriz (minimo: 8): ";
			}
			else
			{
				cout << "\n\t\t* (Error: Entrada invalida) Por favor, ingrese un numero valido: ";
			}
			
			cin >> size;
			
			if(size < 8)
			{
				stop = false;
			}
			else
			{
				stop = true;
			}
		}
		while(!stop);		
		
		graphs_ = vector<vector<int>>(size, vector<int>(size, 0));
		size_ = size;
	}
	
	void Graph::addEdge(int u, int v)
	{
		graphs_[u][v] = 1;
		graphs_[v][u] = 1;
		
		cout << "\n\t* Estableciendo conexion entre los vertices " << u + 1 << " y " << v + 1;
	}
	
	void Graph::printGraphs()
	{
		cout << "\n* Matriz de adyacencia:\n" << endl;
				
		for(const auto& row : graphs_)
		{
			cout << '\t';
			
			for(int val : row)
			{
				cout << val << " ";			
			}
				
			cout << endl;
		}
	}
	
	bool Graph::areAdjacent(int vertex1, int vertex2)
	{
		if(graphs_[vertex1 - 1][vertex2 - 1] == 1)
		{
			return true;
		}
		
		return false;
	}
	
	int Graph::getSize()
	{
		return size_;
	}
	
	void Graph::thereIsPath(int vertex1, int vertex2)
	{
		
	}
	
//Funciones
void exercise01(Graph* graphs)
{
	cout << "-------------------- EJERCICIO 1: CREACION DEL GRAFO E INCORPORACION DE INFORMACION --------------------\n" << endl;
	graphs->createMatrix();
	
	//Se crean las conexiones entre los vertices
	//A: 0, B: 1, C: 2, D: 3, E: 4, F: 5, G: 6, H: 7
	
	graphs->addEdge(0, 1); //A-B
	graphs->addEdge(0, 2); //A-C
	graphs->addEdge(1, 3); //B-C
	graphs->addEdge(1, 4); //B-E
	graphs->addEdge(1, 5); //B-F
	graphs->addEdge(2, 3); //C-D
	graphs->addEdge(2, 5); //C-F
	graphs->addEdge(2, 6); //C-G
	graphs->addEdge(3, 4); //D-E
	graphs->addEdge(4, 5); //E-F
	graphs->addEdge(4, 7); //E-H
	graphs->addEdge(5, 6); //F-G
	graphs->addEdge(5, 7); //F-H	
	graphs->addEdge(6, 7); //G-H
}

void exercise02(Graph* graphs)
{
	cout << "\n\n-------------------- EJERCICIO 2: IMPRESION DE LA MATRIZ DE ADYACENCIA --------------------" << endl;
	graphs->printGraphs();
}

void exercise03(Graph* graphs)
{
	cout << "\n\n-------------------- EJERCICIO 3: VERTICES ADYACENTES --------------------" << endl;
	int v1 = 1, v2 = 2;
	
	if(graphs->areAdjacent(v1, v2))
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " son adyacentes" << endl;
	}
	else
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " nos son adyacentes" << endl;
	}
	
	cout << "\n\t* Ingrese dos vertices para saber si son adyacentes (desde 1 a " << graphs->getSize() << ");\n\n\t* Primer vertice: ";
	cin >> v1;
	
	while(v1 < 1 || v1 > graphs->getSize())
	{
		cout << "\n\t\t* (Error: Numero fuera de rango) Por favor, ingrese un valor valido: ";
		cin >> v1;
	}
	
	cout << "\n\t* Segundo vertice: ";
	cin >> v2;
	
	while(v2 < 1 || v2 > graphs->getSize())
	{
		cout << "\n\t\t* (Error: Numero fuera de rango) Por favor, ingrese un valor valido: ";
		cin >> v2;
	}
	
	if(graphs->areAdjacent(v1, v2))
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " son adyacentes" << endl;
	}
	else
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " nos son adyacentes" << endl;
	}
}

int main() {
	
	//Ejercicio 1: Creacion de estructura e incorporacion de la informacion a la matriz del grafo
	Graph *graphs = new Graph();
	exercise01(graphs);
	
	//Ejercicio 2: Imprimir la matriz del grafo
	exercise02(graphs);
	
	//Ejercicio 3: Vertices adyacentes
	exercise03(graphs);
	
	//Ejercicio 4: Determinar la existencia de un camino entre dos vertices
	
	
	//Ejercicio 5: Convertir el grafo en un grafo dirigido con al menos un vertice que no puede ser alcanzado por otro
	
	
	//Ejercicio 6: Convertir el grafo en un grafo dirigido que contenga un ciclo
	
	
	//Ejercicio 7: Convertir el grafo en un grafo dirigido, transformandolo en dos subgrafos con la misma cantidad de vertices
	
	graphs->~Graph();
	
	return 0;
}
