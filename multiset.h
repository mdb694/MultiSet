#ifndef MULTISET_H
#define MULTISET_H

#include <stdexcept>
#include <algorithm>
#include <cassert>
#include "pair.h"

/** Classe che implementa un mutliset. I dati base sono coppie 
<elemento, occorrenze>. La classe memorizza tali coppie attraverso
una lista. La classe richiede la specifica del tipo di elemento T e
del funtore funct per la comparazione di due elementi.
*/
template <typename T, typename funct>
class multiset {

	/**Struct del nodo elementare della lista di elementi.
	**/
	struct node {
		pair<T> data; ///< dato elementare di tipo T
		node *next; ///< puntatore al prossimo elemento

		/**Costruttore del nodo dato un elemento 
				@param elem elemento
		**/
		node(const T &elem) : data(elem), next(0) {

		}

		/**Costruttore del nodo dato un elemento ripetuto più volte
				@param elem elemento
				@param occ occorrenze dell'elemento
		**/
		node(const T &elem, size_type occ) : data(elem, occ), next(0) {

		}

	/**Costruttore del nodo dato un elemento 
				@param elem elemento
		**/
		node(const T &elem, node *n) : data(elem), next(n) {

		}

		/**Costruttore del nodo dato un elemento ripetuto più volte
				@param elem elemento
				@param occ occorrenze dell'elemento
		**/
		node(const T &elem, size_type occ, node *n) : data(elem, occ), next(n) {

		}

		/**Costruttore di default
		**/
		node () : next(0) {

		}

		/**Distruttore
		**/
		~node() {

		}

		/**Copy constructor
				@param other nodo da copiare
		**/
		node(const node &other) : data(other.data), next(other.next) {

		}

		/**Operatore di assegnamento
				@param other nodo da assegnare
		**/
		node&operator=(const node &other) {
			if(this!=&other) {
				data = other.data;
				next = other.next;
			}
			return *this;
		}
	}; //fine struct node

	node *_head; ///< testa del multiset
	int _size; ///< numero di elementi base(numero di nodi)

	/**Metodo ausiliario che ritorna il puntatore all'elemento
			passato come argomento
		@param elem elemento da cercare
		@return il puntatore al nodo se l'elemento esiste, 0 altrimenti
	**/
	node *find_helper(const T &elem) const {
		node *curr = _head;
		funct comp;

		while(curr!=0) {
			if(comp(curr->data.element(), elem))
				return curr;
			curr = curr->next;
		}
		return 0;
	}

	public:

	/**Costruttore di default
	**/
	multiset() : _head(0), _size(0) {

	}

	/**Distruttore
	**/
	~multiset() {
		clear();	
	}

	/** Metodo che svuota il multiset
	**/
	void clear() {
		node *temp = _head;
		node *temp2 = 0;

		while(temp!=0) {
			temp2 = temp->next;
			delete temp;
			temp = temp2;
		}
	}

	/**Copy constructor
			@param other il multiset da copiare
	**/
	multiset(const multiset& other) : _head(0), _size(0) {
		node *temp = other._head;

		try {
			while(temp!=0) {
				add(temp->data.element(), temp->data.occourrence());
				temp = temp->next;
			}
		}
		catch(...) {
			clear();
			throw;
		}
	}

	/**Operatore di assegnamento
	@param other il multiset da assegnare
	**/
	multiset& operator=(const multiset &other) {
		if(this!=&other) {
			multiset temp(other);
			std::swap(this->_head, temp._head);
			std::swap(this->_size, temp._size);
		}
		return *this;
	}

	/**Metodo che inserisce nel multiset un nuovo elemento base.
			@param elem l'elemento
			@param occ le occorrenze dell'elemento
	**/
	void add(const T &elem, size_type occ) {
		if(check(elem)) {
			if(_head == 0)
				_head = new node(elem, occ);
			else {
				node *tmp = _head;
				_head = new node(elem, occ);
				_head->next = tmp;
			}
			_size++;
		} else {
			node *n = find_helper(elem);
		}
	}
}; //fine classe multiset
#endif
