#include "Bag.h"

#include <iostream>
using namespace std;

Bag::Bag()
: m_headBag(NULL), m_tailBag(NULL), m_size(0), m_uniqueSize(0), ptr_to_m_bag(NULL)	
{
}

Bag::Bag(const Bag &cpyBag)
{	
	ptrBag* temp		= cpyBag.m_headBag;
	int count = 0;
	
	while (temp != NULL)		//Traversal loop to copy and assign each member variable
	{
		ptrBag* newItem	= new ptrBag;
		
		newItem->numCount	= temp->numCount;		//copy numCount and ItemType
		newItem->curType	= temp->curType;
		
		if (count == 0)
			m_headBag		= newItem;
		
		else
		{	
			ptr_to_m_bag->next	= newItem;		//point previous item to new item
			newItem->prev		= ptr_to_m_bag;	//point new item to previous item
		}
		
		if (temp->next == NULL)
			m_tailBag	= newItem;
		
		count ++;
		ptr_to_m_bag	= newItem;				//hold address of previous added item
		temp			= temp->next;
	}
	m_size				= cpyBag.m_size;		//copy total size
	m_uniqueSize		= cpyBag.m_uniqueSize;	//copy unique size
}

Bag& Bag::operator= (const Bag &rhs)
{
	if (this != &rhs)			//Aliasing, ie. b1 = b1, return pointer to this address
	{							//deallocate dynamic memory of current list items
		ptrBag* temp	= m_headBag;
		while (temp != NULL)			//Traversal loop to find value in bag
		{
			ptrBag* next1	= temp->next;
			delete temp;
			temp			= NULL;
			temp			= next1;
		}
	
		temp				= rhs.m_headBag;
		int count = 0;
		
		while (temp != NULL)		//Traversal loop to copy and assign each member variable
		{
			ptrBag* newItem	= new ptrBag;
			
			newItem->numCount	= temp->numCount;
			newItem->curType	= temp->curType;
			
			if (count == 0)
				m_headBag		= newItem;
			
			else
			{	
				ptr_to_m_bag->next	= newItem;		//point previous item to new item
				newItem->prev		= ptr_to_m_bag;	//point new item to previous item
			}
			
			if (temp->next == NULL)
				m_tailBag	= newItem;
			
			count ++;
			ptr_to_m_bag	= newItem;			//hold address of previous added item
			temp			= temp->next;
		}
		m_size				= rhs.m_size;		//copy total size
		m_uniqueSize		= rhs.m_uniqueSize;	//copy unique size
	}	
	return (*this);
}

Bag::~Bag() 
{
	emptyBag();				//deallocate dynamic memory of current list items
}

bool Bag::empty() const
{
	return (m_headBag == NULL && m_tailBag == NULL);
}

int Bag::size() const
{
	return m_size;
}

int Bag::uniqueSize() const
{
	return m_uniqueSize;
}

bool Bag::insert(const ItemType& value)
{
	int slotNum	= find(value);						//find slot position of value in bag, 
													//refer to return values description in find() implementation
	if (slotNum < 0)								//something is wrong
		return false;
	
	ptrBag* target	= m_headBag;
	
	if (contains(value))							//slotNum is at the position of value,  0-n
	{												//Find slot position and increment numCount and m_size by 1
		while (target != NULL)
		{
			if (slotNum-- == 0) break;				
			target	= target->next;
		}
		target->numCount ++;
		m_size ++;
		return true;
	}
	
	else											//slotNum is at position above target value, 1-n
	{
		ptrBag* newItem		= new ptrBag;
		newItem->curType	= value;
		newItem->numCount ++;
		m_size ++;
		m_uniqueSize ++;
		
		if (slotNum == 0)							//Special Case slotNum = 0
		{											//Insert At beginning of a List
			newItem->prev		= NULL;
			if (m_headBag == NULL)					//Insert very first item to list
			{
				newItem->next		= NULL;
				m_headBag			= newItem;
				m_tailBag			= newItem;
				return true;
			}
			newItem->next		= m_headBag;
			m_headBag			= newItem;
			return true;
		}
		
		while (target != NULL)						//Traverse to slot position 
		{
			if (target->next == NULL) break;
			if (--slotNum == 0) break;
			target	= target->next;
		}
		
		if (target == m_tailBag)					//Insert At end of a list
		{
			newItem->next	= NULL;
			if (target == m_headBag)				//Only 1 item in list
			{
				newItem->prev = m_headBag;
				target->next  = newItem;
				m_tailBag	  = newItem;
				return true;
			}	
			newItem->prev	= m_tailBag;
			m_tailBag		= newItem;
			target->next	= newItem;
			return true;
		}
													//Insert At middle of a list
		newItem->prev		= target;
		newItem->next		= target->next;
		target->next->prev	= newItem;
		target->next		= newItem;
		return true;
	}
}

