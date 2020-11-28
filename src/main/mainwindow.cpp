#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ClickableView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();

    this->setWindowTitle("UST Students vs. Assignments - Main Window");

    // Link the objects with the layout manager
    gpa_layout_manager.GPALabel = ui->GPA;
    gpa_layout_manager.GradeLabel = ui->GPAGrade;

    week_layout_manager.SkipWeek = ui->SkipWeek;
    week_layout_manager.TimeLeft = ui->TimeLeft;
    week_layout_manager.WeekCount = ui->WeekNo;
    week_layout_manager.WeekProgress = ui->Week;

    resource_layout_manager.Resource = ui->Resource;
    resource_layout_manager.ResourceCap = ui->ResourceCap;
    resource_layout_manager.ResourceUpgrade = ui->ResourceUpg;

    // Connect signal from clickable GraphicsView to here
    connect(ui->graphicsView, SIGNAL(ClickableView::mouseClicked), this, SLOT(MainWindow::map_clicked));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BuyRegular_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[0]) {
        tower_selected = TowerType::Regular;
        ui->CancelBuy->setEnabled(false);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyArts_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[1]) {
        tower_selected = TowerType::Arts;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyWolfram_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[2]) {
        tower_selected = TowerType::WolframAlpha;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyHacker_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[3]) {
        tower_selected = TowerType::Hacker;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyCalc_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[4]) {
        tower_selected = TowerType::Calc;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyNerd_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[5]) {
        tower_selected = TowerType::Nerd;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyGWriter_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[6]) {
        tower_selected = TowerType::Ghostwriter;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_BuyChegg_clicked() {
    if (resource_manager.getResource() >= TOWER_PRICES[7]) {
        tower_selected = TowerType::Chegg;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message

    }
}

void MainWindow::on_CancelBuy_clicked() {
    tower_selected = TowerType::None;
    ui->CancelBuy->setEnabled(false);
}

void MainWindow::on_TowerMode_clicked() {
    if (sell_mode) {
        sell_mode = false;
        ui->TowerMode->setText("Buy Tower Mode");
    } else {
        sell_mode = true;
        ui->TowerMode->setText("Sell Tower Mode");
    }
}

void MainWindow::on_ResourceUpg_clicked() {
    if (resource_manager.getResource() >= resource_manager.getResourceRequiredForUpgradeCapacity()) {
        resource_manager.upgradeResourceCapacity();
        if (resource_manager.getResourceCapacity() == RESOURCE_CAPACITY[NUM_OF_RESOURCE_CAPACITY - 1]) {
            ui->ResourceUpg->setText("Maxed!");
            ui->ResourceUpg->setEnabled(false);
        }
    }
}

void MainWindow::on_Bestiary_clicked() {

}

void MainWindow::on_StartGame_clicked() {

}

void MainWindow::map_clicked(int x, int y) {
    if (sell_mode) {
        game_grid.placeTower(x, y, tower_selected);
    } else {
        game_grid.removeTower(x, y);
    }
};

