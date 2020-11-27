#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/utility/GameValues.h"
#include "src/utility/resource/ResourceManager.h"
#include "src/utility/resource/ResourceLayoutManager.h"
#include "src/utility/GPA/GPAManager.h"
#include "src/utility/GPA/GPALayoutManager.h"
#include "src/utility/week/WeekManager.h"
#include "src/utility/week/WeekLayoutManager.h"
#include "src/map/GameGrid.h"

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Basically all button click events
    // Buy tower
    void on_BuyRegular_clicked();
    void on_BuyArts_clicked();
    void on_BuyWolfram_clicked();
    void on_BuyHacker_clicked();
    void on_BuyCalc_clicked();
    void on_BuyNerd_clicked();
    void on_BuyGWriter_clicked();
    void on_BuyChegg_clicked();

    // Cancel selection / Sell tower
    void on_CancelBuy_clicked();
    void on_TowerMode_clicked();

    // Upgrade Resource Cap
    void on_ResourceUpg_clicked();

    // Bestiary pressed
    void on_Bestiary_clicked();

    // Start Game Pressed
    void on_StartGame_clicked();

    // Clicking on map
    void map_clicked(int x, int y);


private:
    Ui::MainWindow *ui;

    TowerType tower_selected {TowerType::None};

    ResourceManager resource_manager;
    ResourceLayoutManager resource_layout_manager{&resource_manager};

    GPAManager gpa_manager;
    GPALayoutManager gpa_layout_manager{&gpa_manager};

    WeekManager week_manager;
    WeekLayoutManager week_layout_manager{&week_manager};

    QGraphicsScene scene;
    GameGrid game_grid{&scene};
    bool sell_mode {false};
};
#endif // MAINWINDOW_H
