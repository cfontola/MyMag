#include "smartwatch.h"

Smartwatch::Smartwatch(const QString& u,const QString& i,const QString& b,const QString& p,const QString& m ,double d ,double pr,unsigned int mem,const QString& s,const QString& c,const QString& Mc):
     Item(u,i,b,p,m,d,pr,mem),sensor(s),certificate(c),MaterialC(Mc)/*,MaterialQ(Mq)*/{}

void Smartwatch::setSensor(QString s){sensor=s;}
void Smartwatch::setCertificate(QString c){certificate=c;}
//void Smartwatch::setMaterialQ(QString q){MaterialQ=q;}
void Smartwatch::setMaterialC(QString c){MaterialC=c;}

const QString& Smartwatch::getSensor() const{
    return sensor;
}

const QString& Smartwatch::getCertificate() const{
    return certificate;
}

/*const QString& Smartwatch::getMaterialQ() const{
    return MaterialQ;
}*/

const QString& Smartwatch::getMaterialC() const{
    return MaterialC;
}

QString Smartwatch::type()const {return "Smartwatch";}

void Smartwatch::SaveItem(QXmlStreamWriter &xmlWriter) const{
    xmlWriter.writeStartElement("Smartwatch");
      xmlWriter.writeTextElement("User", getUser());
      xmlWriter.writeTextElement("Id", getId().toUpper());
      xmlWriter.writeTextElement("Brand", getBrand());
      xmlWriter.writeTextElement("Processor", getProcessor());
      xmlWriter.writeTextElement("Model", getModel());
      xmlWriter.writeTextElement("Display", QString::number(getDisplay()));
      xmlWriter.writeTextElement("Price", QString::number(getPrice()));
      xmlWriter.writeTextElement("Memory", QString::number(getMemory()));
      xmlWriter.writeTextElement("Sensor",getSensor());
      xmlWriter.writeTextElement("Certificate", getCertificate());
      xmlWriter.writeTextElement("Material_C", getMaterialC());
    xmlWriter.writeEndElement();


}
