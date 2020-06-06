#ifndef WITHMENU_H
#define WITHMENU_H

#include <QMainWindow>
#include<QSqlTableModel>
#include"database.h"
#include"sqlqueryrewrite.h"
#include"insertwindow.h"
#include"editwindow.h"
#include"searchbyname.h"

namespace Ui {
class withMenu;
}

class withMenu : public QMainWindow
{
    Q_OBJECT
    Database db;
    QSqlTableModel *tableModel;
    SqlQueryRewrite *queryModel;
public:
    explicit withMenu(QWidget *parent = nullptr);
    ~withMenu();

private slots:
    void on_connectButton_clicked();
    void on_queryButton_1_clicked();
    void on_deleteButton_1_clicked();
    void on_action_triggered();
    void on_action_2_triggered();

    void on_action_3_triggered();

private:
    Ui::withMenu *ui;
    InsertWindow insertWindow;
    EditWindow editWindow;
    SearchByName name_searchWindow;
};

#endif // WITHMENU_H
