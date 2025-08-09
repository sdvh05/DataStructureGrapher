#ifndef AREADIBUJO_H
#define AREADIBUJO_H

#include <QWidget>
#include <QVector>

class AreaDibujo : public QWidget {
    Q_OBJECT

public:
    explicit AreaDibujo(QWidget *parent = nullptr);
    void setValores(const QVector<int> &valores);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> valores;
};

#endif // AREADIBUJO_H
