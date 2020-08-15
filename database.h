#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDebug>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include <QSqlQuery>
#include <cstring>

class Database:public QSqlDatabase
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
    static int insertion_check_fix(QString relation,QStringList basic,QStringList extra);
    int insert(QString relation,QStringList basic,QStringList extra);
};

#endif // DATABASE_H
