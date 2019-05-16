#include "admincontroller.h"

adminController::adminController(Admin* a,QObject* parent): QObject(parent),admin(a),adminUI(0)
{}

adminController::~adminController() {if(adminUI) delete adminUI;}

void adminController::openAdminView(){

    adminUI=new adminView(admin);
    connect(adminUI,SIGNAL(signalLogout()),this,SLOT(Logout()));
    adminUI->show();
}

void adminController::Logout(){
    emit signalLogout();
}
