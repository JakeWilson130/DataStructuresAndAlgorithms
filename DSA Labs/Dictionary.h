/*
File:			DList.h
Author(s):
	Base:		Justin Tackett
				jtackett@fullsail.com
	Student:

Created:		1.17.2021
Last Modified:	2.14.2021
Purpose:		A hash-mapped data structure using key/value pairs and separate chaining
Notes:			Property of Full Sail University
*/

// Header protection
#pragma once

/***********/
/* Defines */
/***********/

/*
How to use:

	When working on a lab, turn that lab's #define from 0 to 1

		Example:	#define LAB_1	1

	When working on an individual unit test, turn that #define from 0 to 1

		Example:	#define DYNARRAY_DEFAULT_CTOR	1

NOTE: If the unit test is not on, that code will not be compiled!
*/


// Main toggle
#define LAB_5	0

// Individual unit test toggles
#define LAB5_PAIR_CTOR				1
#define LAB5_CTOR					1
#define LAB5_DTOR					1
#define LAB5_CLEAR					1
#define LAB5_INSERT_NEW				1
#define LAB5_INSERT_EXISTING		1
#define LAB5_FIND					1
#define LAB5_FIND_NOT_FOUND			1
#define LAB5_REMOVE					1
#define LAB5_REMOVE_NOT_FOUND		1
#define LAB5_ASSIGNMENT_OP			1
#define LAB5_COPY_CTOR				1

/************/
/* Includes */
/************/
#include <list>

template<typename Key, typename Value>
class Dictionary {

	friend class UnitTests_Lab5;	// Giving access to test code

	// The objects stored in the hash-table
	struct Pair {
		Key key;			// The key for insertion/lookup
		Value value;		// The data

		// Constructor
		// In:	_key
		//		_value
		Pair(const Key& _key, const Value& _value) {
			
			key = _key;
			value = _value;

		}

		// For testing
		bool operator==(const Pair& _comp) const {
			return (_comp.key == key &&
				_comp.value == value);
		}
	};

	// Data members
	// NOTE: All values set to -1 for unit test purposes
	std::list<Pair>* mTable = reinterpret_cast<std::list<Pair>*>(-1);							// A dynamic array of lists (these are the buckets)
	size_t mNumBuckets = -1;																	// Number of elements in mTable
	unsigned int(*mHashFunc)(const Key&) = reinterpret_cast<unsigned int(*)(const Key&)>(-1);	// Pointer to the hash function


public:

	// Constructor
	// In:	_numBuckets			The number of elements to allocate
	//		_hashFunc			The hashing function to be used
	Dictionary(size_t _numBuckets, unsigned int (*_hashFunc)(const Key&)) {
		// TODO: Implement this method

		mHashFunc = _hashFunc;
		mNumBuckets = _numBuckets;
		mTable = new std::list<Pair>[_numBuckets];
	}

	// Destructor
	//		Cleans up any dynamically allocated memory
	~Dictionary() {
		// TODO: Implement this method
		
		delete[] mTable;
	}

	// Copy constructor
	//		Used to initialize one object to another
	// In:	_copy				The object to copy from
	Dictionary(const Dictionary& _copy) {
		// TODO: Implement this method
		mTable = new std::list<Pair>[_copy.mNumBuckets];

		for (size_t i = 0; i < _copy.mNumBuckets; i++)
		{
			mTable[i] = _copy.mTable[i];
		}
		mNumBuckets = _copy.mNumBuckets;
		mHashFunc = _copy.mHashFunc;
		
	}

	// Assignment operator
	//		Used to assign one object to another
	// In:	_assign				The object to assign from
	//
	// Return: The invoking object (by reference)
	//		This allows us to daisy-chain
	Dictionary& operator=(const Dictionary& _assign) {
		// TODO: Implement this method
		if (this != &_assign)
		{
			mNumBuckets = _assign.mNumBuckets;
			mHashFunc = _assign.mHashFunc;

			delete[] mTable;
			mTable = new std::list<Pair>[_assign.mNumBuckets];
			for (size_t i = 0; i < mNumBuckets; i++)
			{
				mTable[i] = _assign.mTable[i];
			}
		}
		return *this;
	}

	// Clear
	//		Clears all internal data being stored
	//  NOTE:	Does not delete table or reset hash function
	void Clear() {
		// TODO: Implement this method
		for (size_t i = 0; i < mNumBuckets; i++)
		{
			mTable[i].clear();
		}
		
		
		
	}

	// Insert an item into the table
	// In:	_key		The key to add at	
	//		_value		The value at the key
	//
	// NOTE:	If there is already an item at the provided key, overwrite it.
	void Insert(const Key& _key, const Value& _value) {
		// TODO: Implement this method
		

		//see if key exists
		auto x = mHashFunc(_key);
		auto start = mTable[x].begin();
		auto end = mTable[x].end();
		auto it = start;
		bool empty = false;
		for (it = start; it!= end; it++)
		{

			if (it-> key == _key)
			{
				//update value
				
				it->value = _value;
				empty = true;
			}
			
			
		}
		if (empty != true)
		{
			Pair add = Pair(_key, _value);
			mTable[x].push_back(add);
		}
		
	}

	// Find a value at a specified key
	// In:	_key		The key to search for	
	//
	// Return: A const pointer to the value at the searched key
	// NOTE:		Return a null pointer if key is not present
	const Value* Find(const Key& _key) {
		// TODO: Implement this method
		auto x = mHashFunc(_key);
		auto start = mTable[x].begin();
		auto end = mTable[x].end();
		auto it = start;
		bool empty = false;
		for (it = start; it != end; it++)
		{

			if (it->key == _key)
			{
				//update value

				const Value &_value = it->value;
				return &_value;
				empty = true;
			}


		}
		if (empty != true)
		{
			return nullptr;
		}
		
	}

	// Remove a value at a specified key
	// In:	_key		The key to remove
	//
	// Return: True, if an item was removed
	bool Remove(const Key& _key) {
		// TODO: Implement this method
		auto x = mHashFunc(_key);
		auto start = mTable[x].begin();
		auto end = mTable[x].end();
		auto it = start;
		bool empty = false;
		for (it = start; it != end; it++)
		{

			if (it->key == _key)
			{
				//update value

				it->key = NULL;
				it -> value = NULL;
				empty = true;
			}


		}
			return empty;
	}
	
};