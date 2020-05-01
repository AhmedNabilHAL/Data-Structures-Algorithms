
#ifndef FCIVECTOR_H
#define FCIVECTOR_H
#include <iostream>
#include <string>
#include <climits>
#include "IndexOutOfBounds.h"
#define ll long long


template<typename T>
class FCIvector{
	T* elements;
	ll numberOfElements;
	ll capacity;
public:
	// default constructor
	FCIvector();

	// constructor intializes an empty vector with the given size
	FCIvector(ll size) throw(std::bad_alloc);

	// A copy constructor
	FCIvector(const FCIvector& vect) throw(std::bad_alloc);

	// overloading = operator
	void operator=(const FCIvector& vect) throw(std::bad_alloc);

	// returns the size of the vector
	ll size() const;

	// returns the size of the vector including unused space
	ll capacitySize() const;

	// returns true if empty else false
	bool empty() const;

	// returns a reference of the element at index
	T& operator[](int index) const throw(IndexOutOfBounds);

	// returns a pointer to the begining of the vector
	T* begin() const;

	// returns a reference to the first element
	T& front() const throw(IndexOutOfBounds);

	// returns a pointer to last element + 1
	T* end() const;

	// returns a reference to the last element
	T& back() const throw(IndexOutOfBounds);

	// expands the capacity if capacity < MAX long long no. / 2 -> capacity *= 2
	//											 else if capacity < Max long long -> capacity++
	// return 1 if capacity was expanded else 0
	bool expandCapacity();

	// inserts val into the given position if position < size with max no. of elements of MAX LONG LONG
	void insert(T* position, const T val) throw(IndexOutOfBounds);

	// inserts val at the end of position with max no. of elements of MAX LONG LONG
	void push_back(const T val) throw(std::bad_alloc);

	// decreases size by 1 and removes the last element if size > 0
	void pop_back();

	// clears the vector
	void clear();

	// erases the element at the given position if position < size
	void erase(T* position) throw(IndexOutOfBounds);

	// outputs the contents of the vector
	template<typename T1>
	friend std::ostream& operator<<(std::ostream& out, const FCIvector<T1>& vect);
	void print_vect();


	// Destructor
	~FCIvector();
};



template<typename T>
std::ostream& operator<<(std::ostream& out, const FCIvector<T>& vect);

#endif
