#include "heap.h"
void test()
{
	Heap<int> h1;
	h1.Push(1);
	h1.Push(2);
	h1.Push(3);
	h1.Push(25);
	h1.Push(4);

	h1.Pop();
	h1.Pop();
	h1.Pop();
	h1.Pop();
	h1.Print();
}

int main()
{
	test();
	return 0;
}