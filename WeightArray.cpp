#include "WeightArray.h"


WeightArray::WeightArray(Weight* i_Arr, int i_arrSize) : m_arrSize(i_arrSize), m_allocated(true)
{
	m_arr = new Weight[i_arrSize];
	for (int index = 1; index < i_arrSize; index++)
	{
		m_arr[index] = i_Arr[index];
	}
}

WeightArray::~WeightArray()
{
	if (m_allocated)
	{
		delete[] m_arr;
	}
}

int WeightArray::DeleteMinGetIndex()
{
	Weight min = m_arr[0];
	int MinIndex = -1;

	for (int index = 0; index < m_arrSize; index++)
	{
		if (m_arr[index].m_weight == -1)
		{
			continue;
		}
		if (
			(m_arr[index].m_infinity == false && min.m_infinity == true)
			|| ((m_arr[index].m_infinity == false && min.m_infinity == false)
			&& m_arr[index].m_weight < min.m_weight)
			)
		{
			min = m_arr[index];
			MinIndex = index;
		}
	}

	if(MinIndex > 0)
	{	
		m_arr[MinIndex].m_weight = -1;
	}

	return MinIndex;
}

void WeightArray::DecreaseVal(vertex i_vertexU, Weight i_newVal)
{
	m_arr[i_vertexU] = i_newVal;
}
