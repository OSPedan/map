#pragma once

#include <iostream>

template <class Key, class ValueType>
class Node
{
public:
	Node();
	Node(Key key, ValueType date);
	Node(Node<Key, ValueType>* pNodePre, Key key, ValueType date);
	Node(const Node<Key, ValueType>& obj);
	Node(Node<Key, ValueType>&& obj);
	~Node();

	Node<Key, ValueType>* pNodeRight = nullptr;
	Node<Key, ValueType>* pNodeLeft = nullptr;
	Node<Key, ValueType>* pNodePre = nullptr;

	Key key = NULL;
	ValueType date = NULL;
};


template <class Key, class ValueType>
Node<Key, ValueType>::Node() {}

template <class Key, class ValueType>
Node<Key, ValueType>::Node(Key key, ValueType date)
{
	this->key = key;
	this->date = date;
}

template <class Key, class ValueType>
Node<Key, ValueType>::Node(Node<Key, ValueType>* pNodePre, Key key, ValueType date)
{
	this->pNodePre = pNodePre;
	this->pNodeLeft = nullptr;
	this->pNodeRight = nullptr;

	this->key = key;
	this->date = date;
}

template <class Key, class ValueType>
Node<Key, ValueType>::Node(const Node<Key, ValueType>& obj)
{
	if (obj.key > 0)
	{
		this->key = obj.key;
		this->date = obj.date;

		this->pNodeLeft = obj.pNodeLeft;
		this->pNodeRight = obj.pNodeRight;
		this->pNodePre = obj.pNodePre;
	}
}

template <class Key, class ValueType>
Node<Key, ValueType>::Node(Node<Key, ValueType>&& obj)
{
	if (obj.key > 0)
	{
		this->key = obj.key;
		obj.key = NULL;

		this->date = obj.date;
		obj.date = NULL;

		this->pNodeLeft = obj.pNodeLeft;
		obj.pNodeLeft = nullptr;

		this->pNodeRight = obj.pNodeRight;
		obj.pNodeRight = nullptr;

		this->pNodePre = obj.pNodePre;
		obj.pNodePre = nullptr;
	}
}

template <class Key, class ValueType>
Node<Key, ValueType>::~Node() {}

template<class Key, class ValueType>
class Iterator;

template<class T1, class T2>
class Map
{
	//friend class Iterator<T1, T2>;
public:
	typedef Iterator<T1, T2> iter;

	Map() {};
	Map(T1 key, T2 date)
	{
		Push(key, date);
	};

	Map(const Map<T1, T2>& obj)
	{
		if (obj.pStart != nullptr)
		{
			Chose_to_move_to_copy(obj.pStart, obj.pEnd);
		}
	};

	Map(Map<T1, T2>&& obj)
	{
		if (obj.pStart != nullptr)
		{
			this->pStart = obj.pStart;
			obj.pStart = nullptr;

			this->pEnd = obj.pEnd;
			obj.pEnd = nullptr;

			this->uiSize = obj.uiSize;
			obj.uiSize = NULL;

			obj.~Map();
		}
	};

	~Map()
	{
		if (this->pStart != nullptr)
		{
			Chose_to_move_to_delete_node(this->pStart);
		}
	};

	Iterator<T1, T2> Begin()
	{
		Iterator<T1, T2> it(Move_to_first_node(this->pStart));
		return it;
	};

	Iterator<T1, T2> End()
	{
		Iterator<T1, T2> it(this->pEnd);
		return it;
	};

	/*Map<T1, T2>&*/void operator= (const Map<T1, T2>& obj)
	{
		if (this->pStart == obj.pStart)
			return /**this*/;

		if (this->pStart != nullptr)
			this->~Map();

		if (obj.pStart != nullptr)
		{
			Chose_to_move_to_copy(obj.pStart, obj.pEnd);
		}

		/*return *this;*/
	};

	/*Map<T1, T2>&*/void operator= (Map<T1, T2>&& obj)
	{
		if (this->pStart == obj.pStart)
			return /**this*/;

		if (this->pStart != nullptr)
			this->~Map();

		if (obj.pStart != nullptr)
		{
			this->pStart = obj.pStart;
			obj.pStart = nullptr;

			this->pEnd = obj.pEnd;
			obj.pEnd = nullptr;

			this->uiSize = obj.uiSize;
			obj.uiSize = NULL;

			obj.~Map();
		}

		/*return *this*/;
	};

