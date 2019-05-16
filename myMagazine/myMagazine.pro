#-------------------------------------------------
#
# Project created by QtCreator 2018-12-14T17:10:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myMagazine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QMAKE_CXXFLAGS += -std=c++11

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    item.cpp \
    notebook.cpp \
    smartphone.cpp \
    user.cpp \
    manager.cpp \
    admin.cpp \
    database.cpp \
    adminview.cpp \
    managerview.cpp \
    mymagazinecontroller.cpp \
    usercontroller.cpp \
    admincontroller.cpp \
    registrationview.cpp \
    userdataview.cpp \
    additemview.cpp \
    itemdataview.cpp \
    smartwatch.cpp \
    loginview.cpp \




HEADERS += \
    loginview.h \
    item.h \
    notebook.h \
    smartphone.h \
    container.h \
    user.h \
    manager.h \
    admin.h \
    database.h \
    adminview.h \
    managerview.h \
    mymagazinecontroller.h \
    usercontroller.h \
    admincontroller.h \
    registrationview.h \
    userdataview.h \
    additemview.h \
    itemdataview.h \
    smartwatch.h \






FORMS += \
    loginview.ui \
    adminview.ui \
    managerview.ui \
    registrationview.ui \
    userdataview.ui \
    additemview.ui \
    itemdataview.ui

DISTFILES += \
    db/itemDatabase.xml \
    db/userDatabase.xml
