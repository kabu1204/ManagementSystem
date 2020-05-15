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

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , db("rm-bp10ciy2b7p5l0jm70o.mysql.rds.aliyuncs.com","yuchengye","qq20001204_")
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

//    QString sql,name="ycy",gender="male",email="qq.com",phone="15506580556";
//    QString age="19",birthday="2000";
//    sql="INSERT INTO personal_info (name,age,gender,birthday,email,phone) VALUES ("+name+","+age+","+gender+","+birthday+","+email+","+phone+")";
//    qDebug()<<sql;
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    model=new QSqlTableModel(this,*db.getDB());
    model->setTable("classmates");
    model->select();
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    ui->tableView->setModel(model);
    ReadOnlyDelegate *readonly=new ReadOnlyDelegate();
    ui->tableView->setItemDelegateForColumn(2,readonly);
}

void Widget::on_pushButton_2_clicked()
{
    int flag=db.connect("familiar");
}

void Widget::on_pushButton_3_clicked()
{
//    QSqlQueryModel *md=new QSqlQueryModel;
//    md->setQuery("SELECT * FROM classmates UNION SELECT * FROM colleagues");
    QStandardItemModel *model=new QStandardItemModel(this);
    model->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("Name")));
    model->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("Birthday")));
    model->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("Email")));
    model->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("Phone")));

    ui->tableView->setModel(model);
}
