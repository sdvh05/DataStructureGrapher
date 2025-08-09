#include "GraficadorEstruDat.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QInputDialog>
#include <QMessageBox>


GraficadorEstruDat::GraficadorEstruDat(QWidget *parent)
    : QWidget(parent),
    estructuraActual(LINKED_LIST)
{
    crearInterfaz();
    cambiarTextos();
}




// ======================== CREAR INTERFAZ ========================
void GraficadorEstruDat::crearInterfaz() {
    // Tamaño fijo del proyecto
    setFixedSize(800, 800);

    // Layout general vertical (Header arriba, abajo el contenido)
    QVBoxLayout *layoutGeneral = new QVBoxLayout(this);

    // ======== PARTE SUPERIOR ========
    QFrame *headerFrame = new QFrame();
    headerFrame->setFrameShape(QFrame::Box);
    headerFrame->setStyleSheet("background-color: gray;");

    layoutArriba = new QHBoxLayout(headerFrame);
    layoutArriba->setSpacing(5);
    layoutArriba->setContentsMargins(5, 5, 5, 5);

    // Botones de estructuras
    botonesEstructuras[LINKED_LIST] = new QPushButton("LinkedList");
    botonesEstructuras[DOUBLE_LL]  = new QPushButton("Double LL");
    botonesEstructuras[STACK]      = new QPushButton("Stack");
    botonesEstructuras[QUEUE]      = new QPushButton("Queue");
    botonesEstructuras[BST]        = new QPushButton("BST");
    botonesEstructuras[AVL]        = new QPushButton("AVL");

    for (auto it = botonesEstructuras.begin(); it != botonesEstructuras.end(); ++it) {
        it.value()->setFixedHeight(45);
        it.value()->setFixedWidth(90);
        layoutArriba->addWidget(it.value());
        connect(it.value(), &QPushButton::clicked, this, [=](){
            seleccionarEstructura(it.key());
        });
    }

    // Label centrado
    lblTituloEstructura = new QLabel("LinkedList");
    lblTituloEstructura->setAlignment(Qt::AlignCenter);
    layoutArriba->addWidget(lblTituloEstructura, 1);

    // Botones guardar y config
    btnGuardar = new QPushButton("💾");
    btnConfig  = new QPushButton("⚙");
    btnGuardar->setFixedSize(40, 30);
    btnConfig->setFixedSize(40, 30);
    layoutArriba->addWidget(btnGuardar);
    layoutArriba->addWidget(btnConfig);

    layoutGeneral->addWidget(headerFrame, 1);


    // ======== PARTE INFERIOR ========
    QHBoxLayout *layoutPrincipal = new QHBoxLayout();

    // Panel de control (izquierda)
    QFrame *panelControl = new QFrame();
    panelControl->setFrameShape(QFrame::Box);
    panelControl->setStyleSheet("background-color: blue;");
    QVBoxLayout *layoutIzquierda = new QVBoxLayout(panelControl);

    btnAccion1 = new QPushButton("Insertar");
    btnAccion2 = new QPushButton("Eliminar");
    btnAccion3 = new QPushButton("Datos");

    btnAccion1->setMinimumHeight(50);
    btnAccion2->setMinimumHeight(50);
    btnAccion3->setMinimumHeight(50);

    layoutIzquierda->addWidget(btnAccion1);
    btnAccion1->setStyleSheet("background-color: gray;");
    layoutIzquierda->addWidget(btnAccion2);
    btnAccion2->setStyleSheet("background-color: gray;");
    layoutIzquierda->addWidget(btnAccion3);
    btnAccion3->setStyleSheet("background-color: gray;");

    connect(btnAccion1, &QPushButton::clicked, this, &GraficadorEstruDat::onAccion1);
    connect(btnAccion2, &QPushButton::clicked, this, &GraficadorEstruDat::onAccion2);
    connect(btnAccion3, &QPushButton::clicked, this, &GraficadorEstruDat::onAccion3);

    // Área de graficado (derecha)
    areaGrafico = new AreaDibujo();
    areaGrafico->setMinimumSize(400, 400);
    layoutDerecha = new QVBoxLayout();
    layoutDerecha->addWidget(areaGrafico);


    // Agregar ambas partes a layout principal
    layoutPrincipal->addWidget(panelControl, 1);
    layoutPrincipal->addWidget(areaGrafico, 4);

    layoutGeneral->addLayout(layoutPrincipal, 5);

    setLayout(layoutGeneral);
}


