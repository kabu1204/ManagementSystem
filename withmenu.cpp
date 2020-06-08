#include "withmenu.h"
#include "ui_withmenu.h"
#include "QDebug"
#include "database.h"
#include <QSqlDatabase>
#include <QSqlTableModel>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include"readonlydelegate.h"
#include"QTableView"
#include"QStandardItemModel"
#include"sqlqueryrewrite.h"
#include"QSqlError"
#include"editwindow.h"
#include"countbymonth.h"
#include"utils.h"

withMenu::withMenu(QWidget *parent) :
    QMainWindow(parent),
    db("rm-bp10ciy2b7p5l0jm70o.mysql.rds.aliyuncs.com","yuchengye","qq20001204"),
    ui(new Ui::withMenu),
    insertWindow(&db),
    editWindow(parent),
    name_searchWindow(parent)
{
    ui->setupUi(this);
    setWindowTitle("通讯录总览");
    font.setPointSize(10);
    font.setFamily("微软雅黑");
    setFont(font);
    setFixedSize(900,633);

    int flag=db.connect("familiar");
    CategoryModels<<classmatesModel<<friendsModel<<colleaguesModel<<relativesModel<<teachersModel<<superiorsModel<<clientsModel<<othersModel;
    CategoryTables<<ui->classmatesTable<<ui->friendsTable<<ui->colleaguesTable<<ui->relativesTable<<ui->teachersTable
                 <<ui->superiorsTable<<ui->clientsTable<<ui->othersTable;
    AllModel=new QSqlQueryModel(this);
    for(int i=0;i<CategoryModels.size();i++)
        CategoryModels[i]=new QSqlTableModel(this);

    defaultsql="SELECT name,birthday,phone,email,dummy,relation FROM classmates";
    for(int i=1;i<relations().size();i++)
    {
        defaultsql+=(" UNION SELECT name,birthday,phone,email,dummy,relation FROM "+relations()[i]);
    }
    readOnly=new ReadOnlyDelegate(this);
    setTableView();
}

withMenu::~withMenu()
{
    insertWindow.close();
    delete ui;
}

QSqlQueryModel* withMenu::setAllModel(QSqlQueryModel *model,QString sql)
{
    model->setQuery(sql);
    return model;
}
QList<QSqlTableModel*> withMenu::setCategoryModels(QList<QSqlTableModel*> models)
{
    for(int i=0;i<models.size();i++)
    {
        models[i]->setTable(relations()[i]);
        models[i]->select();
    }
    return models;
}

bool withMenu::setTableView()
{
    AllModel=setAllModel(AllModel,defaultsql);
    CategoryModels=setCategoryModels(CategoryModels);
    ui->allTable->setModel(AllModel);
    ui->allTable->setColumnHidden(4,true);
    for(int i=0;i<AllModel->columnCount();i++)
        ui->allTable->setItemDelegateForColumn(i,readOnly);
    for(int i=0;i<CategoryModels.size();i++)
    {
        CategoryTables[i]->setModel(CategoryModels[i]);
        for(int j=0;j<AllModel->columnCount();j++)
            CategoryTables[i]->setItemDelegateForColumn(j,readOnly);
        CategoryTables[i]->setColumnHidden(0,true);
    }
    return true;
}

QString withMenu::deleteSelectedRow(QTableView *table,int dummyIDX)
{
    //QSqlTableModel,删除数据库中的选中行
    if(dummyIDX==0)
    {
        QItemSelectionModel *selections = table->selectionModel();
        QModelIndexList selected = selections->selectedIndexes();
        if(selected.isEmpty())
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit(("请先选中一行要删除的数据")));
            return "";
        }
        QMap<int, int> rows;
        foreach (QModelIndex index, selected)
            rows.insert(index.row(), 0);
        QMapIterator<int, int> r(rows);
        r.toBack();
        while (r.hasPrevious())
        {
            r.previous();
            table->model()->removeRow(r.key());
        }
        return table->objectName().replace("Table","");
    }
    else
    {
        //QSqlQueryModel, 得到dummy(主键)(>0)、relation(指示表名) 并删除数据库数据
        int curRow = table->currentIndex().row();
        QModelIndex index = table->currentIndex();
        index=table->model()->index(curRow,dummyIDX);
        int dummy=table->model()->data(index).toInt();
        QString dummy_=QString::number(dummy);
        QSqlQuery query;
        QString relation;
        relation=index.sibling(curRow,5).data().toString();
        if(dummy_=="0")
        {
            QMessageBox::warning(this,QString::fromLocal8Bit("警告"),QString::fromLocal8Bit(("请先选中一行要删除的数据")));
            return "";
        }
        query.prepare("delete from "+relation+" where dummy ="+dummy_);
        query.exec();
        if(!query.isActive())
        {
            QMessageBox::critical(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("删除失败"));
//            qDebug()<<db.getDB()->lastError();
            return "";
        }
        return relation;
    }
}

void withMenu::on_refreshButton_clicked()
{
    ui->hintlabel->setText("请稍等...");
    setTableView();
    ui->hintlabel->setText("已刷新");
}

