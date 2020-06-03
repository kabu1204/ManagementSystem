#ifndef WITHMENU_H
#define WITHMENU_H

#include <QMainWindow>
#include<QSqlTableModel>
#include"database.h"
#include"sqlqueryrewrite.h"

namespace Ui {
class withMenu;
}

class withMenu : public QMainWindow
{
    Q_OBJECT
    Database db;
    QSqlTableModel *tableModel;
    SqlQueryRewrite *queryModel;
    Ui::withMenu *ui;
public:
    explicit withMenu(QWidget *parent = nullptr);
    ~withMenu();

private slots:
    void on_connectButton_clicked();

//private:
//    Ui::withMenu *ui;
    void on_queryButton_1_clicked();
    void on_pushButton_clicked();
};

#endif // WITHMENU_H
