#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/utility/GameValues.h"
#include "src/utility/ResourceManager.h"
#include "src/utility/GPAManager.h"

#include <QMainWindow>

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
    void on_SellTower_clicked();

    // Upgrade Resource Cap
    void on_ResourceUpg_clicked();

    // Bestiary pressed
    void on_Bestiary_clicked();

    // Clicking on map
    void map_clicked(int row, int col);


private:
	Ui::MainWindow *ui;
    TowerType tower_selected {TowerType::None};
    ResourceManager resource_manager;
    GPAManager gpa_manager;
};
#endif // MAINWINDOW_H
