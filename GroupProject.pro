QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
	src/enemy/EnemyLayoutManager.cpp \
    src/enemy/implementation/CompLab.cpp \
    src/enemy/implementation/Desmond.cpp \
    src/enemy/implementation/Elpa.cpp \
    src/enemy/implementation/EncryptedHW.cpp \
    src/enemy/implementation/Essay.cpp \
    src/enemy/implementation/Final.cpp \
    src/enemy/FocusManager.cpp \
    src/enemy/implementation/Fyp.cpp \
    src/enemy/implementation/GroupProj.cpp \
    src/enemy/IEnemy.cpp \
    src/enemy/implementation/MathExam.cpp \
    src/enemy/implementation/MathHW.cpp \
    src/enemy/ModManager.cpp \
    src/enemy/implementation/Midterm.cpp \
	src/enemy/implementation/NormalHW.cpp \
    src/enemy/implementation/PA.cpp \
    src/enemy/implementation/PopQuiz.cpp \
    src/main/Bestiary.cpp \
    src/main/main.cpp \
    src/main/mainwindow.cpp \
    src/main/ClickableView.cpp \
    src/map/GameGrid.cpp \
    src/map/cell.cpp \
	src/tower/TowerLayoutManager.cpp \
    src/tower/implementation/Arts.cpp \
    src/tower/implementation/Calc.cpp \
    src/tower/implementation/Chegg.cpp \
    src/tower/implementation/Ghostwriter.cpp \
    src/tower/implementation/Hacker.cpp \
    src/tower/implementation/Nerd.cpp \
	src/tower/implementation/Regular.cpp \
    src/tower/implementation/WolframAlpha.cpp \
	src/tower/attack/IAttackStrategy.cpp \
	src/tower/attack/NormalAttack.cpp \
    src/tower/ITower.cpp \
	src/tower/aura/AuraEffect.cpp \
    src/tower/targetSelect/AllSelection.cpp \
	src/tower/targetSelect/ITargetSelectionStrategy.cpp \
    src/tower/targetSelect/NullSelection.cpp \
    src/tower/targetSelect/PrioritySelection.cpp \
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
	src/enemy/EnemyLayoutManager.h \
    src/enemy/implementation/CompLab.h \
    src/enemy/implementation/Desmond.h \
    src/enemy/implementation/Elpa.h \
    src/enemy/implementation/EncryptedHW.h \
    src/enemy/implementation/Essay.h \
    src/enemy/implementation/Final.h \
    src/enemy/FocusManager.h \
    src/enemy/implementation/Fyp.h \
    src/enemy/implementation/GroupProj.h \
    src/enemy/IEnemy.h \
    src/enemy/implementation/MathExam.h \
    src/enemy/implementation/MathHW.h \
    src/enemy/ModManager.h \
    src/enemy/implementation/Midterm.h \
	src/enemy/implementation/NormalHW.h \
    src/enemy/implementation/PA.h \
    src/enemy/implementation/PopQuiz.h \
    src/main/Bestiary.h \
    src/main/mainwindow.h \
    src/main/ClickableView.h \
    src/map/GameGrid.h \
    src/map/cell.h \
	src/tower/TowerLayoutManager.h \
    src/tower/implementation/Arts.h \
    src/tower/implementation/Calc.h \
    src/tower/implementation/Chegg.h \
    src/tower/implementation/Ghostwriter.h \
    src/tower/implementation/Hacker.h \
    src/tower/implementation/Nerd.h \
	src/tower/implementation/Regular.h \
    src/tower/implementation/WolframAlpha.h \
	src/tower/attack/IAttackStrategy.h \
	src/tower/attack/NormalAttack.h \
    src/tower/ITower.h \
	src/tower/aura/AuraEffect.h \
    src/tower/targetSelect/AllSelection.h \
	src/tower/targetSelect/ITargetSelectionStrategy.h \
    src/tower/targetSelect/NullSelection.h \
    src/tower/targetSelect/PrioritySelection.h \
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
    src/main/bestiary.ui \
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
