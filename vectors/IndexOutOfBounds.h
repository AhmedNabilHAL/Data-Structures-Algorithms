
#ifndef INDEXOUTBOUNDS_H
#define INDEXOUTBOUNDS_H

#include <exception>
class IndexOutOfBounds : public std::exception{
	virtual const char* what() const throw(){
		return "Index out of bounds!";
	}
};
#endif
