#include "AreaDibujo.h"
#include <QPainter>
#include <QPen>
#include <QBrush>

AreaDibujo::AreaDibujo(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: black;");
}

void AreaDibujo::setValores(const QVector<int> &valores) {
    this->valores = valores;
    update(); // Redibuja el área
}

void AreaDibujo::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int x = 50;
    int y = height() / 2;
    int radio = 40;
    int separacion = 100;

    QPen pen(Qt::white, 2);
    QBrush brush(Qt::blue);
    painter.setPen(pen);
    painter.setBrush(brush);

    for (int i = 0; i < valores.size(); i++) {
        painter.drawEllipse(QPointF(x, y), radio, radio);
        painter.drawText(QRectF(x - radio, y - radio, radio * 2, radio * 2),
                         Qt::AlignCenter, QString::number(valores[i]));
        x += separacion;
    }
}
