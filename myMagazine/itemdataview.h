#ifndef ITEMDATAVIEW_H
#define ITEMDATAVIEW_H

#include <QWidget>
#include <QMessageBox>
#include "notebook.h"
#include "smartphone.h"
#include "database.h"

namespace Ui {
class itemDataView;
}

class itemDataView : public QWidget
{
    Q_OBJECT

public:
    explicit itemDataView(Item*,Database*,QWidget *parent = 0);
    ~itemDataView();

    void loadItemData();
private:
    Ui::itemDataView *ui;
    Item*item;
    Database*DB;
    Container<const User*> Usn;



public slots:
    void saveChanges();
    void deleteItem();

signals:
    void signalCancel();
    void signalSave();
    void signaldeleteItem();

};

#endif // ITEMDATAVIEW_H
