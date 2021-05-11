#include <iostream>
#include "GraphUnits.h"

#ifndef GRAPH_MINHEAP
#define GRAPH_MINHEAP

using namespace std;

class GraphMinHeap 
{
private:
	pair<Weight, vertex>* m_data;

	//made specificly for graphs - decrease key
	int* m_indexToItemInHeap;
	int m_maxSize;
	int m_heapSize;
	bool m_allocated;

	static vertex Left(int node) {	return (2 * node + 1); }
	static vertex Right(int node) { return (2 * node + 2); }
	static vertex Parent(int node){	return (node - 1) / 2; }
	void FixHeap(int node);
	void swap(pair<Weight, vertex>& io_ref_p1, pair<Weight, vertex>& io_ref_p2);

public:
	GraphMinHeap(int i_maxSize) ;
	GraphMinHeap(Weight* i_dataArr, int i_arrSize);
	~GraphMinHeap();

	/// <summary>	///	returns and doesnt delete the first item in the heap	/// </summary>
	const pair<Weight, vertex>& Min(){	return m_data[0];}

	/// <summary>	/// Returns the first item from the heap and Deletes it.	/// </summary>
	pair<Weight, vertex> DeleteMin();

	/// <summary>	///	insert to the correct location a Pair<Weight,Vertex> item	/// </summary>
	void Insert(pair<Weight, vertex> i_item);

	/// <summary>	/// creates and inserts to the correct location a Pair<Weight,Vertex> Item with the given values  	/// </summary>
	void Insert(Weight i_itemKey, vertex i_itemData)
	{
		pair<Weight, vertex> p1(i_itemKey, i_itemData);
		Insert(p1);
	}

	/// <summary>	///	indicates if the heap is empty or not	/// </summary>
	bool IsEmpty() { return (m_heapSize == 0); }

	/// <summary>	/// Updates the key of i_vertexU To i_newKey and Fixes the heap accordingly	/// </summary>
	void DecreaseKey(const vertex& i_vertexU, const Weight& i_newKey);
};

#endif