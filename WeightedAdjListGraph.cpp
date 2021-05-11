#include "WeightedAdjListGraph.h"


WeightedAdjListGraph::WeightedAdjListGraph(int i_vertexAmount) : m_distanceArr(nullptr) , m_parentArr(nullptr), m_isAllocated(false)
{
	if(i_vertexAmount <= 0)
	{
		throw "Negative Number of Verticies";
	}	

	m_vertexAmount = i_vertexAmount+1;
	m_edgesAmount = 0;
	m_Arr = new MyList<Edge>[m_vertexAmount];
}

WeightedAdjListGraph::~WeightedAdjListGraph()
{
	ClearGraph();
}

void WeightedAdjListGraph::ClearGraph()
{
		delete[] m_Arr;
		m_vertexAmount = 0;
		m_edgesAmount = 0;


		if(m_isAllocated)
		{
			delete[] m_distanceArr;
			delete[] m_parentArr;
		}

		m_isAllocated = false;
}

bool WeightedAdjListGraph::IsAdjacent(vertex i_vertexU, vertex i_vertexV)
{
	const Node<Edge>* listIterator = m_Arr[i_vertexU].GetHead();

	while (listIterator != nullptr) 
	{
		if (listIterator->m_data.m_toVertex == i_vertexV)
			return true;

		listIterator = listIterator->m_next;
	}

	return false;
}

void WeightedAdjListGraph::BuildGraphFromFile(istream& i_inputFile)
{
	vertex vertexU, vertexV;
	float weight;
	string input;
	i_inputFile.ignore(1);
	int finish;
	
	while (!i_inputFile.eof())
	{
		finish = i_inputFile.peek();
		if(finish == EOF)
		{
			break;
		}
		getline(i_inputFile, input);
		
		
		if (input.size()==0)
		{
			break;
		}
		stringstream myStream(input);
		

		myStream >> vertexU;
		myStream >> vertexV;
		myStream >> weight;
		myStream >> ws;
		//when getting 3 numbers and a empty space after them
		// mystream isnt eof therfore we throw bad syntax
		
		/*while(myStream.peek() == ' ')
		{
			myStream >> whiteSpaceEater;
		}*/
		
		if (!myStream.eof()) 
		{
			throw "Bad Syntax";
		}
		try 
		{
			AddEdge(vertexU, vertexV, weight);
		}
		catch(const char* msg)
		{
			throw msg;
		}
	}
}


void WeightedAdjListGraph::GetAdjList(vertex i_vertexU, MyList<vertex>& o_adjListResult)
{
	const Node<Edge>* iterator = m_Arr[i_vertexU].GetHead();
	
	while( iterator != nullptr){

		o_adjListResult.AddToTail(iterator->m_data.m_toVertex);
		iterator = iterator->m_next;
	}

}

void WeightedAdjListGraph::AddEdge(vertex i_vertexU, vertex i_vertexV, float i_Weight)
{
	if (i_vertexU == i_vertexV)
	{
		throw "No Parallel Edges";
	}
	if (i_vertexV > m_vertexAmount || i_vertexU > m_vertexAmount )
	{
		throw "Out Of Range";
	}
	if (i_Weight < 0) 
	{
		throw "No Negative Edges";
	}
	Edge edgeToAdd;
	edgeToAdd.initiateEdge(i_vertexU, i_vertexV, i_Weight);

	if(m_Arr[i_vertexU].GetSize()>0 && m_Arr[i_vertexU].SearchNode(edgeToAdd))
	{
		throw "Edge Already Exists";
	}
	
	m_Arr[i_vertexU].AddToTail(edgeToAdd);
	m_edgesAmount++;
}

void WeightedAdjListGraph::RemoveEdge(vertex i_vertexU, vertex i_vertexV)
{
	Edge edgeToRemove;
	edgeToRemove.initiateEdge(i_vertexU, i_vertexV);

	try 
	{
		m_Arr[i_vertexU].DeleteFromList(edgeToRemove);
		m_edgesAmount--;
	}
	catch (const char* msg) {
		throw msg;
	}
}


void WeightedAdjListGraph::DIJKSTRA_heap(vertex i_startVertex)
{
	if (i_startVertex <= 0 || i_startVertex >= m_vertexAmount)
	{
		throw "Source Verex Not Valid";
	}
	pair <Weight, vertex> U;
	MyList<vertex> neighborListOfVertexU;
	const Node<vertex>* iterator;

	INIT(i_startVertex);

	//sending array from  [1] index in order to ignore [0] index
	GraphMinHeap queue(m_distanceArr+1, m_vertexAmount-1);

	while (queue.IsEmpty() == false ) 
	{
		U = queue.DeleteMin();
		neighborListOfVertexU.ClearList();
		GetAdjList(U.second, neighborListOfVertexU);
		iterator = neighborListOfVertexU.GetHead();

		while (iterator!= nullptr)
		{
			if (RELAX(U.second, iterator->m_data) == true) {
				queue.DecreaseKey(iterator->m_data, m_distanceArr[iterator->m_data]);
			}
			iterator = iterator->m_next;
		}
	}
}

void WeightedAdjListGraph::DIJKSTRA_array(vertex i_startVertex)
{
	if (i_startVertex <= 0 || i_startVertex >= m_vertexAmount)
	{
		throw "Source Verex Not Valid";
	}

	MyList<vertex> neighborListOfVertexU;
	const Node<vertex>* iterator;
	int vertexU;
	WeightArray queue(m_distanceArr, m_vertexAmount);

	INIT(i_startVertex);

	vertexU = queue.DeleteMinGetIndex();
	while (vertexU >= 0)
	{
		neighborListOfVertexU.ClearList();
		GetAdjList(vertexU, neighborListOfVertexU);
		iterator = neighborListOfVertexU.GetHead();

		while (iterator != nullptr)
		{
			if (RELAX(vertexU, iterator->m_data) == true) {
				queue.DecreaseVal(iterator->m_data, m_distanceArr[iterator->m_data]);
			}
			iterator = iterator->m_next;
		}

		vertexU = queue.DeleteMinGetIndex();
	}


}

