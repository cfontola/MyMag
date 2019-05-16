#include "user.h"

//-------------------------COSTRUTTORI------------------------

User::User(const QString& usn, const QString& psw, const QString& nm, const QString& sur, const QString& sx,QObject *parent):
        QObject(parent),username(usn), password(psw), name(nm), surname(sur), sex(sx) {}

User::~User() {}

//-------------------------GET------------------------

const QString& User::getUsername() const {return username;}
const QString& User::getPsw() const {return password;}
const QString& User::getName() const {return name;}
const QString& User::getSurname() const {return surname;}
const QString& User::getSex() const {return sex;}

//-------------------------SET------------------------

void User::setUsername(const QString& usn) {username=usn;}
void User::setPsw(const QString& psw) {password=psw;}
void User::setName(const QString& n) {name=n;}
void User::setSurname(const QString& sn) {surname=sn;}
void User::setSex(const QString& s) {sex=s;}

//-------------------------ALTRI METODI------------------------


bool User::verifyUser(const QString& usn) const{
    return (username==usn);
}



