
#include <QApplication>
#include <QIcon>
#include <QTranslator>

#include "testwindow.h"
#include "trafficsimulatordlg.h"
#include "roadbranchwidget.h"
#include "mutility.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString dir = MUtility::getLanguageDir() + "simulator.qm";
    QTranslator translator;
    translator.load(dir);
    app.installTranslator(&translator);

    TestWindow window;
    dir = MUtility::getImagesDir() + "simulator.ico";
    window.setWindowIcon(QIcon(dir));
    window.show();

    return app.exec();
}
