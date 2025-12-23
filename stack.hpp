/**
  @file stack.hpp

  @brief File header della classe stack

  File di dichiarazioni della classe stack 
*/
#ifndef STACK_HPP
#define STACK_HPP
#include <iostream>
#include <cassert>
#include <algorithm> // std::swap
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include <stdexcept> //std::overflow_error, std::underflow_error

/**
  @brief Classe stack

  Classe genererica che rappresenta uno stack di oggetti di tipo T, con dimensione fissa.
*/
template <typename T>
class stack {
    T *_stack; ///< puntatore all'array dinamico
    unsigned int _size;     ///< dimensione dell'array dinamico
    int _top; ///< questo dato int sarà l'indice della cella in "cima" dello stack
    
    // Inizializza i dati membro
    void set_zero() {
        _stack = nullptr;
        _size = 0;  
        _top = -1;
    }

public:

/**
    @brief Costruttore di default

    Construttore di default che inizializza lo stack ad un array dinamico vuoto.

    @post _size == 0
    @post _stack == nullptr
    @post _top == -1
    */
    stack() : _stack(nullptr), _size(0), _top(-1) {} 


    /**
    @brief Costruttore secondario

    Costruttore secondario che permette di creare un array dinamico della dimensione data.

    @param size dimensione dell'array da istanziare

    @post _size == size
    @post _stack != nullptr 
    @post _top = -1

  */
    explicit stack(unsigned int size): _stack(nullptr), _size(0), _top(-1) {
  
        _stack = new T[size]; //non lo metto all' interno di un try catch, perchè essendo la prima operazione se dovesse fallire non succederebbe nulla
        _size = size;
    }

/**
    @brief Distruttore

    2° METODO FONDAMENTALE DELLE CLASSI
    IL distruttore della classe rimuove le eventuali risorse
    richieste dall'oggetto.

    @post _size == 0
    @post _stack == nullptr
    @post _top = -1
  */
    ~stack(){
        delete[] _stack;
        set_zero();
    }

    /**
    @brief Stampa il contenuto dell'array dinamico su cout

    Stampa il contenuto dell'array dinamico su cout
  */
    
    void print() const{ 
      if(_top == -1)
        std::cout << "lo stack è vuoto" << std::endl;
      for( int  i = _top; i >= 0; --i)
        std::cout << _stack[i] << std::endl;
    }

    /**
    @brief Getter della dimensione dell'array

    Metodo che ritorna la dimensione dell'array

    @return _size
  */
    unsigned int size() const{
      return this->_size;
    }

  /**
    @brief metodo push

    questo metodo fa si che si aggiunga un oggetto di tipo T all' interno dello stack con la logica LIFO.

    @param value elemento da inserire nello stack

    @post _top++
    @throw std::overflow_error se lo stack è pieno

  */
    void push(const T &value){
      if (_top + 1 >= _size){ //controlla se lo stack è pieno
        throw std::overflow_error("Stack overflow: lo stack è pieno");
      }  
      _top++;
      _stack[_top] = value;
    }

    /**
    @brief metodo pop

    questo metodo preleva l' ultimo elemento dalla "cima".

    @post _top--
    @throw std::underflow_error se lo stack è vuoto

  */
    T pop(){
        if (_top == -1) {  // Controlla se lo stack è vuoto
          throw std::underflow_error("Stack underflow: lo stack è vuoto");
        }
        T val = _stack[_top];
        _top--;
        return val;
    }

