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
	pair(const T &elem, size_type occ);

	/** Costruttore secondario
			Crea una coppia con una sola occorrenza dell'elemento
			@param elem elemento della coppia
	**/
	pair(const T &elem);

	/** Distruttore **/
	~pair(void);

	/** Copy constructor 
			@param other pair da copiare
	**/
	pair(const pair& other);

	/** Operatore di assegnamento
			@param other pair da cui effettuare la copiare
	**/
	pair& operator=(const pair &other);

	/** Metodo getter dell'elemento
	**/
	T &element(void);

	/** Metode getter costante dell'elemento
	**/
	const T &element(void) const;

	/** Metodo getter delle occorrenze
	**/
	size_type occourrence(void);
}
#endif 
