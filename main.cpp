#include "logic_layer.h"
#include "welcome_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication CardCheX(argc, argv);
//    HomeWindow w;
//    w.show();
    LogicLayer logic_layer;

    logic_layer.ShowWelcome();
    logic_layer.Sleep(3000);
    logic_layer.HideWelcome();
    logic_layer.ShowHome();

    return CardCheX.exec();
}