void WeightedAdjListGraph::Timed_DIJKSTRA_heap(vertex i_startVertex, ofstream& OutputFile)
{
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	DIJKSTRA_heap(i_startVertex);// Here you put the name of the function you wish to measure

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program. 
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	// The name of the file which is in argv[2]
	OutputFile << "Adjacency Dijkstra heap  " << fixed
		<< time_taken << setprecision(9);
	OutputFile << " sec" << endl;
}

void WeightedAdjListGraph::Timed_DIJKSTRA_array(vertex i_startVertex, ofstream& OutputFile)
{
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	DIJKSTRA_array(i_startVertex);// Here you put the name of the function you wish to measure

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program. 
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	// The name of the file which is in argv[2]
	OutputFile << "Adjacency Dijkstra array " << fixed
		<< time_taken << setprecision(9);
	OutputFile << " sec" << endl;
}

void WeightedAdjListGraph::Timed_BELLMAN_FORD(vertex i_startVertex, ofstream& OutputFile)
{
	auto start = chrono::high_resolution_clock::now();
	// unsync the I/O of C and C++. 
	ios_base::sync_with_stdio(false);

	BELLMAN_FORD(i_startVertex);// Here you put the name of the function you wish to measure

	auto end = chrono::high_resolution_clock::now();
	// Calculating total time taken by the program. 
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	// The name of the file which is in argv[2]
	OutputFile << "Adjacency Bellman Ford   " << fixed
		<< time_taken << setprecision(9);
	OutputFile << " sec" << endl;
}

void WeightedAdjListGraph::BELLMAN_FORD(vertex i_startVertex)
{
	if (i_startVertex <= 0 || i_startVertex >= m_vertexAmount)
	{
		throw "Source Verex Not Valid";
	}

	bool relaxFlag = false;
	int vertexIndex, edgeIndex, bellmanIndex;
	const Node<Edge>* iterator;

	INIT(i_startVertex);
	for (bellmanIndex = 1; bellmanIndex < m_vertexAmount; bellmanIndex++)
	{
		for (vertexIndex = 1; vertexIndex < m_vertexAmount; vertexIndex++)
		{
			for (iterator = m_Arr[vertexIndex].GetHead(); iterator != nullptr; iterator = iterator->m_next)
			{
				edgeIndex = iterator->m_data.m_toVertex;
				relaxFlag = RELAX(vertexIndex, edgeIndex);

				if (relaxFlag == true && bellmanIndex == (m_vertexAmount - 1))
				{
					throw "Negative Cycle";
				}
			}
		}
	}
}



void WeightedAdjListGraph::INIT(vertex i_startVertex)
{
	if (!m_isAllocated) 
	{
		m_distanceArr = new Weight[m_vertexAmount];
		m_parentArr = new Parent[m_vertexAmount];
		m_isAllocated = true;
	}
	else
	{
		for(int index = 0 ; index < m_vertexAmount ; index++)
		{
			m_distanceArr[index].m_infinity = true;
			m_distanceArr[index].m_weight = 0;

			m_parentArr[index].m_nulled = true;
			m_parentArr[index].m_parent = 0;
		}
	}

	m_distanceArr[(int)i_startVertex].m_infinity = false;
	m_distanceArr[(int)i_startVertex].m_weight = 0;
}

bool WeightedAdjListGraph::RELAX(vertex i_vertexU, vertex i_vertexV)
{
	Weight U = m_distanceArr[(int)i_vertexU];
	Weight V = m_distanceArr[(int)i_vertexV];
	float weightOfEdge = 0; ///this

	Edge edgeToFind;
	const Node<Edge>* iterator;
	edgeToFind.m_edgeExists = true;
	edgeToFind.m_fromVertex = i_vertexU;
	edgeToFind.m_toVertex = i_vertexV;
	iterator = m_Arr[i_vertexU].SearchNode(edgeToFind);
	weightOfEdge = iterator->m_data.m_weight;

	if((V.m_infinity == true && U.m_infinity == false)				// (u has value v doesnt)
		|| ((V.m_infinity == false && U.m_infinity == false)		// (both have values &&
		&& V.m_weight > U.m_weight + weightOfEdge )) // normal Relax)
	{	
		m_distanceArr[(int)i_vertexV].m_weight = m_distanceArr[(int)i_vertexU].m_weight + weightOfEdge;
		m_distanceArr[(int)i_vertexV].m_infinity = false;
		m_parentArr[(int)i_vertexV].m_nulled = false;
		m_parentArr[(int)i_vertexV].m_parent = i_vertexU;

		return true;
	}

	return false;
}

Weight WeightedAdjListGraph::GetDistanceToVertex(vertex i_targetVertex)
{
	
	if(i_targetVertex > m_vertexAmount)
	{
		throw "Target Vertex Not Valid";
	}

	return m_distanceArr[i_targetVertex];
}

void WeightedAdjListGraph::PrintDistanceOfAlgo(vertex i_targetVertex, string i_algoName) 
{
	Weight weightOfTargetVertex = GetDistanceToVertex(i_targetVertex);
	cout << "Adjency " << i_algoName << " ";
	if (weightOfTargetVertex.m_infinity)
	{
		cout << "No route" << endl;
	}
	else
	{
		cout << weightOfTargetVertex.m_weight << endl;
	}
}

