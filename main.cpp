#include"withmenu.h"
#include"loginwindow.h"
#include <QApplication>
#include"control.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    control ctrl;
    return a.exec();
}
