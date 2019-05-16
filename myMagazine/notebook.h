#ifndef NOTEBOOK_H
#define NOTEBOOK_H
#include "item.h"

class Notebook:public Item
{
private:
    bool backlight;
    bool fanless;
    QString GPU;

public:

    Notebook(const QString& u,const QString& i,const QString&,const QString&,const QString&,double,double,unsigned int,bool,bool,QString);

    bool getBackight()const;
    bool getfan()const;
    const QString& getGPU()const;

    void setbacklight(bool);
    void setfan(bool);
    void setGPU(QString);

    virtual void SaveItem(QXmlStreamWriter &xmlWriter) const;
    virtual QString type() const;
};

#endif // NOTEBOOK_H