int Bag::erase(const ItemType& value)
{
	if (!contains(value))			//value is not in bag		
		return 0;
	
	int slotNum		= find(value);
	ptrBag* target	= m_headBag;
	
	while (target != NULL)			//Traverse to slotNum
	{
		if (slotNum-- == 0) break;				
		target	= target->next;
	}
	
	if (target->numCount > 1)		//more than one value in bag
	{
		target-> numCount --;		//decrement numCount and m_size by 1
		m_size --;
		return 1;
	}
	
	else 
	{	m_size --;					//decrement m_size and m_uniqueSize by 1
		m_uniqueSize --;			//
									//If value to be erased is at the beginning of the list
		if (target == m_headBag)
		{
			if (target == m_tailBag)//only one item in bag
			{
				delete target;
				m_headBag	= NULL;
				m_tailBag	= NULL;
				return 1;
			}
			m_headBag			= target->next;
			target->next->prev	= NULL;
			delete target;
			return 1;
		}
									//If value to be erased is at the end of the list
		if (target == m_tailBag)
		{
			m_tailBag			= target->prev;
			target->prev->next	= NULL;
			delete target;
			return 1;
		}
									//If value to be erased is at the middle of the list
		target->next->prev	= target->prev;
		target->prev->next	= target->next;
		delete target;
		return 1;
	}
}

int Bag::eraseAll(const ItemType& value)
{
	int erased	= 0;
	if (contains(value))
	{
		int slotNum	= find(value);
		ptrBag* target	= m_headBag;
		
		while (target != NULL)		//traverse to slotNum
		{
			if (slotNum-- == 0) break;				
			target	= target->next;
		}
		
		erased				= target->numCount;		//record how many to be erased
		m_size	   		   -= erased;				//decrease m_size by erased
		m_uniqueSize --;							//decrement m_uniqueSize by 1
									//If value to be erased is at the beginning of the list
		if (target == m_headBag)
		{
			if (target == m_tailBag)//only one item in bag
			{	
				delete target;
				m_headBag	= NULL;
				m_tailBag	= NULL;
				return erased;
			}
			m_headBag			= target->next;
			target->next->prev	= NULL;
			delete target;
			return erased;
		}
									//If value to be erased is at the end of the list
		if (target == m_tailBag)
		{
			m_tailBag			= target->prev;
			target->prev->next	= NULL;
			delete target;
			return erased;
		}
									//If value to be erased is at the middle of the list
		target->next->prev	= target->prev;
		target->prev->next	= target->next;
		delete target;
		return erased;
	}
	return erased;
}

bool Bag::contains(const ItemType& value) const
{
	ptrBag* check	= m_headBag;
	
	while (check != NULL)			//Traversal loop to find value in bag
	{
		if(check->curType == value)	
			return true;
		check	= check->next;
	}
	return false;
}

int Bag::count(const ItemType& value) const
{
	ptrBag* check	= m_headBag;
	
	while (check != NULL)			//Traversal loop to find value in bag
	{
		if(check->curType == value)
			return check->numCount; //return numCount of value in bag
		check	= check->next;
	}
	return 0;
}

/*
void Bag::dump() const
{
	if (m_headBag == NULL)
		return;
	ptrBag* temp	= m_headBag;
	while (temp != NULL)
	{
		cerr << temp->curType << "\t" << temp->numCount << endl;
		temp = temp->next;
	}
	cerr << "m_size:\t" << m_size << "\t" << "m_uniqueSize:\t" << m_uniqueSize << endl;
	cerr << "m_headBag:\t" << m_headBag->curType << "\t" << "m_tailBag:\t" << m_tailBag->curType << endl;
}
*/

void Bag::swap(Bag& other)
{
	ptrBag* tempH	= m_headBag;			//swap m_headBag 
	m_headBag		= other.m_headBag;
	other.m_headBag	= tempH;
 
	ptrBag* tempT	= m_tailBag;			//swap m_tailBag
	m_tailBag		= other.m_tailBag;
	other.m_tailBag	= tempT;
	
	int temp;
	
	temp			= m_size;				//swap m_size
	m_size			= other.m_size;
	other.m_size	= temp;
 
	temp				= m_uniqueSize;		//swap m_uniqueSize
	m_uniqueSize		= other.m_uniqueSize;
	other.m_uniqueSize	= temp;
}

