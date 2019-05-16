#ifndef REGISTRATIONVIEW_H
#define REGISTRATIONVIEW_H

#include <QWidget>
#include "database.h"

namespace Ui {
class registrationView;
}

class registrationView : public QWidget
{
    Q_OBJECT

public:
    explicit registrationView(Database* db,QWidget *parent = 0);
    ~registrationView();

    void setGraphic();

private:
    Database* DB;
    Ui::registrationView *ui;


public slots:
    void closeRegistration();
    void tryRegistration();

signals:
    void signalGoLogin();
    void signalRegistration(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&);
};

#endif // REGISTRATIONVIEW_H
