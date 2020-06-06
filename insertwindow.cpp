#include "insertwindow.h"
#include "ui_insertwindow.h"
#include"QDebug"
#include"QStringList"
#include"database.h"
InsertWindow::InsertWindow(Database *db_,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertWindow)
{
    ui->setupUi(this);
    db=db_;
    setFixedSize(814,382);
    setWindowTitle("Insert");
    labelfont.setPointSize(12);
    labelfont.setFamily("微软雅黑");
    setFont(labelfont);

    labelfont.setPointSize(10);
    ui->placeIn->setFont(labelfont);
    ui->relationCombo->setFont(labelfont);
    labelfont.setPointSize(9);
    ui->emailIn->setFont(labelfont);

    //年龄、电话只能输入数字
    QRegExp regexp("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regexp);
    ui->ageIn->setValidator(validator);
    ui->phoneIn->setValidator(validator);

    extraBoxDefault();
}

InsertWindow::~InsertWindow()
{
    delete ui;
}

void InsertWindow::extraBoxDefault()
{
    ui->schoolIn->setEnabled(false);
    ui->courseIn->setEnabled(false);
    ui->companyIn->setEnabled(false);
    ui->postIn->setEnabled(false);
    ui->callIn->setEnabled(false);
    ui->placeIn->setEnabled(false);
}

void InsertWindow::raiseError(int errCode)
{
    if(errCode==-1) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":Please select the relation!");
    if(errCode==1) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Name\" cannot be empty!");
    if(errCode==2) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Age\" cannot be empty!");
    if(errCode==3) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Gender\" cannot be empty!");
    if(errCode==4) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Birthday\" cannot be empty!");
    if(errCode==5) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Email\" cannot be empty!");
    if(errCode==6) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Phone\" cannot be empty!");
    if(errCode==7) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"School\" cannot be empty!");
    if(errCode==8) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Course\" cannot be empty!");
    if(errCode==9) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Company\" cannot be empty!");
    if(errCode==10) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Post\" cannot be empty!");
    if(errCode==11) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Call\" cannot be empty!");
    if(errCode==12) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":\"Place\" cannot be empty!");
    if(errCode==13) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":Age must be positive!");
    if(errCode==14) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":Phone number must be positive");
    if(errCode==15) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":Birthday must be earlier than today!");
    if(errCode==16) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":The format of the email address is wrong!");
    if(errCode==17) QMessageBox::critical(this,"Error","Insert failed! Error "+QString::number(errCode)+":Age cannot be larger than 200!");
}

void InsertWindow::on_relationCombo_currentIndexChanged(int idx)
{
    extraBoxDefault();
    switch(idx)
    {
    case 1:
        ui->schoolIn->setEnabled(true);
        return;
    case 2:
        ui->placeIn->setEnabled(true);
        return;
    case 3:
        ui->companyIn->setEnabled(true);
        return;
    case 4:
        ui->callIn->setEnabled(true);
        return;
    case 5:
        ui->courseIn->setEnabled(true);
        ui->schoolIn->setEnabled(true);
        return;
    case 6:
        ui->companyIn->setEnabled(true);
        ui->postIn->setEnabled(true);
        return;
    case 7:
        ui->companyIn->setEnabled(true);
        return;
    case 8:
        return;
    }
}

void InsertWindow::on_insertButton_clicked()
{
    QString relation=ui->relationCombo->currentText();
    QStringList basic,extra;
    basic<<ui->nameIn->text()<<ui->ageIn->text()<<ui->genderBox->currentText()<<ui->birthdayIn->date().toString("yyyy-MM-dd")
        <<ui->emailIn->text()<<ui->phoneIn->text();
    extra<<(ui->schoolIn->isEnabled()?ui->schoolIn->text():"Unabled")<<(ui->courseIn->isEnabled()?ui->courseIn->text():"Unabled")
        <<(ui->companyIn->isEnabled()?ui->companyIn->text():"Unabled")<<(ui->postIn->isEnabled()?ui->postIn->text():"Unabled")
       <<(ui->callIn->isEnabled()?ui->callIn->text():"Unabled")<<(ui->placeIn->isEnabled()?ui->placeIn->text():"Unabled")
      <<ui->remarkIn->toPlainText();
    int errCode=Database::insertion_check_fix(relation,basic,extra);
    if(errCode==0) db->insert(relation,basic,extra);
    else raiseError(errCode);
}
