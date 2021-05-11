#include <iostream>
#include "GraphUnits.h"

#ifndef NON_NEG_ARRAY
#define NON_NEG_ARRAY

using namespace std;

class WeightArray
{

private:
	
	Weight* m_arr;
	int m_arrSize;
	bool m_allocated;

public:
	/// <summary>
	/// Creates WeightArray from given array
	/// </summary>
	WeightArray(Weight* i_Arr, int i_arrSize);
	~WeightArray();


	/// <summary>	///	Returns the Index of the item with the minimal value, destroys its value to -1	/// IF not minimal item exists - returns -1 as index	/// </summary>
	int DeleteMinGetIndex();

	/// <summary>
	/// Updates the value of i_vertexU To i_newVal
	/// </summary>
	void DecreaseVal(vertex i_vertexU, Weight i_newVal);


};


#endif