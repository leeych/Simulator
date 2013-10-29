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
    mutility.cpp

HEADERS += \
    qextserialport/win_qextserialport.h \
    qextserialport/qextserialport.h \
    qextserialport/qextserialbase.h \
    testwindow.h \
    macrostrings.h \
    trafficsimulatordlg.h \
    roadbranchwidget.h \
    mutility.h

RESOURCES += \
    resources.qrc

DESTDIR = ./
