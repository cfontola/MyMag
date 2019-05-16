#include "mymagazinecontroller.h"

myMagazineController::myMagazineController(Database* db, loginView* lv, adminController* aC,userController* uC,QObject* parent) : QObject(parent), DB(db), startUI(lv), aController(aC),uController(uC)
{
   startUI->show();
   connect(startUI,SIGNAL(signaluserLogin(const QString& ,const QString& )),this,SLOT(verifyuserLogin(const QString& ,const QString& )));
   DB->loadUserDb();
}

myMagazineController::~myMagazineController(){DB->emptyUserDb();}


void myMagazineController::openLoginView(){
    if(uController){
        delete uController;
        uController=0;
    }
    if(aController){
        delete aController;
        aController=0;
    }
    startUI->getUusn()->clear();
    startUI->getUpass()->clear();
    startUI->show();
}

//--------VERIFY
void myMagazineController::verifyuserLogin(const QString& usn, const QString& psw){
    DB->loadUserDb();
    if(DB->verifyUser(usn,psw)){
        if(dynamic_cast<const Admin*>(DB->getUser(usn,psw))){
            aController=new adminController(dynamic_cast<Admin*>(const_cast<User*>(DB->getUser(usn,psw))));
            if(aController){
                startUI->hide();
                aController->openAdminView();
                connect(aController,SIGNAL(signalLogout()),this,SLOT(openLoginView()));
            }
        }
        else{
            uController = new userController(const_cast<User*>(DB->getUser(usn,psw)));
            if(uController){
                startUI->hide();
                uController->openUserView();
                connect(uController,SIGNAL(signalLogout()),this,SLOT(openLoginView()));
            }
        }
    }
    else{
        QMessageBox* msg = new QMessageBox();
        msg->setText("Username o Password errati.");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
}





