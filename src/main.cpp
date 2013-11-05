
#include <QApplication>
#include <QIcon>
#include <QTranslator>

#include "simulatorwidget.h"
#include "roadbranchwidget.h"
#include "mutility.h"

#include "detectorideditwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//#if 0
    QString dir = MUtility::getLanguageDir() + "simulator.qm";
    QTranslator translator;
    translator.load(dir);
    app.installTranslator(&translator);
#if 1
    SimulatorWidget window;
    dir = MUtility::getImagesDir() + "simulator.ico";
    window.setWindowIcon(QIcon(dir));
    window.show();
#endif

#if 0
    DetectorIdEditWidget widget;
    widget.show();
#endif
    return app.exec();
}
