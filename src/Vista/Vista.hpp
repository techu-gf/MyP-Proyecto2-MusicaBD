#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QWidget>

class QPushButton;
class QTextBrowser;

class Vista : public QWidget{
    Q_OBJECT

public:

    explicit Vista(QWidget *parent = 0);
    ~Vista();

private:

    QPushButton* boton;
    QTextBrowser* texto;
};

#endif
