#ifndef MULTISET_H
#define MULTISET_H

#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <stddef.h>
#include <iostream>
#include "pair.h"

/** Classe che implenta una eccezione custom per
 il multiset.
**/
class element_not_found : public std::runtime_error {
public:
	/**Costruttore secondario che prende un messaggio
		@param msg messaggio dell'errore
	*/
	element_not_found(const char *msg) : std::runtime_error(msg) {}	
};


/** Classe che implementa un mutliset. I dati base sono coppie 
<elemento, occorrenze>. La classe memorizza tali coppie attraverso
una lista. La classe richiede la specifica del tipo di elemento T e
del funtore funct per la comparazione di due elementi.
*/
template <typename T, typename funct>
class multiset {
	typedef unsigned int size_type;
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
	int _numbelement; ///< numero totale di elementi

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

	node *find_previous(const node *mynode) const {
		node *curr = _head;
		node *next = curr->next;

		while(mynode != next || next == 0) {
			curr = next;
			next = curr->next;	
		}
		return curr;
	}

	public:

	/**Costruttore di default
	**/
	multiset() : _head(0), _size(0), _numbelement(0) {

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
	multiset(const multiset& other) : _head(0), _size(0), _numbelement(0) {
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
			std::swap(this->_numbelement, temp._numbelement);
		}
		return *this;
	}

	/**Operatore di confronto.
			@param other il multiset da confrontare
			@return true se i due multiset contengono gli stessi elementi con
											le stesse occorrenze, false altrimenti
	**/
	bool operator==(const multiset &other) const {
		typename multiset<T,funct>::const_iterator i,ie,j,je;
		if (this->_size != other._size){
			return false;
		} else {
			for(i=this->begin(), ie=this->end();i!=ie;++i) {
				bool ok = false;
				for(j=other.begin(), je=other.end();j!=je;++j)	{
					if (comp(i, j)) {
						ok = true;
					}
				}
				if (ok == false)
					return false;
			}
		}
	return true;
	}

	/**Metodo che inserisce nel multiset un nuovo elemento base.
			@param elem l'elemento
			@param occ le occorrenze dell'elemento
	**/
	void add(const T &elem, size_type occ) {
		if(!contains(elem)) {
			if(_head == 0)
				_head = new node(elem, occ);
			else {
				node *tmp = _head;
				_head = new node(elem, occ);
				_head->next = tmp;
			}
			_size++;
			_numbelement += occ;
		} else {
			node *n = find_helper(elem);
			n->data.set_occourrence(n->data.occourrence() + occ);
			_numbelement += occ;
		}
	}

	/**Metodo che inserisce nel multiset un nuovo elemento base.
			@param elem l'elemento
	**/
	void add(const T &elem) {
		if(!contains(elem)) {
			if(_head == 0)
				_head = new node(elem);
			else {
				node *tmp = _head;
				_head = new node(elem);
				_head->next = tmp;
			}
			_size++;
			_numbelement++;
		} else {
			node *n = find_helper(elem);
			n->data.set_occourrence(n->data.occourrence() + 1);
			_numbelement ++;
		}
	}

	/** Metodo che rimuove nel multiset un occorrenza dell'elemento
			@param elem l'elemento da rimuovere
	**/
	void remove(const T &elem) {
		if(contains(elem)) {
			node *n = find_helper(elem);
			if(n->data.occourrence() > 1)
				n->data.set_occourrence(n->data.occourrence() - 1);
			else {
				node *prev = find_previous(n);
				prev->next = n->next;
				delete n;
			}
		} else throw element_not_found("Element not found");
	}

	/** Metodo che rimuove nel multiset un numero di occorrenza dell'elemento
			@param elem l'elemento da rimuovere
			@param occ il numero di occorrenze
	**/
	void remove(const T &elem, size_type occ) {
	 for (int i = 0; i < occ; i++)
			remove(elem);
	}

