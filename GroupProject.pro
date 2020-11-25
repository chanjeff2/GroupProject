QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/enemy/FocusManager.cpp \
    src/enemy/IEnemy.cpp \
    src/enemy/ModManager.cpp \
    src/main/main.cpp \
    src/main/mainwindow.cpp \
    src/map/GameGrid.cpp \
    src/map/cell.cpp \
	src/tower/attack/IAttackStrategy.cpp \
	src/tower/aura/IAuraEffectStrategy.cpp \
    src/tower/ITower.cpp \
	src/tower/targetSelect/ITargetSelectionStrategy.cpp \
    src/utility/EnemyUtility.cpp \
    src/utility/GPALayoutManager.cpp \
	src/utility/GPAManager.cpp \
	src/utility/PathFindingUtility.cpp \
	src/utility/ResourceManager.cpp \
	src/utility/TowerUtility.cpp \
    src/utility/WeekLayoutManager.cpp \
        src/utility/WeekManager.cpp

HEADERS += \
    src/enemy/FocusManager.h \
    src/enemy/IEnemy.h \
    src/enemy/ModManager.h \
    src/main/mainwindow.h \
    src/map/GameGrid.h \
    src/map/cell.h \
	src/tower/attack/IAttackStrategy.h \
	src/tower/aura/IAuraEffectStrategy.h \
    src/tower/ITower.h \
	src/tower/targetSelect/ITargetSelectionStrategy.h \
    src/utility/EnemyUtility.h \
    src/utility/GPALayoutManager.h \
	src/utility/GPAManager.h \
    src/utility/GameValues.h \
	src/utility/PathFindingUtility.h \
	src/utility/ResourceManager.h \
	src/utility/TowerUtility.h \
    src/utility/WeekLayoutManager.h \
	src/utility/WeekManager.h

FORMS += \
    src/main/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
	.gitignore \
	LICENSE \
	README.md

RESOURCES += \
    assets.qrc
