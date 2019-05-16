#include <QApplication>
#include "mymagazinecontroller.h"

int main(int argc, char *argv[])
{
    QApplication MyMagazine(argc, argv);
    Database db;
    loginView startUI;
    myMagazineController controller(&db,&startUI);

    return MyMagazine.exec();
}
