#ifndef GRAFICADORESTRUDAT_H
#define GRAFICADORESTRUDAT_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGraphicsView>
#include <QPainter>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>
#include <QMap>

#include "LinkedList.h"
#include "DoubleLL.h"
#include "Stack.h"
#include "Queue.h"
// Árboles despues

class GraficadorEstruDat : public QWidget
{
    Q_OBJECT

public:
    explicit GraficadorEstruDat(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    // ENUM para controlar la estructura actual
    enum EstructuraActual {
        LINKED_LIST,
        DOUBLE_LL,
        STACK,
        QUEUE,
        BST,
        AVL
    } estructuraActual;

    // UI
    QHBoxLayout *layoutPrincipal;      // Layout principal horizontal
    QVBoxLayout *layoutIzquierda;      // Panel de control
    QVBoxLayout *layoutDerecha;        // Área de dibujo
    QHBoxLayout *layoutArriba;         // Barra superior

    // Botones de selección de estructura
    QMap<EstructuraActual, QPushButton*> botonesEstructuras;

    // Botones panel de control
    QPushButton *btnAccion1; // Insertar
    QPushButton *btnAccion2; // Eliminar
    QPushButton *btnAccion3; // Datos

    // Barra superior
    QLabel *lblTituloEstructura;
    QPushButton *btnGuardar;
    QPushButton *btnConfig;

    // Tamaño de los nodos dibujados
    int radioNodo = 30;

    // Estructuras de datos
    LinkedList listaSimple;
    DoubleLL listaDoble;
    Stack pila;
    Queue cola;

    //funcoines
    void crearInterfaz();
    void cambiarTextos();
    void insertarEjemplo();
    void eliminarEjemplo();

    void accionPila(int opcion);
    void accionCola(int opcion);
    void accionLista(int opcion);
    void accionDLL(int opcion);

private slots:
    void seleccionarEstructura(EstructuraActual estructura);
    void onAccion1(); // Insertar
    void onAccion2(); // Eliminar
    void onAccion3(); // Datos
};

#endif // GRAFICADORESTRUDAT_H
