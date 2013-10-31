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
    serialdata.cpp

HEADERS += \
    qextserialport/win_qextserialport.h \
    qextserialport/qextserialport.h \
    qextserialport/qextserialbase.h \
    testwindow.h \
    macrostrings.h \
    trafficsimulatordlg.h \
    roadbranchwidget.h \
    mutility.h \
    serialdata.h


DESTDIR = ./

TRANSLATIONS = $$PWD/../resource/language/simulator.ts

RC_FILE = ../resource/appicon.rc

RESOURCES +=