void Bag::start()
{
	ptr_to_m_bag		= m_headBag;		//assign a pointer to m_headBag
}

void Bag::next()
{	
	if (ptr_to_m_bag	== NULL)			//At the end of bag's list
		return;
	ptr_to_m_bag		= ptr_to_m_bag->next;	//goto next item in bag
}

bool Bag::ended() const
{
	if (ptr_to_m_bag == NULL)				//At the end of bag's list
		return true;
	return false;
}

const ItemType& Bag::currentValue() const
{
	return ptr_to_m_bag->curType;
}

int Bag::currentCount() const
{
	return ptr_to_m_bag->numCount;
}

void Bag::emptyBag()					//deallocate dynamic memory of current list items
{
	if (m_headBag == NULL && m_tailBag == NULL)
		return;
	ptrBag* temp = m_headBag;
	ptrBag* nextOne;
	
	while (temp != NULL)
	{
		nextOne	= temp->next;
		delete temp;
		temp = NULL;
		temp = nextOne;
	}
	m_size			= 0;
	m_uniqueSize	= 0;
}

int Bag::find(const ItemType& value) const	//return the slot number, 
{										// 1).Value is in bag, list starts at slot position 0 up to n
	int slotNum		= 0;				// 2).Value is not in bag, list starts at slot position 1 up to n, return 0 if it belongs to front of the list
	if (m_headBag == NULL)				
		return slotNum;					//return slotNum = 0 for very first item to list
	else
	{	
		ptrBag* check = m_headBag;
		while(check != NULL)			//Traverse to each item in bag 
		{
			if(check->curType == value)						//Found value in bag
				return slotNum;
			
			slotNum ++;
			
			if (check == m_tailBag)							//at the end of the list and did not find value in list
			{	
				if (check == m_headBag)						//There is only one item in list	
				{
					if (value < check->curType)				
						return slotNum-1;		//return 0
					else if (value > check->curType)
						return slotNum;			//return 1
				}
				
				while (check != NULL)						//traverse backwards to find current slotNum
				{
					if (check->prev == NULL && value < check->curType)					//slotNum is at the beginning of the list
						return slotNum-1;
					else if (check->next == NULL && value > check->curType)				//slotNum is at the end of the list
						return slotNum;
					else if (value < check->curType && value > check->prev->curType)	//slotNum is at the middle of the list
						return slotNum-1;
					slotNum--;
					check	= check->prev;
				}
			}
			check 	= check->next;
	 	}
		return slotNum;
	}
}

void combine(Bag& b1, Bag& b2, Bag& result)
{	
	Bag* newResult	= new Bag;
	bool aliasing	= false;
	
	Bag* bag;
	for (int k = 0; k < 2; k++)				//This will loop twice
	{
		if (&b1 == &b2 || (&b1 == &result &&  &b2 ==&result))
		{
			aliasing	= true;
			for (b1.start(); !b1.ended(); b1.next())
			{
				int num			= b1.currentCount();
				for (int i = 0; i < num*2; i++)		//loop once for each item in bag
					newResult->insert(b1.currentValue());
			}
			break;
		}
		if (!aliasing)	
		{	
			switch (k)
			{
				case 0:	bag	= &b1;		break;	//first loop
				case 1:	bag	= &b2;		break;	//second loop
			}
	
			for (bag->start(); !bag->ended(); bag->next())
			{
				for (int i = 0; i < bag->currentCount(); i++)	//loop once for each item in bag
					newResult->insert(bag->currentValue());		//store each item to result bag
			}
		}
	}	
	result	= *newResult;	//Assign result bag to newResult bag
	delete newResult;
	newResult	= NULL;
}

void subtract(Bag& b1, Bag& b2, Bag& result)
{
	Bag* newResult	= new Bag;			//empty Bag
	bool aliasing	= (&b1 == &b2 || (&b1 == &result &&  &b2 ==&result));
	if (!aliasing)
	{
		for (b1.start(); !b1.ended(); b1.next())	//Traverse b1 bag list
		{
			if (b2.contains(b1.currentValue()))		//if b2 also contains this value of b1
			{ 
				int add	= b1.currentCount() - b2.count(b1.currentValue());
				if (add > 0)						//add to result back only if add > 0
				{
					for (int i = 0; i < add; i++)
						newResult->insert(b1.currentValue());
				}
			}
			else								//b2 does not have this item, so add to result bag
			{
				for (int k = 0; k < b1.currentCount(); k++)
					newResult->insert(b1.currentValue());
			}
		}
	}
	result.swap(*newResult);		//Assign result bag to newResult bag
	delete newResult;
	newResult	= NULL;	
}