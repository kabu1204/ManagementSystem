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
#include"QSqlError"
#include"editwindow.h"

withMenu::withMenu(QWidget *parent) :
    QMainWindow(parent),
    db("rm-bp10ciy2b7p5l0jm70o.mysql.rds.aliyuncs.com","yuchengye","qq20001204"),
    ui(new Ui::withMenu),
    insertWindow(&db),
    editWindow(parent),
    name_searchWindow(parent)
{
    ui->setupUi(this);
}

withMenu::~withMenu()
{
    insertWindow.close();
    delete ui;
}

void withMenu::on_connectButton_clicked()
{
    int flag=db.connect("familiar");
    QStringList basic,extra;
//    if(flag==1)
//    ui->connectInfo->setText("已连接到"+(*db.getDB()).hostName());
//    else ui->connectInfo->setText("连接失败");
}


void withMenu::on_queryButton_1_clicked()
{
    queryModel=new SqlQueryRewrite(this);
    queryModel->setQuery("SELECT name,birthday,phone,email,relation,dummy FROM classmates UNION SELECT name,birthday,phone,email,relation,dummy FROM friends UNION SELECT name,birthday,phone,email,relation,dummy FROM colleagues UNION SELECT name,birthday,phone,email,relation,dummy FROM relatives UNION SELECT name,birthday,phone,email,relation,dummy FROM teachers UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM clients UNION SELECT name,birthday,phone,email,relation,dummy FROM others");
    qDebug()<<db.getDB()->lastError();
    ui->tableView->setModel(queryModel);
    ui->tableView->setColumnHidden(5,true);
}

void withMenu::on_deleteButton_1_clicked()
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
    //得到dummy(主键)、relation(指示表名) 并删除数据库数据
    int curRow = ui->tableView->currentIndex().row();
    QModelIndex index = ui->tableView->currentIndex();
    int dummy=index.sibling(curRow,5).data().toInt();
    QString relation=index.sibling(curRow,4).data().toString();
    QString dummy_=QString::number(dummy);
    qDebug()<<relation;
    qDebug()<<dummy_;
    if(relation=="")
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("Error"),QString::fromLocal8Bit(("Please select a row!")));
        return;
    }
    //删除数据库中数据
    QSqlQuery query;
    query.prepare("delete from "+relation+" where dummy ="+dummy_);
    query.exec();
    queryModel->setQuery("SELECT name,birthday,phone,email,relation,dummy FROM classmates UNION SELECT name,birthday,phone,email,relation,dummy FROM colleagues UNION SELECT name,birthday,phone,email,relation,dummy FROM relatives UNION SELECT name,birthday,phone,email,relation,dummy FROM teachers UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM superiors UNION SELECT name,birthday,phone,email,relation,dummy FROM clients");
    ui->tableView->setColumnHidden(5,true);
    qDebug()<<db.getDB()->lastError();
    if(!query.isActive())
    {
        QMessageBox::critical(this,QString::fromLocal8Bit("Error"),QString::fromLocal8Bit("failed"));
        qDebug()<<db.getDB()->lastError();
        return;
    }
}

void withMenu::on_action_triggered()
{
    insertWindow.show();
}

void withMenu::on_action_2_triggered()
{
    editWindow.TableModelInitializer();
    editWindow.show();
}

void withMenu::on_action_3_triggered()
{
    name_searchWindow.show();
}

void withMenu::on_action_4_triggered()
{
    birthday_searchWindow.show();
}