	/** Metodo che valuta l'esistenza dell'elemento nella lista
			@param elem l'elemento da cercare
			@return true se l'elemento esiste, false altrimenti.
	**/
	bool contains(const T &elem) const {
		node *n = find_helper(elem);
		return (n!=0);
	}

	/** Ritorna il numero di elementi del multiset
			@return il numero di elementi del multiset
	**/
	int get_numbelement() const {
		return _numbelement;
	}

	/** Ritorna il numero di occorrenze di un elemento del multiset
			@param elem l'elemento da cercare'
			@return il numero di occorrenze dell'ellemento
	**/
	size_type get_occourrence(const T &elem) const {
		node *n = find_helper(elem);
		if(n!=0)
			return n->data.occourrence();
		else
			return 0;
	}

	/** Forward pair iterator di sola lettura
	**/
	class const_iterator {
		public:
			typedef std::forward_iterator_tag iterator_category;
			typedef pair<T> 																		value_type;
			typedef ptrdiff_t 																difference_type;
			typedef const pair<T>* 											pointer;
			typedef const pair<T>& 											reference;

			/** Costruttore di default
			**/
			const_iterator() {
				n = 0;
			}

			/** Costruttore di copia
					@param other l'iteratore da copiare
			**/
			const_iterator(const const_iterator &other) {
				n = other.n;
			}

			/** Operatore di assegnamento
					@param other l'iteratore da assegnare
					@return *this
			**/
			const_iterator& operator=(const const_iterator &other) {
				n = other.n;
				return *this;
			}

			/** Distruttore
			**/
			~const_iterator() {

			}

			/** Dereferenziamento per reference
					@return riferimento costante alla coppia
			**/
			const pair<T>& operator*() const {
				return n->data;
			}

			/** Dereferenziamento per puntatore
					@return puntatore costante alla coppia
			**/
			const pair<T>* operator->() const {
				return&(n->data);
			}

			/** Post incremento
					@return l'iteratore alla coppia precedente
			**/
			const_iterator operator++(int) {
				const_iterator tmp(*this);
				n = n->next;
				return tmp;
			}

			/** Pre incremento
					@return l'iteratore alla coppia successiva
			**/
			const_iterator& operator++() {
				n = n->next;
				return *this;
			}

			/** Operatore di confronto per l'uguaglianza
					@param other l'iteratore da confrontare
					@return true se i due iteratori puntano alla stessa posizione
			**/
			bool operator==(const const_iterator &other) const {
				return n == other.n;
			}

			/** Operatore di confronto per la diversità
					@param other l'iteratore da confrontare
					@return false se i due iteratori puntano alla stessa posizione
			**/
			bool operator!=(const const_iterator &other) const {
				return n!=other.n;
			}
		
		private:
			const node *n; ///< puntatore al nodo corrente del multiset
			friend class multiset;

			/** Costruttore secondario di inizializzazione
					@param pn puntatore ad un nodo della lista del multiset
			**/
			const_iterator(const node *pn) {
				n = pn;
			}
	}; //fine classe const_iterator
	
	/** Iteratore di inizio sequenza
			@return l'iteratore al primo elemento della sequenza
	**/
	const_iterator begin() const {
		return const_iterator(_head);
	}

	/** Iteratore di fine sequenza
			@return l'iteratore all'ultimo elemento della sequenza
	**/
	const_iterator end() const {
		return const_iterator(0);
	}
	
	/** Forward single element iterator di sola lettura
	**/
	class const_element_iterator {
		public:
			typedef std::forward_iterator_tag iterator_category;
			typedef T						 																		value_type;
			typedef ptrdiff_t 																difference_type;
			typedef const T* 																	pointer;
			typedef const T&																		reference;

			/** Costruttore di default
			**/
			const_element_iterator() {
				n = 0;
				elem = 0;
				nocc = 0;
			}

			/** Costruttore di copia
					@param other l'iteratore da copiare
			**/
			const_element_iterator(const const_element_iterator &other) {
				elem = other.elem;
				n = other.n;
				nocc = other.nocc;
			}

