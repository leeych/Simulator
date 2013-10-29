
#include <QApplication>
#include "testwindow.h"
#include "trafficsimulatordlg.h"
#include "roadbranchwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TestWindow window;
    window.show();
//    RoadBranchWidget roadwidget;
//    roadwidget.show();

    return app.exec();
}
