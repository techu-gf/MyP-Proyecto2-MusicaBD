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

    QPushButton* getBotonMinar() const{
	return minar;
    }
    
    void mostrarMensaje(const std::string& mensaje);

private:

    QWidget* crearBarraSuperior();
    QWidget* crearListaCanciones();
    QWidget* crearCancion(int num_performer);
    QWidget* crearInfoCancion();

    QPushButton* minar;
};

#endif
