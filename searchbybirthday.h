#ifndef SEARCHBYBIRTHDAY_H
#define SEARCHBYBIRTHDAY_H

#include <QWidget>
#include"QFont"
#include"QSqlQueryModel"
#include"QSqlTableModel"
#include"QTableView"
#include"readonlydelegate.h"

namespace Ui {
class SearchByBirthday;
}

class SearchByBirthday : public QWidget
{
    Q_OBJECT

public:
    explicit SearchByBirthday(QWidget *parent = nullptr);
    ~SearchByBirthday();

private slots:
    void on_searchButton_clicked();

private:
    Ui::SearchByBirthday *ui;
    QFont font;
    int pre_search(int days);
    ReadOnlyDelegate *readOnly;
    QSqlTableModel* tableModel(int idx);
    QSqlQueryModel* queryModel();
    int setTableView(QTableView* table,int days);
};

#endif // SEARCHBYBIRTHDAY_H