	void Push(T1 key, T2 date)
	{
		if (this->uiSize == 0)
		{
			this->pStart = new Node<T1, T2>(key, date);
			this->pEnd = new Node<T1, T2>;

			this->pStart->pNodeLeft = nullptr;
			this->pStart->pNodePre = nullptr;
			this->pStart->pNodeRight = this->pEnd;

			this->pEnd->pNodePre = this->pStart;
			this->pEnd->pNodeLeft = nullptr;
			this->pEnd->pNodeRight = nullptr;

			++this->uiSize;
			return;
		}

		Choose_to_move_to_create_node(this->pStart, key, date);
	};

	void Show()
	{
		if (this->pStart != nullptr)
		{
			Choose_to_move_to_print(this->pStart);
		}
	};

	unsigned int Size()
	{
		return this->uiSize;
	};

private:
	void Choose_to_move_to_print(Node<T1, T2>*& pPosOfNode)
	{
		if (pPosOfNode->pNodeLeft != nullptr && pPosOfNode->pNodeRight != nullptr)
		{
			Choose_to_move_to_print(pPosOfNode->pNodeLeft);
			Print_value(pPosOfNode);
			Choose_to_move_to_print(pPosOfNode->pNodeRight);
		}
		else if (pPosOfNode->pNodeLeft != nullptr && pPosOfNode->pNodeRight == nullptr)
		{
			Choose_to_move_to_print(pPosOfNode->pNodeLeft);
		}
		else if (pPosOfNode->pNodeRight == this->pEnd && pPosOfNode->pNodeLeft == nullptr)
		{
			Print_value(pPosOfNode);
		}
		else if (pPosOfNode->pNodeRight != nullptr && pPosOfNode->pNodeLeft == nullptr)
		{
			Choose_to_move_to_print(pPosOfNode->pNodeRight);
		}
		else if (pPosOfNode->pNodeLeft == nullptr && pPosOfNode->pNodeRight == nullptr)
		{
			Print_value(pPosOfNode);
		}
	};

	void Choose_to_move_to_create_node(Node<T1, T2>*& pPosOfNode, T1& key, T2& date)
	{
		if (pPosOfNode->key > key)
		{
			if (pPosOfNode->pNodeLeft == nullptr)
			{
				Create_left_node(pPosOfNode, key, date);
				return;
			}
			else
				Choose_to_move_to_create_node(pPosOfNode->pNodeLeft, key, date);
		}
		else if (pPosOfNode->key < key)
		{
			if (pPosOfNode->pNodeRight == this->pEnd)
			{
				pPosOfNode->pNodeRight = nullptr;
				Create_right_node(pPosOfNode, key, date);
				pPosOfNode->pNodeRight->pNodeRight = this->pEnd;

				this->pEnd->pNodePre = pPosOfNode->pNodeRight;
				return;
			}
			else if (pPosOfNode->pNodeRight != this->pEnd && pPosOfNode->pNodeRight == nullptr)
			{
				Create_right_node(pPosOfNode, key, date);
				return;
			}
			else if (pPosOfNode->pNodeRight != this->pEnd && pPosOfNode->pNodeRight != nullptr)
			{
				Choose_to_move_to_create_node(pPosOfNode->pNodeRight, key, date);
			}
		}
		else
		{
			// drop eror
		}
	};

	void Chose_to_move_to_copy(Node<T1, T2>* pNodeOrig, Node<T1, T2>* pNodeEnd)
	{
		Copy(pNodeOrig);

		if (pNodeOrig->pNodeLeft != nullptr && pNodeOrig->pNodeRight != nullptr)
		{
			Chose_to_move_to_copy(pNodeOrig->pNodeLeft, pNodeEnd);
			Chose_to_move_to_copy(pNodeOrig->pNodeRight, pNodeEnd);
		}
		else if (pNodeOrig->pNodeLeft != nullptr && pNodeOrig->pNodeRight == nullptr)
		{
			Chose_to_move_to_copy(pNodeOrig->pNodeLeft, pNodeEnd);
		}
		else if (pNodeOrig->pNodeRight != nullptr && pNodeOrig->pNodeRight == pNodeEnd && pNodeOrig->pNodeLeft == nullptr)
		{
			return;
		}
		else if (pNodeOrig->pNodeRight != nullptr && pNodeOrig->pNodeLeft == nullptr)
		{
			Chose_to_move_to_copy(pNodeOrig->pNodeRight, pNodeEnd);
		}
		else if (pNodeOrig->pNodeLeft == nullptr && pNodeOrig->pNodeRight == nullptr)
		{
			return;
		}
	};

