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
		void printGraph();
		bool areAdjacent(int, int);
		int getSize();
		void addEdge(int, int, bool);
		void removeNode(int);
		void removeEdge(int, int);
	
	//Atributos
	private:
		vector<vector<int>> graph_;
		int size_;
};

//Funciones
void exercise01(Graph* graph);
void exercise02(Graph* graph);
void exercise03(Graph* graph);
void exercise05(Graph* graph);
void exercise06(Graph* graph);
void exercise07(Graph* graph);

int main() {
	
	//Ejercicio 1: Creacion de estructura e incorporacion de la informacion a la matriz del grafo
	Graph *graph = new Graph();
	exercise01(graph);
	
	//Ejercicio 2: Imprimir la matriz del grafo
	exercise02(graph);
	
	//Ejercicio 3: Vertices adyacentes
	exercise03(graph);
	
	//Ejercicio 5: Convertir el grafo en un grafo dirigido con al menos un vertice que no puede ser alcanzado por otro
	exercise05(graph);
	
	//Ejercicio 6: Convertir el grafo en un grafo dirigido que contenga un ciclo
	exercise06(graph);
	
	//Ejercicio 7: Convertir el grafo en un grafo dirigido, transformandolo en dos subgrafos con la misma cantidad de vertices
	exercise07(graph);
	
	graph->~Graph();
	
	return 0;
}

//Funciones
void exercise01(Graph* graph)
{
	cout << "-------------------- EJERCICIO 1: CREACION DEL GRAFO E INCORPORACION DE INFORMACION --------------------\n" << endl;
	graph->createMatrix();
	
	//Se crean las conexiones entre los vertices
	//A: 0, B: 1, C: 2, D: 3, E: 4, F: 5, G: 6, H: 7
	
	graph->addEdge(0, 1); //A-B
	graph->addEdge(0, 2); //A-C
	graph->addEdge(1, 3); //B-D
	graph->addEdge(1, 4); //B-E
	graph->addEdge(1, 5); //B-F
	graph->addEdge(2, 3); //C-D
	graph->addEdge(2, 5); //C-F
	graph->addEdge(2, 6); //C-G
	graph->addEdge(3, 4); //D-E
	graph->addEdge(4, 5); //E-F
	graph->addEdge(4, 7); //E-H
	graph->addEdge(5, 6); //F-G
	graph->addEdge(5, 7); //F-H	
	graph->addEdge(6, 7); //G-H
}

void exercise02(Graph* graph)
{
	cout << "\n\n-------------------- EJERCICIO 2: IMPRESION DE LA MATRIZ DE ADYACENCIA --------------------" << endl;
	graph->printGraph();
}

void exercise03(Graph* graph)
{
	cout << "\n\n-------------------- EJERCICIO 3: VERTICES ADYACENTES --------------------" << endl;
	int v1 = 1, v2 = 2;
	
	if(graph->areAdjacent(v1, v2))
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " son adyacentes" << endl;
	}
	else
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " nos son adyacentes" << endl;
	}
	
	cout << "\n\t* Ingrese dos vertices para saber si son adyacentes (desde 1 a " << graph->getSize() << ");\n\n\t* Primer vertice: ";
	cin >> v1;
	
	while(v1 < 1 || v1 > graph->getSize())
	{
		cout << "\n\t\t* (Error: Numero fuera de rango) Por favor, ingrese un valor valido: ";
		cin >> v1;
	}
	
	cout << "\n\t* Segundo vertice: ";
	cin >> v2;
	
	while(v2 < 1 || v2 > graph->getSize())
	{
		cout << "\n\t\t* (Error: Numero fuera de rango) Por favor, ingrese un valor valido: ";
		cin >> v2;
	}
	
	if(graph->areAdjacent(v1, v2))
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " son adyacentes" << endl;
	}
	else
	{
		cout << "\n\tLos vertices " << v1 << " y " << v2 << " nos son adyacentes" << endl;
	}
}

