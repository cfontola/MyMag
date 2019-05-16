#include "item.h"

Item::Item(const QString& u,const QString& i,const QString& b,const QString& p,const QString& m ,double d ,double pr,unsigned int mem):
    user(u),id(i),brand(b),processor(p),model(m),display(d),price(pr),memory(mem){}

Item::~Item(){}
const QString& Item::getUser() const{return user;}
const QString& Item::getId() const{return id;}
const QString& Item::getBrand()const{return brand;}
const QString& Item::getProcessor()const{return processor;}
const QString& Item::getModel()const{return model;}
double Item::getDisplay()const{return display;}
double Item::getPrice()const{return price;}
unsigned int Item::getMemory()const{return memory;}


void Item::setUser(const QString& u){user=u;}
void Item::setbrand(const QString & b){brand=b;}
void Item::setprocessor(const QString & p){processor=p;}
void Item::setmodel(const QString & m){model=m;}
void Item::setdisplay(double d){display=d;}
void Item::setprice(double pr){price=pr;}
void Item::setmemory(unsigned int mem){memory=mem;}
