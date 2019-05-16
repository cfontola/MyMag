#ifndef SMARTPHONE_H
#define SMARTPHONE_H
#include "item.h"

class Smartphone:public Item
{
private:
    bool fingerprint;
    unsigned int Megapx;
    unsigned int Megapx2;

public:
    /*-------------------------------------------------------------------------------fingerprint, camera1, camera 2-----------------*/
    Smartphone(const QString& u,const QString&,const QString&,const QString&,const QString&,double,double,unsigned int, bool,unsigned int, unsigned int );

    void setfingerprint(bool);
    void setmegapx(unsigned int);
    void setmegapx2( unsigned int);

    bool getFingerPrint()const;
    unsigned int getMegaPx1()const;
    unsigned int getMegaPx2()const;


    virtual void SaveItem(QXmlStreamWriter &xmlWriter) const;
    virtual QString type() const;
};

#endif // SMARTPHONE_H
