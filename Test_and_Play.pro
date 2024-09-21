QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dialog.cpp \
    about.cpp \
    main.cpp \
    MainWindow.cpp \
    questions_snake.cpp \
    race_game.cpp \
    snake.cpp \
    snake_game.cpp \
    tank_game.cpp

HEADERS += \
    Dialog.h \
    MainWindow.h \
    about.h \
    questions_snake.h \
    race_game.h \
    snake.h \
    snake_game.h \
    tank_game.h

FORMS += \
    Dialog.ui \
    MainWindow.ui \
    about.ui \
    questions_snake.ui \
    race_game.ui \
    snake_game.ui \
    tank_game.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
