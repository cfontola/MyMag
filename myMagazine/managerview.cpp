#include "managerview.h"
#include "ui_managerview.h"
#include <QDebug>
#include <QDesktopWidget>
managerView::managerView(User*a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::managerView),
    manager(a)


{


    DB=new Database(); DB->loadItemDb();
    ui->setupUi(this);
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
    setFixedSize(this->geometry().width(),this->geometry().height());
    setWindowTitle("Manager panel - myMagazine");
    ui->logged->setText("Logged as : " + manager->getUsername());
    loadTable();
    connect(ui->itemtable,SIGNAL(cellClicked(int,int)),this,SLOT(openItemData(int)));
    connect(ui->addItem,SIGNAL(clicked()),this,SLOT(addItemData()));
    connect(ui->search,SIGNAL(clicked()),this,SLOT(search()));
    connect(ui->logout,SIGNAL(clicked()),this,SLOT(Logout()));


}
managerView::~managerView()
{
    delete ui;
}


void managerView::Logout(){
    emit signalLogout();
    DB->saveItemDb();
}

void managerView::openItemData(int row){
  QString id = ui->itemtable->item(row,0)->text();
  Item*itemx=const_cast<Item*>(DB->findItem(id));
  if(itemDataUI){
      itemDataUI = new itemDataView(itemx,DB);
      connect(itemDataUI,SIGNAL(signaldeleteItem()),this,SLOT(closeItemData()));
      connect(itemDataUI,SIGNAL(signalSave()),this,SLOT(closeItemData()));
      itemDataUI->show();

  }else{
      itemDataUI = new itemDataView(itemx,DB);
      connect(itemDataUI,SIGNAL(signaldeleteItem()),this,SLOT(closeItemData()));
      connect(itemDataUI,SIGNAL(signalSave()),this,SLOT(closeItemData()));
      itemDataUI->show();
   }
}

void managerView::closeItemData(){

    if(itemDataUI) {
        itemDataUI->hide();
        delete itemDataUI;
        itemDataUI=0;
    }
    loadTable();

}

void managerView::loadTable(){
            Container<const Item*> item=DB->getItemDb();
            Container<const Item*>::Iterator it= item.begin();
            int counter =0;
            for(;it!=item.end(); ++it){
                if(item[it]->getUser()==manager->getUsername()){

                    ui->itemtable->setRowCount(counter+1);
                    QTableWidgetItem* codice= new QTableWidgetItem(item[it]->getId());
                    QTableWidgetItem* type= new QTableWidgetItem(item[it]->type());
                    QTableWidgetItem* brand= new QTableWidgetItem(item[it]->getBrand());
                    QTableWidgetItem* processor= new QTableWidgetItem(item[it]->getProcessor());
                    QTableWidgetItem* model= new QTableWidgetItem(item[it]->getModel());
                    QTableWidgetItem* display= new QTableWidgetItem(QString::number(item[it]->getDisplay()));
                    QTableWidgetItem* price= new QTableWidgetItem(QString::number(item[it]->getPrice()));
                    QTableWidgetItem* memory= new QTableWidgetItem(QString::number(item[it]->getMemory()));



                    ui->itemtable->setItem(counter,0,codice);
                    ui->itemtable->setItem(counter,1,type);
                    ui->itemtable->setItem(counter,2,brand);
                    ui->itemtable->setItem(counter,3,processor);
                    ui->itemtable->setItem(counter,4,model);
                    ui->itemtable->setItem(counter,5,display);
                    ui->itemtable->setItem(counter,6,price);
                    ui->itemtable->setItem(counter,7,memory);

                    ++counter;
               }

           }
            if(counter==0){
                QMessageBox* msg =new QMessageBox();
                msg->setText("Nessun Oggetto Presente");
                msg->addButton("OK",QMessageBox::AcceptRole);
                msg->show();
            }
}

void managerView::closeAddItemaData(){
    if(addItemUI){
        addItemUI->hide();
        delete addItemUI;
        addItemUI=0;
    }
    loadTable();
}




void managerView::addItemData()
{
    addItemUI = new addItemView(manager,DB);
    connect(addItemUI,SIGNAL(signalConfirm()),this,SLOT(closeAddItemaData()));
    addItemUI->show();
}




