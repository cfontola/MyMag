#include "userdataview.h"
#include "ui_userdataview.h"
#include <QErrorMessage>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDebug>
userDataView::userDataView(User* u,Database* db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userDataView),
    user(u),
    DB(db)
{
    ui->setupUi(this);
    item=DB->getItemDb();
    loadData();
    setWindowTitle("Gestione dati utente");
    setFixedSize(this->geometry().width(),this->geometry().height());
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    connect(ui->confirmbtn,SIGNAL(clicked()),this,SLOT(Confirm()));
    connect(ui->deletebtn,SIGNAL(clicked()),this,SLOT(deleteUser()));

}

userDataView::~userDataView()
{
    delete ui;
}

void userDataView::loadData(){
    ui->usn->setText(user->getUsername());
    ui->name->setText(user->getName());
    ui->surname->setText(user->getSurname());
    if(user->getSex()=="Maschio") ui->radioM->setChecked(true);
    if(user->getSex()=="Femmina") ui->radioF->setChecked(true);
}

void userDataView::Cancel(){
    emit signalCancel();
}

void userDataView::Confirm(){
    if(ui->name->text()==""){
        QErrorMessage* error =new QErrorMessage();
        error->showMessage("Campo nome non può rimanere vuoto");
    }

    else if(ui->surname->text()==""){
        QErrorMessage* error =new QErrorMessage();
        error->showMessage("Campo cognome non può rimanere vuoto");
    }
    else{
        QString name = ui->name->text();
        QString surname = ui->surname->text();
        QString sex;
        if(ui->radioM->isChecked()) sex="Maschio";
        if(ui->radioF->isChecked()) sex="Femmina";

        if(user->Type()=="Manager"){
            User* u = const_cast<User*>(DB->findUser(user->getUsername()));
            u->setName(name);
            u->setSurname(surname);
            u->setSex(sex);
        }


        emit signalConfirm();
    }

}

void userDataView::deleteUser(){
    QMessageBox::StandardButton question;
    question=QMessageBox::question(this,"Elimina utente","Eliminare utente? ATTENZIONE verranno anche eliminati gli oggetti ad esso associati",QMessageBox::Yes|QMessageBox::No);
    if(question==QMessageBox::Yes){
        User* u = const_cast<User*>(DB->findUser(user->getUsername()));
        for(auto it=item.begin(); it!=item.end(); ++it){ //elimino tutti gli oggetti associati all'user rimosso
            if(item[it]->getUser()==u->getUsername()){
                DB->deleteItem(item[it]->getId());
            }
        }
        DB->deleteUser(u);
    }
    DB->saveItemDb();
    DB->saveUserDb();
    this->close();
    emit signalCancel();
}


