#include "qsqldatemodel.h"
#include"QSqlQueryModel"
#include"QDate"

QSqlDateQueryModel::QSqlDateQueryModel(QObject *parent):QSqlQueryModel(parent)
{

}

QSqlDateTableModel::QSqlDateTableModel(QObject *parent):QSqlTableModel(parent)
{
}

QVariant QSqlDateQueryModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    QVariant value = QSqlQueryModel::data(index, role);
    if(index.column()==4)
    {
        QDate birthday=value.toDate();
        QDate currentDate=QDate::currentDate();
        birthday.setDate(currentDate.year(),birthday.month(),birthday.day());
        bool inThisYear=currentDate.daysTo(birthday)>=0;
        QString prefix=inThisYear?"今年":"明年";
        if(!inThisYear)
            birthday.setDate(currentDate.year()+1,birthday.month(),birthday.day());
        QString week=birthday.toString("dddd");
        QString date=birthday.toString("MM-dd");
        QString result=prefix+date+"("+week+")";
        //直接用MM-dd(dddd)显示不了横杠
        return result;
    }
    return value;
}

QVariant QSqlDateTableModel::data(const QModelIndex & index,int role) const
{
    if(!index.isValid())
        return QVariant();
    QVariant value = QSqlQueryModel::data(index, role);
    if(index.column()==4)
    {
        QDate birthday=value.toDate();
        QDate currentDate=QDate::currentDate();
        birthday.setDate(currentDate.year(),birthday.month(),birthday.day());
        bool inThisYear=currentDate.daysTo(birthday)>=0;
        QString prefix=inThisYear?"今年":"明年";
        if(!inThisYear)
            birthday.setDate(currentDate.year()+1,birthday.month(),birthday.day());
        QString week=birthday.toString("dddd");
        QString date=birthday.toString("MM-dd");
        QString result=prefix+date+"("+week+")";
        //直接用MM-dd(dddd)显示不了横杠
        return result;
    }
    return value;
}
