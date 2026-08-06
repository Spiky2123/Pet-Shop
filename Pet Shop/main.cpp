#include "PetShop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PetShop window;
    window.show();
    return app.exec();
}
