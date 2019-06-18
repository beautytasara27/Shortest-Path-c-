#include <queue>
using namespace std;
class Graph{
	public:
		void createGraph();
		//Function to create the graph and the weight matrix.
		
		void shortestPath(int vertex);
		//Function to determine the weight of a shortest path
		//from vertex, that is, source, to every other vertex
		//in the graph.
		void printShortestDistance(int smallestWeight[],int path[],int vertex);
		void printPath(int path[], int dest);
		//Function to print the shortest weight from the source vertex
		//to every other vertex in the graph.
		Graph(int size = 0);
		//Constructor
		
		~Graph();
		//Destructor
		//The storage occupied by the vertices and the arrays
		//weights and smallestWeight is deallocated.
		protected:
		int gSize, maxSize;
		int **weights;
		int *smallestWeight; //pointer to create the array to store
		//the smallest weight from source to vertices
		int *path ;
		//to store the path with the smallest vertex for every vertex in the graph
		queue <int> parent; //temporary storage for the path, enables the path
		//to be exported to the csv file
};

