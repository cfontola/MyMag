#ifndef ITEM_H
#define ITEM_H

#include <Qstring>
#include <QXmlStreamWriter>

class Item
{
protected:
    QString user;
    QString id;
    QString brand;
    QString processor;
    QString model;
    double display;
    double price;
    unsigned int memory;

public:
    Item(const QString&,const QString&,const QString&,const QString&,const QString&,double,double,unsigned int);
    virtual ~Item();

    const QString& getUser() const;
    const QString& getId() const;
    const QString& getBrand() const;
    const QString& getProcessor() const;
    const QString& getModel() const;
    double getDisplay()const;
    double getPrice()const;
    unsigned int getMemory()const;

    void setUser(const QString&);
    void setbrand(const QString&);
    void setprocessor(const QString&);
    void setmodel(const QString&);
    void setdisplay(double d);
    void setprice(double p);
    void setmemory(unsigned int m);



    virtual void SaveItem(QXmlStreamWriter& xmlWriter)const=0;

    virtual QString type() const=0;

};

#endif // ITEM_H
