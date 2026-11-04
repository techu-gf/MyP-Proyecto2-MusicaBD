#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>
#include <QGroupBox>

class QPushButton;
class QLineEdit;

class Vista : public QWidget{
    Q_OBJECT

public:

    explicit Vista(QWidget *parent = 0);
    ~Vista();

private:

    QWidget* crearBarraSuperior();
    QWidget* crearListaCanciones();
    QWidget* crearCancion(int num_performer);
    QWidget* crearInfoCancion();
};

#endif
