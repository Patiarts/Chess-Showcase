QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    boardwidget.cpp \
    chess.cpp \
    chessboard.cpp \
    chesspiece.cpp \
    chesssquarewidget.cpp \
    knight.cpp \
    main.cpp \
    mainwindow.cpp \
    pawn.cpp \
    king.cpp \
    pieceimage.cpp \
    queen.cpp \
    rook.cpp

HEADERS += \
    bishop.hh \
    boardwidget.hh \
    chess.hh \
    chessboard.hh \
    chesspiece.hh \
    chesssquarewidget.hh \
    knight.hh \
    mainwindow.hh \
    pawn.hh \
    king.hh \
    pieceimage.hh \
    queen.hh \
    rook.hh

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    chess_icons.qrc
