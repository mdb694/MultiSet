#ifndef PAIR_H
#define PAIR_H

template<typename T> 
class pair {
	public:
	typedef unsigned int size_type; ///< tipo che rappresenta il numero di occorrenze di un elemento

	private:
	T _element; ///< elemento della coppia
	size_type _occourrence;	///<numero di occorrenze dell'elemento'

	public:

	/** Costruttore di default **/ 
 pair(void);
	
	/** Costruttore secondario 
			Crea una coppia con un numero specificato di elementi
			@param elem elemento della coppia
			@param occ numero di occorrenze dell'elemento 
	**/
	pair(T elem, size_type occ);

	/** Costruttore secondario
			Crea una coppia con una sola occorrenza dell'elemento
			@param elem elemento della coppia
	**/
	pair(T elem);

	/** Distruttore **/
	~pair(void);
}
#endif 
