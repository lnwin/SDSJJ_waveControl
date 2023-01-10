QT       += core gui network printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    crc.cpp \
    main.cpp \
    mainwindow.cpp \
    mychart.cpp \
    qcustomplot.cpp \
    socket.cpp \
    waveconfig.cpp

HEADERS += \
    crc.h \
    mainwindow.h \
    mychart.h \
    qcustomplot.h \
    socket.h \
    waveconfig.h

FORMS += \
    mainwindow.ui \
    waveconfig.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
