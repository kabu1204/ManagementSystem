#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include"QSqlTableModel"
#include"QStringList"
#include"QList"
#include"QTableView"
#include"readonlydelegate.h"
#include"genderdelegate.h"
#include"numberdelegate.h"
#include"nonemptydelegate.h"
#include"emailformatdelegate.h"

namespace Ui {
class EditWindow;
}

class EditWindow : public QWidget
{
    Q_OBJECT

public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();
    void TableModelInitializer();

private slots:
    void on_commitButton_clicked();

    void on_withdrawButtion_clicked();

private:
    Ui::EditWindow *ui;
    QFont defaultfont;
    ReadOnlyDelegate *readOnly;
    genderDelegate *genderOnly;
    numberDelegate *ageLimit;
    numberDelegate *phoneLimit;
    nonEmptyDelegate *nonEmpty;
    emailFormatDelegate *emailCheck;

    QStringList relations;
    QList<QTableView*> tables;
    QList<QSqlTableModel*> models;

    QSqlTableModel *classmatesModel;
    QSqlTableModel *friendsModel;
    QSqlTableModel *colleaguesModel;
    QSqlTableModel *relativesModel;
    QSqlTableModel *teachersModel;
    QSqlTableModel *superiorsModel;
    QSqlTableModel *clientsModel;
    QSqlTableModel *othersModel;
    QSqlTableModel* initializeModel(QSqlTableModel *model,QString relation);
    QTableView* initializeTable(QTableView *table,QSqlTableModel *model);
    void refreshTable(QTableView *table,QSqlTableModel *model);
};

#endif // EDITWINDOW_H
