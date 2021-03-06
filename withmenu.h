#ifndef WITHMENU_H
#define WITHMENU_H

#include <QMainWindow>
#include<QSqlTableModel>
#include"database.h"
#include"sqlqueryrewrite.h"
#include"insertwindow.h"
#include"editwindow.h"
#include"searchbyname.h"
#include"searchbybirthday.h"
#include"QList"
#include"countbymonth.h"

namespace Ui {
class withMenu;
}

class withMenu : public QMainWindow
{
    Q_OBJECT
    Database db;
public:
    explicit withMenu(QWidget *parent = nullptr);
    ~withMenu();

private slots:
    void receiveMonth(int month);
    void on_refreshButton_clicked();
    void on_deleteButton_1_clicked();
    void on_action_triggered();
    void on_action_2_triggered();

    void on_action_3_triggered();

    void on_action_4_triggered();

    void on_action_13_triggered();

    void on_action_12_triggered();

    void on_action_8_triggered();

    void on_action_9_triggered();

    void on_actionh_triggered();

private:
    Ui::withMenu *ui;
    QFont font;
    InsertWindow insertWindow;
    EditWindow editWindow;
    SearchByName name_searchWindow;
    SearchByBirthday birthday_searchWindow;
    CountByMonth *monthDialog;
    QSqlQueryModel *AllModel;
    QSqlTableModel *classmatesModel;
    QSqlTableModel *friendsModel;
    QSqlTableModel *colleaguesModel;
    QSqlTableModel *relativesModel;
    QSqlTableModel *teachersModel;
    QSqlTableModel *superiorsModel;
    QSqlTableModel *clientsModel;
    QSqlTableModel *othersModel;
    QList<QSqlTableModel*> CategoryModels;
    QList<QTableView*> CategoryTables;
    QString defaultsql;
    ReadOnlyDelegate *readOnly;
    bool setTableView();
    QSqlQueryModel* setAllModel(QSqlQueryModel *model,QString sql);
    QList<QSqlTableModel*> setCategoryModels(QList<QSqlTableModel*> models);
    QString deleteSelectedRow(QTableView *table,int dummyIDX);
};

#endif // WITHMENU_H
