#include "withmenu.h"
#include "ui_withmenu.h"
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

withMenu::withMenu(QWidget *parent) :
    QMainWindow(parent),
    db("rm-bp10ciy2b7p5l0jm70o.mysql.rds.aliyuncs.com","yuchengye","qq20001204_"),
    ui(new Ui::withMenu)
{
    ui->setupUi(this);
}

withMenu::~withMenu()
{
    delete ui;
}

void withMenu::on_connectButton_clicked()
{
    int flag=db.connect("familiar");
//    if(flag==1)
//    ui->connectInfo->setText("已连接到"+(*db.getDB()).hostName());
//    else ui->connectInfo->setText("连接失败");
}


void withMenu::on_queryButton_1_clicked()
{
    queryModel=new SqlQueryRewrite(this);
    queryModel->setQuery("SELECT name,birthday,phone,email,relation,dummy FROM classmates UNION SELECT name,birthday,phone,email,relation,dummy FROM colleagues UNION SELECT name,birthday,phone,email,relation,dummy FROM relatives UNION SELECT name,birthday,phone,email,relation,dummy FROM teachers UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM clients");
    ui->tableView->setModel(queryModel);
    ui->tableView->setColumnHidden(5,true);
}

void withMenu::on_pushButton_clicked()
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
    int dummy=index.sibling(curRow,5).data().toInt();
    QString relation=index.sibling(curRow,4).data().toString();
    QString dummy_=QString::number(dummy);
    qDebug()<<relation<<endl;
    qDebug()<<dummy_;
    //删除数据库中数据
    QSqlQuery query;
    query.prepare("delete from "+relation+" where dummy ="+dummy_);
    query.exec();
    queryModel->setQuery("SELECT name,birthday,phone,email,relation,dummy FROM classmates UNION SELECT name,birthday,phone,email,relation,dummy FROM colleagues UNION SELECT name,birthday,phone,email,relation,dummy FROM relatives UNION SELECT name,birthday,phone,email,relation,dummy FROM teachers UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM clients");
    ui->tableView->setColumnHidden(5,true);
    qDebug()<<db.getDB()->lastError();
    if(!query.isActive())
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("hint"),QString::fromLocal8Bit("failed"));
        qDebug()<<db.getDB()->lastError();
        return;
    }
}
