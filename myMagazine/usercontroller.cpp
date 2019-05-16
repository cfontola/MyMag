#include "usercontroller.h"

userController::userController(User* u,QObject *parent) : QObject(parent), user(u) {}
userController::~userController() {}

void userController::openUserView() const{
     user->openUI(user);
     connect(user,SIGNAL(signalLogout()),this,SLOT(Logout()));
}
void userController::Logout(){
    emit signalLogout();
}
