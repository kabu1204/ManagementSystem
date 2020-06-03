//#include "widget.h"
#include"withmenu.h"
//#include"insertwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
    withMenu wm;
    wm.show();
    return a.exec();
}
