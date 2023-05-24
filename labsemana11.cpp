#include <iostream>
#include <vector>
using namespace std;
/*
// Function to add an edge between vertices u and v
void addEdge(vector<vector<int>>& graph, int u, int v) {
	graph[u][v] = 1;
	graph[v][u] = 1;
}

// Function to print the adjacency matrix
void printGraph(const vector<vector<int>>& graph) {
	cout << "Adjacency Matrix:\n";
	for (const auto& row : graph) {
	for (int val : row) {
	cout << val << " ";
	}
	cout << '\n';
	}
}*/

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
		
	
	//Atributos
	private:
		vector<vector<int>> graphs_;
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
		
		cout << "Indique la medida de la matriz: ";
		cin >> size;
		cout << endl;
		
		graphs_ = vector<vector<int>>(size, vector<int>(size, 0));
	}
	
	void Graph::addEdge(int u, int v)
	{
		graphs_[u][v] = 1;
		graphs_[v][u] = 1;
	}
	
	void Graph::printGraphs()
	{
		cout << "\nMatriz de adyacencia:\n";
				
		for(const auto& row : graphs_)
		{
			for(int val : row)
			{
				if(val == 0)
				{
					cout << "   ";
				}
				else
				{
					cout << val << " ";
				}				
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
	
int main() {
	
	//Ejercicio 1: Creacion de estructura e incorporacion de la informacion a la matriz del grafo
	Graph *graphs = new Graph();
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
	
	//Ejercicio 2: Imprimir la matriz del grafo
	graphs->printGraphs();
	
	//Ejercicio 3: Vertices adyacentes
	int v1 = 0, v2 = 1;
	
	if(graphs->areAdjacent(v1, v2))
	{
		cout << "\nLos vertices " << v1 << " y " << v2 << " son adyacentes" << endl;
	}
	else
	{
		cout << "\nLos vertices " << v1 << " y " << v2 << " nos son adyacentes" << endl;
	}
	
	cout << "\nIngrese dos vertices para saber si son adyacentes (desde 1 a 8);\nPrimer vertice: ";
	cin >> v1;
	cout << "Segundo vertice: ";
	cin >> v2;
	
	if(graphs->areAdjacent(v1, v2))
	{
		cout << "\nLos vertices " << v1 << " y " << v2 << " son adyacentes" << endl;
	}
	else
	{
		cout << "\nLos vertices " << v1 << " y " << v2 << " nos son adyacentes" << endl;
	}
	
	graphs->~Graph();
	
	return 0;
}
