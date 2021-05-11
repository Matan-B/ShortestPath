#pragma once
#include <istream>
#include <string>
#include <sstream>


using vertex = unsigned int;

struct Weight
{
	bool m_infinity;
	float m_weight;

	Weight()
	{
		m_infinity = true;
		m_weight = 0;
	};
};
struct Parent
{
	bool m_nulled;
	vertex m_parent;

	Parent()
	{
		m_nulled = true;
		m_parent = 0;
	}
};

class Edge 
{
public:
	float m_weight;
	bool m_edgeExists;
	vertex m_fromVertex, m_toVertex;

	Edge();

	void initiateEdge(vertex i_fromVertex, vertex i_toVertex);
	void initiateEdge(vertex i_fromVertex, vertex i_toVertex,float i_weight);

	inline bool operator==(const Edge& rightVal) {
		bool result=false;
		if (rightVal.m_edgeExists) {
			if ((rightVal.m_fromVertex == this->m_fromVertex) && (rightVal.m_toVertex == this->m_toVertex))
			result = true;
		}

		return result;
	}

};