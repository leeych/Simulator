QT += widgets

INCLUDEPATH += ./qextserialport
SOURCES += \
    main.cpp \
    qextserialport/win_qextserialport.cpp \
    qextserialport/qextserialport.cpp \
    qextserialport/qextserialbase.cpp \
    testwindow.cpp \
    trafficsimulatordlg.cpp \
    roadbranchwidget.cpp \
    mutility.cpp \
    serialdata.cpp \
    detectorideditwidget.cpp

HEADERS += \
    qextserialport/win_qextserialport.h \
    qextserialport/qextserialport.h \
    qextserialport/qextserialbase.h \
    testwindow.h \
    macrostrings.h \
    trafficsimulatordlg.h \
    roadbranchwidget.h \
    mutility.h \
    serialdata.h \
    detectorideditwidget.h \
    utilmacros.h


DESTDIR = ./

TRANSLATIONS = $$PWD/../resource/languages/simulator.ts

RC_FILE = ../resource/appicon.rc

RESOURCES +=
