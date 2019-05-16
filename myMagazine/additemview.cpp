#include "additemview.h"
#include "ui_additemview.h"
#include <QMessageBox>
#include <QDesktopWidget>
#include "admin.h"

addItemView::addItemView(User*a,Database* db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addItemView),
    DB(db),
    A(a)


{
  Usn=db->getUserDb();
  ui->setupUi(this);
  ui->cam1label->hide();
  ui->cam2label->hide();
  ui->checkBox_finger->hide();
  ui->sensorlabel->hide();
  ui->certificatelabel->hide();
  ui->materiallabel->hide();
  if(!dynamic_cast<Admin*>(a)){
      ui->UserBox->hide();
      ui->Userlabel->hide();
  }

  for(auto it=Usn.begin(); it!=Usn.end(); ++it){
      if(!dynamic_cast< const Admin*>(Usn[it])){
      ui->UserBox->addItem(Usn[it]->getUsername());
      }
  }
  setWindowTitle("Inserimento nuovo oggetto");
  setFixedSize(this->geometry().width(),this->geometry().height());
  connect(ui->radioSmartphone,SIGNAL(clicked()),this,SLOT(updatebtns()));
  connect(ui->radioNotebook,SIGNAL(clicked()),this,SLOT(updatebtns()));
  connect(ui->radioSmartwatch,SIGNAL(clicked()),this,SLOT(updatebtns()));
  connect(ui->cancelbtn,SIGNAL(clicked()),this,SLOT(close()));
  connect(ui->confirmbtn,SIGNAL(clicked()),this,SLOT(Confirm()));
  this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());

}
addItemView::~addItemView()
{
    delete ui;
}


void addItemView::updatebtns(){
    if(ui->radioNotebook->isChecked()){
        ui->checkBox_finger->hide();
        ui->cam1label->hide();
        ui->cam2label->hide();
        ui->sensorlabel->hide();
        ui->certificatelabel->hide();
        ui->materiallabel->hide();
        ui->checkBox_backL->show();
        ui->checkBox_fanles->show();
        ui->GPUlabel->show();
    }
    if(ui->radioSmartphone->isChecked()){
        ui->checkBox_backL->hide();
        ui->checkBox_fanles->hide();
        ui->sensorlabel->hide();
        ui->certificatelabel->hide();
        ui->materiallabel->hide();
        ui->checkBox_finger->show();
        ui->cam1label->show();
        ui->cam2label->show();
        ui->GPUlabel->hide();
    }
    if(ui->radioSmartwatch->isChecked()){
        ui->checkBox_finger->hide();
        ui->cam1label->hide();
        ui->cam2label->hide();
        ui->GPUlabel->hide();
        ui->checkBox_backL->hide();
        ui->checkBox_fanles->hide();
        ui->sensorlabel->show();
        ui->certificatelabel->show();
        ui->materiallabel->show();
    }
}

void addItemView::Confirm(){
    QString codice = ui->iDEdit->text().toUpper();
    bool findError=false;
    QString user;
    if(!DB->findItem(codice)){
        if(ui->UserBox->currentText().size()==0){
            user=A->getUsername();
        }
        else{user=ui->UserBox->currentText();}

        bool display_ok;
        bool price_ok;
        bool memory_ok;
        bool cam1_ok;
        bool cam2_ok;


        QString brand = ui->brandEdit->text();
        QString processor= ui->processorEdit->text();
        QString model=ui->modelEdit->text();
        double display = ui->displayEdit->text().toDouble(&display_ok);
        double price=ui->priceEdit->text().toDouble(&price_ok);
        int memory  = ui->memoryEdit->text().toInt(&memory_ok);

        bool backlight=ui->checkBox_backL->isChecked();
        bool fanless=ui->checkBox_fanles->isChecked();
        QString GPU=ui->GPUEdit->text();

        bool fingerprint=ui->checkBox_finger->isChecked();
        unsigned int camera1=ui->cam1Edit->text().toInt(&cam1_ok);
        unsigned int camera2=ui->cam2Edit->text().toInt(&cam2_ok);

        QString sensor=ui->sensorEdit->text();
        QString certificate=ui->certificateEdit->text();
        QString material=ui->materialEdit->text();






        if(ui->iDEdit->text().size()<4 || ui->iDEdit->text().size()>=8){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Codice ID min 4 max 7 caratteri");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if(ui->brandEdit->text()==""){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Inserire brand dell'oggetto da inserire!");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if(ui->processorEdit->text()==""){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Inserire processor dell'oggetto da inserire!");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if(ui->modelEdit->text()==""){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Inserire model dell'oggetto da inserire!");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if(ui->displayEdit->text()=="" || !display_ok){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Formato dimensioni display! Richiesto un double.");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if((ui->cam1Edit->text()=="" || !cam1_ok) && ui->radioSmartphone->isChecked() ){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Formato cam ant!Richiesto un double. ");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if((ui->cam2Edit->text()=="" || !cam2_ok) && ui->radioSmartphone->isChecked()){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Formato cam post! Richiesto un double.");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if(ui->priceEdit->text()=="" || !price_ok){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Formato price.Richiesto un double.");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }
        else if(ui->memoryEdit->text()=="" || !memory_ok){
            QMessageBox* msg =new QMessageBox();
            msg->setText("Formato memory.Richiesto un intero.");
            msg->addButton("OK",QMessageBox::AcceptRole);
            msg->setAttribute(Qt::WA_DeleteOnClose);
            msg->show();
            findError=true;
        }

           if(!findError){
            if(ui->radioNotebook->isChecked()){
                const Notebook* n = new Notebook(user,codice,brand,processor,model,display,price,memory,backlight,fanless,GPU);
                DB->addItem(n);

                QMessageBox* msg =new QMessageBox();
                msg->setText("Notebook aggiunto correttamente.");
                msg->addButton("OK",QMessageBox::AcceptRole);
                msg->setAttribute(Qt::WA_DeleteOnClose);
                msg->show();
                this->close();
                }

            else if(ui->radioSmartphone->isChecked()){
                const Smartphone* s = new Smartphone(user,codice,brand,processor,model,display,price,memory,fingerprint,camera1,camera2);
                DB->addItem(s);

                QMessageBox* msg =new QMessageBox();
                msg->setText("Smartphone aggiunto correttamente.");
                msg->addButton("OK",QMessageBox::AcceptRole);
                msg->setAttribute(Qt::WA_DeleteOnClose);
                msg->show();
                this->close();
                }
            else if(ui->radioSmartwatch->isChecked()){
                const Smartwatch* s=new Smartwatch(user,codice,brand,processor,model,display,price,memory,sensor,certificate,material);
                DB->addItem(s);

                QMessageBox* msg =new QMessageBox();
                msg->setText("Smartwatch aggiunto correttamente.");
                msg->addButton("OK",QMessageBox::AcceptRole);
                msg->setAttribute(Qt::WA_DeleteOnClose);
                msg->show();
                this->close();
            }
    }


emit signalConfirm();
    }
    else{
        QMessageBox* msg =new QMessageBox();
        msg->setText("Item già presente in database con ID inserito.");
        msg->addButton("OK",QMessageBox::AcceptRole);
        msg->setAttribute(Qt::WA_DeleteOnClose);
        msg->show();
    }
}


void addItemView::Cancel(){
    emit signalCancel();
}


