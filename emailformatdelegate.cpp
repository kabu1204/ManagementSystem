#include "emailformatdelegate.h"
#include"nonemptydelegate.h"
#include"QLineEdit"
#include"QMessageBox"

emailFormatDelegate::emailFormatDelegate():nonEmptyDelegate()
{

}

int emailFormatDelegate::count(QString str)const
{
    int r=0;
    for(int i=0;i<str.size();i++)
        r=(str[i]=="@")?r+1:r;
    return r;
}

void emailFormatDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit=static_cast<QLineEdit*>(editor);
    QString text=lineEdit->text();
    if(text.isEmpty())
    {
        QMessageBox::warning(nullptr,"Warning","Cannot be empty!");
        return;
    }
    if((!text.contains("@")||(text.indexOf("@")==0)||(count(text)>1)))
    {
        QMessageBox::warning(nullptr,"Warning","Email format wrong!");
        return;
    }
    model->setData(index, lineEdit->text(), Qt::EditRole);
}
