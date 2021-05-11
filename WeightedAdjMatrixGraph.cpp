#include "WeightedAdjMatrixGraph.h"

WeightedAdjMatrixGraph::WeightedAdjMatrixGraph(int i_vertexAmount) : m_distanceArr(nullptr), m_parentArr(nullptr), m_isAllocated(false)
{
	if (i_vertexAmount <= 0) 
	{
		throw "Negative Number of Verticies";
	}
	m_vertexAmount = i_vertexAmount+1;
	m_edgesAmount = 0;
	m_matrix = new Edge* [m_vertexAmount];

	int indexOfLeftVertex, indexOfRightVertex;

	//starts from 1 beacuse vertex names begin from '1','2' ...
	for (indexOfLeftVertex = 1; indexOfLeftVertex < m_vertexAmount; indexOfLeftVertex++) 
	{
		m_matrix[indexOfLeftVertex] = new Edge[m_vertexAmount];

		for (indexOfRightVertex = 1; indexOfRightVertex < m_vertexAmount; indexOfRightVertex++) 
		{
			m_matrix[indexOfLeftVertex][indexOfRightVertex].initiateEdge(indexOfLeftVertex, indexOfRightVertex);
		}
	}

}




WeightedAdjMatrixGraph::~WeightedAdjMatrixGraph()
{
	ClearGraph();
}

void WeightedAdjMatrixGraph::ClearGraph()
{
	int indexOfLeftVertex;

	//constructor doesnt allocate mem to m_matrix[0]
	for (indexOfLeftVertex = 1; indexOfLeftVertex < m_vertexAmount; indexOfLeftVertex++) 
	{
		delete[] m_matrix[indexOfLeftVertex];
	}
	delete[] m_matrix;

	if(m_isAllocated == true)
	{
		delete[] m_distanceArr;
		delete[] m_parentArr;
		m_isAllocated = false;
	}

	m_vertexAmount = 0;
	m_edgesAmount = 0;

}

bool WeightedAdjMatrixGraph::IsAdjacent(vertex i_vertexU, vertex i_vertexV)
{
	return m_matrix[i_vertexU][i_vertexV].m_edgeExists;
}

void WeightedAdjMatrixGraph::GetAdjList(vertex i_vertexU, MyList<vertex>& o_adjListResult)
{
	
	int indexVertex;

	for(indexVertex = 1 ; indexVertex < m_vertexAmount ; indexVertex++)
	{
		if(m_matrix[i_vertexU][indexVertex].m_edgeExists)
		{
			o_adjListResult.AddToTail(indexVertex);
		}
	}

}

