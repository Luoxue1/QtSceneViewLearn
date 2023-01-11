QT  += core gui widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/mygraphicsitem.cpp \
    src/mygraphicsscene.cpp \
    src/mygraphicsview.cpp \
    src/operatorhelper.cpp

HEADERS += \
    src/mainwindow.h \
    src/mygraphicsitem.h \
    src/mygraphicsscene.h \
    src/mygraphicsview.h \
    src/operatorhelper.h

FORMS += \
    src/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
