#ifndef MYMAGAZINECONTROLLER_H
#define MYMAGAZINECONTROLLER_H

#include <QMessageBox>
#include "database.h"
#include "loginview.h"
#include "usercontroller.h"
#include "admincontroller.h"

class myMagazineController: public QObject
{
    Q_OBJECT
private:
    Database* DB;
    loginView* startUI;
    adminController* aController;
    userController* uController;

public:
    myMagazineController(Database*,loginView* =0, adminController* =0,userController* =0,QObject* =0);
    ~myMagazineController();

public slots:

    void openLoginView();

    void verifyuserLogin(const QString& usn,const QString& psw);

};

#endif // MYMAGAZINECONTROLLER_H

