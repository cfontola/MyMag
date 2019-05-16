#include "database.h"
#include "manager.h"
#include "admin.h"
#include <QDebug>


//---COSTRUTTORE---

Database::Database() {}


Database::~Database(){
    //svuoto entrambi i database
    emptyUserDb();
    emptyItemDb();
}

//-------------------------METODI----------------------

Container<const User*> Database::getUserDb() const{
    return userDatabase;
}
Container<const Item*> Database::getItemDb() const{
    return itemDatabase;
}

Container<const Item*> Database::getNotebook() const{
    Container<const Item*> notebook;
    Container<const Item*>::Iterator it = itemDatabase.begin();
    for(; it!= itemDatabase.end(); ++it){
        if(dynamic_cast<const Notebook*>(*it)){
            notebook.push_back(*it);
        }
    }
    return notebook;
}
Container<const Item*> Database::getSmartphone() const{
    Container<const Item*> smartphone;
    Container<const Item*>::Iterator it = itemDatabase.begin();
    for(; it!= itemDatabase.end(); ++it){
        if(dynamic_cast<const Smartphone*>(*it)){
            smartphone.push_back(*it);
        }
    }
    return smartphone;
}

Container<const Item*> Database::getSmartwatch() const{
    Container<const Item*> smartwatch;
    Container<const Item*>::Iterator it=itemDatabase.begin();
    for(; it!= itemDatabase.end(); ++it){
        if(dynamic_cast<const Smartwatch*>(*it)){
            smartwatch.push_back(*it);
        }
    }
    return smartwatch;
}

bool Database::matchUser(const QString& usn) const{
    for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
        if(userDatabase[it]->getUsername()==usn)
            return true;
    return false;
}

bool Database::verifyUser(const QString& usn, const QString& psw) const{
    for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
        if(userDatabase[it]->getUsername()==usn && userDatabase[it]->getPsw()==psw)
            return true;
    return false;
}


void Database::addUser(const User* u) {
    if(!getUser(u->getUsername(),u->getPsw()))
        userDatabase.push_back(u);
}

void Database::deleteUser(const User* u){
    if(getUser(u->getUsername(),u->getPsw()))
        userDatabase.pop_element(u);
}

void Database::addItem(const Item* a){
    if(!findItem(a->getId())){
        itemDatabase.push_back(a);
    }
}

void Database::deleteItem(const QString& c){
    if(findItem(c))
        itemDatabase.pop_element(findItem(c));
}

const User* Database::findUser(const QString& usn) const{
    if(!userDatabase.isEmpty()){
        for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
            if(userDatabase[it]->getUsername()==usn)
                return userDatabase[it];
    }
    return 0;
}

const Item* Database::findItem(const QString& id) const{
    if(!itemDatabase.isEmpty()){
        for(Container<const Item*>::Iterator it=itemDatabase.begin(); it!=itemDatabase.end();++it)
            if(itemDatabase[it]->getId() == id)
                return itemDatabase[it];
    }
    return 0;
}

const User* Database::getUser(const QString& usn, const QString& psw) const {
    for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
        if(userDatabase[it]->getUsername()==usn && userDatabase[it]->getPsw()==psw)
            return userDatabase[it];
    return 0;
}

void Database::emptyUserDb(){
    while(!userDatabase.isEmpty()){
        userDatabase.pop_front();
    }
}

void Database::emptyItemDb(){
    while(!itemDatabase.isEmpty()){
        itemDatabase.pop_front();
    }
}

//----LOAD E SAVE USER----

void Database::loadUserDb(){

    QString username;
    QString password;
    QString name;
    QString surname;
    QString sex;

    bool file=true;

    QFile UserFile("C:/Users/Carlo/Desktop/myMagazine/db/userDatabase.xml");
    if(!UserFile.open(QFile::ReadOnly | QFile::Text)){
        std::cout<<"Users database not found, load failed!"<<std::endl;
        file=false;
    }

    if(file){

    QXmlStreamReader xmlReader(&UserFile);
    xmlReader.readNext();

    while(!xmlReader.atEnd()){
        if(xmlReader.isStartElement()){
            if(xmlReader.name()=="database" || xmlReader.name()=="manager" || xmlReader.name()=="admin")
                xmlReader.readNext();
            else if(xmlReader.name()=="username")
                username=xmlReader.readElementText();
            else if(xmlReader.name()=="password")
                password=xmlReader.readElementText();
            else if(xmlReader.name()=="nome")
                name=xmlReader.readElementText();
            else if(xmlReader.name()=="cognome")
                surname=xmlReader.readElementText();
            else if(xmlReader.name()=="sesso")
                sex=xmlReader.readElementText();
        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="manager"){    // </manager>
            Manager* manager=new Manager(username,password,name,surname,sex);
            userDatabase.push_back(manager);
            xmlReader.readNext();
        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="admin"){    // </admin>
            Admin* admin=new Admin(username,password,name,surname,sex);
            userDatabase.push_back(admin);
            xmlReader.readNext();
        }
        else
            xmlReader.readNext();
    }
    std::cout<<"Users db loaded"<<std::endl;

    UserFile.close();
    }
}

