QT       += core gui
QT       += multimedia
QT       += testlib

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
    double_mode.cpp \
    end.cpp \
    end1.cpp \
    end2.cpp \
    end_double_mode.cpp \
    lose_end.cpp \
    main.cpp \
    mainwindow.cpp \
    single_modee.cpp \
    test.cpp \
    victory_end.cpp

HEADERS += \
    double_mode.h \
    end.h \
    end1.h \
    end2.h \
    end_double_mode.h \
    lose_end.h \
    mainwindow.h \
    single_modee.h \
    test.h \
    victory_end.h

FORMS += \
    double_mode.ui \
    end.ui \
    end1.ui \
    end2.ui \
    end_double_mode.ui \
    lose_end.ui \
    mainwindow.ui \
    single_modee.ui \
    victory_end.ui

RC_ICONS = xiyangyang.ico


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

DISTFILES += \
    images/N_E.png \
    images/N_S.png \
    images/S_E.png \
    images/W_E.png \
    images/W_N.png \
    images/W_S.png \
    images/ball1.png \
    images/ball1_1.png \
    images/ball1_2.png \
    images/ball1_3.png \
    images/ball2.png \
    images/ball2_1.png \
    images/ball2_2.png \
    images/ball2_3.png \
    images/ball3.png \
    images/ball3_1.png \
    images/ball3_2.png \
    images/ball3_3.png \
    images/ball4.png \
    images/ball4_1.png \
    images/ball4_2.png \
    images/ball4_3.png \
    images/ball5.png \
    images/ball5_1.png \
    images/ball5_2.png \
    images/ball5_3.png \
    images/ball6.png \
    images/ball6_1.png \
    images/ball6_2.png \
    images/ball6_3.png \
    images/ball7.png \
    images/ball7_1.png \
    images/ball7_2.png \
    images/ball7_3.png \
    images/ball8.png \
    images/ball8_1.png \
    images/ball8_2.png \
    images/ball8_3.png \
    images/ball9.png \
    images/ball9_1.png \
    images/ball9_2.png \
    images/ball9_3.png \
    images/castle.jpg \
    images/dizzy.png \
    images/flash.png \
    images/freeze.png \
    images/grass.jpg \
    images/hint.png \
    images/if.jpg \
    images/main.jpg \
    images/plus.png \
    images/shuffle.png \
    images/user.jpg \
    images/user1.png \
    images/user2.png \
    images/xiyangyang.wav



