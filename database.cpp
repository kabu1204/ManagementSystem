#include "database.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include<cstring>
#include "widget.h"

Database::Database(QString host_,QString user_,QString passwd_)
{
    db=QSqlDatabase::addDatabase("QMYSQL");
    host=host_;
    user=user_;
    passwd=passwd_;
}

QSqlDatabase* Database::getDB()
{
    return &db;
}

int Database::connect(QString databaseName)
{
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(passwd);
    db.setDatabaseName(databaseName);
    if(!db.open())
    {
        qDebug() << db.lastError();
        return 0;
    }
    else return 1;
}

//int Database::query()
//{

//}

int Database::insert(QString name,QString age,QString gender,QString birthday,QString email,QString phone)
{
    QSqlQuery query;
    QString sql;
    sql="INSERT INTO personal_info (name,age,gender,birthday,email,phone) VALUES (\""+name+"\","+age+",\""+gender+"\","+birthday+",\""+email+"\","+phone+")";
    qDebug()<<sql;
    query.exec(sql);
    if(db.lastError().isValid())
    {
        qDebug()<<db.lastError();
        return 0;
    }
    else return 1;
}
