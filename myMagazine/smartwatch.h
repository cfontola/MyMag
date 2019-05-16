#ifndef SMARTWATCH_H
#define SMARTWATCH_H
#include "item.h"

class Smartwatch:public Item
{
private:
    QString sensor;
    QString certificate;
    //QString MaterialQ;
    QString MaterialC;
public:
    Smartwatch(const QString& u,const QString&,const QString&,const QString&,const QString&,double,double,unsigned int,const QString&,const QString&,const QString&);

    void setSensor(QString);
    void setCertificate(QString);
    void setMaterialQ(QString);
    void setMaterialC(QString);

    const QString& getSensor() const;
    const QString& getCertificate() const;
    //const QString& getMaterialQ() const;
    const QString& getMaterialC() const;

    virtual void SaveItem(QXmlStreamWriter &xmlWriter) const;
    virtual QString type() const;

};

#endif // SMARTWATCH_H
