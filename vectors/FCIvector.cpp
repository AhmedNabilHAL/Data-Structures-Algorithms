#include "FCIvector.h"

template<typename T>
FCIvector<T>::FCIvector(){
	this->numberOfElements = 0;
	this->capacity = 0;
	this->elements = NULL;
}

template<typename T>
FCIvector<T>::FCIvector(ll size) throw(std::bad_alloc){
	this->numberOfElements = 0;
	this->capacity = size;
	this->elements = new T[this->capacity];

}

template<typename T>
FCIvector<T>::FCIvector(const FCIvector& vect) throw(std::bad_alloc){
	delete[] this->elements;
	this->elements = NULL;
	this->numberOfElements = vect.size();
	this->capacity = vect.capacitySize();
	if (!this->capacity) this->elements = new T[this->capacity];
	for (int i = 0; i < this->numberOfElements; ++i){
		this->elements[i] = vect[i];
	}
}

template<typename T>
void FCIvector<T>::operator=(const FCIvector& vect) throw(std::bad_alloc){
	delete[] this->elements;
	this->elements = NULL;
	this->numberOfElements = vect.size();
	this->capacity = vect.capacitySize();
	if (this->capacity) this->elements = new T[this->capacity];
	for (int i = 0; i < this->numberOfElements; ++i){
		this->elements[i] = vect[i];
	}
}

template<typename T>
ll FCIvector<T>::size() const{
	return this->numberOfElements;
}

template<typename T>
ll FCIvector<T>::capacitySize() const{
	return this->capacity;
}

template<typename T>
bool FCIvector<T>::empty() const{
	return !this->numberOfElements;
}

template<typename T>
T& FCIvector<T>::operator[](int index) const throw(IndexOutOfBounds){
	if (index >= this->numberOfElements) { IndexOutOfBounds iofb; throw(iofb); }
	return this->elements[index];
}

template<typename T>
T* FCIvector<T>::begin() const{
	return this->elements;
}

template <typename T>
T& FCIvector<T>::front() const throw(IndexOutOfBounds){
	if (!this->numberOfElements) { IndexOutOfBounds iofb; throw(iofb); }
	return this->elements[0];
}

template <typename T>
T* FCIvector<T>::end() const{
	return this->elements + this->numberOfElements;
}

template <typename T>
T& FCIvector<T>::back() const throw(IndexOutOfBounds){
	if (!this->numberOfElements) { IndexOutOfBounds iofb; throw(iofb); }
	return this->elements[this->numberOfElements - 1];
}

template <typename T>
bool FCIvector<T>::expandCapacity(){
	if (!this->capacity) this->capacity = 1;
	if (this->capacity < LLONG_MAX / 2) this->capacity *= 2;
	else if (this->capacity < LLONG_MAX) this->capacity++;
	else return 0;
	FCIvector<T> temp(this->capacity);
	for (int i = 0; i < this->numberOfElements; ++i) temp.push_back(this->elements[i]);
	*this = temp;
	return 1;
}

template <typename T>
void FCIvector<T>::insert(T* position, const T val) throw(IndexOutOfBounds){

	if (position >= this->end() || position < this->begin() || position == NULL) { IndexOutOfBounds iofb; throw(iofb); }
	ll idx = position - this->begin();
	if (this->numberOfElements >= this->capacity) {
		if (!expandCapacity()) return;
		position = this->begin() + idx;
	}
	this->numberOfElements++;
	for (T* it = this->end() - 1; it > position; --it) *it = *(it - 1);
	*position = val;
}


template <typename T>
void FCIvector<T>::push_back(const T val) throw(std::bad_alloc){
	if (this->numberOfElements >= this->capacity) if (!expandCapacity()) return;
	this->elements[numberOfElements++] = val;
}

template <typename T>
void FCIvector<T>::pop_back(){
	if (this->numberOfElements <= 0) return;
	this->elements[numberOfElements--] = -101;
}

template <typename T>
void FCIvector<T>::clear(){
	this->numberOfElements = 0;
}

template <typename T>
void FCIvector<T>::erase(T* position) throw(IndexOutOfBounds){
	if (position >= this->end() || position < this->begin() || position == NULL) { IndexOutOfBounds iofb; throw(iofb); }

	for (T* it = position; it < this->end() - 1; ++it) *it = *(it + 1);
	this->numberOfElements--;
}



template<typename T>
void FCIvector<T>::print_vect(){
	for (int i = 0; i < this->numberOfElements; ++i){
		std::cout << this->elements[i] << '\t';
	}
}


template<typename T>
std::ostream& operator<<(std::ostream& out, const FCIvector<T>& vect){
	for (int i = 0; i < vect.numberOfElements; ++i){
		out << vect.elements[i] << '\t';
	}

	return out;
}

template<typename T>
FCIvector<T>::~FCIvector(){
	delete[] this->elements;
	this->elements = NULL;
}
