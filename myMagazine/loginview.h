#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include "ui_loginview.h"

namespace Ui {
class loginView;
}

class loginView : public QWidget
{
    Q_OBJECT

public:
    loginView(QWidget* = 0);
    ~loginView();
    void setGraphic();
    QLineEdit* getUusn() const;
    QLineEdit* getUpass() const;
private:
    Ui::loginView* ui;

public slots:
    void tryuserLogin();
signals:
    void signaluserLogin(const QString& ,const QString&);
};

#endif // LOGINVIEW_H