void WeightedAdjMatrixGraph::BuildGraphFromFile(istream& i_inputFile)
{
	vertex vertexU, vertexV;
	float weight;
	int finish;
	string input;
	i_inputFile.ignore(1);

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

void WeightedAdjMatrixGraph::AddEdge(vertex i_vertexU, vertex i_vertexV, float i_Weight)
{
	if (m_matrix[i_vertexU][i_vertexV].m_edgeExists)
	{
		throw "Edge Already Exists";
	}
	if(i_vertexU == i_vertexV)
	{
		throw "No Parallel Edges";
	}
	if (i_Weight < 0) {
		throw "No Negative Edges";
	}
	if( i_vertexU > m_vertexAmount || i_vertexV > m_vertexAmount)
	{
		throw "Vertex Out of Range";
	}


	m_matrix[i_vertexU][i_vertexV].m_edgeExists = true;
	m_matrix[i_vertexU][i_vertexV].m_weight = i_Weight;
	m_edgesAmount++;
}

void WeightedAdjMatrixGraph::RemoveEdge(vertex i_vertexU, vertex i_vertexV)
{
	if (!m_matrix[i_vertexU][i_vertexV].m_edgeExists)
	{
		throw "Edge Does not Exist";
	}
	m_matrix[i_vertexU][i_vertexV].m_edgeExists = false;
	m_edgesAmount--;
}

void WeightedAdjMatrixGraph::DIJKSTRA_heap(vertex i_startVertex)
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

void WeightedAdjMatrixGraph::DIJKSTRA_array(vertex i_startVertex)
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
	while ( vertexU >= 0 )
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

void WeightedAdjMatrixGraph::BELLMAN_FORD(vertex i_startVertex) 
{
	if (i_startVertex <= 0 || i_startVertex >= m_vertexAmount)
	{
		throw "Source Verex Not Valid";
	}
	
	bool relaxFlag = false;
	int vertexIndex, edgeIndex, bellmanIndex;

	INIT(i_startVertex);
	for (bellmanIndex = 1; bellmanIndex < m_vertexAmount; bellmanIndex++)
	{
		for (vertexIndex = 1; vertexIndex < m_vertexAmount; vertexIndex++)
		{
			for (edgeIndex = 1; edgeIndex < m_vertexAmount; edgeIndex++)
			{
				if (m_matrix[vertexIndex][edgeIndex].m_edgeExists == true)
				{
					relaxFlag = RELAX(vertexIndex, edgeIndex);
					
					if (relaxFlag == true && bellmanIndex == (m_vertexAmount - 1))
					{
						throw "Negative Cycle";
					}
				}
			}
		}
	}
}

void WeightedAdjMatrixGraph::Timed_DIJKSTRA_heap(vertex i_startVertex ,ofstream& OutputFile)
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
	OutputFile << "Matrix Dijkstra heap     " << fixed
		<< time_taken << setprecision(9);
	OutputFile << " sec" << endl;
}

void WeightedAdjMatrixGraph::Timed_DIJKSTRA_array(vertex i_startVertex, ofstream& OutputFile)
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
	OutputFile << "Matrix Dijkstra array    " << fixed
		<< time_taken << setprecision(9);
	OutputFile << " sec" << endl;
}

void WeightedAdjMatrixGraph::Timed_BELLMAN_FORD(vertex i_startVertex, ofstream& OutputFile)
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
	OutputFile << "Matrix Bellman Ford      " << fixed
		<< time_taken << setprecision(9);
	OutputFile << " sec" << endl;
}


Weight WeightedAdjMatrixGraph::GetDistanceToVertex(vertex i_targetVertex)
{
	if(i_targetVertex > m_vertexAmount)
	{
		throw "Target Vertex Not Valid";
	}

	return m_distanceArr[i_targetVertex];
}

void WeightedAdjMatrixGraph::PrintDistanceOfAlgo(vertex i_targetVertex, string i_algoName)
{
	Weight weightOfTargetVertex = GetDistanceToVertex(i_targetVertex);
	cout << "Matrix " << i_algoName << " ";
	if (weightOfTargetVertex.m_infinity)
	{
		cout << "No route" << endl;
	}
	else
	{
		cout << weightOfTargetVertex.m_weight << endl;
	}
}


void WeightedAdjMatrixGraph::INIT(vertex i_startVertex)
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

bool WeightedAdjMatrixGraph::RELAX(vertex i_vertexU, vertex i_vertexV)
{
	Weight U = m_distanceArr[(int)i_vertexU];
	Weight V = m_distanceArr[(int)i_vertexV];

	if((V.m_infinity == true && U.m_infinity == false)				// (u has value v doesnt)
		|| ((V.m_infinity == false && U.m_infinity == false)		// (both have values &&
		&& V.m_weight > U.m_weight + m_matrix[i_vertexU][i_vertexV].m_weight )) // normal Relax)
	{	
		m_distanceArr[(int)i_vertexV].m_weight = m_distanceArr[(int)i_vertexU].m_weight + m_matrix[i_vertexU][i_vertexV].m_weight;
		m_distanceArr[(int)i_vertexV].m_infinity = false;
		m_parentArr[(int)i_vertexV].m_nulled = false;
		m_parentArr[(int)i_vertexV].m_parent = i_vertexU;

		return true;
	}

	return false;
}
