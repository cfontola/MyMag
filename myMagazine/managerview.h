#ifndef MANAGERVIEW_H
#define MANAGERVIEW_H

#include <QMainWindow>
 #include "user.h"
#include "database.h"
#include "additemview.h"
#include "itemdataview.h"

namespace Ui {
class managerView;
}

class managerView : public QMainWindow
{
    Q_OBJECT

public:
    explicit managerView(User*,QWidget *parent = 0);
    ~managerView();

     void loadTable();

private:
    Ui::managerView *ui;
    User* manager;
    Database* DB;
    addItemView* addItemUI;
    itemDataView * itemDataUI;
public slots:
    void closeItemData();
    void openItemData(int);
    void Logout();
    void addItemData();
    void search();
    void closeAddItemaData();
signals:
    void signalLogout();


};

#endif // MANAGERVIEW_H
