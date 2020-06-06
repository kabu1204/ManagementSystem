#ifndef SEARCHBYNAME_H
#define SEARCHBYNAME_H

#include <QWidget>
#include"QSqlQueryModel"
#include"QSqlTableModel"

namespace Ui {
class SearchByName;
}

class SearchByName : public QWidget
{
    Q_OBJECT

public:
    explicit SearchByName(QWidget *parent = nullptr);
    ~SearchByName();

private slots:
    void on_searchButton_clicked();

private:
    Ui::SearchByName *ui;
    QFont font;
    int pre_search(QString name);
    QSqlTableModel* tableModel(int idx,QString name);
    QSqlQueryModel* queryModel(QString name);
};

#endif // SEARCHBYNAME_H
