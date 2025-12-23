#include <iostream>
#include <cassert>
#include <vector>
#include "stack.hpp" // Include il file della tua classe stack

/**
  @brief Funtore per verificare se un valore intero è pari.
*/
struct is_even {
    bool operator()(int v) const {
        return (v % 2) == 0;
    }
};

/**
  @brief Funtore per calcolare il quadrato di un numero intero.
*/
struct square {
    int operator()(int v) const {
        return v * v;
    }
};

/**
  @brief Test dei metodi fondamentali della classe stack.
*/
void test_metodi_fondamentali_int() {
    std::cout << "******** Test metodi fondamentali dello stack ********" << std::endl;

    stack<int> s1(5); // Costruttore con dimensione

    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.pop();

    std::cout << "Stack iniziale:" << std::endl;
    s1.print(); // Dovrebbe stampare [ 1 2 3 ]

    stack<int> s2(s1); // Copy constructor
    std::cout << "Stack copiato con copy constructor:" << std::endl;
    s2.print(); // Dovrebbe stampare [ 1 2 3 ]

    stack<int> s3(5);
    s3 = s1; // Operatore di assegnamento
    std::cout << "Stack copiato con operatore di assegnamento:" << std::endl;
    s3.print(); // Dovrebbe stampare [ 1 2 3 ]
    s1.clear();
    s1.print(); // test per vedere cosa succede se voglio stampare uno stack vuoto
}

/**
  @brief Test dell'uso della classe stack.
*/
void test_uso_stack() {
    std::cout << "******** Test d'uso dello stack ********" << std::endl;

    int a[] = {10, 20, 30, 40, 50};
    stack<int> s1(a, a + 5); // Costruttore con iteratori

    std::cout << "Stack creato dal costruttore con iteratori:" << std::endl;
    s1.print(); // Dovrebbe stampare [ 10 20 30 40 50 ]

    std::cout << "Dimensione dello stack:" << std::endl;
    std::cout << s1.size() << std::endl; // Dovrebbe stampare 5

    // Test eccezione pop su stack vuoto
    std::cout << "Test pop su uno stack vuoto:" << std::endl;
    s1.clear(); // Svuota lo stack
    try {
        s1.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "Eccezione catturata: " << e.what() << std::endl;
    }

    // Test eccezione push su stack pieno
    std::cout << "Test push su uno stack pieno:" << std::endl;
    stack<int> s2(2); // Stack con capacità 2
    s2.push(1);
    s2.push(2);
    try {
        s2.push(3); 
    } catch (const std::overflow_error& e) {
        std::cout << "Eccezione catturata: " << e.what() << std::endl;
    }
}

/**
  @brief Test delle funzioni filter_out e transform.
*/
void test_filter_transform() {
    std::cout << "******** Test filter_out e transform ********" << std::endl;

    stack<int> s1(5);
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);

    std::cout << "Stack iniziale:" << std::endl;
    s1.print(); // Dovrebbe stampare [ 1 2 3 4 5 ]

    stack<int> filtered = s1.filter_out(is_even());
    std::cout << "Stack filtrato (numeri pari):" << std::endl;
    filtered.print(); // Dovrebbe stampare [ 2 4 ]

    transform(s1, square());
    std::cout << "Stack trasformato (quadrati):" << std::endl;
    s1.print(); // Dovrebbe stampare [ 1 4 9 16 25 ]
}

/**
  @brief Test degli iteratori della classe stack.
*/
void test_iteratori_stack() {
    std::cout << "******** Test iteratori dello stack ********" << std::endl;

    stack<int> s1(5);
    s1.push(10);
    s1.push(20);
    s1.push(30);

    std::cout << "Iterazione sullo stack:" << std::endl;
    for (stack<int>::iterator it = s1.begin(); it != s1.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

}
void test_load_from_range() {
    std::cout << "******** Test load_from_range ********" << std::endl;

    stack<int> s1(5); // Stack con capacità 5
    s1.push(3); //faccio la push per testare se viene liberato lo stack
    std::vector<int> vec = {10, 20, 30};

    // Caricamento corretto da un range
    try {
        s1.load_from_range(vec.begin(), vec.end());
        std::cout << "Stack dopo load_from_range (range valido):" << std::endl;
        s1.print(); // Dovrebbe stampare [ 10 20 30 ]
    } catch (const std::exception& e) {
        std::cout << "Errore inaspettato: " << e.what() << std::endl;
    }

    // Test caricamento da un range troppo grande
    std::vector<int> large_vec = {1, 2, 3, 4, 5, 6}; // Più grande della capacità dello stack
    try {
        s1.load_from_range(large_vec.begin(), large_vec.end());
    } catch (const std::overflow_error& e) {
        std::cout << "Eccezione catturata: " << e.what() << std::endl;
    }

    // Test caricamento da un range vuoto
    std::vector<int> empty_vec;
        s1.load_from_range(empty_vec.begin(), empty_vec.end());
        std::cout << "Stack dopo load_from_range (range vuoto):" << std::endl;
        s1.print(); // Dovrebbe stampare [ ]
}

int main() {
    test_metodi_fondamentali_int();
    test_uso_stack();
    test_filter_transform();
    test_iteratori_stack();
    test_load_from_range();

    return 0;
}


