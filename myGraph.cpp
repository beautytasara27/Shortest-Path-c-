#include "myGraph.h"
#include <cfloat>
#include <iostream>
#include<iomanip>
#include <fstream>
#include <queue>
using namespace std;


//this function creates the weighted graph from a text file and represents the graph 
//in an adjacency matrix
void Graph::createGraph(){
	ifstream infile;
	char fileName[50];
	int vertex;
	int adjacentVertex;
	int weight;
	
	cout << "Enter input file name: ";
	cin >> fileName;
	cout << endl;
	infile.open(fileName);
	if (!infile){
		cout << "Invalid file name " << endl;
		return;
		}
			
	infile >> gSize; //get the number of vertices from file
	
	//initializing every value in the matrix to infinity
	for (int index=0; index< gSize;index++){
		for (int x=0; x < gSize; x++){
			weights[index][x]=DBL_MAX;
		}
	}
	//reading data according to the file
	for (int index = 0; index < 18; index++){ //18 is the number of edges
		infile >> vertex;
		infile >> adjacentVertex;
		infile >> weight;
			weights[vertex][adjacentVertex]=weight;
	}
	infile.close();
} 




void Graph::shortestPath(int vertex){
	//initializing array smallest weight with the values from the matrix 
	for (int j = 1; j < gSize; j++)
		smallestWeight[j] = weights[vertex][j];
		bool *weightFound;
		
	weightFound = new bool[gSize];
	//path is the array to store the vertex before the current vertex
	//in the shortest path tree
	path = new int [gSize];

	for (int j = 1; j < gSize; j++){
		weightFound[j] = false;
		path[j]=0;
		path[0]=-1;
		}
	//set the weight found of the source vertex to true because the 
	//shortest distance is already found = 0
	weightFound[vertex] = true;
	smallestWeight[vertex] = 0;
	
	//dijkstra's algorithm to find shortest path 
	for (int i = 1; i < gSize - 1; i++)
		{
		double minWeight = DBL_MAX;
		int v;
		for (int j = 1; j < gSize; j++)
			if (!weightFound[j])
				if (smallestWeight[j] < minWeight)
				{
				v = j;
				minWeight = smallestWeight[v];
				}
		weightFound[v] = true;
		for (int j = 1; j < gSize; j++){
			//update if there is a path to any adjacent vertex to j
			// via j that can be improved
			if (!weightFound[j]){
				if (minWeight + weights[v][j] < smallestWeight[j]){	
					path[j]=v;	
				
				smallestWeight[j] = minWeight + weights[v][j];
			
			}
			}
			
			}
				
	} 
	//calling printShortestDistance to print and write to the csv file
	printShortestDistance(smallestWeight, path, vertex);
	
	
	
} 


void Graph::printShortestDistance(int smallestWeight[],int path[], int vertex){
	//oopen a csv file to write the calculated shortest distance and path 
	ofstream myfile;
	myfile.open ("path.csv");

	cout << "Source   dest   Shortest_Distance    path" << endl;
	//this loop prints the output on the screen and writes also to the csv file
	for(int i=1 ; i< gSize ;i++){
		cout << vertex << setw(12)<<i << setw(12) << smallestWeight[i] <<
		setw(12)<<vertex;
		printPath(path, i);
		cout<< endl;
		myfile << vertex<<"," << i<< ","<<smallestWeight[i]<<","<< vertex <<",";
		//parent is a queue to store the path for evry vertex
		while(!parent.empty()){
			myfile<< parent.front()<<",";
			parent.pop();
		}
		myfile <<endl;
	}

	myfile.close();
	
} 

//this function recursively push vertices making up the path to the destination
void Graph::printPath(int path[], int dest) { 
	
// Base Case : If j is source
    if (path[dest]==-1)
		return;
	//if the destination is the origin
	else if (path[dest]== 0)
		cout<<"";
		
    printPath(path, path[dest]);
    cout<<" -> "<<dest;
    //push the vertices visited before the dest vertex in the queue for each dest vertex
    parent.push(dest);
    
    	
}

  
//Constructor
Graph::Graph(int size){
	//maxSize is the size of the graph and initialize weights
	//a 2d array to store the adjacency matrix
	maxSize = size;
	weights = new int*[size];
	for (int i = 0; i < size; i++)
		weights[i] = new int[size];
	smallestWeight = new int[size];
	
}
//Destructor
Graph::~Graph(){
	//delete the pointers and dynamic arrays
	for (int i = 0; i < gSize; i++){
		delete [] weights[i];
	}
	delete [] weights;
	delete smallestWeight;
	delete path;
	
}

int main(){
	int source;
	bool status;
	Graph wgt(12);
	wgt.createGraph();
	bool option= true;
	char choice;
	while(option){
		do{
		cout<<"enter the source vertex between 1 and 11:"<<endl;
		cin>>source;
		if(source>0 && source<12){
			status = true;
			wgt.shortestPath(source);
			system("viz.py");
			
		}
		else{
			cout<<"the source is invalid, try again"<<endl;
			status = false;
		}
		
	}while(status==false);
	do{
	
	cout<<"do you want to calculate from another source?(Y/N) :"<<endl;
	cin>>choice;
	if (choice=='N' || choice == 'n'){
		option= false;
	}
	else if(choice=='Y' || choice=='y'){
		option = true;
	}
	else {
		option=false;
		cout<<"invalid option"<<endl;
		
	}
	}while(option==false && !(choice=='n' || choice=='N'));
	}
	
	
}


