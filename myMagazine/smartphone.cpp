#include "smartphone.h"

Smartphone::Smartphone(const QString& u,const QString& i,const QString& b,const QString& p,const QString& m ,double d ,double pr,unsigned int mem,bool f, unsigned int cam1, unsigned int cam2):
    Item(u,i,b,p,m,d,pr,mem),fingerprint(f),Megapx(cam1),Megapx2(cam2){}


void Smartphone::setfingerprint(bool f){
    fingerprint=f;
}

void Smartphone::setmegapx(unsigned int front){
    Megapx=front;
}

void Smartphone::setmegapx2(unsigned int back){
    Megapx2=back;
}

bool Smartphone::getFingerPrint()const{return fingerprint;}
unsigned int Smartphone::getMegaPx1()const{return Megapx;}
unsigned int Smartphone::getMegaPx2()const{return Megapx2;}

QString Smartphone::type()const {return "Smartphone";}

void Smartphone::SaveItem(QXmlStreamWriter &xmlWriter) const{
    xmlWriter.writeStartElement("Smartphone");
      xmlWriter.writeTextElement("User", getUser());
      xmlWriter.writeTextElement("Id", getId().toUpper());
      xmlWriter.writeTextElement("Brand", getBrand());
      xmlWriter.writeTextElement("Processor", getProcessor());
      xmlWriter.writeTextElement("Model", getModel());
      xmlWriter.writeTextElement("Display", QString::number(getDisplay()));
      xmlWriter.writeTextElement("Price", QString::number(getPrice()));
      xmlWriter.writeTextElement("Memory", QString::number(getMemory()));
      xmlWriter.writeTextElement("FingerPrint", QString::number(getFingerPrint()));
      xmlWriter.writeTextElement("Cam1", QString::number(getMegaPx1()));
      xmlWriter.writeTextElement("Cam2", QString::number(getMegaPx2()));
    xmlWriter.writeEndElement();


}
