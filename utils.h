#ifndef UTILS_H
#define UTILS_H
#include"QString"
#include"QStringList"
#include"QTableView"
#include"QList"

int countCharacter(QString str,QString ch);

QStringList relations();

void setReadOnly(QTableView* table,QList<int>*idx=nullptr);

#endif // UTILS_H
