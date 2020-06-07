#include "utils.h"
#include"QString"
#include"QTableView"
#include"QList"
#include"readonlydelegate.h"


int countCharacter(QString str, QString ch)
{
    int r=0;
    for(int i=0;i<str.size();i++)
        r=(str[i]==ch)?(r+1):r;
    return r;
}

QStringList relations()
{
    QStringList rlt;
    rlt<<"classmates"<<"friends"<<"colleagues"<<"relatives"<<"teachers"<<"superiors"<<"clients"<<"others";
    return rlt;
}

void setReadOnly(QTableView *table,QList<int>*idx)
{
    ReadOnlyDelegate *readOnly=new ReadOnlyDelegate();
    if(idx==nullptr)
    {
        for(int i=0;i<table->model()->columnCount();i++)
            table->setItemDelegateForColumn(i,readOnly);
    }
    else
    {
        for(int i=0;i<idx->size();i++)
            table->setItemDelegateForColumn(i,readOnly);
    }
}
