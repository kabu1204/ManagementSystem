#include "sqlqueryrewrite.h"
#include <QSqlQuery>
#include <QDebug>

SqlQueryRewrite::SqlQueryRewrite(QObject *parent):QSqlQueryModel(parent)
{

}

Qt::ItemFlags SqlQueryRewrite::flags(
       const QModelIndex &index) const
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column()!=6&&index.column()!=7)
       flags |= Qt::ItemIsEditable;
    return flags;
}
