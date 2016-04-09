# MultiSet
Progetto C++ Programmazione e Amministrazione di Sistema A.A. 2015/2016; Implementazione di un MultiSet

Il progetto richiede la progettazione e realizzazione di una classe che implementa un MultiSet di elementi generici T. Un MultiSet è come un insieme di dati che può contenere duplicati: es. S={1,4,6,4,9,4,7,10,12}. Implementare il MultiSet in modo tale da minimizzare l’uso della memoria cioè non dovete memorizzare i duplicati di un elemento. Facendo riferimento all’esempio precedente, il '4' và memorizzato una sola volta sapendo però che ci sono tre occorrenze di '4' in S.   
A parte i metodi essenziali per la classe (tra cui conoscere il numero totale di elementi, aggiunta/rimozione elementi, conteggio occorrenze di un elemento, ecc...), devono essere implementate le seguenti funzionalità:  
1. Gli iteratori (scegliere la tipologia) devono ritornare tutti gli elementi del MultiSet. I duplicati vanno ritornati in numero corretto.  
2. Implementare l’operatore di confronto operator== tra due MultiSet che ritorna true sse i due MultiSet (dello stesso tipo) contengono gli stessi elementi con lo stesso numero di occorrenze dei duplicati.  
3. Implementate un metodo contains che, dato un elemento di tipo T,  ritorna true se l'elemento esiste nel MultiSet.  
4. Implementare la funzione globale operator<< per inviare su std::ostream il contenuto del MultiSet nella forma:      {<X1, occorrenzeX1>, <X2, occorrenzeX2>,...,<XN, occorrenzeXN>}  
Tenete anche conto che:  - L’ordine degli elementi nel MultiSet non è rilevante.  - La rimozione di un elemento X avviene quando il numero di      occorrenze di tale elemento diventa zero.  - Fate in modo che gli elementi del MultiSet siano immutabili (una     volta inseriti, non cambiano valore).  
Utilizzare dove opportuno la gestione delle eccezioni.
