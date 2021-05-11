#include "GraphUnits.h"

Edge::Edge()
{
	m_edgeExists = false;
}

void Edge::initiateEdge(vertex i_fromVertex, vertex i_toVertex)
{
	m_edgeExists = false;
	m_fromVertex = i_fromVertex;
	m_toVertex = i_toVertex;
}

void Edge::initiateEdge(vertex i_fromVertex, vertex i_toVertex, float i_weight)
{
	initiateEdge(i_fromVertex, i_toVertex);
	m_weight = i_weight;
	m_edgeExists = true;
}
