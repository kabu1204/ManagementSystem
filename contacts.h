#ifndef CONTACTS_H
#define CONTACTS_H
#include <QString>
#include<iostream>
using namespace std;

//基类
class contacts              //使用QString不用担心内存分配的问题，还提供了许多方便的函数。
{
    QString name;
    unsigned int age;      //便于自增。
    QString gender;
    QString birthday;
    QString email;
    QString phone;
    QString remarks;
public:
    contacts(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_);
    ~contacts();
};

#endif // CONTACTS_H
//###########################第二层########################
class familiar:public contacts
{

public:
    familiar(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_);
};

class unfamiliar:public contacts
{
public:
    unfamiliar(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_);
};
//###########################第三层########################
class classmates:public familiar
{
    QString school;
public:
    classmates(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString school_);
};
class teachers:public familiar
{
    QString school;
    QString course;
public:
    teachers(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString school_,QString course_);
};
class colleagues:public familiar
{
    QString company;
public:
    colleagues(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString company_);
};
class relatives:public familiar
{
    QString call;
public:
    relatives(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString call_);
};
//###################################################################################
class superiors:public unfamiliar
{
    QString company;
    QString post;
public:
    superiors(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString company_,QString post_);
};
class clients:public unfamiliar
{
    QString company;
public:
    clients(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString company_);
};
class others:public unfamiliar
{
public:
    others(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_);
};
