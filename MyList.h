using namespace std;
#include <iostream>

#ifndef LIST_H
#define LIST_H

template <typename T>
class MyList;

template <typename T>
class Node
{
	friend class MyList<T>;
public:
	T m_data;
	Node* m_next = nullptr;
};

template <typename T>
class MyList 
{
private:
	Node<T>* m_head;
	Node<T>* m_tail;
	unsigned int m_listLen;

public:
	MyList()
	{
		m_head = m_tail = nullptr;
		m_listLen = 0;
	}

	~MyList()
	{
		ClearList();
	}
	
	void AddToTail(const T& i_toInsert)
	{
		Node<T>* nodetoAdd = new Node<T>;

		nodetoAdd->m_data = i_toInsert;
		nodetoAdd->m_next = nullptr;

		if (m_head == nullptr)
		{
			m_head = nodetoAdd;
		}
		else
		{
			m_tail->m_next = nodetoAdd;
		}
		m_tail = nodetoAdd;
		m_listLen++;
	}

	/// <summary>
	///	Removes the last item from the list, and return the node to the user
	/// </summary>
	Node<T>* RemoveAndReturnTail()
	{
		if (m_listLen == 0)
		{
			throw "List Is Empty";
		}

		Node<T>* newTail = m_head;
		Node<T>* oldTail = m_tail;

		if (m_listLen == 1)
		{
			m_head = m_tail = nullptr;
		}
		else {
			while (newTail->m_next != m_tail)
			{
				newTail = newTail->m_next;
			}
		}

		m_tail = newTail;
		m_tail->m_next = nullptr;
		m_listLen--;

		return oldTail;
	}

	/// <summary>
	/// Delete tail from list , doesnt return tail to user
	/// </summary>
	void DeleteTail()
	{

		try {
			delete RemoveAndReturnTail();
		}
		catch (const char* msg) {
			throw msg;
		}

	}

	bool IsEmpty()
	{
		return (m_listLen == 0);

	}
	
	unsigned int GetSize()
	{
		return m_listLen;
	}

	const Node<T>* GetHead()
	{
		return m_head;

	}
	const Node<T>* GetTail()
	{
		return m_tail;
	}

	/// <summary>
	///	Frees all the items in the list, sets list len to 0
	/// </summary>
	void ClearList()
	{
		Node<T>* nodeToRemove = m_head;
		while (nodeToRemove != nullptr)
		{
			nodeToRemove = nodeToRemove->m_next;
			delete(m_head);
			m_head = nodeToRemove;
		}

		m_head = m_tail = nullptr;
		m_listLen = 0;
	}

	/// <summary>
	/// Searches the node and returns the node
	/// </summary>
	Node<T>* SearchNode(T& i_valToSeach)
	{

		if (m_listLen == 0)
		{
			throw "List Is Empty";
		}
		Node<T>* listIterator = m_head;

		while (listIterator != nullptr)
		{
			if (i_valToSeach == listIterator->m_data)
			{
				return listIterator;
			}

			listIterator = listIterator->m_next;
		}

		return nullptr;
	}

	/// <summary>
	/// Searches the node and returns it. also returns the node before the found one (for later uses)
	/// </summary>
	 Node<T>* SearchNode(T& i_valToSeach, Node<T>*& o_ref_previousToVal)
	{

		if (m_listLen == 0)
		{
			throw "\nList Is Empty";
		}

		o_ref_previousToVal = nullptr;
		Node<T>* listIterator = m_head;


		while (listIterator != nullptr)
		{
			if (i_valToSeach == listIterator->m_data)
			{
				return listIterator;
			}

			o_ref_previousToVal = listIterator;
			listIterator = listIterator->m_next;
		}

		o_ref_previousToVal = nullptr;
		return nullptr;
	}

	/// <summary>
	///	Detaches the Node with i_val from the list and return it to the user
	/// </summary>
	 Node<T>* RemoveFromList(T& i_valToRemove)
	{

		 Node<T>* prevNode = nullptr;
		 Node<T>* valNode;

		try
		{
			valNode = SearchNode(i_valToRemove, prevNode);
		}
		catch (const char* msg)
		{
			throw msg;
		}
		if (valNode == nullptr)
		{
			return nullptr;
		}
		else
		{
			if (valNode == m_head)
			{
				m_head = valNode->m_next;
			}
			else if (valNode == m_tail)
			{
				m_tail = prevNode;
				if (m_tail != nullptr)
				{
					m_tail->m_next = nullptr;
				}
			}
			else
			{
				prevNode->m_next = valNode->m_next;
			}
		}

		m_listLen--;
		return valNode;
	}

	/// <summary>
	///	Detaches the node with i_val and deletes it
	/// </summary>
	void DeleteFromList(T& i_valToDelete)
	{
		
		 Node<T>* nodeToDelete;

		try {
			nodeToDelete = RemoveFromList(i_valToDelete);
			if (nodeToDelete != nullptr)
			{
				delete nodeToDelete;
			}
			else
			{
				throw "\nValue doesn't exists";
			}
		}
		catch (const char* msg) {
			throw msg;
		}
	}
};

#endif
 