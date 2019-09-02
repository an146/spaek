#include <cassert>
#include <QApplication>
#include <QtCharts/QChart>
#include "dataset.h"
#include "tablewidget.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    TableWidget w;
    w.show();

    return app.exec();
}
