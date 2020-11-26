#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("UST Students vs. Assignments - Main Window");

    // Link the objects with the layout manager
    gpa_manager.accessToLayoutManager()->GPALabel = ui->GPA;
    gpa_manager.accessToLayoutManager()->GradeLabel = ui->GPAGrade;

    week_manager.accessToLayoutManager()->SkipWeek = ui->SkipWeek;
    week_manager.accessToLayoutManager()->TimeLeft = ui->TimeLeft;
    week_manager.accessToLayoutManager()->WeekCount = ui->WeekNo;
    week_manager.accessToLayoutManager()->WeekProgress = ui->Week;

    resource_manager.accessToLayoutManager()->Resource = ui->Resource;
    resource_manager.accessToLayoutManager()->ResourceCap = ui->ResourceCap;
    resource_manager.accessToLayoutManager()->ResourceUpgrade = ui->ResourceUpg;

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

