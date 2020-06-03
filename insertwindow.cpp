#include "insertwindow.h"
#include "ui_insertwindow.h"
#include"QDebug"

InsertWindow::InsertWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertWindow)
{
    ui->setupUi(this);
    setWindowTitle("Insert");
    labelfont.setPointSize(12);
    labelfont.setFamily("微软雅黑");
    setFont(labelfont);
//    ui->basicBox->setFont(labelfont);
//    ui->extraBox->setFont(labelfont);
//    ui->remarkBox->setFont(labelfont);
//    ui->relationlabel->setFont(labelfont);
//    ui->namelabel->setFont(labelfont);
//    ui->agelabel->setFont(labelfont);
//    ui->genderlabel->setFont(labelfont);
//    ui->birthdaylabel->setFont(labelfont);
//    ui->emaillabel->setFont(labelfont);
//    ui->phonelabel->setFont(labelfont);
//    ui->nameIn->setFont(labelfont);
//    ui->ageIn->setFont(labelfont);
//    ui->genderBox->setFont(labelfont);
//    ui->birthdayIn->setFont(labelfont);
//    ui->phoneIn->setFont(labelfont);
    labelfont.setPointSize(10);
    ui->placeIn->setFont(labelfont);
    ui->relationCombo->setFont(labelfont);
    labelfont.setPointSize(9);
    ui->emailIn->setFont(labelfont);

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
