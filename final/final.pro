QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4) {
        QT += widgets
        DEFINES += HAVE_QT5
    }
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bento.cpp \
    client.cpp \
    dialog.cpp \
    form.cpp \
    identity.cpp \
    main.cpp \
    mainwindow.cpp \
    networkclient.cpp \
    otherserving.cpp \
    package.cpp \
    people.cpp \
    simulation.cpp \
    staff.cpp \
    tickets.cpp \
    train.cpp

HEADERS += \
    bento.h \
    client.h \
    databasesystem.h \
    dialog.h \
    form.h \
    identity.h \
    mainwindow.h \
    networkclient.h \
    networkserver.h \
    otherserving.h \
    package.h \
    people.h \
    simulation.h \
    staff.h \
    table.h \
    tickets.h \
    train.h

FORMS += \
    dialog.ui \
    form.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    pic.qrc