void exercise05(Graph* graph)
{
	cout << "\n\n-------------------- EJERCICIO 5: GRAFO DIRIGIDO CON UN VERTICE INALCANZABLE --------------------" << endl;
	
	//Vertices A y G, inalcanzables
	//A: 0, B: 1, C: 2, D: 3, E: 4, F: 5, G: 6, H: 7
	
	graph->addEdge(0, 1, true); //A->B
	graph->addEdge(0, 2, true); //A->C
	graph->addEdge(1, 3, false); //B<->D
	graph->addEdge(1, 4, true); //B->E
	graph->addEdge(1, 5, true); //B->F
	graph->addEdge(2, 3, true); //C->D
	graph->addEdge(2, 5, false); //C<->F
	graph->addEdge(6, 2, true); //C<-G
	graph->addEdge(4, 3, true); //D<-E
	graph->addEdge(4, 5, false); //E<->F
	graph->addEdge(4, 7, true); //E->H
	graph->addEdge(6, 5, true); //F<-G
	graph->addEdge(5, 7, true); //F->H	
	graph->addEdge(6, 7, true); //G->H
	
	graph->printGraph();
}

void exercise06(Graph* graph)
{
	cout << "\n\n-------------------- EJERCICIO 6: GRAFO DIRIGIDO Y CICLICO --------------------" << endl;
	
	//A: 0, B: 1, C: 2, D: 3, E: 4, F: 5, G: 6, H: 7
	
	graph->addEdge(1, 0, true); //A<-B
	graph->addEdge(0, 2, true); //A->C
	graph->addEdge(3, 1, true); //B<-D
	graph->addEdge(4, 1, true); //B<-E
	graph->addEdge(5, 1, true); //B<-F
	graph->addEdge(2, 3, true); //C->D
	graph->addEdge(2, 5, true); //C->F
	graph->addEdge(2, 6, true); //C->G
	graph->addEdge(3, 4, true); //D->E
	graph->addEdge(5, 4, true); //E<-F
	graph->addEdge(7, 4, true); //E<-H
	graph->addEdge(5, 6, true); //F->G
	graph->addEdge(5, 7, true); //F->H	
	graph->addEdge(6, 7, true); //G->H
	
	graph->printGraph();
}

void exercise07(Graph* graph)
{
	cout << "\n\n-------------------- EJERCICIO 7: SUBGRAFOS DIRIGIDOS --------------------" << endl;
	
	//A: 0, B: 1, C: 2, D: 3, E: 4, F: 5, G: 6, H: 7
	
	//Eliminando vertices D y F
	graph->removeNode(3);
	graph->removeNode(5);
	
	//Eliminando conexiones
	graph->removeEdge(1, 4); //B-/-E
	graph->removeEdge(2, 6); //C-/-G
	
	//Nuevas conexiones
	graph->addEdge(1, 2, true); //B->C
	graph->addEdge(4, 6, true); //E->G
	
	graph->printGraph();
}

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
		
		graph_ = vector<vector<int>>(size, vector<int>(size, 0));
		size_ = size;
	}
	
	void Graph::addEdge(int u, int v)
	{
		graph_[u][v] = 1;
		graph_[v][u] = 1;
		
		cout << "\n\t* Estableciendo conexion entre los vertices " << u + 1 << " y " << v + 1;
	}
	
	void Graph::printGraph()
	{
		cout << "\n* Matriz de adyacencia:\n" << endl;
				
		for(const auto& row : graph_)
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
		if(graph_[vertex1 - 1][vertex2 - 1] == 1)
		{
			return true;
		}
		
		return false;
	}
	
	int Graph::getSize()
	{
		return size_;
	}
	
	void Graph::addEdge(int u, int v, bool directed)
	{
		if(directed)
		{
			graph_[u][v] = 1;
			graph_[v][u] = 0;
		}
		else
		{
			graph_[u][v] = 1;
			graph_[v][u] = 1;
		}
	}
	
	void Graph::removeNode(int u)
	{
		for(int i = 0; i < graph_.size(); i++)
		{
			graph_[u][i] = 0;
			graph_[i][u] = 0;
		}
	}
	
	void Graph::removeEdge(int u, int v)
	{
		graph_[u][v] = 0;
		graph_[v][u] = 0;
	}
