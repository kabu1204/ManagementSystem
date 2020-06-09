#ifndef CONTROL_H
#define CONTROL_H
#include"withmenu.h"
#include"loginwindow.h"

class control:public QObject
{
    Q_OBJECT
public:
    control(QWidget *parent=nullptr):mainwindow(parent),loginwindow(parent){
        loginwindow.show();
        connect(&loginwindow,SIGNAL(loginSuccess()),this,SLOT(enterMainWindow()));
    };
    ~control()
    {
        loginwindow.close();
        mainwindow.close();
        loginwindow.~LoginWindow();
        mainwindow.~withMenu();
    }
private:
    withMenu mainwindow;
    LoginWindow loginwindow;

private slots:
    void enterMainWindow()
    {
        loginwindow.close();
        mainwindow.show();
    }
};

#endif // CONTROL_H
