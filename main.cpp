#include"withmenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    withMenu wm;
    wm.show();
    return a.exec();
}
