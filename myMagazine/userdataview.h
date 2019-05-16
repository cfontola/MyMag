#ifndef USERDATAVIEW_H
#define USERDATAVIEW_H

#include <QWidget>
#include "manager.h"
#include "database.h"

namespace Ui {
class userDataView;
}

class userDataView : public QWidget
{
    Q_OBJECT

public:
    explicit userDataView(User* ,Database* ,QWidget *parent = 0);
    ~userDataView();

    void loadData();

private:
    Ui::userDataView *ui;
    User* user;
    Database* DB;
    Container<const Item*> item;


public slots:
    void Cancel();
    void Confirm();
    void deleteUser();
signals:
    void signalCancel();
    void signalConfirm();

};

#endif // USERDATAVIEW_H

