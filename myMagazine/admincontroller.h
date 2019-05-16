#ifndef ADMINCONTROLLER_H
#define ADMINCONTROLLER_H

#include "adminview.h"
#include "admin.h"
#include <QMessageBox>

class adminController : public QObject
{
    Q_OBJECT
private:
    Admin* admin;
    adminView* adminUI;
public:
    explicit adminController(Admin*,QObject* =0);
    ~adminController();

    void openAdminView();
signals:
    void signalLogout();
public slots:
    void Logout();
};

#endif // ADMINCONTROLLER_H
