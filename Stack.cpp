#include "Stack.h"
#include <iostream>
#include <QDebug>


Stack::Stack() : tope(nullptr) {}

Stack::~Stack() {
    limpiar();
}

void Stack::push(int val) {
    Nodo* nuevo = new Nodo(val);
    nuevo->siguiente = tope;
    tope = nuevo;
}

int Stack::pop() {
    if (estaVacia()) return -1;
    Nodo* temp = tope;
    int val = temp->valor;
    tope = tope->siguiente;
    delete temp;
    return val;
}

int Stack::peek() const {
    return estaVacia() ? -1 : tope->valor;
}

bool Stack::estaVacia() const {
    return tope == nullptr;
}

void Stack::imprimir() const {
    Nodo* iterador = tope;
    QString resultado;
    while (iterador) {
        resultado += QString::number(iterador->valor) + " -> ";
        iterador = iterador->siguiente;
    }
    resultado += "nullptr";
    qDebug() << resultado;
}


void Stack::limpiar() {
    while (!estaVacia()) pop();
}

Nodo* Stack::getTop() const {
    return tope;
}

bool Stack::isEmpty() const {
    return tope == nullptr;
}

int Stack::size() const {
    int count = 0;
    Nodo* actual = tope;
    while (actual) {
        ++count;
        actual = actual->siguiente;
    }
    return count;
}

QVector<int> Stack::getValues() const {
    QVector<int> valores;
    Nodo* actual = tope;
    while (actual) {
        valores.append(actual->valor);
        actual = actual->siguiente;
    }
    return valores;
}
