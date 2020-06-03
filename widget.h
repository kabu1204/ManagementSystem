#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSqlTableModel>
#include"database.h"
#include"sqlqueryrewrite.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    Database db;
    QSqlTableModel *tableModel;
    SqlQueryRewrite *queryModel;
    Ui::Widget *ui;
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_connectButton_1_clicked();

    void on_tableButton_1_clicked();

    void on_queryButton_1_clicked();

//private:
//    Ui::Widget *ui;
    void on_insertButton_1_clicked();
    void on_deleteButton_clicked();
};
#endif // WIDGET_H