    /**
    @brief Operatore di assegnamento

    3° METODO FONDAMENTALE DELLE CLASSI
    Operatore che copia il contenuto di uno stack nello stack corrente.

    @param other stack sorgente

    @return reference a this

    @post _size == other._size
    @post _stack[i] == other._stack[i]

  */
    stack &operator=(const stack &other){
        if (this != &other) { // Controllo auto-assegnamento
            stack temp(other); 
            this->swap(temp); 
        }
            return *this;
    }
    /**
    @brief Costruttore di copia (Copy constructor)

    4° METODO FONDAMENTALE DELLE CLASSI
    Crea uno stack a partire da un altro stack

    @param other stack sorgente

    @post _size == other._size
    @post _stack[i] == other._stack[i]
    @post _top == other._top

    @throw std::bad_alloc in caso di fallimento
  */
  stack(const stack &other) : _stack(nullptr), _size(other._size), _top(other._top) {
    
    try {
      _stack = new T[other._size];
      for(int i=0; i<=_top; ++i)
        _stack[i] = other._stack[i];
    }
    catch(...) {
      delete[] _stack;
      set_zero();
      throw;
    }
  }
    
    /**
    @brief Metodo swap

    Metodo che scambia lo stato di other con quello di this.

    @param other stack con cui scambiare lo stato

    @post this->_size == other._size
    @post this->_stack == other._stack
    @post this->_top == other._top
    @post other._size == this->_size
    @post other._stack == this->other._stack
    @post other._top == this->other._top
  */
  void swap(stack &other){
    std::swap(this->_size,other._size);
    std::swap(this->_stack,other._stack);  
    std::swap(this-> _top, other._top);
  }    
  /**
  @brief metodo clear()
    il metodo clear non fa altro che svuotare lo stack:
    potrei fare un ciclo che continua ad eseguire la pop sullo stack finche _top non raggiunge il valore -1.
    però il metodo pop non fa altro che decrementare il valore _top e ritornare i valori estratti,
    essendo che noi non siamo interessati ai valori estratti, possiamo semplicemente porre _top = -1

    @post _top = -1
  */
  void clear(){
    
    /*while (_top > -1){
        pop();
    }*/
   _top = -1; 
  }

  /**
    @brief costruttore con iteratori
    Costruttore che crea uno stack riempito con dati
    presi da una sequenza identificata da un iteratore di 
    inizio e uno di fine. Gli iteratori possono essere di
    qualunque tipo. 

    @param b iteratore di inizio sequenza
    @param e iteratore di fine sequenza

  */
    template <typename IterT>
    stack(IterT b, IterT e) : _size(0), _stack(nullptr), _top(-1) {
      int tempSize = 0;
      for (IterT it = b; it != e; ++it) {
          ++tempSize; // Conta gli elementi
      }
      _size = tempSize;
      if (_size > 0) {
          _stack = new T[_size]; // Allocazione della memoria
      } 

      // Copia gli elementi nell'array dello stack
      while(b != e) {
          push(static_cast<T>(*b));
          ++b;
      }
    }
    /**
    @brief funzione load_from_range
    metodo che riempie uno stack con dati
    presi da una sequenza identificata da un iteratore di 
    inizio e uno di fine. Gli iteratori possono essere di
    qualunque tipo. 

    @param b iteratore di inizio sequenza
    @param e iteratore di fine sequenza

  */
    template <typename IterT>
    void load_from_range(IterT b, IterT e) {
    // Svuota lo stack esistente se non è gia vuoto
      clear();
      int count = 0;
      for (IterT it = b; it != e; ++it) {
        ++count;
    }
      if(count<= _size ){
        // Aggiungi i nuovi dati nello stack
        while (b != e) {
          push(static_cast<T>(*b));
          ++b;
        }
      }else{
        throw std::overflow_error("Stack overflow: il vettore che si vuole copiare supera la grandezza dello stack");
      }
    }
    /**
    @brief funzione filter_out
    metodo che ritorna un nuovo stack che contiene tutti gli elementi
    T dello stack di partenza che soddisfano il predicato P.

    @param predicate predicato generico di tipo P

    @return stack filtrato

  */
    template <typename P>
    stack filter_out(P predicate) const {
        stack<T> filtered(_size); // Crea un nuovo stack della stessa dimensione
        for (int i = 0; i <= _top; ++i) {
            if (predicate(_stack[i])) {
                filtered.push(_stack[i]); // Aggiungi elemento se soddisfa il predicato
            }
        }
        return filtered;
    }
class const_iterator;
class iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;

	
		iterator() : _ptr(nullptr) { }
		
