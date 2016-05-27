#pragma once

template<class T>
struct _List_Node
{
	_List_Node<T>* _prev;
	_List_Node<T>* _next;
	T _data;
	_List_Node(const T& x)
		:_next(NULL)
		, _prev(NULL)
		, _data(x)
	{}
};

template<class T>
class _List_Iterator
{
	typedef _List_Node<T> LinkNode;
	typedef LinkNode* LinkType;
	typedef _List_Iterator<T> Iterator;
public:
	_List_Iterator(const LinkType node)
		:_node(node)
	{}
	_List_Iterator()
	{}
	_List_Iterator(const Iterator& it)
		:_node(it._node)
	{}
public:
	Iterator operator++()
	{
		_node = _node->_next;
		return *this;
	}
	Iterator operator++(int)
	{
		Iterator tmp = *this;
		_node = _node->_next;
		return tmp;
	}
	Iterator operator--()
	{
		_node = _node->_prev;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator tmp = *this;
		_node = _node->_prev;
		return tmp;
	}
	T& operator*()
	{
		return _node->_data;
	}
	bool operator==(const Iterator& it)
	{
		return _node == it._node;
	}
	bool operator!=(const Iterator& it)
	{
		return _node != it._node;
	}
public:
	LinkType _node;
};

template<class T>
class _List_Iterator_Reverse
{
	typedef _List_Node<T> LinkNode;
	typedef LinkNode* LinkType;
	typedef _List_Iterator_Reverse<T> Reverse_Iterator;
public:
	_List_Iterator_Reverse(const LinkType node)
		:_node(node)
	{}
	_List_Iterator_Reverse()
	{}
	_List_Iterator_Reverse(const Reverse_Iterator& it)
		:_node(it._node)
	{}
public:
	Reverse_Iterator operator++()
	{
		_node = _node->_prev;
		return *this;
	}
	Reverse_Iterator operator++(int)
	{
		Iterator tmp = *this;
		_node = _node->_prev;
		return tmp;
	}
	Reverse_Iterator operator--()
	{
		_node = _node->_next;
		return *this;
	}
	Reverse_Iterator operator--(int)
	{
		Iterator tmp = *this;
		_node = _node->_next;
		return tmp;
	}
	T& operator*()
	{
		return _node->_data;
	}
	bool operator==(const Reverse_Iterator& it)
	{
		return _node == it._node;
	}
	bool operator!=(const Reverse_Iterator& it)
	{
		return _node != it._node;
	}
public:
	LinkType _node;
};

template<class T>
class List
{
	typedef _List_Node<T> LinkNode;
	typedef LinkNode* LinkType;
public:
	typedef _List_Iterator<T> Iterator;
	typedef _List_Iterator_Reverse<T> Reverse_Iterator;
public:
	List(const T x = T())
		:_head(new LinkNode(x))
	{
		_head->_next = _head;
		_head->_prev = _head;
	}
	void Insert(const Iterator pos,const T& x)
	{
		LinkType node = new LinkNode(x);
		LinkType cur = pos._node;
		LinkType prev = cur->_prev;
		prev->_next = node;
		node->_prev = prev;
		node->_next = cur;
		cur->_prev = node;
	}
	void Erase(const Iterator pos)
	{
		LinkType cur = pos._node;
		if (cur == _head)
			return;
		LinkType prev = cur->_prev;
		LinkType next = cur->_next;
		prev->_next = next;
		next->_prev = prev;
		delete cur;
	}
	void PushBack(const T& x)
	{
		Insert(End(),x);
	}
	void PushFront(const T& x)
	{
		Insert(Begin(),x);
	}
	void PopBack()
	{
		Erase(--End());
	}
	void PopFront()
	{
		Erase(Begin());
	}
	void Reverse()
	{
		LinkType left = Begin()._node;
		LinkType right = (--End())._node;

		while (left < right)
		{
			swap(left->_data, right->_data);
			left = left->_next;
			right = right->_prev;
		}
	}
	Iterator Begin()
	{
		return _head->_next;
	}
	Iterator End()
	{
		return _head;
	}
	Reverse_Iterator rBegin()
	{
		return _head;
	}
	Reverse_Iterator rEnd()
	{
		return _head->_next;
	}
protected:
	LinkType _head;
};

void TestList()
{
	List<int> l;

	l.PushBack(1);
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);

	l.PushFront(0);

	l.PopBack();
	l.PopFront();

	l.Reverse();

	List<int>::Iterator it = l.Begin();
	while (it != l.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	List<int>::Reverse_Iterator ret = l.rEnd();
	while (ret != l.rBegin())
	{
		cout << *ret << " ";
		--ret;
	}
	cout << endl;
}