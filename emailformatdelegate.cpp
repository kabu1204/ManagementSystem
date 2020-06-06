#include "emailformatdelegate.h"
#include"nonemptydelegate.h"
#include"QLineEdit"
#include"QMessageBox"
#include"utils.h"

emailFormatDelegate::emailFormatDelegate():nonEmptyDelegate()
{

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
    if((!text.contains("@")||(text.indexOf("@")==0)||(text.indexOf("@")==(text.size()-1))||(countCharacter(text,"@")>1)))
    {
        QMessageBox::warning(nullptr,"Warning","Email format wrong!");
        return;
    }
    model->setData(index, lineEdit->text(), Qt::EditRole);
}
