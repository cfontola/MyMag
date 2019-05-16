#ifndef USER_H
#define USER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <iostream>

//ABSTRACT CLASS USER
class User:public QObject {
    Q_OBJECT
private:
    QString username;
    QString password;
    QString name;
    QString surname;
    QString sex;

public:
    User(const QString& usn, const QString& psw, const QString& nm, const QString& sur, const QString& sx,QObject *parent = 0);
    virtual ~User();

    const QString& getUsername() const;
    const QString& getPsw() const;
    const QString& getName() const;
    const QString& getSurname() const;
    const QString& getSex() const;

    void setUsername(const QString& );
    void setPsw(const QString& );
    void setName(const QString& );
    void setSurname(const QString& );
    void setSex(const QString& );

    //-----------altri metodi----------

    bool verifyUser(const QString&) const;

    //-----metodi virtuali puri-----

    virtual void openUI(User* u)  =0;
    virtual void writeUser(QXmlStreamWriter& xmlWriter) const =0;
    virtual const QString Type() const =0;
public slots:
    virtual void Logout() =0;
signals:
    void signalLogout();

};

#endif // USER_H
