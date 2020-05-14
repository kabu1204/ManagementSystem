#include "widget.h"
#include "ui_widget.h"
#include "QDebug"
#include "database.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,db("rm-bp10ciy2b7p5l0jm70o.mysql.rds.aliyuncs.com","yuchengye","qq20001204_","personal_info")
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
    db.connect();
}

void Widget::on_pushButton_2_clicked()
{
    db.insert("yuchengye","19","MALE","20001204","kabu1204@qq.com","15506580556");
}
