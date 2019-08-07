#include "include/mainWindow.h"
#include <QApplication>
int main(int argc, char *argv[]) {
    qputenv("QT_STYLE_OVERRIDE", "");
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(100,100,1500,800);
    w.show();
    return a.exec();
}