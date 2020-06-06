#include "database.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QDebug>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include<cstring>
#include "widget.h"
#include"QDate"
#include"utils.h"

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

int Database::insertion_check_fix(QString relation,QStringList basic,QStringList extra)
{
    if(relation=="") return -1;
    //判断基本信息是否有效(是否为空或者格式是否正确) ErrorCode 1-6、13-17
    for(int i=1;i<=6;i++)
    {
        basic[i-1]=basic[i-1].simplified();        //去掉多余空格
        if(basic[i-1].isEmpty()) return i;
    }
    if(basic[1].toInt()<=0) return 13;
    if(basic[1].toInt()>=200) return 17;
    if(basic[5].toLongLong()<=0) return 14;
    QDate date=QDate::fromString(basic[3],"yyyy-MM-dd");
    if(date>QDate::currentDate()) return 15;
    if((!basic[4].contains("@"))||(basic[4].indexOf("@")==basic[4].size()-1)||(basic[4].indexOf("@")==0)
            ||(countCharacter(basic[4],"@")))
        return 16;

    //判断额外信息是否为空  ErrorCode 7-12
    for(int i=7;i<=12;i++)
    {
        basic[i-7]=basic[i-7].simplified();         //去掉多余空格
        if((extra[i-7]!=QString(false))&&(extra[i-7]=="")) return i;
    }
    return 0;
}

int Database::insert(QString relation,QStringList basic,QStringList extra)
{
    QSqlQuery query;
    QString head,body,tail,sql;
    head="INSERT INTO "+relation+" ";
    body="(name,age,gender,birthday,email,phone,";
    tail="(\""+basic[0]+"\",\""+basic[1]+"\",\""+basic[2]+"\",\""+basic[3]+"\",\""+basic[4]+"\",\""+basic[5]+"\",\"";
    if(relation=="classmates")
    {
        body+="school,remarks,relation) VALUES ";
        tail+=extra[0]+"\",\""+extra[6]+"\",\""+relation+"\")";
    }

    else if(relation=="friends")
    {
        body+="place,remarks,relation) VALUES ";
        tail+=extra[5]+"\",\""+extra[6]+"\",\""+relation+"\")";
    }
    else if(relation=="colleagues")
    {
        body+="company,remarks,relation) VALUES ";
        tail+=extra[2]+"\",\""+extra[6]+"\",\""+relation+"\")";
    }
    else if(relation=="relatives")
    {
        body+="`call`,remarks,relation) VALUES ";
        tail+=extra[4]+"\",\""+extra[6]+"\",\""+relation+"\")";
    }
    else if(relation=="teachers")
    {
        body+="school,course,remarks,relation) VALUES ";
        tail+=extra[0]+"\",\""+extra[1]+"\",\""+extra[6]+"\",\""+relation+"\")";
    }
    else if(relation=="superiors")
    {
        body+="company,post,remarks,relation) VALUES ";
        tail+=extra[2]+"\",\""+extra[3]+"\",\""+extra[6]+"\",\""+relation+"\")";
    }
    else if(relation=="clients")
    {
        body+="company,remarks,relation) VALUES ";
        tail+=extra[2]+"\",\""+extra[6]+"\",\""+relation+"\")";
    }
    else
    {
        body+="remarks,relation) VALUES ";
        tail+=extra[6]+"\",\""+relation+"\")";
    }
    sql=head+body+tail;
    qDebug()<<sql;
    query.exec(sql);
    if(db.lastError().isValid())
    {
        qDebug()<<db.lastError();
        return 0;
    }
    else return 1;
}
