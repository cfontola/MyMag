#include "notebook.h"

Notebook::Notebook(const QString& u,const QString& i,const QString& b,const QString& p,const QString& m ,double d ,double pr,unsigned int mem,bool bl, bool fan, QString gp):
    Item(u,i,b,p,m,d,pr,mem),backlight(bl),fanless(fan),GPU(gp){}

void Notebook::setbacklight(bool bl){backlight=bl;}

void Notebook::setGPU(QString g){GPU=g;}

void Notebook::setfan(bool fan){fanless=fan;}

bool Notebook::getBackight()const{return backlight;}

bool Notebook::getfan()const{return fanless;}

const QString& Notebook::getGPU()const{return GPU;}


void Notebook::SaveItem(QXmlStreamWriter &xmlWriter) const{
    xmlWriter.writeStartElement("Notebook");
      xmlWriter.writeTextElement("User", getUser());
      xmlWriter.writeTextElement("Id", getId());
      xmlWriter.writeTextElement("Brand", getBrand());
      xmlWriter.writeTextElement("Processor", getProcessor());
      xmlWriter.writeTextElement("Model", getModel());
      xmlWriter.writeTextElement("Display", QString::number(getDisplay()));
      xmlWriter.writeTextElement("Price", QString::number(getPrice()));
      xmlWriter.writeTextElement("Memory", QString::number(getMemory()));
      xmlWriter.writeTextElement("Backlight", QString::number(getBackight()));
      xmlWriter.writeTextElement("GPU", getGPU().toUpper());
      xmlWriter.writeTextElement("Fanless", QString::number(getfan()));
    xmlWriter.writeEndElement();


}

QString Notebook::type()const {return "Notebook";}
