#include "loginview.h"
#include "ui_loginview.h"
#include <QDesktopWidget>

loginView::loginView(QWidget *parent) : QWidget(parent),
    ui(new Ui::loginView)
{
    ui->setupUi(this);
    setGraphic();
    setFixedSize(this->geometry().width(),this->geometry().height());
    this->move(QApplication::desktop()->availableGeometry().center() - this->rect().center());
}

loginView::~loginView()
{
    delete ui;
}

QLineEdit* loginView::getUusn() const {return ui->user_usn;}
QLineEdit* loginView::getUpass() const {return ui->user_pass;}

void loginView::setGraphic(){
    setWindowTitle("Log in - myMagazine");
    setFixedWidth(480);

    ui->user_usn->setPlaceholderText("Inserisci Username");
    ui->user_pass->setPlaceholderText("Inserisci Password");
    ui->user_pass->setEchoMode(QLineEdit::Password);

    connect(ui->exitbtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->usloginbtn, SIGNAL(clicked()),this, SLOT(tryuserLogin()));
}

void loginView::tryuserLogin(){
    emit signaluserLogin(ui->user_usn->text(),ui->user_pass->text());
}
