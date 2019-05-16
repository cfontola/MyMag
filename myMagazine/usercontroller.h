#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <QObject>
#include "user.h"
#include "database.h"

class userController : public QObject
{
    Q_OBJECT
private:
    User* user;
public:
    explicit userController(User*,QObject *parent = 0);
    ~userController();

    void openUserView() const;

signals:
    void signalLogout();
public slots:
    void Logout();
};

#endif // USERCONTROLLER_H
