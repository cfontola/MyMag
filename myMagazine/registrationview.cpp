#include "registrationview.h"
#include "ui_registrationview.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <iostream>

registrationView::registrationView(Database* db,QWidget *parent) :
    QWidget(parent),
    DB(db),
    ui(new Ui::registrationView)
{
    ui->setupUi(this);
    setGraphic();
    setFixedSize(this->geometry().width(),this->geometry().height());
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
}

registrationView::~registrationView()
{
    delete ui;
}

void registrationView::setGraphic(){
    setWindowTitle("Registrazione utente - myMagazine");
    ui->passEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPassword->setEchoMode(QLineEdit::Password);

    connect(ui->cancelbtn,SIGNAL(clicked()),this,SLOT(closeRegistration()));
    connect(ui->confirmbtn,SIGNAL(clicked()),this,SLOT(tryRegistration()));
}

//---SLOTS---
void registrationView::closeRegistration(){
    emit signalGoLogin();
}

void registrationView::tryRegistration(){

    QString sex="";
    if(ui->radioM->isChecked()) sex="Maschio";
    if(ui->radioF->isChecked()) sex="Femmina";
    QString type;
    if(ui->TypeBox->isChecked()){type="admin";}
    else{type="manager";}



    if(ui->Username->text()==""){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Campo username vuoto!");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else if(DB->matchUser(ui->Username->text()) || ui->Username->text() == "admin"){  //username non disponibile
        QMessageBox* msg =new QMessageBox();
        msg->setText("Username non disponibile.");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else if(ui->passEdit->text()==""){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Campo password vuoto.");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else if(ui->passEdit->text().size()<5){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Password troppo corta! Deve essere lunga almeno 5 caratteri");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else if(ui->confirmPassword->text()==""){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Campo conferma password vuoto!");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else if(ui->confirmPassword->text()!=ui->passEdit->text()){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Password devono coincidere!");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else if(ui->nomeLineEdit->text()==""){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Inserisci nome!");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else if(ui->cognomeLineEdit->text()==""){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Inserisci cognome!");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
    else
        emit signalRegistration(ui->Username->text(),ui->passEdit->text(), ui->nomeLineEdit->text(),ui->cognomeLineEdit->text(),sex, type);

}