void withMenu::on_deleteButton_1_clicked()
{
    if(ui->toolBox->currentIndex()==0)
    {
        QString relation=deleteSelectedRow(ui->allTable,4);
        if(!relation.isEmpty())
        {
            AllModel->setQuery(defaultsql);
            ui->allTable->setModel(AllModel);
            for(int i=0;i<relations().size();i++)
            {
                if(CategoryModels[i]->tableName()==relation)
                {
                    CategoryModels[i]->select();
                    CategoryTables[i]->setModel(CategoryModels[i]);
                    return;
                }
            }
        }
        else return;
    }
    else
    {
        int tabIDX=ui->tabWidget->currentIndex();
        QString relation=deleteSelectedRow(CategoryTables[tabIDX],0);
        CategoryModels[tabIDX]->select();
        CategoryTables[tabIDX]->setModel(CategoryModels[tabIDX]);
        AllModel->setQuery(defaultsql);
        ui->allTable->setModel(AllModel);
        return;
    }
}

void withMenu::on_action_triggered()
{
    insertWindow.show();
}

void withMenu::on_action_2_triggered()
{
    editWindow.TableModelInitializer();
    editWindow.show();
}

void withMenu::on_action_3_triggered()
{
    name_searchWindow.show();
}

void withMenu::on_action_4_triggered()
{
    birthday_searchWindow.show();
}

void withMenu::on_action_13_triggered()
{
    QString sql="(SELECT name,birthday,phone,email,dummy,relation FROM classmates";
    for(int i=1;i<relations().size();i++)
    {
        sql+=(" UNION SELECT name,birthday,phone,email,dummy,relation FROM "+relations()[i]);
    }
    sql+=") ORDER BY name ASC";
    AllModel->setQuery(sql);
    ui->allTable->setModel(AllModel);
    for(int i=0;i<relations().size();i++)
    {
        CategoryModels[i]->setSort(1,Qt::AscendingOrder);
        CategoryModels[i]->select();
        CategoryTables[i]->setModel(CategoryModels[i]);
    }
    ui->hintlabel->setText("已按照姓名升序排列(A-Z)");
}

void withMenu::on_action_12_triggered()
{
    QString sql="(SELECT name,birthday,phone,email,dummy,relation FROM classmates";
    for(int i=1;i<relations().size();i++)
    {
        sql+=(" UNION SELECT name,birthday,phone,email,dummy,relation FROM "+relations()[i]);
    }
    sql+=") ORDER BY name DESC";
    AllModel->setQuery(sql);
    ui->allTable->setModel(AllModel);
    for(int i=0;i<relations().size();i++)
    {
        CategoryModels[i]->setSort(1,Qt::DescendingOrder);
        CategoryModels[i]->select();
        CategoryTables[i]->setModel(CategoryModels[i]);
    }
    ui->hintlabel->setText("已按照姓名降序排列(Z-A)");
}

void withMenu::on_action_8_triggered()
{
    QString sql="(SELECT name,birthday,phone,email,dummy,relation FROM classmates";
    for(int i=1;i<relations().size();i++)
    {
        sql+=(" UNION SELECT name,birthday,phone,email,dummy,relation FROM "+relations()[i]);
    }
    sql+=") ORDER BY birthday DESC";
    AllModel->setQuery(sql);
    ui->allTable->setModel(AllModel);
    for(int i=0;i<relations().size();i++)
    {
        CategoryModels[i]->setSort(4,Qt::DescendingOrder);
        CategoryModels[i]->select();
        CategoryTables[i]->setModel(CategoryModels[i]);
    }
    ui->hintlabel->setText("已按照出生日期降序排列(从晚到早)");
}

void withMenu::on_action_9_triggered()
{
    QString sql="(SELECT name,birthday,phone,email,dummy,relation FROM classmates";
    for(int i=1;i<relations().size();i++)
    {
        sql+=(" UNION SELECT name,birthday,phone,email,dummy,relation FROM "+relations()[i]);
    }
    sql+=") ORDER BY birthday ASC";
    AllModel->setQuery(sql);
    ui->allTable->setModel(AllModel);
    for(int i=0;i<relations().size();i++)
    {
        CategoryModels[i]->setSort(4,Qt::AscendingOrder);
        CategoryModels[i]->select();
        CategoryTables[i]->setModel(CategoryModels[i]);
    }
    ui->hintlabel->setText("已按照出生日期升序排列(从早到晚)");
}

void withMenu::receiveMonth(int month)
{
    if(month==0)
        monthDialog->close();
    else
    {
        monthDialog->close();
        QString sql="SELECT name,birthday,phone,email,dummy,relation FROM classmates WHERE MONTH(birthday)="+QString::number(month);
        for(int i=1;i<relations().size();i++)
        {
            sql+=(" UNION SELECT name,birthday,phone,email,dummy,relation FROM "+relations()[i]+" WHERE MONTH(birthday)="+QString::number(month));
        }
        AllModel->setQuery(sql);
        ui->allTable->setModel(AllModel);
        for(int i=0;i<relations().size();i++)
        {
            CategoryModels[i]->setFilter(tr("MONTH(birthday)='%1'").arg(QString::number(month)));
            CategoryModels[i]->select();
            CategoryTables[i]->setModel(CategoryModels[i]);
        }
        QMessageBox::information(this,"成功","找到"+QString::number(AllModel->rowCount())+"个结果，总表和各分类列表显示结果已更新");
        ui->toolBox->setCurrentIndex(0);
    }
}

void withMenu::on_actionh_triggered()
{
    monthDialog=new CountByMonth(this);
    connect(monthDialog,SIGNAL(sendMonth(int)),this,SLOT(receiveMonth(int)));
    monthDialog->show();
}
