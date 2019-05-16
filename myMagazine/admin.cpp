#include "admin.h"


Admin::Admin(const QString& usn,const QString& psw, const QString& nm, const QString& sur, const QString& sx):
    User(usn,psw,nm,sur,sx) {}


void Admin::openUI(User *u) {
    adminUI=new adminView(u);
    connect(adminUI,SIGNAL(signalLogout()),this,SLOT(Logout()));
    adminUI->show();
}


void Admin::writeUser(QXmlStreamWriter &xmlWriter) const{ //override del metodo virtuale puro della classe User
    xmlWriter.writeStartElement("admin");
        xmlWriter.writeTextElement("username",getUsername());
        xmlWriter.writeTextElement("password",getPsw());
        xmlWriter.writeTextElement("nome",getName());
        xmlWriter.writeTextElement("cognome",getSurname());
        xmlWriter.writeTextElement("sesso",getSex());
    xmlWriter.writeEndElement();
}

const QString Admin::Type() const{
    return "Admin";
}

void Admin::Logout(){
    if(adminUI){
        adminUI->hide();
        delete adminUI;
        adminUI=0;
    }
    emit signalLogout();
}
