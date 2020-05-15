#include "contacts.h"
#include "QString"
contacts::contacts(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_):
    name(name_),
    age(age_),
    gender(gender_),
    birthday(birthday_),
    email(email_),
    phone(phone_)
{
}


familiar::familiar(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_):
    contacts (name_, age_, gender_, birthday_, email_, phone_)
{

}
unfamiliar::unfamiliar(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_):
    contacts (name_, age_, gender_, birthday_, email_, phone_)
{

}

classmates::classmates(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString school_):
    familiar(name_, age_, gender_, birthday_, email_, phone_)
{
    school=school_;
}
teachers::teachers(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString school_,QString course_):
    familiar(name_, age_, gender_, birthday_, email_, phone_)
{
    school=school_;
    course=course_;
}
colleagues::colleagues(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString company_):
    familiar(name_, age_, gender_, birthday_, email_, phone_)
{
    company=company_;
}
relatives::relatives(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString call_):
    familiar(name_, age_, gender_, birthday_, email_, phone_)
{
    call=call_;
}
superiors::superiors(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString company_,QString post_):
    unfamiliar(name_, age_, gender_, birthday_, email_, phone_)
{
    company=company_;
    post=post_;
}
clients::clients(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_,QString company_):
    unfamiliar(name_, age_, gender_, birthday_, email_, phone_)
{
    company=company_;
}
others::others(QString name_,unsigned int age_,QString gender_,QString birthday_,QString email_,QString phone_):
    unfamiliar(name_, age_, gender_, birthday_, email_, phone_)
{

}

