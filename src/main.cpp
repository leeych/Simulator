
#include <QApplication>
#include <QIcon>
#include <QTranslator>

#include "testwindow.h"
#include "trafficsimulatordlg.h"
#include "roadbranchwidget.h"
#include "mutility.h"

#include "detectorideditwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
#if 0
    QString dir = MUtility::getLanguageDir() + "simulator.qm";
    QTranslator translator;
    translator.load(dir);
    app.installTranslator(&translator);

    TestWindow window;
    dir = MUtility::getImagesDir() + "simulator.ico";
    window.setWindowIcon(QIcon(dir));
    window.show();
#endif
    DetectorIdEditWidget widget;
    widget.show();
    return app.exec();
}
