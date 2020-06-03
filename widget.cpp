#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include "database.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include"readonlydelegate.h"
#include"QTableView"
#include"QStandardItemModel"
#include"sqlqueryrewrite.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , db("rm-bp10ciy2b7p5l0jm70o.mysql.rds.aliyuncs.com","yuchengye","qq20001204_")
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_tableButton_1_clicked()
{
    tableModel=new QSqlTableModel(this,*db.getDB());
    tableModel->setTable("classmates");
    tableModel->select();
    tableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(tableModel);
    ReadOnlyDelegate *readonly=new ReadOnlyDelegate();
    ui->tableView->setItemDelegateForColumn(2,readonly);
}

void Widget::on_connectButton_1_clicked()
{
    int flag=db.connect("familiar");
    if(flag==1)
    ui->connectInfo->setText("已连接到"+(*db.getDB()).hostName());
    else ui->connectInfo->setText("连接失败");
}

void Widget::on_queryButton_1_clicked()
{
    queryModel=new SqlQueryRewrite(this);
    queryModel->setQuery("SELECT name,birthday,phone,email FROM classmates UNION SELECT name,birthday,phone,email FROM colleagues UNION SELECT name,birthday,phone,email FROM relatives UNION SELECT name,birthday,phone,email FROM teachers UNION SELECT name,birthday,phone,email FROM superiors UNION SELECT name,birthday,phone,email FROM superiors UNION SELECT name,birthday,phone,email FROM clients");
    ui->tableView->setModel(queryModel);
}

void Widget::on_insertButton_1_clicked()
{
    //
}

void Widget::on_deleteButton_clicked()
{

    //删除数据库中的选中行
    QItemSelectionModel *selections = ui->tableView->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QMap<int, int> rows;
    foreach (QModelIndex index, selected)
       rows.insert(index.row(), 0);
    QMapIterator<int, int> r(rows);
    r.toBack();
    while (r.hasPrevious())
    {
        r.previous();
       queryModel->removeRow(r.key());
    }
    //得到id 并删除数据库数据
    int curRow = ui->tableView->currentIndex().row();
    QModelIndex index = ui->tableView->currentIndex();
    int id=index.sibling(curRow,7).data().toInt();
    //删除数据库中数据
    QSqlQuery query;
    query.prepare("delete from table where id =:id ");
    query.bindValue("id",id);
    query.exec();
    if(!query.isActive())
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("提示"),QString::fromLocal8Bit("删除数据失败!"));
        return;
    }
}