// ======================== CAMBIAR TEXTOS ========================
void GraficadorEstruDat::cambiarTextos() {
    // Reset color
    for (auto btn : botonesEstructuras) {
        btn->setStyleSheet("background-color: cyan;");
    }


    //Azul oscuro la estru actual
    botonesEstructuras[estructuraActual]->setStyleSheet("background-color: blue; color: white;");

    // Cambiar título
    QString nombre;
    switch (estructuraActual) {
    case LINKED_LIST: nombre = "Linked List"; break;
    case DOUBLE_LL:   nombre = "Double Linked List"; break;
    case STACK:       nombre = "Stack"; break;
    case QUEUE:       nombre = "Queue"; break;
    case BST:         nombre = "Binary Search \n Tree (BST)"; break;
    case AVL:         nombre = "AVL Tree"; break;
    }
    lblTituloEstructura->setText(nombre);

    // Cambiar textos de panel de control
    if (estructuraActual == STACK) {
        btnAccion1->setText("Push");
        btnAccion2->setText("Pop");
        btnAccion3->setText("Peek");
    }
    else if (estructuraActual == QUEUE) {
        btnAccion1->setText("Enqueue");
        btnAccion2->setText("Dequeue");
        btnAccion3->setText("Peek");
    }
    else {
        btnAccion1->setText("Insertar");
        btnAccion2->setText("Eliminar");
        btnAccion3->setText("Buscar");
    }
}

// ======================== SELECCIONAR ESTRUCTURA ========================
void GraficadorEstruDat::seleccionarEstructura(EstructuraActual estructura) {
    estructuraActual = estructura;
    cambiarTextos();

    switch (estructuraActual) {
    case LINKED_LIST:
        areaGrafico->setValores(listaSimple.getValues());
        break;
    case DOUBLE_LL:
        areaGrafico->setValores(listaDoble.getValuesForward());
        break;
    case STACK:
        areaGrafico->setValores(pila.getValues());
        break;
    case QUEUE:
        areaGrafico->setValores(cola.getValues());
        break;
    case BST:

        break;
    case AVL:

        break;
    }

    areaGrafico->update();
}



// ======================== ACCIONES ========================
void GraficadorEstruDat::onAccion1() {
    switch (estructuraActual) {
    case LINKED_LIST:
        accionLista(1);
        break;
    case DOUBLE_LL:
        accionDLL(1);
        break;
    case STACK:
        accionPila(1);
        break;
    case QUEUE:
        accionCola(1);
        break;
    default: break;
    }
}

void GraficadorEstruDat::onAccion2() {
    switch (estructuraActual) {
    case LINKED_LIST:
        accionLista(2);
        break;
    case DOUBLE_LL:
        accionDLL(2);
        break;
    case STACK:
        accionPila(2);
        break;
    case QUEUE:
        accionCola(2);
        break;
    default: break;
    }
}

void GraficadorEstruDat::onAccion3() {
    qDebug() << "Acción 3 ejecutada";
    switch (estructuraActual) {
    case LINKED_LIST:
        accionLista(3);
        break;
    case DOUBLE_LL:
        accionDLL(3);
        break;
    case STACK:
        accionPila(3);
        break;
    case QUEUE:
        accionCola(3);
        break;
    default:
        break;
    }
}




