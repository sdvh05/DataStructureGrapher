#ifndef STACK_H
#define STACK_H

#include "Nodo.h"
#include <QVector>

class Stack {
private:
    Nodo* tope;

public:
    Stack();
    ~Stack();

    void push(int val);

    int pop();

    int peek() const;

    bool estaVacia() const;
    void imprimir() const;
    void limpiar();


    Nodo* getTop() const;
    bool isEmpty() const;
    int size() const;
    QVector<int> getValues() const;
};

#endif // STACK_H
