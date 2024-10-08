#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Ltem_Sorting_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
//#include <QApplication>
//#include <QLabel>
//#include <QTextCodec>

//int main(int argc, char **argv)
//{
//    QApplication app(argc, argv);

//    nt fontId = QFontDatabase::addApplicationFont("/usr/share/fonts/truetype/wqy/wqy-zenhei.ttc");

//    QTextCodec *coder = QTextCodec::codecForName("gbk");

//    QLabel label(coder->toUnicode("����!"));
//    label.show();

//    return app.exec();
//}
