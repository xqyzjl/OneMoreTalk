QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cloud.cpp \
    forgetwindow.cpp \
    friendlistitem.cpp \
    global/globaldata.cpp \
    global/groupinfo.cpp \
    global/message.cpp \
    global/publicinfo.cpp \
    infowindow.cpp \
    loginwindow.cpp \
    loglistitem.cpp \
    main.cpp \
    mainwindow.cpp \
    mdwindow.cpp \
    signupwindow.cpp

HEADERS += \
    cloud.h \
    forgetwindow.h \
    friendlistitem.h \
    global/globaldata.h \
    global/groupinfo.h \
    global/message.h \
    global/publicinfo.h \
    infowindow.h \
    loginwindow.h \
    loglistitem.h \
    mainwindow.h \
    mdwindow.h \
    signupwindow.h

FORMS += \
    forgetwindow.ui \
    infowindow.ui \
    loginwindow.ui \
    mainwindow.ui \
    mdwindow.ui \
    signupwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Resources.qrc
