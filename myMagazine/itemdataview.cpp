#include "itemdataview.h"
#include "ui_itemdataview.h"
#include <QDesktopWidget>
#include <QDebug>
#include "admin.h"


itemDataView::itemDataView(Item* a,Database*db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::itemDataView),
    item(a),
    DB(db)




{
  Usn=DB->getUserDb();
  ui->setupUi(this);
  setFixedSize(this->geometry().width(),this->geometry().height());
  setWindowTitle("Gestione dati item");
  loadItemData();
  this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());

}

itemDataView::~itemDataView()
{
    delete ui;
}

void itemDataView::loadItemData(){
    ui->iDEdit->setText(item->getId());
    ui->brandEdit->setText(item->getBrand());
    ui->processorEdit->setText(item->getProcessor());
    ui->modelEdit->setText(item->getModel());
    ui->displayEdit->setText(QString::number(item->getDisplay()));
    ui->priceEdit->setText(QString::number(item->getPrice()));
    ui->memoryEdit->setText(QString::number(item->getMemory()));

    Notebook* b = dynamic_cast<Notebook*>(item);
    Smartphone* o = dynamic_cast<Smartphone*>(item);
    Smartwatch* s=dynamic_cast<Smartwatch*>(item);

    if(b){
        ui->radioNotebook->setChecked(true);
        ui->radioSmartphone->hide();
        ui->radioSmartwatch->hide();
        ui->checkBox_finger->hide();
        ui->cam1label->hide();
        ui->cam1Edit->hide();
        ui->cam2label->hide();
        ui->cam2Edit->hide();
        ui->sensorlabel->hide();
        ui->sensorEdit->hide();
        ui->certificatelabel->hide();
        ui->certificateEdit->hide();
        ui->materiallabel->hide();
        ui->materialEdit->hide();
        ui->checkBox_backL->setChecked(b->getBackight());
        ui->checkBox_fanles->setChecked(b->getfan());
        ui->GPUEdit->setText(b->getGPU());

    }
    if(o){
        ui->radioSmartphone->setChecked(true);
        ui->radioNotebook->hide();
        ui->radioSmartwatch->hide();
        ui->checkBox_backL->hide();
        ui->checkBox_fanles->hide();
        ui->GPUlabel->hide();
        ui->GPUEdit->hide();
        ui->sensorlabel->hide();
        ui->sensorEdit->hide();
        ui->certificatelabel->hide();
        ui->certificateEdit->hide();
        ui->materiallabel->hide();
        ui->materialEdit->hide();
        ui->checkBox_finger->setChecked(o->getFingerPrint());
        ui->cam1Edit->setText(QString::number(o->getMegaPx1()));
        ui->cam2Edit->setText(QString::number(o->getMegaPx2()));
    }
    if(s){
        ui->radioSmartwatch->setChecked(true);
        ui->radioNotebook->hide();
        ui->radioSmartphone->hide();
        ui->checkBox_finger->hide();
        ui->cam1label->hide();
        ui->cam1Edit->hide();
        ui->cam2label->hide();
        ui->cam2Edit->hide();
        ui->checkBox_backL->hide();
        ui->checkBox_fanles->hide();
        ui->GPUlabel->hide();
        ui->GPUEdit->hide();
        ui->sensorEdit->setText(s->getSensor());
        ui->certificateEdit->setText(s->getCertificate());
        ui->materialEdit->setText(s->getMaterialC());
    }
}

void itemDataView::deleteItem(){
    QMessageBox::StandardButton question;
    question=QMessageBox::question(this,"Elimina oggetto","Eliminare oggettp selezionato dal magazzino?",QMessageBox::Yes|QMessageBox::No);
    if(question==QMessageBox::Yes){
        QString codice = item->getId();
        DB->deleteItem(codice);
    }
    DB->saveItemDb();
    this->close();
}

void itemDataView::saveChanges(){
    QMessageBox::StandardButton question;
    question=QMessageBox::question(this,"Conferma modifiche","Confermi modifiche effettuate?",QMessageBox::Yes|QMessageBox::No);

    if(question==QMessageBox::Yes){
        QString codice = ui->iDEdit->text();
        QString brand=ui->brandEdit->text();
        QString processor=ui->processorEdit->text();
        QString model=ui->modelEdit->text();
        double display=ui->displayEdit->text().toDouble();
        double price=ui->priceEdit->text().toDouble();
        unsigned int memory=ui->memoryEdit->text().toInt();


        Notebook* n=dynamic_cast<Notebook*>(item);
        Smartphone* s=dynamic_cast<Smartphone*>(item);
        Smartwatch* w=dynamic_cast<Smartwatch*>(item);

        bool backlight=ui->checkBox_backL->isChecked();
        bool fanless=ui->checkBox_fanles->isChecked();
        QString gpu=ui->GPUEdit->text();

        bool finger=ui->checkBox_finger->isChecked();
        unsigned int cam1=ui->cam1Edit->text().toInt();
        unsigned int cam2=ui->cam2Edit->text().toInt();

        QString sensor=ui->sensorEdit->text();
        QString certificate=ui->certificateEdit->text();
        QString material=ui->materialEdit->text();



            if(n){
                n->setbrand(brand);
                n->setprocessor(processor);
                n->setmodel(model);
                n->setdisplay(display);
                n->setprice(price);
                n->setmemory(memory);
                n->setbacklight(backlight);
                n->setfan(fanless);
                n->setGPU(gpu);

                QMessageBox* msg =new QMessageBox();
                msg->setText("Notebook modificato correttamente.");
                msg->addButton("OK",QMessageBox::AcceptRole);
                msg->setAttribute(Qt::WA_DeleteOnClose);
                msg->show();
            }
            if(s){
                s->setbrand(brand);
                s->setprocessor(processor);
                s->setmodel(model);
                s->setdisplay(display);
                s->setprice(price);
                s->setmemory(memory);
                s->setfingerprint(finger);
                s->setmegapx(cam1);
                s->setmegapx2(cam2);

                QMessageBox* msg =new QMessageBox();
                msg->setText("Smartphone modificato correttamente.");
                msg->addButton("OK",QMessageBox::AcceptRole);
                msg->setAttribute(Qt::WA_DeleteOnClose);
                msg->show();
            }
            if(w){
                w->setbrand(brand);
                w->setprocessor(processor);
                w->setmodel(model);
                w->setdisplay(display);
                w->setprice(price);
                w->setmemory(memory);
                w->setSensor(sensor);
                w->setCertificate(certificate);
                w->setMaterialC(material);

                QMessageBox* msg =new QMessageBox();
                msg->setText("Smartwatch modificato correttamente.");
                msg->addButton("OK",QMessageBox::AcceptRole);
                msg->setAttribute(Qt::WA_DeleteOnClose);
                msg->show();
            }

            emit signalSave();
        }
    }




void itemDataView::on_confirmbtn_clicked()
{
    saveChanges();
}

void itemDataView::on_cancelbtn_clicked()
{
    deleteItem();
}
