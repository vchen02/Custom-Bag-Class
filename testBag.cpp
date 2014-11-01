#include "Bag.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
	Bag b;
	cout << "Bag b was just created!" << endl;
	assert(b.empty());
	assert(b.size() == 0 && b.uniqueSize() == 0);
	
	//assert(! b.contains("")); //only test for string
	assert(b.erase("Ben") == 0);
	b.insert("Ben");
	b.insert("Ben");
	b.insert("Ben");
	b.insert("Eva");
	b.insert("Eva");
	b.insert("Joe");
	b.insert("Peter");
	b.insert("Frank");
	b.insert("Zebra");
	b.insert("Joe");;
	b.insert("Zebra");
	b.insert("Zephyr");
	b.insert("Apple");
	
	int erased = 0;
	
	//Test case for erase function
/*	
	erased += b.erase("Zebra");
	erased += b.erase("Apple");
	erased += b.erase("Ben");
	erased += b.erase("Ben");
	erased += b.erase("Ben");
	erased += b.erase("Joe");
	erased += b.erase("Peter");
	erased += b.erase("Frank");
	erased += b.erase("Joe");
	erased += b.erase("Zebra");
	erased += b.erase("Zephyr");
	erased += b.erase("Test");
*/
	//Test case for eraseAll function

	erased += b.eraseAll("Zebra");
	erased += b.eraseAll("Apple");
	erased += b.eraseAll("Ben");
	erased += b.eraseAll("Joe");
	erased += b.eraseAll("Peter");
	erased += b.eraseAll("Frank");
	erased += b.eraseAll("Zephyr");

	
	b.insert("Victor");
	b.insert("Victor");
	
	b.dump();
	cout << "Total erased was:\t" << erased << endl;
	cout << "The bag has " <<	b.count("Eva") << " Eva, " << b.count("Victor") << " Victor, but ";
	cout << b.count("Justin") << " Justin.\n";
	assert(! b.contains("999"));
	
	Bag c;
	c.insert("Jones");
	cout << endl << "Bag c was just created! And Jones was added." << endl;
	b.swap(c);
	cout << "After swap bag b with c, size of b and c is: " << b.size() << " " << c.size() << endl;
	cout << "Contents of bag c\n\n";
	c.dump();
	cout << "Contents of bag b\n\n";
	b.dump();

	Bag d;
	cout << endl << "Bag d was created and testing..." << endl;
    d.insert("Kobe Byrant");
	d.insert("Plays");
	d.insert("Tennis");
	d.insert("Michael Jordan");
    d.insert("Plays");
	d.insert("Golf");
    for (d.start(); !d.ended(); d.next())
        cout << d.currentValue() << " occurs " << d.currentCount()<< " times." << endl;
	cout << "\n";
	
	cout << "Contents of bag d\n\n";
	d.dump();
	
	Bag* test = new Bag(d);			//Uses Copy Constructor
	d.insert("Copy Contructor Failed");
	assert(d.size() != test->size());
	
	cerr << "\nContents of bag test using copy constructor\n";
	test->dump();
	
	
	
	
	Bag test1 = b;	
	
	//combine(d,c,d);
						//Uses Assignment Constructor
	
	cerr << "\nContents of bag test1 using Assignment operator\n";
	test1.dump();
	//combine(c,d,d);
	//combine(d,d,d);					//check		return twice d's content
	//combine(d,d,b);					//check		return twice d's content
	//assert(d.size() == (2*(test1.size())));
	//combine(b,c,d);
	
	//cout << "\nAfter combine(d,d,d), Contents of bag d\n";
	//d.dump();

	//subtract(c,c,d);		//ok		return empty bag
	//subtract(d,c,d);		//ok		return d content above
	//subtract(c,d,d);		//ok		should return c content
	//subtract(d,d,d);		//ok		return empty bag
	//subtract(d,c,b);		//ok		return d content above
	//cout << "\nAfter subtract(d,c,d), Contents of bag d After subtract()\n";
	//d.dump();
	
	cout << "Passed all tests" << endl;

}