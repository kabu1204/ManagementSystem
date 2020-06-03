#include "sqlqueryrewrite.h"
#include <QSqlQuery>
#include <QDebug>

SqlQueryRewrite::SqlQueryRewrite(QObject *parent):QSqlQueryModel(parent)
{

}

Qt::ItemFlags SqlQueryRewrite::flags(
       const QModelIndex &index) const //返回表格是否可更改的标志
{
    Qt::ItemFlags flags = QSqlQueryModel::flags(index);
    if (index.column()!=6&&index.column()!=7) //可编辑状态
       flags |= Qt::ItemIsEditable;
    return flags;
}

//bool SqlQueryRewrite::setData(const QModelIndex &index, const QVariant &value, int /* role */) //表格添加数据
//{
//    QModelIndex primaryKeyIndex = QSqlQueryModel::index(index.row(), 0);
//    int id = data(primaryKeyIndex).toInt(); //获取id号 也可以这样用,primaryKeyIndex.data();

//    clear();
//    bool isOk;
//    if (index.column() == 1) //第二个属性可更改
//    {
//        QSqlQuery query;
//        query.prepare("UPDATE STUDENT SET NAME = :name WHERE id = :id");
//        query.bindValue(":name","小五");
//        query.bindValue(":id",id);
//        isOk = query.exec();

//        return true;
//    }
//    return false;
//}
