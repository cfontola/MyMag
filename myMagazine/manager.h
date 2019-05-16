#ifndef MANAGER_H
#define MANAGER_H

#include <managerview.h>
#include <QString>
#include "user.h"


class Manager:public User
{
private:
    managerView* managerUI;

public:
    Manager(const QString& usn, const QString& psw, const QString& nm, const QString& sur, const QString& sx);
    //...IMPLEMENTAZIONE METODI VIRTUALI PURI DELLA CLASSE USER...

    virtual void writeUser(QXmlStreamWriter& xmlWriter) const;
    virtual void openUI(User* u);
    virtual const QString Type() const;
public slots:
    virtual void Logout();
};

#endif // MANAGER_H


