#ifndef BAG_H
#define BAG_H

#include <string>

#include "IntWrapper.h"      // TODO: remove this line after testing
typedef IntWrapper ItemType; // TODO: replace this line after testing

//typedef unsigned long ItemType;

class Bag
{
public:
	
	Bag();         // Create an empty bag.
	
	Bag(const Bag &cpyBag);		//Copy constructor to handle dynamically allocated member variables
	
	Bag& operator= (const Bag &rhs);	//Assignment constructor to handle dynamically allocated member variables.
	
	~Bag();						//Deallocate memory of dynamic member variables.
	
	bool empty() const;  // Return true if the bag is empty, otherwise false.
	
	int size() const;
	// Return the number of items in the bag.  For example, the size
	// of a bag containing "cumin", "cumin", "cumin", "turmeric" is 4.
	
	int uniqueSize() const;
	// Return the number of distinct items in the bag.  For example,
	// the uniqueSize of a bag containing "cumin", "cumin", "cumin",
	// "turmeric" is 2.
	
	bool insert(const ItemType& value);
	// Insert value into the bag.  Return true if the value was
	// actually inserted.  Return false if the value was not inserted
	// (perhaps because the bag has a fixed capacity and is full).

	int erase(const ItemType& value);
	// Remove one instance of value from the bag if present.
	// Return the number of instances removed, which will be 1 or 0.
	
	int eraseAll(const ItemType& value);
	// Remove all instances of value from the bag if present.
	// Return the number of instances removed.
	
	bool contains(const ItemType& value) const;
	// Return true if the value is in the bag, otherwise false.

	int count(const ItemType& value) const;
	// Return the number of instances of value in the bag.
	
	//void dump() const;

	void swap(Bag& other);
	// Exchange the contents of this bag with the other one.
	
	// Iteration functions (explained below)
	void start();
	void next();
	bool ended() const;
	const ItemType& currentValue() const;
	int currentCount() const;
	
private:
	struct ptrBag
	{
		int numCount;			//numCount contains the number of the ItemType in array m_bag
		ItemType curType;		//ItemType in m_bag
		ptrBag* next;			//Point to next linked ptrBag
		ptrBag* prev;			//Point to previous linked ptrBag
		
						//inline struct constructor initialization
		ptrBag(): numCount(0), next(NULL), prev(NULL) {}	//default initialization
	};
	
	ptrBag*			m_headBag;
	ptrBag*			m_tailBag;
	int				m_size;
	int				m_uniqueSize;
	
	//private function
	void emptyBag();
	int find(const ItemType& value) const;
	
	//member data variables for iterator functions
	ptrBag*			ptr_to_m_bag;			//dummy node
};

void combine(Bag& b1, Bag& b2, Bag& result);
// Given three bags, b1, b2, and result. Contents of b1 and b2 are added to result bag.
// result = result + b1 + b2

void subtract(Bag& b1, Bag& b2, Bag& result);
// Given three bags, b1, b2, and result. Contents of b1 and b2 are subtracted and then add to result bag.
// result = result + (b1 - b2), do no add to result if an item n1 < n2 (n1 is an item in b1, n2 is an item in b2)

#endif			//BAG_H