#include <cassert>
#include <string>
#include <QApplication>
#include <QtCharts/QChart>
#include "dataset.h"
#include "tablewidget.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    bool justShow = false;
    bool learn = false;
    if (argc == 2 && std::string("-s") == argv[1])
        justShow = true;
    if (argc == 2 && std::string("-l") == argv[1])
        learn = true;

    TableWidget w(justShow, learn);
    w.show();

    return app.exec();
}
