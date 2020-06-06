#include "editwindow.h"
#include "ui_editwindow.h"
#include"database.h"
#include"QSqlTableModel"
#include"QTableView"
#include"readonlydelegate.h"
#include"genderdelegate.h"
#include"numberdelegate.h"
#include"nonemptydelegate.h"
#include"emailformatdelegate.h"

EditWindow::EditWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
    setWindowTitle("Edit");
    defaultfont.setPointSize(10);
    defaultfont.setFamily("微软雅黑");
    setFont(defaultfont);

    readOnly=new ReadOnlyDelegate();
    genderOnly=new genderDelegate();
    ageLimit=new numberDelegate(1,200);
    phoneLimit=new numberDelegate(1,2147483647);
    nonEmpty=new nonEmptyDelegate();
    emailCheck=new emailFormatDelegate();

    relations<<"classmates"<<"friends"<<"colleagues"<<"relatives"<<"teachers"<<"superiors"<<"clients"<<"others";
    tables<<ui->classmatesTable<<ui->friendsTable<<ui->colleaguesTable<<ui->relativesTable<<ui->teachersTable<<ui->superiorsTable
         <<ui->clientsTable<<ui->othersTable;
    models<<classmatesModel<<friendsModel<<colleaguesModel<<relativesModel<<teachersModel<<superiorsModel<<clientsModel<<othersModel;
}

QSqlTableModel* EditWindow::initializeModel(QSqlTableModel *model, QString relation)
{
    model=new QSqlTableModel(this);
    model->setTable(relation);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
    return model;
}

QTableView* EditWindow::initializeTable(QTableView *table,QSqlTableModel *model)
{
    table->setModel(model);
    table->setColumnHidden(0,true);
    table->setItemDelegateForColumn(1,readOnly);
    table->setItemDelegateForColumn(2,ageLimit);
    table->setItemDelegateForColumn(3,genderOnly);
    table->setItemDelegateForColumn(4,readOnly);
    table->setItemDelegateForColumn(5,emailCheck);
    table->setItemDelegateForColumn(6,phoneLimit);
    for(int i=7;i<model->columnCount()-2;i++)
        table->setItemDelegateForColumn(i,nonEmpty);
    table->setItemDelegateForColumn(model->columnCount()-1,readOnly);
    return table;
}

void EditWindow::TableModelInitializer()
{
    for(int i=0;i<relations.size();i++)
    {
        models[i]=initializeModel(models[i],relations[i]);
    }

    for(int i=0;i<relations.size();i++)
    {
        tables[i]=initializeTable(tables[i],models[i]);
    }
}

void EditWindow::refreshTable(QTableView *table, QSqlTableModel *model)
{
    model->select();
    table->setModel(model);
    return;
}

EditWindow::~EditWindow()
{
    delete ui;
}

void EditWindow::on_commitButton_clicked()
{
    for(int i=0;i<relations.size();i++)
    {
        models[i]->database().transaction();
        if (models[i]->submitAll())
        {
            models[i]->database().commit();
            ui->hintlabel->setText("Seccessfally committed!");
//            refreshTable(tables[i],models[i]);
        }
        else
        {
            models[i]->database().rollback();
            QMessageBox::critical(this,"Error","Commit failed!");
            return;
        }
    }
}

void EditWindow::on_withdrawButtion_clicked()
{
    for(int i=0;i<relations.size();i++)
    {
        models[i]->revertAll();
        tables[i]->setModel(models[i]);
    }
}
