#include "GraphMinHeap.h"

void GraphMinHeap::FixHeap(int node)
{
	int min;
	int left = Left(node);
	int right = Right(node);

	if (
		(left < m_heapSize) && (
			(m_data[left].first.m_infinity == false && m_data[node].first.m_infinity == true)  //left is smaller than node
			|| (m_data[left].first.m_infinity == false && m_data[node].first.m_infinity == false	// both have values
				&& m_data[left].first.m_weight < m_data[node].first.m_weight))							// actual check
		)
	{
		min = left;
	}
	else
	{
		min = node;
	}
	if (
		(right < m_heapSize) && (
			(m_data[right].first.m_infinity == false && m_data[min].first.m_infinity == true)  //left is smaller than node
			|| (m_data[right].first.m_infinity == false && m_data[min].first.m_infinity == false // both have values
				&& m_data[right].first.m_weight < m_data[min].first.m_weight)))
	{
		min = right;
	}
	if (min != node)
	{
		swap(m_data[node], m_data[min]);
		FixHeap(min);
	}
}

void GraphMinHeap::swap(pair<Weight, vertex>& io_ref_p1, pair<Weight, vertex>& io_ref_p2)
{
	int tempIndex;
	tempIndex = m_indexToItemInHeap[io_ref_p2.second];
	m_indexToItemInHeap[io_ref_p2.second] = m_indexToItemInHeap[io_ref_p1.second];
	m_indexToItemInHeap[io_ref_p1.second] = tempIndex;

	pair<Weight, vertex> temp = io_ref_p1;
	io_ref_p1 = io_ref_p2;
	io_ref_p2 = temp;

}

GraphMinHeap::GraphMinHeap(int i_maxSize) : m_maxSize(i_maxSize), m_heapSize(0), m_allocated(true)
{
	m_data = new pair<Weight, vertex>[i_maxSize];
	m_indexToItemInHeap = new int[i_maxSize + 1];
}

GraphMinHeap::GraphMinHeap(Weight* i_dataArr, int i_arrSize) : m_allocated(true), m_heapSize(0), m_maxSize(i_arrSize)
{

	m_data = new pair<Weight, vertex>[i_arrSize];
	m_indexToItemInHeap = new int[i_arrSize + 1]; // index aray

	for (int index = 0; index < i_arrSize; index++)
	{

		//						reminder: vertex I is in I in Graph, going from 1 to n
		Insert(i_dataArr[index], (index + 1));		//vertex I in i_dataArr is in i_dataArr[I-1] 
	}
}

GraphMinHeap::~GraphMinHeap()
{
	if (m_allocated == true)
	{
		delete[] m_data;
		m_allocated = false;
	}
}

pair<Weight, vertex> GraphMinHeap::DeleteMin()
{
	if (m_heapSize < 1)
	{
		throw "Heap Size Not Valid";
	}
	pair<Weight, vertex> min = m_data[0];
	m_heapSize--;
	m_indexToItemInHeap[m_data[m_heapSize].second] = 0;
	m_data[0] = m_data[m_heapSize];
	FixHeap(0);
	return min;
}

void GraphMinHeap::Insert(pair<Weight, vertex> i_item)
{
	if (m_heapSize == m_maxSize)
	{
		throw "Heap Is Full";
	}

	int index = m_heapSize;
	m_heapSize++;

	while (
		(index > 0) &&
		((m_data[Parent(index)].first.m_infinity == true && i_item.first.m_infinity == false) // (u has weight v doesnt)
			|| (m_data[Parent(index)].first.m_infinity == false && i_item.first.m_infinity == false
				&& m_data[Parent(index)].first.m_weight > i_item.first.m_weight))) // if both !inf check who weights more
	{
		m_data[index] = m_data[Parent(index)];
		m_indexToItemInHeap[m_data[index].second] = index;
		index = Parent(index);
		//update index array also here

	}


	m_indexToItemInHeap[i_item.second] = index;
	m_data[index] = i_item;
}

void GraphMinHeap::DecreaseKey(const vertex& i_vertexU, const Weight& i_newKey)
{
	int locationInHeap = m_indexToItemInHeap[i_vertexU];

	if ((i_newKey.m_infinity == true) ||
		(i_newKey.m_infinity == false && m_data[locationInHeap].first.m_infinity == false && m_data[locationInHeap].first.m_weight <= i_newKey.m_weight))
	{
		throw "Cannot Decrease - new Weight Not Smaller";
	}


	m_data[locationInHeap].first = i_newKey;


	//pushing the decreased key node upward in the heap
	int index = locationInHeap;
	while (index > 0)
	{
		if ((m_data[Parent(index)].first.m_infinity == true && m_data[index].first.m_infinity == false)
			||
			(m_data[Parent(index)].first.m_infinity == false && m_data[index].first.m_infinity == false)
			&& (m_data[Parent(index)].first.m_weight > m_data[index].first.m_weight)
			)
		{
			swap(m_data[Parent(index)], m_data[index]);
		}
		else
		{
			break;
		}

		index = Parent(index);
	}

}
