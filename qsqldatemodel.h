#ifndef QSQLDATEMODEL_H
#define QSQLDATEMODEL_H
#include"QSqlQueryModel"
#include"QSqlTableModel"

class QSqlDateQueryModel:public QSqlQueryModel
{
    Q_OBJECT
public:
    QSqlDateQueryModel(QObject *parent=nullptr);
    QVariant data(const QModelIndex & index,int role) const;
};

class QSqlDateTableModel:public QSqlTableModel
{
    Q_OBJECT
public:
    QSqlDateTableModel(QObject *parent=nullptr);
    QVariant data(const QModelIndex & index,int role) const;
};

#endif // QSQLDATEMODEL_H
