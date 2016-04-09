#include "pair.h"
#include <cassert>
#include <algorithm>

pair::pair(void) : _element(0), _occourrence(0) {

}

pair::pair(const T &elem, size_type occ) : _element(elem), _occourrence(occ) {

}

pair::pair(const T &elem) : _element(elem), _occourrence(1) {

}

pair::~pair(void) {
	_element = 0;
	_occourrence = 0;
}

pair::pair(const pair& other) : _element(other._element), _occourrence(other._occourrence) {

}

pair& pair::operator=(const pair &other) {
	if (this != &other) {
		pair tmp(other);
		
		std::swap(_element, tmp._element);
		std::swap(_occourrence, tmp._occourrence);
	}

	return *this;
}

T pair::&element(void) {
	return _element;
}

const T pair::&element(void) const {
	return _element;
}

size_type pair::occourrence(void) {
	return _occourrence;
}
