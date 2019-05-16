#include "manager.h"
//#include "database.h"

Manager::Manager(const QString& usn, const QString& psw, const QString& nm, const QString& sur, const QString& sx):
    User(usn,psw,nm,sur,sx) {}

void Manager::openUI(User* u) {
    managerUI = new managerView(u);
    connect(managerUI,SIGNAL(signalLogout()),this,SLOT(Logout()));
    managerUI->show();
}

void Manager::writeUser(QXmlStreamWriter& xmlWriter) const{
    xmlWriter.writeStartElement("manager");
        xmlWriter.writeTextElement("username",getUsername());
        xmlWriter.writeTextElement("password",getPsw());
        xmlWriter.writeTextElement("nome",getName());
        xmlWriter.writeTextElement("cognome",getSurname());
        xmlWriter.writeTextElement("sesso",getSex());
    xmlWriter.writeEndElement();
}

const QString Manager::Type() const {return "Manager";}

void Manager::Logout(){
    if(managerUI) {
        managerUI->hide();
        delete managerUI;
        managerUI=0;
    }
    emit signalLogout();
}


