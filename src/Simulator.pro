QT += widgets
QT += network xml

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
    simulatorwidget.cpp \
    synccommand.cpp \
    command.cpp \
    xmlhelper.cpp \
    tscparam.cpp \
    filereaderwriter.cpp \
    mdatabase.cpp \
    timingparam.cpp \
    timesection.cpp \
    signalerparam.cpp \
    phasetiming.cpp \
    phaseparam.cpp \
    phaseconflictparam.cpp \
    detectorparam.cpp \
    channelparam.cpp \
    scheduleparam.cpp \
    testdlg.cpp \
    phasehandler.cpp

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
    simulatorwidget.h \
    synccommand.h \
    command.h \
    xmlhelper.h \
    tscparam.h \
    tsc.h \
    filereaderwriter.h \
    mdatabase.h \
    timingparam.h \
    timesection.h \
    signalerparam.h \
    scheduleparam.h \
    phasetiming.h \
    phaseparam.h \
    phaseconflictparam.h \
    detectorparam.h \
    channelparam.h \
    testdlg.h \
    phasehandler.h


DESTDIR = ./

TRANSLATIONS = $$PWD/../resource/languages/simulator.ts

RC_FILE = ../resource/appicon.rc

RESOURCES +=