void managerView::search() //tasto di rierca
{
    bool find=false;
    if(ui->itemType->currentText()=="Notebook"){
        int counter =0;
        Container<const Item*> notebook=DB->getNotebook();
        Container<const Item*>::Iterator it= notebook.begin();
        for(;it!=notebook.end(); ++it){
            if(notebook[it]->getUser()==manager->getUsername()){
            if((notebook[it]->getId()==ui->codice_edit->text()||ui->codice_edit->text()=="") && notebook[it]->getPrice()>=ui->prezzo_edit->text().toDouble() && (notebook[it]->getBrand()==ui->brand_edit->text()||ui->brand_edit->text()=="")){
                find=true;

                ui->itemtable->setRowCount(counter+1);
                QTableWidgetItem* codice= new QTableWidgetItem(notebook[it]->getId());
                QTableWidgetItem* type= new QTableWidgetItem(notebook[it]->type());
                QTableWidgetItem* brand= new QTableWidgetItem(notebook[it]->getBrand());
                QTableWidgetItem* processor= new QTableWidgetItem(notebook[it]->getProcessor());
                QTableWidgetItem* model= new QTableWidgetItem(notebook[it]->getModel());
                QTableWidgetItem* display= new QTableWidgetItem(QString::number(notebook[it]->getDisplay()));
                QTableWidgetItem* price= new QTableWidgetItem(QString::number(notebook[it]->getPrice()));
                QTableWidgetItem* memory= new QTableWidgetItem(QString::number(notebook[it]->getMemory()));



                ui->itemtable->setItem(counter,0,codice);
                ui->itemtable->setItem(counter,1,type);
                ui->itemtable->setItem(counter,2,brand);
                ui->itemtable->setItem(counter,3,processor);
                ui->itemtable->setItem(counter,4,model);
                ui->itemtable->setItem(counter,5,display);
                ui->itemtable->setItem(counter,6,price);
                ui->itemtable->setItem(counter,7,memory);

                ++counter;


            }
         }
      }
          if(!find){
          QMessageBox* msg =new QMessageBox();
          msg->setText("Nessun Notebook trovato con tali parametri");
          msg->addButton("OK",QMessageBox::AcceptRole);
          msg->setAttribute(Qt::WA_DeleteOnClose);
          msg->show();
          }
    }
    else if(ui->itemType->currentText()=="Smartphone"){
        find=false;
        Container<const Item*> smartphone=DB->getSmartphone();
        Container<const Item*>::Iterator it= smartphone.begin();
        int counter=0;
        for(;it!=smartphone.end(); ++it){
            if(smartphone[it]->getUser()==manager->getUsername()){
            if((smartphone[it]->getId()==ui->codice_edit->text()||ui->codice_edit->text()=="") && smartphone[it]->getPrice()>=ui->prezzo_edit->text().toDouble() && (smartphone[it]->getBrand()==ui->brand_edit->text()||ui->brand_edit->text()=="")){
                find=true;

                ui->itemtable->setRowCount(counter+1);
                QTableWidgetItem* codice= new QTableWidgetItem(smartphone[it]->getId());
                QTableWidgetItem* type= new QTableWidgetItem(smartphone[it]->type());
                QTableWidgetItem* brand= new QTableWidgetItem(smartphone[it]->getBrand());
                QTableWidgetItem* processor= new QTableWidgetItem(smartphone[it]->getProcessor());
                QTableWidgetItem* model= new QTableWidgetItem(smartphone[it]->getModel());
                QTableWidgetItem* display= new QTableWidgetItem(QString::number(smartphone[it]->getDisplay()));
                QTableWidgetItem* price= new QTableWidgetItem(QString::number(smartphone[it]->getPrice()));
                QTableWidgetItem* memory= new QTableWidgetItem(QString::number(smartphone[it]->getMemory()));



                ui->itemtable->setItem(counter,0,codice);
                ui->itemtable->setItem(counter,1,type);
                ui->itemtable->setItem(counter,2,brand);
                ui->itemtable->setItem(counter,3,processor);
                ui->itemtable->setItem(counter,4,model);
                ui->itemtable->setItem(counter,5,display);
                ui->itemtable->setItem(counter,6,price);
                ui->itemtable->setItem(counter,7,memory);

                ++counter;

            }
          }
     }
        if(!find){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Nessun Smartphone trovato con tali parametri");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
        }

   }
    else if(ui->itemType->currentText()=="Smartwatch"){
        find=false;
        Container<const Item*> smartwatch=DB->getSmartwatch();
        Container<const Item*>::Iterator it= smartwatch.begin();
        int counter=0;
        for(;it!=smartwatch.end(); ++it){
            if(smartwatch[it]->getUser()==manager->getUsername()){
            if((smartwatch[it]->getId()==ui->codice_edit->text()||ui->codice_edit->text()=="") && smartwatch[it]->getPrice()>=ui->prezzo_edit->text().toDouble() && (smartwatch[it]->getBrand()==ui->brand_edit->text()||ui->brand_edit->text()=="")){
                find=true;

                ui->itemtable->setRowCount(counter+1);
                QTableWidgetItem* codice= new QTableWidgetItem(smartwatch[it]->getId());
                QTableWidgetItem* type= new QTableWidgetItem(smartwatch[it]->type());
                QTableWidgetItem* brand= new QTableWidgetItem(smartwatch[it]->getBrand());
                QTableWidgetItem* processor= new QTableWidgetItem(smartwatch[it]->getProcessor());
                QTableWidgetItem* model= new QTableWidgetItem(smartwatch[it]->getModel());
                QTableWidgetItem* display= new QTableWidgetItem(QString::number(smartwatch[it]->getDisplay()));
                QTableWidgetItem* price= new QTableWidgetItem(QString::number(smartwatch[it]->getPrice()));
                QTableWidgetItem* memory= new QTableWidgetItem(QString::number(smartwatch[it]->getMemory()));



                ui->itemtable->setItem(counter,0,codice);
                ui->itemtable->setItem(counter,1,type);
                ui->itemtable->setItem(counter,2,brand);
                ui->itemtable->setItem(counter,3,processor);
                ui->itemtable->setItem(counter,4,model);
                ui->itemtable->setItem(counter,5,display);
                ui->itemtable->setItem(counter,6,price);
                ui->itemtable->setItem(counter,7,memory);

                ++counter;

            }
          }
     }
        if(!find){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Nessun smartwatch trovato con tali parametri");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
        }

   }
    else{
        find=false;
        Container<const Item*> item=DB->getItemDb();
        Container<const Item*>::Iterator it= item.begin();
        int counter=0;
        for(;it!=item.end(); ++it){
            if(item[it]->getUser()==manager->getUsername()){
            if((item[it]->getId()==ui->codice_edit->text()||ui->codice_edit->text()=="") && item[it]->getPrice()>=ui->prezzo_edit->text().toDouble() && (item[it]->getBrand()==ui->brand_edit->text()||ui->brand_edit->text()=="")){
                find=true;

                ui->itemtable->setRowCount(counter+1);
                QTableWidgetItem* codice= new QTableWidgetItem(item[it]->getId());
                QTableWidgetItem* type= new QTableWidgetItem(item[it]->type());
                QTableWidgetItem* brand= new QTableWidgetItem(item[it]->getBrand());
                QTableWidgetItem* processor= new QTableWidgetItem(item[it]->getProcessor());
                QTableWidgetItem* model= new QTableWidgetItem(item[it]->getModel());
                QTableWidgetItem* display= new QTableWidgetItem(QString::number(item[it]->getDisplay()));
                QTableWidgetItem* price= new QTableWidgetItem(QString::number(item[it]->getPrice()));
                QTableWidgetItem* memory= new QTableWidgetItem(QString::number(item[it]->getMemory()));



                ui->itemtable->setItem(counter,0,codice);
                ui->itemtable->setItem(counter,1,type);
                ui->itemtable->setItem(counter,2,brand);
                ui->itemtable->setItem(counter,3,processor);
                ui->itemtable->setItem(counter,4,model);
                ui->itemtable->setItem(counter,5,display);
                ui->itemtable->setItem(counter,6,price);
                ui->itemtable->setItem(counter,7,memory);

                ++counter;

            }
          }
     }
        if(!find){
        QMessageBox* msg =new QMessageBox();
        msg->setText("Nessun oggetto trovato con tali parametri");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
        }
    }

}
