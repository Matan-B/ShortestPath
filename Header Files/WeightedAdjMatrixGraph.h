#pragma once
#include "MyList.h"
#include "GraphMinHeap.h"
#include "WeightArray.h"
#include <chrono>
#include <fstream>
#include <iomanip> 


class WeightedAdjMatrixGraph
{

private:
	unsigned int m_vertexAmount;
	unsigned int m_edgesAmount;
	Edge** m_matrix;

	Weight* m_distanceArr;
	Parent* m_parentArr;
	bool m_isAllocated;

	void INIT(vertex i_startVertex);
	bool RELAX(vertex i_vertexU, vertex i_vertexV);

public:
	
	WeightedAdjMatrixGraph(int i_vertexAmount);
	~WeightedAdjMatrixGraph();

	void ClearGraph();
	bool IsAdjacent(vertex i_vertexU, vertex i_vertexV);
	void GetAdjList(vertex i_vertexU, MyList<vertex>& o_adjListResult);

	/// <summary>
	/// Buillding Graph (Syntax- As Instructed) Using inputFile
	/// </summary>
	void BuildGraphFromFile(istream& i_inputFile);
	void AddEdge(vertex i_vertexU, vertex i_vertexV, float i_Weight);
	void RemoveEdge(vertex i_vertexU, vertex i_vertexV);

	void DIJKSTRA_heap(vertex i_startVertex);
	void DIJKSTRA_array(vertex i_startVertex);
	void BELLMAN_FORD(vertex i_startVertex);
	
	/// <summary>
	///FOR ALL "TIMED_" methods: Mesuaring time for each algorithm and prints to OutputFile	
	/// </summary>
	void Timed_DIJKSTRA_heap(vertex i_startVertex, ofstream& OutputFile);
	void Timed_DIJKSTRA_array(vertex i_startVertex, ofstream& OutputFile);
	void Timed_BELLMAN_FORD(vertex i_startVertex, ofstream& OutputFile);

	/// <summary>
	/// returns the Distance from the source vertex to i_targetVertex
	/// </summary>
	Weight GetDistanceToVertex(vertex i_targetVertex);

	/// <summary>
	/// Prints the Distance from the source vertex to i_targetVertex
	/// </summary>
	void PrintDistanceOfAlgo(vertex i_targetVertex, string i_algoName);

};