		iterator(const iterator &other) : _ptr(other.ptr) { } 

		iterator& operator=(const iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

		~iterator() {
            _ptr = nullptr; // L'iteratore NON è proprietario dei dati!
        }

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
            return *_ptr;
        }

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
            return _ptr;
        }

		// Operatore di iterazione post-incremento
		iterator operator++(int) {
            iterator temp(*this);
            ++(*this);
            return temp;
        }

		// Operatore di iterazione pre-incremento
		iterator &operator++() {
            ++_ptr;
            return *this;
        }

		// Uguaglianza
		bool operator==(const iterator &other) const {
            return _ptr == other.ptr;
        }

		// Diversita'
		bool operator!=(const iterator &other) const {
            return _ptr != other._ptr;
        }
		
		// Solo se serve anche const_iterator aggiungere le seguenti definizioni
		friend class const_iterator;

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
            return _ptr == other.ptr;
        }

		// Diversita'
		bool operator!=(const const_iterator &other) const {
            return _ptr != other.ptr;
        }
		

	private:
		T *_ptr;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class stack; 

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		iterator(T *p) : _ptr(p) { }
		
		// !!! Eventuali altri metodi privati
		
	}; // classe iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return iterator(_stack);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return iterator(_stack+_top+1);
	}
	
	
	
	class const_iterator {
		//	
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : _ptr(nullptr) { }
		
		const_iterator(const const_iterator &other) : _ptr(other._ptr) { }

		const_iterator& operator=(const const_iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

		~const_iterator() {
            _ptr = nullptr;
        }

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
            return *_ptr;
        }

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
            return _ptr;
        }
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
            const_iterator temp(*this);
            ++_ptr;
            return temp;
        }

		// Operatore di iterazione pre-incremento
		const_iterator &operator++() {
            ++_ptr;
            return *this;
        }

		// Uguaglianza
        bool operator==(const const_iterator &other) const {
            return _ptr == other.ptr;
        }
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
            return _ptr != other.ptr;
        }

		// Solo se serve anche iterator aggiungere le seguenti definizioni
		
		friend class iterator;

		// Uguaglianza
		bool operator==(const iterator &other) const {
            return _ptr == other.ptr;
        }

        // Diversita'
        bool operator!=(const iterator &other) const {
            return _ptr != other.ptr;
        }

		// Costruttore di conversione iterator -> const_iterator
        // Vogliamo condivisione!
        const_iterator(const iterator &other)  : _ptr(other._ptr) { }

        // Assegnamento di un iterator ad un const_iterator
        // Vogliamo condivisione!
        const_iterator &operator=(const iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

		// Solo se serve anche iterator aggiungere le precedenti definizioni

	private:
		const T*_ptr;

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class stack; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const T*p) : _ptr(p) { }
	}; // classe const_iterator

  
  // Ritorna l'iteratore all'inizio della sequenza dati
    const_iterator begin() const {
        return const_iterator(_stack);
    }
  
  // Ritorna l'iteratore alla fine della sequenza dati
    const_iterator end() const {
        return const_iterator(_stack+_top+1);
    }

};

/**
    @brief funzione tranform
    funzione globale che  dato un uno stack generico e funtore generico F su un elemento di tipo T,
    trasforma tutti i valori contenuti in S usando F sovrascrivendoli.

    @param s stack su cui modificare gli elementi all' interno
    @param func funtore che opera su dati T e ritorna dati T

  */
template <typename T, typename F>
void transform(stack<T> &s, F func) {
    typename stack<T>::iterator i, ie;

  for(i=s.begin(), ie=s.end(); i!=ie; ++i) {
        *i = func(*i); // Applica la trasformazione e sovrascrive
    }
}

#endif


