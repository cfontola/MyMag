#ifndef ADMINVIEW_H
#define ADMINVIEW_H

#include <QMainWindow>
#include "user.h"
#include "registrationview.h"
#include "database.h"
#include "userdataview.h"
#include "additemview.h"

namespace Ui {
class adminView;
}

class adminView : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminView(User*,QWidget *parent = 0);
    ~adminView();
    void loadUserTable();
    void loadItemTable();

private:
    Ui::adminView *ui;
    registrationView* regUI;
    User* admin;
    userDataView* userDataUI;
    addItemView* addItemUI;
    itemDataView * itemDataUI;
    Database* DB;
    Container<const Item*> item;

public slots:
    void Logout();
    void openUserData(int);
    void openItemData(int);
    void addItemData();
    void closeUserData();
    void openRegistrationView();
    void closeRegistrationView();
    void refreshtable();
    void userRegistration(const QString&,const QString&,const QString&,const QString&,const QString&,const QString&);
signals:
    void signalLogout();
    void signalOpenRegistration();


};

#endif // ADMINVIEW_H
