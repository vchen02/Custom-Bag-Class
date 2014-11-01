/*
#include "Bag.h"

void thisFunctionWillNeverBeCalled()
{
	Bag b;
	Bag b2(b);
	b2 = b;
	bool (Bag::*p1)() const          = &Bag::empty;
	int  (Bag::*p2)() const          = &Bag::size;
	int  (Bag::*p3)() const          = &Bag::uniqueSize;
	bool (Bag::*p4)(const ItemType&) = &Bag::insert;
	int  (Bag::*p5)(const ItemType&) = &Bag::erase;
	int  (Bag::*p6)(const ItemType&) = &Bag::eraseAll;
	bool (Bag::*p7)(const ItemType&) const = &Bag::contains;
	int  (Bag::*p8)(const ItemType&) const = &Bag::count;
	void (Bag::*p9)(Bag&)            = &Bag::swap;
	void (Bag::*p10)()               = &Bag::start;
	void (Bag::*p11)()               = &Bag::next;
	bool (Bag::*p12)() const         = &Bag::ended;
	const ItemType& (Bag::*p13)() const = &Bag::currentValue;
	int  (Bag::*p14)() const         = &Bag::currentCount;
	
	void (*p15)(Bag&, Bag&, Bag&) = combine;
	void (*p16)(Bag&, Bag&, Bag&) = subtract;
}

int main()
{
}

#include "Bag.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Bag sb;
	assert(sb.insert("cumin"));
	assert(sb.insert("turmeric"));
	assert(sb.insert("cumin"));
	assert(sb.insert("coriander"));
	assert(sb.insert("cumin"));
	assert(sb.insert("turmeric"));
	assert(sb.size() == 6  &&  sb.uniqueSize() == 3);
	assert(sb.count("turmeric") == 2);
	assert(sb.count("cumin") == 3);
	assert(sb.count("coriander") == 1);
	assert(sb.count("cardamom") == 0);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}
*/


 #include "Bag.h"
 #include <iostream>
 #include <cassert>
 using namespace std;
 
 void test()
 {
 Bag ulb;
 assert(ulb.insert(20));
 assert(ulb.insert(10));
 assert(ulb.insert(20));
 assert(ulb.insert(30));
 assert(ulb.insert(20));
 assert(ulb.insert(10));
 assert(ulb.size() == 6  &&  ulb.uniqueSize() == 3);
 assert(ulb.count(10) == 2);
 assert(ulb.count(20) == 3);
 assert(ulb.count(30) == 1);
 assert(ulb.count(40) == 0);
 }
 
 int main()
 {
 test();
 cout << "Passed all tests" << endl;
 }