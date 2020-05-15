#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <cstring>

class Database
{
private:
    QSqlDatabase db;
    QString host;
    QString user;
    QString passwd;

public:
    Database(QString host_,QString user_,QString passwd_);
    QSqlDatabase* getDB();
    int connect(QString databaseName);
    int query();
    int insert(QString name="",QString age="10",QString gender="male",QString birthday="19991231",QString email="",QString phone="");
};

#endif // DATABASE_H
