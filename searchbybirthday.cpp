#include "searchbybirthday.h"
#include "ui_searchbybirthday.h"
#include"QSqlQueryModel"
#include"qsqldatemodel.h"
#include"QSqlTableModel"
#include"QMessageBox"
#include"utils.h"
#include"QDate"
#include"readonlydelegate.h"
#include"QDebug"
#include"QFileDialog"

SearchByBirthday::SearchByBirthday(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchByBirthday)
{
    ui->setupUi(this);
    font.setPointSize(11);
    font.setFamily("微软雅黑");
    setFont(font);
    setWindowTitle("按照出生日期查找");

    readOnly=new ReadOnlyDelegate(this);

    ui->daysIn->setValidator(new QIntValidator(0,364, this));
}

SearchByBirthday::~SearchByBirthday()
{
    delete ui;
}

int SearchByBirthday::pre_search(int days)
{
    int count=0,idx=-1;
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql;
    for(int i=0;i<relations().size();i++)
    {
        sql="SELECT birthday FROM "+relations()[i];
        model->setQuery(sql);
        for(int j=0;j<model->rowCount();j++)
        {
            QModelIndex modelIDX=model->index(j,0);
            QDate birthday_1=model->data(modelIDX).toDate();
            QDate birthday_2=birthday_1;
            QDate currentDate=QDate::currentDate();
            bool isValid_1=birthday_1.setDate(currentDate.year(),birthday_1.month(),birthday_1.day());
            bool isValid_2=birthday_2.setDate(currentDate.year()+1,birthday_2.month(),birthday_2.day());
            bool theVeryYear=(currentDate.daysTo(birthday_1)<=days)&&(currentDate.daysTo(birthday_1)>=0);
            bool theNextYear=(currentDate.daysTo(birthday_2)<=days)&&(currentDate.daysTo(birthday_2)>=0);
            if(!isValid_1&&!isValid_2)
                continue;
            if(theVeryYear||theNextYear)
            {
                count++;
                idx=i;
                break;
            }
        }
        if(count>1)
            break;
    }
    if(count==0) return -1;
    else if(count==1) return idx;
    else return -2;
}

QSqlQueryModel* SearchByBirthday::queryModel()
{
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql="SELECT relation,name,age,gender,birthday,email,phone FROM classmates";
    for(int i=1;i<relations().size();i++)
        sql+=(" UNION SELECT relation,name,age,gender,birthday,email,phone FROM "+relations()[i]);
    model->setQuery(sql);
    return model;
}

QSqlTableModel* SearchByBirthday::tableModel(int idx)
{
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable(relations()[idx]);
    model->select();
    return model;
}

QSqlDateQueryModel* SearchByBirthday::DateQeuryModel()
{
    QSqlDateQueryModel *model=new QSqlDateQueryModel(this);
    QString sql="SELECT relation,name,age,gender,birthday,email,phone FROM classmates";
    for(int i=1;i<relations().size();i++)
        sql+=(" UNION SELECT relation,name,age,gender,birthday,email,phone FROM "+relations()[i]);
    model->setQuery(sql);
    return model;
}

QSqlDateTableModel* SearchByBirthday::DateTableModel(int idx)
{
    QSqlDateTableModel *model=new QSqlDateTableModel(this);
    model->setTable(relations()[idx]);
    model->select();
    return model;
}

