#ifndef ADMIN_H
#define ADMIN_H

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <iostream>
#include <QFile>
#include "adminview.h"
#include "container.h"
#include "user.h"


class Admin : public User{
private:
    adminView* adminUI;
public:
    Admin(const QString& usn,const QString& psw, const QString& nm, const QString& sur, const QString& sx);

    //metodi virtuali puri
    virtual void writeUser(QXmlStreamWriter& xmlWriter) const;
    virtual void openUI(User* u);
    virtual const QString Type() const;
    virtual void Logout();
};

#endif // ADMIN_H