			/** Operatore di assegnamento
					@param other l'iteratore da assegnare
					@return *this
			**/
			const_element_iterator& operator=(const const_element_iterator &other) {
				elem = other.elem;
				n = other.n;
				nocc = other.nocc;
				return *this;
			}

			/** Distruttore
			**/
			~const_element_iterator() {

			}

			/** Dereferenziamento per reference
					@return riferimento costante all'elemento
			**/
			const T& operator*() const {
				return *(elem);
			}

			/** Dereferenziamento per puntatore
					@return puntatore costante all'elemento
			**/
			const T* operator->() const {
				return elem;
			}

			/** Post incremento
					@return l'iteratore all'elemento precedente
			**/
			const_element_iterator operator++(int) {
				const_element_iterator tmp(*this);
				if(nocc > 1) {
					nocc--;
				} else {
					n = n->next;
					if (n!=0){
						elem = &(n->data.element());
						nocc = n->data.occourrence();
					} else {
						elem = 0;
						nocc = 0;
					}
				}
				return tmp;
			}

			/** Pre incremento
					@return l'iteratore all'elemento successivo
			**/
			const_element_iterator& operator++() {
				if(nocc > 1) {
					nocc--;
					return *this;
				} else {
					n = n->next;
					if(n!=0){
						elem = &(n->data.element());
						nocc = n->data.occourrence();
					} else {
						elem = 0;
						nocc = 0;
					}
					return *this;
				}
			}

			/** Operatore di confronto per l'uguaglianza
					@param other l'iteratore da confrontare
					@return true se i due iteratori puntano alla stessa posizione
			**/
			bool operator==(const const_element_iterator &other) const {
				return (n == other.n && nocc == other.nocc && elem == other.elem);
			}

			/** Operatore di confronto per la diversità
					@param other l'iteratore da confrontare
					@return false se i due iteratori puntano alla stessa posizione
			**/
			bool operator!=(const const_element_iterator &other) const {
				return (n!=other.n || nocc!=other.nocc || elem!= other.elem);
			}
		
		private:
			const node *n; ///< puntatore al nodo corrente del multiset
			const T *elem; ///< puntatore all'elemento del nodo attuale
			size_type nocc; ///<numero occorrenze elemento nodo n
			friend class multiset;

			/** Costruttore secondario di inizializzazione
					@param pn puntatore ad un nodo della lista del multiset
			**/
			const_element_iterator(const node *pn) {
				n = pn;
				elem = &(pn->data.element());
				nocc = pn->data.occourrence();
			}
	}; //fine classe const_element_iterator
	
	/** Iteratore di inizio sequenza
			@return l'iteratore al primo elemento della sequenza
	**/
	const_element_iterator elem_begin() const {
		return const_element_iterator(_head);
	}

	/** Iteratore di fine sequenza
			@return l'iteratore all'ultimo elemento della sequenza
	**/
	const_element_iterator elem_end() const {
		return const_element_iterator();
	}

	private:
	/** Metodo di supporto per l'operatore ==
					confronta se due pair sono uguali
					@param first il primo iteratore
					@param second il secondo iteratore
	**/
	bool comp(typename multiset<T,funct>::const_iterator first, 
											typename multiset<T,funct>::const_iterator second) const {
		funct comp;
		
		if (comp(first->element(), second->element())) {
			if (first->occourrence() == second->occourrence()) {
				return true;
			}
		}
		return false;
	}
}; //fine classe multiset

/** Operatore di stream di output per la stampa del multiset
		@param os stream di output
		@param ms multiset da stampare
		@return lo stream di output
**/
template<typename T, typename F>
std::ostream & operator<<(std::ostream &os, const multiset<T,F> &ms) {
	typename multiset<T,F>::const_iterator i,ie;

	for(i=ms.begin(), ie=ms.end();i!=ie;++i)
		os<<"<"<<i->element()<<", "<<i->occourrence()<<"> ";

	return os;
}

#endif
