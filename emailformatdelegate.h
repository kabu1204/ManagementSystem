#ifndef EMAILFORMATDELEGATE_H
#define EMAILFORMATDELEGATE_H
#include"nonemptydelegate.h"
#include"utils.h"

class emailFormatDelegate : public nonEmptyDelegate
{
public:
    emailFormatDelegate();
    virtual void setModelData(QWidget *editor,QAbstractItemModel *model,const QModelIndex &index)const;
    int count(QString str)const;
};

#endif // EMAILFORMATDELEGATE_H
