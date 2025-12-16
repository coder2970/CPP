#pragma once
#include <iostream>
#include <cstdlib>
#include <cassert>
template <class T>
class Heap /*建小堆*/
{
private:
	T *_arr;
	int _size;
	int _capacity;

	void AdjustUp(int child)
	{
		int parent = (child - 1) / 2;
		while (child > 0)
		{
			if (_arr[parent] > _arr[child])
			{
				std::swap(_arr[parent], _arr[child]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
			{
				break;
			}
		}
	}

	void AdjustDown(int parent)
	{
		int child = parent * 2 + 1;
		while (child < _size)
		{
			if (child + 1 < _size && _arr[child] > _arr[child + 1])
			{
				child = child + 1;
			}
			if (_arr[parent] > _arr[child])
			{
				std::swap(_arr[parent], _arr[child]);
				parent = child;
				child = child * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}

public:
	Heap() : _arr(nullptr), _size(0), _capacity(0)
	{
	}

	~Heap()
	{
		delete[] _arr;
		_size = _capacity = 0;
	}

	Heap(const Heap &hp)
	{
		_size = hp._size;
		_capacity = hp._capacity;

		if (hp._arr)
		{
			_arr = new T[_capacity];
			for (int i = 0; i < _size; i++)
			{
				_arr[i] = hp._arr[i];
			}
		}
		else
		{
			_arr = nullptr;
		}
	}

	Heap &operator=(const Heap &hp)
	{
		if (this != &hp)
		{
			delete[] _arr;
			_size = hp._size;
			_capacity = hp._capacity;
			if (hp._arr)
			{
				_arr = new T[_capacity];
				for (int i = 0; i < _size; i++)
				{
					_arr[i] = hp._arr[i];
				}
			}
			else
			{
				_arr = nullptr;
			}
		}
		return *this;
	}

	void reserve(int n)
	{
		if (n > _capacity)
		{
			T *newarr = new T[n];
			for (int i = 0; i < _size; i++)
			{
				newarr[i] = _arr[i];
			}
			delete[] _arr;

			_arr = newarr;
			_capacity = n;
		}
	}

	void Push(const T &x)
	{
		if (_size >= _capacity)
		{
			reserve(_capacity == 0 ? 4 : 2 * _capacity);
		}
		_arr[_size++] = x;
		// 向上调整
		AdjustUp(_size - 1);
	}
	void Pop()
	{
		assert(_arr || _size == 0);
		std::swap(_arr[0], _arr[_size - 1]);
		_size--;
		AdjustDown(0);
	}

	void Print()
	{
		for (int i = 0; i < _size; i++)
		{
			std::cout << _arr[i] << std::endl;
		}
	}
};
