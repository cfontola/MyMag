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

    //void Cancel();
    void saveChanges();
    void deleteItem();
    //void updatebtns();
signals:
    void signalCancel();
    void signalSave();
    void signaldeleteItem(const QString&);
private slots:
    void on_confirmbtn_clicked();
    void on_cancelbtn_clicked();
};

#endif // ITEMDATAVIEW_H
