#include "utils.h"
#include"QString"


int countCharacter(QString str, QString ch)
{
    int r=0;
    for(int i=0;i<str.size();i++)
        r=(str[i]==ch)?(r+1):r;
    return r;
}

QStringList relations()
{
    QStringList rlt;
    rlt<<"classmates"<<"friends"<<"colleagues"<<"relatives"<<"teachers"<<"superiors"<<"clients"<<"others";
    return rlt;
}
