#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Nodo.h"
#include <QVector>

class LinkedList {
private:
    Nodo* head;

public:
    LinkedList();
    ~LinkedList();

    bool insertarPos(int pos, int val);
    void insertarInicio(int val);
    void insertarFinal(int val);

    void eliminarVal(int val);
    bool eliminarPos(int pos);

    bool buscar(int val) const;
    void imprimir() const;
    void limpiar();

    Nodo* getHead() const;
    bool isEmpty() const;
    int size() const;
    QVector<int> getValues() const;
};

#endif // LINKEDLIST_H