	void Chose_to_move_to_delete_node(Node<T1, T2>*& pPosOfNode)
	{
		if (pPosOfNode->pNodeLeft != nullptr && pPosOfNode->pNodeRight != nullptr)
		{
			Chose_to_move_to_delete_node(pPosOfNode->pNodeLeft);
			Chose_to_move_to_delete_node(pPosOfNode->pNodeRight);
			delete pPosOfNode;
		}
		else if (pPosOfNode->pNodeLeft != nullptr && pPosOfNode->pNodeRight == nullptr)
		{
			Chose_to_move_to_delete_node(pPosOfNode->pNodeLeft);
		}
		else if (pPosOfNode->pNodeRight != nullptr && pPosOfNode->pNodeLeft == nullptr)
		{
			Chose_to_move_to_delete_node(pPosOfNode->pNodeRight);
		}
		else if (pPosOfNode->pNodeLeft == nullptr && pPosOfNode->pNodeRight == nullptr)
		{
			delete pPosOfNode;
		}
	};

	void Print_value(Node<T1, T2>* pPosOfNode)
	{
		if (pPosOfNode != nullptr)
			std::cout << "Key: " << pPosOfNode->key << " " << "Value: " << pPosOfNode->date << std::endl;
	};

	void Create_left_node(Node<T1, T2>*& pPosOfNode, T1& key, T2& date)
	{
		pPosOfNode->pNodeLeft = new Node<T1, T2>(pPosOfNode, key, date);
		++this->uiSize;
	};

	void Create_right_node(Node<T1, T2>*& pPosOfNode, T1& key, T2& date)
	{
		pPosOfNode->pNodeRight = new Node<T1, T2>(pPosOfNode, key, date);
		++this->uiSize;
	};

	Node<T1, T2>* Move_to_first_node(Node<T1, T2>* pPos)
	{
		if (pPos != nullptr)
		{
			if (pPos->pNodeLeft != nullptr)
				this->Move_to_first_node(pPos->pNodeLeft);
			else
				return pPos;
		}
	};


	void Copy(Node<T1, T2>* obj)
	{
		if (obj != nullptr)
		{
			Push(obj->key, obj->date);
		}
	};

	Node<T1, T2>* pStart = nullptr;
	Node<T1, T2>* pEnd = nullptr;

	unsigned int uiSize = 0;
};

template <class Key, class ValueType>
class Iterator : public std::iterator<std::input_iterator_tag, ValueType>
{
	friend class Map<Key, ValueType>;
	friend class Node<Key, ValueType>;
public:
	Iterator() {};

	Iterator(Node<Key, ValueType>* node)
	{
		if (node != nullptr)
		{
			this->pNode = node;
			this->pNext = node->pNodePre;
		}
	};

	Iterator(const Iterator<Key, ValueType>& iter)
	{
		if (iter.pNode != nullptr)
		{
			this->pNode = iter.pNode;
			this->pNext = iter.pNext;
		}
	};

	~Iterator() {};

	//bool operator==(Node<T1, T2>* node);
	//bool operator!=(Node<T1, T2>* node);

	bool operator==(const Iterator<Key, ValueType>& other) const
	{
		if (this->pNode == other.pNode)
			return true;
		return false;
	};

	
	bool operator!=(const Iterator<Key, ValueType>& other) const
	{
		if (this->pNode != other.pNode)
			return true;
		return false;
	};

	/*void operator= (Node<T1, T2>* pPos);
	Node<T1, T2>& operator++();*/

	void operator= (Iterator<Key, ValueType> it)
	{
		if (it != nullptr)
		{
			this->pNode = it.pNode;
			this->pNext = it.pNext;
		}
	};

	ValueType& operator*()
	{
		this->*pNode;
		return pNode->date;
	};

	Iterator<Key, ValueType>& operator++ ()
	{
		Node<Key, ValueType>* tmpNode;
		tmpNode = this->pNext;

		if (this->pNext->pNodePre == this->pNode && this->pNode->pNodePre != nullptr && this->pNext->pNodeRight == nullptr)
			this->pNext = this->pNode->pNodePre;
		else if (this->pNext->pNodeRight == nullptr && this->pNext->pNodePre != nullptr)
			this->pNext = this->pNext->pNodePre;
		else if (this->pNext->pNodeRight != nullptr && this->pNext->pNodeRight != this->pNode)
			this->pNext = Move_to_left(this->pNext->pNodeRight);
		else if (this->pNext->pNodePre != nullptr && this->pNext->pNodeRight == this->pNode)
			this->pNext = this->pNext->pNodePre;

		this->pNode = tmpNode;

		return *this;
	};

private:
	Node<Key, ValueType>* Move_to_left(Node<Key, ValueType>* pNode)
	{
		if (pNode->pNodeLeft != nullptr)
			return Move_to_left(pNode->pNodeLeft);
	};

	Node<Key, ValueType>* pNode = nullptr;
	Node<Key, ValueType>* pNext = nullptr;
};
