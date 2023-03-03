#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <exception>

template<typename T>
class Queue
{
	int _capacity = 2;
	int _size = 0;
	int _header = 0;
	int _tail = 0;
	T* _array;
public:
	Queue();
	Queue(T*, T*);
	~Queue();
	bool Expand();
	bool Compact();
	void Output();
	bool Empty();
	bool Push(T);
	T Pop();
};

template<typename T>
bool Queue<T>::Expand()
{
	T* tmp;
	this->_capacity = this->_capacity * 2;
	try
	{
		tmp = new T[this->_capacity];
	}
	catch (std::bad_alloc ex)
	{
		printf_s("%s\n", ex.what());
		return false;
	}
	for (int i = this->_header, j = 0; j < this->_size; ++i, ++j)
	{
		tmp[j] = this->_array[i % (this->_capacity / 2)];
	}
	delete[](this->_array);
	this->_array = tmp;
	this->_header = 0;
	this->_tail = _size;
	return true;
}


template<typename T>
bool Queue<T>::Empty()
{
	return _size == 0;
}


template<typename T>
void Queue<T>::Output()
{
	printf_s("          Queue         \n");
	printf_s("------------------------\n");
	for (int i = this->_header, j = 0; j < this->_size; ++i, ++j)
	{
		printf_s("|%22d|\n", _array[(i + this->_capacity) % (this->_capacity)]);
		printf_s("------------------------\n");
	}
}


template<typename T>
Queue<T>::Queue(T* begin, T* end)
{
	while (begin != end)
	{
		this->Push(*begin);
		++begin;
	}
}

template<typename T>
bool Queue<T>::Compact()
{
	T* tmp;
	try
	{
		tmp = new T[this->_capacity / 2];
	}
	catch (std::bad_alloc ex)
	{
		printf_s("%s\n", ex.what());
		return false;
	}
	for (int i = this->_header, j = 0; j < this->_size; ++i, ++j)
	{
		tmp[j] = _array[i % (this->_capacity)];
	}
	delete[](this->_array);
	this->_array = tmp;
	this->_header = 0;
	this->_tail = _size - 1;
	this->_capacity = this->_capacity / 2;
	return true;
}


template<typename T>
bool Queue<T>::Push(T val)
{
	try
	{
		if (this->_array == nullptr)
		{
			this->_array = new T[this->_capacity];
		}
		if (this->_capacity == this->_size)
		{
			this->Expand();
		}
	}
	catch (std::bad_alloc ex)
	{
		printf_s(ex.what());
		return false;
	}

	this->_array[this->_tail] = val;
	this->_tail = (this->_tail + 1) % this->_capacity;
	++this->_size;
	return true;
}


template<typename T>
T Queue<T>::Pop()
{
	if (this->Empty()) throw "Empty";
	T tmp = this->_array[this->_header];
	this->_header = (this->_header + 1) % this->_capacity;
	try
	{
		if (this->_size == this->_capacity / 4) this->Compact();
		--this->_size;
	}
	catch (std::bad_alloc ex)
	{
		printf_s("%s\n", ex.what());
	}
	return tmp;
}


template<typename T>
Queue<T>::Queue()
{
	_capacity = 2;
	_size = 0;
	_header = 0;
	_tail = 0;
	_array = nullptr;
}


template<typename T>
Queue<T>::~Queue()
{
	delete[](_array);
}






int main()
{
	srand(time(NULL));
	Queue<int> a;
	int n = 100;
	for (int i = 0; i < n; i++)
	{
		a.Push(rand() % n);
	}
	a.Output();
	for (int i = 0; i < n / 2; i++)
	{
		printf_s("%d\n", a.Pop());
	}
	a.Output();
	for (int i = 0; i < n / 2; i++)
	{
		printf_s("%d\n", a.Pop());
	}
	a.Output();
	a.Push(111);
	a.Output();
	return 0;
}