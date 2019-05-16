#ifndef ADDITEMVIEW_H
#define ADDITEMVIEW_H

#include <QWidget>
#include "database.h"
#include "notebook.h"
#include "smartphone.h"
#include "user.h"


namespace Ui {
class addItemView;
}

class addItemView : public QWidget
{
    Q_OBJECT

public:
    explicit addItemView(User*,Database*,QWidget *parent = 0);
    ~addItemView();

private:
    Ui::addItemView *ui;
    Database* DB;
    User* A;
    Container<const User*> Usn;

public slots:
    void Cancel();
    void Confirm();
    void update();
    void setGraphics();

signals:
    void signalCancel();
    void signalConfirm();

};

#endif // ADDITEMVIEW_H
