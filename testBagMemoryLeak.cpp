#include "Bag.h"
#include <iostream>
#include <cassert>

using namespace std;

void test()
{
	cerr << "test A" << endl;
	Bag b;
	cerr << "test B" << endl;
	b.insert(IntWrapper(10));
	cerr << "test C" << endl;
	b.insert(IntWrapper(20));
	cerr << "test D" << endl;
	Bag b2;
	cerr << "test E" << endl;
	b2.insert(IntWrapper(30));
	cerr << "test F" << endl;
	b2 = b;
	cerr << "test G" << endl;
	b2.insert(IntWrapper(40));
	cerr << "test H" << endl;
}

int main()
{
	test();
	cerr << "DONE" << endl;
}