int SearchByBirthday::setTableView(QTableView *table,int days,int idx)
{
    int results=table->model()->rowCount();
    int n=results;
    QAbstractItemModel *model=table->model();
    if(idx==-2)
    {
        QSqlDateQueryModel *DatequeryModel=DateQeuryModel();
        table->setModel(DatequeryModel);
        for(int i=0;i<n;i++)
        {
            QModelIndex modelIDX=model->index(i,4);
            QDate birthday_1=model->data(modelIDX).toDate();
            QDate birthday_2=birthday_1;
            QDate currentDate=QDate::currentDate();
            bool isValid_1=birthday_1.setDate(currentDate.year(),birthday_1.month(),birthday_1.day());
            bool isValid_2=birthday_2.setDate(currentDate.year()+1,birthday_2.month(),birthday_2.day());
            if(!isValid_1&&!isValid_2)
            {
                table->setRowHidden(i,true);
                results--;
                continue;
            }
            bool theVeryYear=(currentDate.daysTo(birthday_1)<=days)&&(currentDate.daysTo(birthday_1)>=0);
            bool theNextYear=(currentDate.daysTo(birthday_2)<=days)&&(currentDate.daysTo(birthday_2)>=0);
            if(!theVeryYear&&!theNextYear)
            {
                table->setRowHidden(i,true);
                results--;
                continue;
            }
        }
    }
    else
    {
        QSqlDateTableModel *DatetableModel=DateTableModel(idx);
        table->setModel(DatetableModel);
        for(int i=0;i<n;i++)
        {
            QModelIndex modelIDX=model->index(i,4);
            QDate birthday_1=model->data(modelIDX).toDate();
            QDate birthday_2=birthday_1;
            QDate currentDate=QDate::currentDate();
            bool isValid_1=birthday_1.setDate(currentDate.year(),birthday_1.month(),birthday_1.day());
            bool isValid_2=birthday_2.setDate(currentDate.year()+1,birthday_2.month(),birthday_2.day());
            if(!isValid_1&&!isValid_2)
            {
                table->setRowHidden(i,true);
                results--;
                continue;
            }
            bool theVeryYear=(currentDate.daysTo(birthday_1)<=days)&&(currentDate.daysTo(birthday_1)>=0);
            bool theNextYear=(currentDate.daysTo(birthday_2)<=days)&&(currentDate.daysTo(birthday_2)>=0);
            if(!theVeryYear&&!theNextYear)
            {
                table->setRowHidden(i,true);
                results--;
                continue;
            }
        }
    }
    setReadOnly(table);
    table->horizontalHeader()->setStretchLastSection(true);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->setColumnWidth(4,200);
    return results;
}

void SearchByBirthday::on_searchButton_clicked()
{
    int days=ui->daysIn->text().toInt();
    int idx=pre_search(days);
    if(idx==-1)
    {
        QMessageBox::warning(this,"警告","未查询到符合要求的结果");
        return;
    }
    else if(idx==-2)
    {
        QSqlQueryModel *model=queryModel();
        ui->tableView->setModel(model);
        int results=setTableView(ui->tableView,days);
        ui->hintlabel->setText("在多个人际关系中找到"+QString::number(results)
                               +"个结果，因此只展示基本信息。");
    }
    else
    {
        QSqlTableModel* model=tableModel(idx);
        ui->tableView->setModel(model);
        int results=setTableView(ui->tableView,days,idx);
        ui->tableView->setColumnHidden(0,true);
        ui->hintlabel->setText("在关系\""+relations()[idx]+"\"中，找到"+QString::number(results)+"个结果。");
    }
    ui->emaillabel->setText("现在你可以选中一名成员并生成和保存邮件文本。");
}

void SearchByBirthday::on_emailButton_clicked()
{
    int curRow=ui->tableView->currentIndex().row();
    QModelIndex idx;
    QString name="";
    QString text=":\n\t祝生日快乐，健康幸福。\n\t\t\t\tYCY";
    idx=ui->tableView->model()->index(curRow,1);
    name=ui->tableView->model()->data(idx).toString();
    if(name.isEmpty())
    {
        QMessageBox::warning(this,"错误","请先选中一名成员");
        return;
    }
    else
    {
        text=name+text;
        QString filepath=QFileDialog::getSaveFileName(this,"保存邮件文本","./email_to_"+name+".txt","Text Files(*.txt)");
        QFile file(filepath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream output(&file);
        output<<text;
        file.close();
        ui->emaillabel->setText("邮件文本已保存到："+filepath);
    }
}
