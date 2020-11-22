#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->setWindowTitle("UST Students vs. Assignments - Main Window");

    // Connect signal from clickable GraphicsView to here
    connect(ui->graphicsView, &ClickableView::mouseClicked, this, &MainWindow::map_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BuyRegular_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[0]) {
        tower_selected = TowerType::Regular;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyArts_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[1]) {
        tower_selected = TowerType::Arts;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyWolfram_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[2]) {
        tower_selected = TowerType::WolframAlpha;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyHacker_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[3]) {
        tower_selected = TowerType::Hacker;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyCalc_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[4]) {
        tower_selected = TowerType::Calc;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyNerd_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[5]) {
        tower_selected = TowerType::Nerd;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyGWriter_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[6]) {
        tower_selected = TowerType::Ghostwriter;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyChegg_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[7]) {
        tower_selected = TowerType::Chegg;
        CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