void Database::loadItemDb(){

    //----item----
    QString user;
    QString id;
    QString brand;
    QString processor;
    QString model;
    double display;     // display in pollici
    double price;       //prezzo in euro
    unsigned int memory;         // memoria in Gb


    //----notebook----
    bool backlight;  //true sse tastiera retroilluminata
    bool fanless;  //true se non sono presenti ventole
    QString GPU; //modello GPU montata su notebook

    //----smartphone----
    bool fingerprint; //true sse smartphone ha sensore impronte
    unsigned int camera1; //megapixel camera1
    unsigned int camera2; //megapixel camera2

    //---smartwatch-----
    QString sensor;
    QString certificate;
    //QString MaterialQ;
    QString MaterialC;

    QFile ItemFile("C:/Users/Carlo/Desktop/myMagazine/db/itemDatabase.xml");
    bool file=true;

    if(!ItemFile.open(QFile::ReadOnly | QFile::Text)){
        std::cout<<"Item database not found, load failed!"<<std::endl;
        file=false;
    }

    QXmlStreamReader xmlReader(&ItemFile); //Creates a new stream reader that reads from device.
    xmlReader.readNext();

    if(file){
    while(!xmlReader.atEnd()){
        if(xmlReader.isStartElement()){ //lettura dei tag aperti <namespaceURI>

            if(xmlReader.name()=="item" || xmlReader.name()=="Notebook" || xmlReader.name()=="Smartphone" ||xmlReader.name()=="Smartwatch")
                xmlReader.readNext();
            else if(xmlReader.name()=="User")
                user=xmlReader.readElementText();
            else if(xmlReader.name()=="Id")
                id=xmlReader.readElementText();
            else if(xmlReader.name()=="Brand")
                brand=xmlReader.readElementText();
            else if(xmlReader.name()=="Processor")
                processor=xmlReader.readElementText();
            else if(xmlReader.name()=="Model")
                model=xmlReader.readElementText();
            else if(xmlReader.name()=="Display")
                display=xmlReader.readElementText().toDouble();
            else if(xmlReader.name()=="Price")
                price=xmlReader.readElementText().toDouble();
            else if(xmlReader.name()=="Memory")
                memory=xmlReader.readElementText().toInt();

            else if(xmlReader.name()=="Backlight")
                backlight=xmlReader.readElementText().toInt();
            else if(xmlReader.name()=="Fanless")
                fanless=xmlReader.readElementText().toInt();
            else if(xmlReader.name()=="GPU")
                GPU=xmlReader.readElementText();

            else if(xmlReader.name()=="FingerPrint")
                fingerprint=xmlReader.readElementText().toInt();
            else if(xmlReader.name()=="Cam1")
                camera1=xmlReader.readElementText().toInt();
            else if(xmlReader.name()=="Cam2")
                camera2=xmlReader.readElementText().toInt();

            else if(xmlReader.name()=="Sensor")
                sensor=xmlReader.readElementText();
            else if(xmlReader.name()=="Certificate")
                certificate=xmlReader.readElementText();
            else if(xmlReader.name()=="Material_C")
                MaterialC=xmlReader.readElementText();

        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="Notebook"){
            Notebook* notebook=new Notebook(user,id,brand,processor,model,display,price,memory,backlight,fanless,GPU);



            itemDatabase.push_back(notebook);
            xmlReader.readNext();
        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="Smartphone"){
            Smartphone* smartphone=new Smartphone(user,id,brand,processor,model,display,price,memory,fingerprint,camera1,camera2);

            itemDatabase.push_back(smartphone);
            xmlReader.readNext();
        }
        else if(xmlReader.isEndElement() && xmlReader.name()=="Smartwatch"){
            Smartwatch* smartwatch=new Smartwatch(user,id,brand,processor,model,display,price,memory,sensor,certificate,MaterialC);

            itemDatabase.push_back(smartwatch);
            xmlReader.readNext();
        }

        else
            xmlReader.readNext();
    }
    std::cout<<"Item db loaded"<<std::endl;

    ItemFile.close();
    }
}

void Database::saveUserDb(){
    QFile userFile("C:/Users/Carlo/Desktop/myMagazine/db/userDatabase.xml");
    bool file=true;

    if(!userFile.open(QIODevice::WriteOnly)){
        std::cout<<"Users database not found"<<std::endl;
        file=false;
    }

    if(file){
    QXmlStreamWriter xmlWriter(&userFile);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("database");

    if(!userDatabase.isEmpty())
        for(Container<const User*>::Iterator it=userDatabase.begin(); it!=userDatabase.end(); ++it)
           userDatabase[it]->writeUser(xmlWriter);

    xmlWriter.writeEndDocument();

    std::cout<<"Users db saved"<<std::endl;
    userFile.close();
    }
}

void Database::saveItemDb(){
    QFile animalFile("C:/Users/Carlo/Desktop/myMagazine/db/itemDatabase.xml");
    bool file=true;

    if(!animalFile.open(QIODevice::WriteOnly)){
        std::cout<<"Item database not found"<<std::endl;
        file=false;
    }

    if(file){
    QXmlStreamWriter xmlWriter(&animalFile);

    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("item");

    if(!itemDatabase.isEmpty())
        for(Container<const Item*>::Iterator it=itemDatabase.begin(); it!=itemDatabase.end(); ++it)
            itemDatabase[it]->SaveItem(xmlWriter);

    xmlWriter.writeEndDocument();

    std::cout<<"Item db saved"<<std::endl;
    animalFile.close();
    }
}

