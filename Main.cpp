#include <iostream>
#include <fstream>
using namespace std;
#include "WeightedAdjMatrixGraph.h"
#include "WeightedAdjListGraph.h"

int main(int argc, char* argv[])
{
	vertex sourceVertex , targetVertex;
	unsigned int vertexAmount;
	unsigned long position;
	Weight weightOfTargetVertex;
	ofstream myOutputFile;
	ifstream myFile;
	bool routeExists = false;

	myFile.exceptions(std::ifstream::failbit | std::ifstream::badbit ); // turn on Exeptions
	try {
		myFile.open(argv[1], ios::in);
		myOutputFile.open(argv[2], ios::out);

		myFile >> vertexAmount;
		myFile >> sourceVertex;
		myFile >> targetVertex;
			
		//save offset of file
		position = myFile.tellg();

		WeightedAdjMatrixGraph matrixGraph(vertexAmount);
		WeightedAdjListGraph listGraph(vertexAmount);
		try {
			listGraph.BuildGraphFromFile(myFile);

			listGraph.Timed_DIJKSTRA_heap(sourceVertex, myOutputFile);
			listGraph.PrintDistanceOfAlgo(targetVertex, "Adjency Dijkstra heap ");

			listGraph.Timed_DIJKSTRA_array(sourceVertex, myOutputFile);
			listGraph.PrintDistanceOfAlgo(targetVertex, "Adjency Dijkstra array ");

			listGraph.Timed_BELLMAN_FORD(sourceVertex, myOutputFile);
			listGraph.PrintDistanceOfAlgo(targetVertex, "Adjency Bellman-Ford ");

			//Go to offset
			myFile.seekg(position);
			
			matrixGraph.BuildGraphFromFile(myFile);
			matrixGraph.Timed_DIJKSTRA_heap(sourceVertex, myOutputFile);
			matrixGraph.PrintDistanceOfAlgo(targetVertex, "Matrix Dijkstra heap ");

			matrixGraph.Timed_DIJKSTRA_array(sourceVertex, myOutputFile);
			matrixGraph.PrintDistanceOfAlgo(targetVertex, "Matrix Dijkstra array ");

			matrixGraph.Timed_BELLMAN_FORD(sourceVertex, myOutputFile);
			matrixGraph.PrintDistanceOfAlgo(targetVertex, "Matrix Bellman-Ford ");

		}
		catch (const char* msg) {
			cout << msg;
		}
		

		myFile.close();
		myOutputFile.close();
	}
	catch (std::ifstream::failure e) {
		cout << "\n ******** \nFailed to Open\n ********\n";
	}
}