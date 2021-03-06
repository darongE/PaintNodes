#include <QApplication>
#include "mainwindow.h"
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTextCodec::setCodecForCStrings( QTextCodec::codecForName( "utf8" ) );

    MainWindow w;
    w.show();

    return app.exec();
}
