#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QString>
#include <iostream>
#include "notebook.h"
#include "smartphone.h"
#include "smartwatch.h"
#include "container.h"
#include "user.h"

class Database{
private:
    Container<const User*> userDatabase;
    Container<const Item*> itemDatabase;
public:
    Database();
    ~Database();

    Container<const User*> getUserDb() const;
    Container<const Item*> getItemDb() const;

    Container<const Item*> getNotebook() const;
    Container<const Item*> getSmartphone() const;
    Container<const Item*> getSmartwatch() const;


    bool matchUser(const QString& ) const;  //true sse matcha un username nel db utenti
    bool verifyUser(const QString& usn,const QString& psw) const; //true sse username e password presenti associati nel db

    void addUser(const User* );
    void deleteUser(const User* );

    void addItem(const Item*);
    void deleteItem(const QString&);


    const User* findUser(const QString& usn) const;
    const User* getUser(const QString& , const QString& ) const; //ritorna ptn all'utente verificato

    const Item* findItem(const QString& id) const;

    void loadUserDb();
    void loadItemDb();

    void emptyUserDb();
    void emptyItemDb();

    void saveUserDb();
    void saveItemDb();
};


#endif // DATABASE_H
