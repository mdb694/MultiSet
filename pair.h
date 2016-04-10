#ifndef PAIR_H
#define PAIR_H

#include <algorithm>

template<typename T> 
class pair {
	public:
	typedef unsigned int size_type; ///< tipo che rappresenta il numero di occorrenze di un elemento

	private:
	T _element; ///< elemento della coppia
	size_type _occourrence;	///<numero di occorrenze dell'elemento'

	public:

	/** Costruttore di default **/ 
 pair() : _element(0), _occourrence(0) {

	}
	
	/** Costruttore secondario 
			Crea una coppia con un numero specificato di elementi
			@param elem elemento della coppia
			@param occ numero di occorrenze dell'elemento 
	**/
	pair(const T &elem, size_type occ) : _element(elem), _occourrence(occ) {

	}

	/** Costruttore secondario
			Crea una coppia con una sola occorrenza dell'elemento
			@param elem elemento della coppia
	**/
	pair(const T &elem) : _element(elem), _occourrence(1) {

	}

	/** Distruttore **/
	~pair() {
		_element = 0;
		_occourrence = 0;
	}

	/** Copy constructor 
			@param other pair da copiare
	**/
	pair(const pair& other) : _element(other._element), _occourrence(other._occourrence) {

	}

	/** Operatore di assegnamento
			@param other pair da cui effettuare la copiare
	**/
	pair& operator=(const pair &other) {
		if (this != &other) {
			pair tmp(other);
		
			std::swap(_element, tmp._element);
			std::swap(_occourrence, tmp._occourrence);
		}

		return *this;
	}

	/** Metodo getter dell'elemento
	**/
	T &element() {
		return _element;
	}

	/** Metode getter costante dell'elemento
	**/
	const T &element() const {
		return _element;
	}

	/** Metodo getter delle occorrenze
	**/
	size_type occourrence() {
		return _occourrence;
	}

	/** Matodo setter delle occorrenze
	**/
	void set_occourrence(size_type value) {
		_occourrence = value;
	}
}; //fine classe
#endif 