void GraficadorEstruDat::accionLista(int opcion) {
    bool ok;

    if (opcion == 1) {
        // Insertar
        QStringList opciones;
        opciones  << "Insertar al inicio" << "Insertar al final" << "Insertar en posición";

        QString seleccion = QInputDialog::getItem(this, "Insertar en Lista",
                                                  "Seleccione tipo de inserción:", opciones, 0, false, &ok);
        if (!ok) return;

        int val, pos;

        if (seleccion == "Insertar en posición") {
            int maxPos = listaSimple.size();
            pos = QInputDialog::getInt(this, "Insertar en posición",
                                       "Posición:", 0, 0, maxPos, 1, &ok);
            if (!ok) return;

            val = QInputDialog::getInt(this, "Insertar en posición",
                                       "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;

            listaSimple.insertarPos(pos, val);
        }
        else if (seleccion == "Insertar al inicio") {
            val = QInputDialog::getInt(this, "Insertar al inicio", "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;
            listaSimple.insertarInicio(val);
        }
        else if (seleccion == "Insertar al final") {
            val = QInputDialog::getInt(this, "Insertar al final", "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;
            listaSimple.insertarFinal(val);
        }
    }
    else if (opcion == 2) {
        // Eliminar
        QStringList opciones;
        opciones << "Eliminar por valor" << "Eliminar por posicion" <<"Limpiar Lista";

        QString seleccion = QInputDialog::getItem(this, "Eliminar de Lista","Seleccione tipo de eliminación:", opciones, 0, false, &ok);
        if (!ok) return;

        int val, pos;

        if (seleccion == "Eliminar por valor") {
            val = QInputDialog::getInt(this, "Eliminar por valor", "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;
            listaSimple.eliminarVal(val);
        }
        else if (seleccion == "Eliminar por posición") {
            int maxPos = listaSimple.size();
            pos = QInputDialog::getInt(this, "Eliminar por posición", "Posición:", 0, 0, maxPos, 1, &ok);
            if (!ok) return;
            listaSimple.eliminarPos(pos);
        }
        else if(seleccion =="Limpiar Lista"){
            listaSimple.limpiar();
        }
    }
    else if (opcion == 3) {
        // Buscar
        int val = QInputDialog::getInt(this, "Buscar en Lista", "Valor a buscar:", 0, -9999, 9999, 1, &ok);
        if (!ok) return;

        if (listaSimple.buscar(val)) {
            QMessageBox::information(this, "Buscar", "El valor SI está en la lista.");
        } else {
            QMessageBox::warning(this, "Buscar", "El valor NO está en la lista.");
        }
    }

    areaGrafico->setValores(listaSimple.getValues());
    areaGrafico->update();
}

void GraficadorEstruDat::accionDLL(int opcion) {
    bool ok;

    if (opcion == 1) {
        // Insertar
        QStringList opciones;
        opciones  << "Insertar al inicio" << "Insertar al final"<< "Insertar en posición";

        QString seleccion = QInputDialog::getItem(this, "Insertar en Lista Doble",
                                                  "Seleccione tipo de inserción:", opciones, 0, false, &ok);
        if (!ok) return;

        int val, pos;

        if (seleccion == "Insertar en posición") {
            int maxPos = listaDoble.size();
            pos = QInputDialog::getInt(this, "Insertar en posición",
                                       "Posición:", 0, 0, maxPos, 1, &ok);
            if (!ok) return;

            val = QInputDialog::getInt(this, "Insertar en posición",
                                       "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;

            listaDoble.insertarPos(pos, val);
        }
        else if (seleccion == "Insertar al inicio") {
            val = QInputDialog::getInt(this, "Insertar al inicio", "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;
            listaDoble.insertarInicio(val);
        }
        else if (seleccion == "Insertar al final") {
            val = QInputDialog::getInt(this, "Insertar al final", "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;
            listaDoble.insertarFinal(val);
        }
    }
    else if (opcion == 2) {
        // Eliminar
        QStringList opciones;
        opciones << "Eliminar por valor" << "Eliminar por posición"<<"Limpiar Lista";

        QString seleccion = QInputDialog::getItem(this, "Eliminar de Lista Doble",
                                                  "Seleccione tipo de eliminación:", opciones, 0, false, &ok);
        if (!ok) return;

        int val, pos;

        if (seleccion == "Eliminar por valor") {
            val = QInputDialog::getInt(this, "Eliminar por valor", "Valor:", 0, -9999, 9999, 1, &ok);
            if (!ok) return;
            listaDoble.eliminarVal(val);
        }
        else if (seleccion == "Eliminar por posición") {
            int maxPos = listaDoble.size();
            if (listaDoble.size() == 0) return;
            pos = QInputDialog::getInt(this, "Eliminar por posición", "Posición:", 0, 0, maxPos, 1, &ok);
            listaDoble.eliminarPos(pos);
        }
        else if(seleccion =="Limpiar Lista"){
            listaDoble.limpiar();
        }
    }
    else if (opcion == 3) {
        // Buscar
        int val = QInputDialog::getInt(this, "Buscar en Lista Doble", "Valor a buscar:", 0, -9999, 9999, 1, &ok);
        if (!ok) return;

        if (listaDoble.buscar(val)) {
            QMessageBox::information(this, "Buscar", "El valor SÍ está en la lista doble.");
        } else {
            QMessageBox::warning(this, "Buscar", "El valor NO está en la lista doble.");
        }
    }

    areaGrafico->setValores(listaDoble.getValuesForward());
    areaGrafico->update();
}

void GraficadorEstruDat::accionPila(int opcion) {
    bool ok;

    if (opcion == 1) {
        // Push
        int val = QInputDialog::getInt(this, "Push en Pila", "Valor:", 0, -9999, 9999, 1, &ok);
        if (!ok) return;
        pila.push(val);
    }
    else if (opcion == 2) {
        // Pop
        if (pila.isEmpty()) {
            QMessageBox::warning(this, "Pop", "La pila está vacía.");
            return;
        }
        int val = pila.pop();
        QMessageBox::information(this, "Pop", QString("Valor eliminado: %1").arg(val));
    }
    else if (opcion == 3) {
        // Peek
        if (pila.isEmpty()) {
            QMessageBox::warning(this, "Peek", "La pila está vacía.");
            return;
        }
        int val = pila.peek();
        QMessageBox::information(this, "Peek", QString("Valor en el tope: %1").arg(val));
    }

    areaGrafico->setValores(pila.getValues());
    areaGrafico->update();
}

void GraficadorEstruDat::accionCola(int opcion) {
    bool ok;

    if (opcion == 1) {
        // Enqueue
        int val = QInputDialog::getInt(this, "Enqueue en Cola", "Valor:", 0, -9999, 9999, 1, &ok);
        if (!ok) return;
        cola.enqueue(val);
    }
    else if (opcion == 2) {
        // Dequeue
        if (cola.isEmpty()) {
            QMessageBox::warning(this, "Dequeue", "La cola está vacía.");
            return;
        }
        int val = cola.dequeue();
        QMessageBox::information(this, "Dequeue", QString("Valor eliminado: %1").arg(val));
    }
    else if (opcion == 3) {
        // Peek
        if (cola.isEmpty()) {
            QMessageBox::warning(this, "Peek", "La cola está vacía.");
            return;
        }
        int val = cola.peek();
        QMessageBox::information(this, "Peek", QString("Valor en el frente: %1").arg(val));
    }

    areaGrafico->setValores(cola.getValues());
    areaGrafico->update();
}

