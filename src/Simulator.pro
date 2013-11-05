QT += widgets

INCLUDEPATH += ./qextserialport
SOURCES += \
    main.cpp \
    qextserialport/win_qextserialport.cpp \
    qextserialport/qextserialport.cpp \
    qextserialport/qextserialbase.cpp \
    roadbranchwidget.cpp \
    mutility.cpp \
    serialdata.cpp \
    detectorideditwidget.cpp \
    detectoriddelegate.cpp \
    simulatorwidget.cpp

HEADERS += \
    qextserialport/win_qextserialport.h \
    qextserialport/qextserialport.h \
    qextserialport/qextserialbase.h \
    macrostrings.h \
    roadbranchwidget.h \
    mutility.h \
    serialdata.h \
    detectorideditwidget.h \
    utilmacros.h \
    detectoriddelegate.h \
    simulatorwidget.h


DESTDIR = ./

TRANSLATIONS = $$PWD/../resource/languages/simulator.ts

RC_FILE = ../resource/appicon.rc

RESOURCES +=
