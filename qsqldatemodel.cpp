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
        birthday.setDate(QDate::currentDate().year(),birthday.month(),birthday.day());
        QString week=birthday.toString("dddd");
        QString date=birthday.toString("MM-dd");
        QString result=date+"("+week+")";
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
        birthday.setDate(QDate::currentDate().year(),birthday.month(),birthday.day());
        QString week=birthday.toString("dddd");
        QString date=birthday.toString("MM-dd");
        QString result=date+"("+week+")";
        return result;
    }
    return value;
}
