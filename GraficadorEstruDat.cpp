#include "GraficadorEstruDat.h"
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>


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
    QFrame *areaGrafico = new QFrame();
    areaGrafico->setFrameShape(QFrame::Box);
    areaGrafico->setStyleSheet("background-color: black;");
    layoutDerecha = new QVBoxLayout(areaGrafico);

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
    case BST:         nombre = "Binary Search Tree (BST)"; break;
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
    update();
}

// ======================== PINTAR ========================
void GraficadorEstruDat::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Área de dibujo
    QRect area = QRect(200, 100, width() - 220, height() - 120);

    int x = area.left() + 50;
    int y = area.top() + 100;
    int radio = 40;
    int separacion = 100;


    // --- Obtener valores reales según estructura actual ---
    QVector<int> valores;
    switch (estructuraActual) {
    case LINKED_LIST:
        valores = listaSimple.getValues();
        break;
    case DOUBLE_LL:
        valores = listaDoble.getValuesForward();
        break;
    case STACK:
        valores = pila.getValues();
        break;
    case QUEUE:
        valores = cola.getValues();
        break;
    default:
        break;
    }

    QPen pen(Qt::black, 2);
    QBrush brush(Qt::white);
    painter.setPen(pen);
    painter.setBrush(brush);

    // --- Dibujar nodos ---
    for (int i = 0; i < valores.size(); i++) {
        painter.drawEllipse(QPointF(x, y), radio, radio);
        painter.drawText(QRectF(x - radio, y - radio, radio*2, radio*2),
                         Qt::AlignCenter, QString::number(valores[i]));

        if (i < valores.size() - 1) {
            int xLineaInicio = x + radio;
            int xLineaFin = x + separacion - radio;
            painter.drawLine(xLineaInicio, y, xLineaFin, y);
            painter.drawLine(xLineaFin, y, xLineaFin - 10, y - 5);
            painter.drawLine(xLineaFin, y, xLineaFin - 10, y + 5);
        }
        x += separacion;
    }
}



// ======================== ACCIONES ========================
void GraficadorEstruDat::onAccion1() {
    insertarEjemplo();
    update();
}

void GraficadorEstruDat::onAccion2() {
    eliminarEjemplo();
    update();
}

void GraficadorEstruDat::onAccion3() {
    qDebug() << "Acción 3 ejecutada";
}

void GraficadorEstruDat::insertarEjemplo() {
    int val = rand() % 100;
    switch (estructuraActual) {
    case LINKED_LIST:
        listaSimple.insertarFinal(val);
        listaSimple.imprimir();
        break;
    case DOUBLE_LL:
        listaDoble.insertarFinal(val);
        listaDoble.imprimirAdelante();
        break;
    case STACK:
        pila.push(val);
        pila.imprimir();
        break;
    case QUEUE:
        cola.enqueue(val);
        cola.imprimir();
        break;
    default: break;
    }
}

void GraficadorEstruDat::eliminarEjemplo() {
    switch (estructuraActual) {
    case LINKED_LIST:
        listaSimple.eliminarPos(0);
        listaSimple.imprimir();
        break;
    case DOUBLE_LL:
        listaDoble.eliminarPos(0);
        listaDoble.imprimirAdelante();
        break;
    case STACK:
        pila.pop();
        pila.imprimir();
        break;
    case QUEUE:
        cola.dequeue();
        cola.imprimir();
        break;
    default: break;
    }
}

void GraficadorEstruDat::accionLista(int opcion){
    if (opcion ==1){
        //ACCIONES Insertar
            //Hacer que el Usuario elija entre
        //    bool insertarPos(int pos, int val);
        //    void insertarInicio(int val);
        //    void insertarFinal(int val);
        //y hacerlo ingresar los valores requeridos
    }

    if(opcion==2){
        //Acciones Borrar
                //Hacer que el Usuario elija entre

        /*
        void eliminarVal(int val);
        bool eliminarPos(int pos);
        y hacerlo ingresar o el valor o la poscicion

         */
    }

    if(opcion==3){
        //Acciones Datos
            //llamar buscar, y hacer al usuario poner que valor buscar
    }

}
