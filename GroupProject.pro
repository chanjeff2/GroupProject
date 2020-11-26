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
	src/enemy/NormalHW.cpp \
    src/main/main.cpp \
    src/main/mainwindow.cpp \
    src/map/GameGrid.cpp \
    src/map/cell.cpp \
	src/tower/Regular.cpp \
	src/tower/attack/IAttackStrategy.cpp \
	src/tower/attack/NormalAttack.cpp \
    src/tower/ITower.cpp \
	src/tower/aura/AuraEffect.cpp \
	src/tower/targetSelect/ITargetSelectionStrategy.cpp \
	src/tower/targetSelect/RandomSelection.cpp \
	src/utility/enemy/EnemyUtility.cpp \
	src/utility/GPA/GPALayoutManager.cpp \
	src/utility/GPA/GPAManager.cpp \
	src/utility/pathfinding/Path.cpp \
	src/utility/pathfinding/PathFindingUtility.cpp \
	src/utility/resource/ResourceLayoutManager.cpp \
	src/utility/resource/ResourceManager.cpp \
	src/utility/tower/TowerUtility.cpp \
	src/utility/week/WeekLayoutManager.cpp \
		src/utility/week/WeekManager.cpp

HEADERS += \
    src/enemy/FocusManager.h \
    src/enemy/IEnemy.h \
    src/enemy/ModManager.h \
	src/enemy/NormalHW.h \
    src/main/mainwindow.h \
    src/map/GameGrid.h \
    src/map/cell.h \
	src/tower/Regular.h \
	src/tower/attack/IAttackStrategy.h \
	src/tower/attack/NormalAttack.h \
    src/tower/ITower.h \
	src/tower/aura/AuraEffect.h \
	src/tower/targetSelect/ITargetSelectionStrategy.h \
	src/tower/targetSelect/RandomSelection.h \
	src/utility/enemy/EnemyUtility.h \
	src/utility/GPA/GPALayoutManager.h \
	src/utility/GPA/GPAManager.h \
    src/utility/GameValues.h \
	src/utility/pathfinding/Path.h \
	src/utility/pathfinding/PathFindingUtility.h \
	src/utility/resource/ResourceLayoutManager.h \
	src/utility/resource/ResourceManager.h \
	src/utility/tower/TowerUtility.h \
	src/utility/week/WeekLayoutManager.h \
	src/utility/week/WeekManager.h

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
