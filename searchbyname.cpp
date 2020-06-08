#include "searchbyname.h"
#include "ui_searchbyname.h"
#include"QFont"
#include"QMessageBox"
#include"QSqlQueryModel"
#include"utils.h"
#include"QDebug"

SearchByName::SearchByName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchByName)
{
    ui->setupUi(this);
    setWindowTitle("按照名字搜索");
    font.setPointSize(10);
    font.setFamily("微软雅黑");
    setFont(font);

}

SearchByName::~SearchByName()
{
    delete ui;
}

int SearchByName::pre_search(QString name)
{
    int count=0;
    int idx=-1;
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql;
    for(int i=0;i<relations().size();i++)
    {
        sql="SELECT name,relation FROM "+relations()[i]+" WHERE name=\'"+name+"\'";
        model->setQuery(sql);
        if(model->rowCount()>0)
        {
            count++;
            idx=i;
        }
    }
    if(count==0) return -1;
    else if(count==1) return idx;
    else return -2;
}

QSqlTableModel* SearchByName::tableModel(int idx,QString name)
{
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable(relations()[idx]);
    model->setFilter(QObject::tr("name='%1'").arg(name));
    model->select();
    return model;
}

QSqlQueryModel* SearchByName::queryModel(QString name)
{
    QSqlQueryModel *model=new QSqlQueryModel(this);
    QString sql="SELECT relation,name,age,gender,birthday,email,phone FROM classmates WHERE name=\'"+name+"\'";
    for(int i=1;i<relations().size();i++)
    {
        QString tail=" UNION SELECT relation,name,age,gender,birthday,email,phone FROM "+relations()[i]+" WHERE name=\'"+name+"\'";
        sql+=tail;
    }
    model->setQuery(sql);
    return model;
}

void SearchByName::on_searchButton_clicked()
{
    QString name=ui->nameIn->text();
    if(name.isEmpty())
    {
        QMessageBox::warning(this,"警告","请输入姓名！");
        return;
    }
    else
    {
        int idx=pre_search(name);
        if(idx==-1)
        {
            QMessageBox::warning(this,"警告","未找到符合要求的结果");
            return;
        }
        else if(idx==-2)
        {
            QSqlQueryModel *model=queryModel(name);
            ui->tableView->setModel(model);
            setReadOnly(ui->tableView);
            ui->hintlabel->setText("在多个人际关系中找到"+QString::number(model->rowCount())+"个结果，因此只展示基本信息");
        }
        else
        {
            QSqlTableModel *model=tableModel(idx,name);
            ui->tableView->setModel(model);
            setReadOnly(ui->tableView);
            ui->tableView->setColumnHidden(0,true);
            ui->hintlabel->setText("在关系\""+relations()[idx]+"\"中，找到"+QString::number(model->rowCount())+"个结果。");
        }
    }
}
