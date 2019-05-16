#include "adminview.h"
#include "ui_adminview.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDebug>
#include "manager.h"
#include "admin.h"

adminView::adminView(User*a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminView),
    regUI(0),
    admin(a),
    userDataUI(0),
    addItemUI(0),
    itemDataUI(0),
    DB(0)

{

    ui->setupUi(this);
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    setFixedSize(this->geometry().width(),this->geometry().height());
    setWindowTitle("Admin panel - myMagazine");
    ui->logged->setText("Logged as : " + admin->getUsername());
    connect(ui->usertable,SIGNAL(cellClicked(int,int)),this,SLOT(openUserData(int)));
    connect(ui->itemtable,SIGNAL(cellClicked(int,int)),this,SLOT(openItemData(int)));
    connect(ui->addItem,SIGNAL(clicked()),this,SLOT(addItemData()));
    connect(ui->addUtente,SIGNAL(clicked()),this,SLOT(openRegistrationView()));
    connect(ui->logoutbtn,SIGNAL(clicked()),this,SLOT(Logout()));
    DB=new Database();
    DB->loadUserDb();
    DB->loadItemDb();
    loadUserTable();
    loadItemTable();
    ui->itemtable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->usertable->setSelectionMode(QAbstractItemView::NoSelection);
}

adminView::~adminView()
{
    delete ui;
}

void adminView::loadUserTable(){

    Container<const User*> db = DB->getUserDb();
    Container<const User*>::Iterator it= db.begin();
    int row=0;
    for( ; it!=db.end(); ++it){
        ui->usertable->setRowCount(row+1);
        QTableWidgetItem* usn = new QTableWidgetItem(db[it]->getUsername());
        QTableWidgetItem* name = new QTableWidgetItem(db[it]->getName());
        QTableWidgetItem* surname = new QTableWidgetItem(db[it]->getSurname());
        QTableWidgetItem* type = new QTableWidgetItem(db[it]->Type());


        usn->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        name->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        surname->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        type->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        ui->usertable->setItem(row,0,usn);
        ui->usertable->setItem(row,1,name);
        ui->usertable->setItem(row,2,surname);
        ui->usertable->setItem(row,3,type);

        row++;
    }
}


void adminView::loadItemTable(){
            Container<const Item*> db=DB->getItemDb();
            Container<const Item*>::Iterator it= db.begin();
            int counter =0;
            for(;it!=db.end(); ++it){


                    ui->itemtable->setRowCount(counter+1);
                    QTableWidgetItem* utente= new QTableWidgetItem(item[it]->getUser());
                    QTableWidgetItem* id= new QTableWidgetItem(item[it]->getId());
                    QTableWidgetItem* brand= new QTableWidgetItem(item[it]->getBrand());
                    QTableWidgetItem* type= new QTableWidgetItem(item[it]->type());



                    ui->itemtable->setItem(counter,0,utente);
                    ui->itemtable->setItem(counter,1,id);
                    ui->itemtable->setItem(counter,2,type);
                    ui->itemtable->setItem(counter,3,brand);

                   ;
                    ++counter;


                }
            }
void adminView::openRegistrationView(){
    regUI=new registrationView(DB);
    regUI->show();
    connect(regUI,SIGNAL(signalRegistration(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&)),this,SLOT(userRegistration(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&)));
    connect(regUI,SIGNAL(signalGoLogin()),this,SLOT(closeRegistrationView()));
}

void adminView::userRegistration(const QString& usn, const QString& pass, const QString& nam, const QString& sur, const QString& sx,const QString& ty){

    if(!DB->matchUser(usn)){
        if(ty=="manager") {
            Manager* manager = new Manager(usn,pass,nam,sur,sx);
            DB->addUser(manager);
            QMessageBox* msg=new QMessageBox();
            msg->setText("Utente registrato correttamente");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
        }
        else if(ty=="admin"){
            Admin* admin = new Admin(usn,pass,nam,sur,sx);
            DB->addUser(admin);
            QMessageBox* msg=new QMessageBox();
            msg->setText("Admin registrato correttamente");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
        }
        closeRegistrationView();
        loadUserTable();

    }
    else{
        QMessageBox* msg=new QMessageBox();
        msg->setText("Username già utilizzato. Prova con uno differente.");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }

}

void adminView::closeRegistrationView(){
    if(regUI) {regUI->hide(); delete regUI;}
}

void adminView::openUserData(int row){
  QString usn = ui->usertable->item(row,0)->text();
  User* user = const_cast<User*>(DB->findUser(usn));
  if(userDataUI){
      userDataUI->hide(); delete userDataUI;
      userDataUI = new userDataView(user,DB);
      connect(userDataUI,SIGNAL(signalCancel()),this,SLOT(closeUserData()));
      connect(userDataUI,SIGNAL(signalConfirm()),this,SLOT(closeUserData()));
      userDataUI->show();
  }else{
      userDataUI = new userDataView(user,DB);
      connect(userDataUI,SIGNAL(signalCancel()),this,SLOT(closeUserData()));
      connect(userDataUI,SIGNAL(signalConfirm()),this,SLOT(closeUserData()));
      userDataUI->show();
  }
}

void adminView::openItemData(int row){
  QString id = ui->itemtable->item(row,1)->text();
  Item*itemx=const_cast<Item*>(DB->findItem(id));
  if(itemDataUI){
      itemDataUI->hide(); delete itemDataUI;
      itemDataUI = new itemDataView(itemx,DB);
      connect(itemDataUI,SIGNAL(signaldeleteItem()),this,SLOT(closeItemData()));
      connect(itemDataUI,SIGNAL(signalSave()),this,SLOT(closeItemData()));
      itemDataUI->show();

  }
  else{
      itemDataUI = new itemDataView(itemx,DB);
      connect(itemDataUI,SIGNAL(signaldeleteItem()),this,SLOT(closeItemData()));
      connect(itemDataUI,SIGNAL(signalSave()),this,SLOT(closeItemData()));
      itemDataUI->show();
  }
}

void adminView::closeUserData(){

    if(userDataUI) {
        userDataUI->hide();
        delete userDataUI;
        userDataUI=0;
    }
    loadUserTable();
    loadItemTable();

}

void adminView::closeItemData(){
    if(itemDataUI) {
        itemDataUI->hide();
        delete itemDataUI;
        itemDataUI=0;
    }
    loadItemTable();
}

void adminView::Logout(){
    DB->saveItemDb();
    DB->saveUserDb();
    emit signalLogout();
}

void adminView::closeadditemadata(){
    if(addItemUI){
        addItemUI->hide();
        delete addItemUI;
        addItemUI=0;
    }
    loadItemTable();
}


void adminView::addItemData()
{
    addItemUI = new addItemView(admin,DB);
    connect(addItemUI,SIGNAL(signalConfirm()),this,SLOT(closeadditemadata()));
    addItemUI->show();
}
