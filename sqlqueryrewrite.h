#ifndef SQLQUERYREWRITE_H
#define SQLQUERYREWRITE_H
#include <QObject>
#include <QSqlQueryModel>


class SqlQueryRewrite:public QSqlQueryModel
{
public:
    SqlQueryRewrite(QObject *parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;
//    bool setData(const QModelIndex &index, const QVariant &value, int /* role */);
};

#endif // SQLQUERYREWRITE_H
