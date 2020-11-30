#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/main/clickableview.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(&scene);
    ui->graphicsView->show();
    ui->graphicsView->setMouseTracking(true);

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
    resource_layout_manager.ResourceNeededToUpg = ui->CapUpgCost;
    resource_layout_manager.NotEnoughResources = ui->NotEnoughRes;

	// link manager with layout manager
	game_grid.gpaManager.setLayoutManager(&gpa_layout_manager);
	game_grid.weekManager.setLayoutManager(&week_layout_manager);
	game_grid.resourceManager.setLayoutManager(&resource_layout_manager);

    // Misc stuff
    ui->graphicsView->fitInView(QRect(0, 0, NUM_OF_COL*2, NUM_OF_ROW*2), Qt::KeepAspectRatio);
    week_layout_manager.SkipWeek->setEnabled(false);
    ui->NotEnoughRes->setVisible(false);
    ui->NotEnoughRes->setStyleSheet(QStringLiteral("QLabel{color: rgb(255, 0, 0);}"));

    // Connect signal from clickable GraphicsView to here
    connect(ui->graphicsView, &ClickableView::mouseClicked, this, &MainWindow::map_clicked);
    connect(ui->graphicsView, &ClickableView::mouseHovered, this, &MainWindow::map_hovered);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BuyRegular_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[0]) {
        tower_selected = TowerType::Regular;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_BuyArts_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[1]) {
        tower_selected = TowerType::Arts;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_BuyWolfram_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[2]) {
        tower_selected = TowerType::WolframAlpha;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_BuyHacker_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[3]) {
        tower_selected = TowerType::Hacker;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_BuyCalc_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[4]) {
        tower_selected = TowerType::Calc;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_BuyNerd_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[5]) {
        tower_selected = TowerType::Nerd;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_BuyGWriter_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[6]) {
        tower_selected = TowerType::Ghostwriter;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_BuyChegg_clicked() {
    if (game_grid.resourceManager.getResource() >= TOWER_PRICES[7]) {
        tower_selected = TowerType::Chegg;
        ui->CancelBuy->setEnabled(true);
    }
    else { // Return Not enough resource message
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
        resource_layout_manager.indicateNotEnoughResource();
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

        // Cancel buying towers
        tower_selected = TowerType::None;
        ui->CancelBuy->setEnabled(false);
    }
}

void MainWindow::on_ResourceUpg_clicked() {
    if (game_grid.resourceManager.getResource() >= game_grid.resourceManager.getResourceRequiredForUpgradeCapacity()) {
        game_grid.resourceManager.upgradeResourceCapacity();
    } else {
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_Bestiary_clicked() {
    bestiary_window.show();
}

void MainWindow::on_StartGame_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Waves file"), ".", tr("Text Files (*.txt)"));
    qDebug() << "Wave Info: " << filename;  // You can use qDebug() for debug info
    if (filename == "") return;
    else {
        game_grid.weekManager.loadEnemy(filename.toStdString());
        week_layout_manager.SkipWeek->setEnabled(true);
        game_started = true;
    }
}

void MainWindow::on_SkipWeek_clicked() {
    week_layout_manager.TimeLeft->setText("Time left:");
    game_grid.weekManager.skipToNextWeek();
}

void MainWindow::map_clicked(int x, int y) {
    qDebug() << x << y;
    if (!game_started) return;
    if (!game_grid.isValidCoordinate(x, y)) return;
    if (!sell_mode) {
        game_grid.placeTower(x, y, tower_selected);
    } else {
        game_grid.removeTower(x, y);
    }
};

void MainWindow::map_hovered(int x, int y) {
    delete drawn_range;
    drawn_range = nullptr;
    if (!game_started) return;
    if (!game_grid.isValidCoordinate(x, y)) return;
    if (game_grid.getCell(x, y)->hasTower()) {
        // Draw out the range
        int range = game_grid.getCell(x, y)->getTower()->getRange();
        int starting_pos_x = CELL_SIZE.first * x - range * CELL_SIZE.first;
        int starting_pos_y = CELL_SIZE.second * y - range * CELL_SIZE.second;
        int length_x = CELL_SIZE.first * (2 * range + 1);
        int length_y = CELL_SIZE.second * (2 * range + 1);

        // Constraints to prevent drawing out of bounds
        if (x - range < 0) { starting_pos_x = 0; length_x = CELL_SIZE.first * (x + range + 1);}
        if (y - range < 0) { starting_pos_y = 0; length_y = CELL_SIZE.second * (x + range + 1);}
        if (x + range >= NUM_OF_COL) { length_x = NUM_OF_COL * CELL_SIZE.first - starting_pos_x; }
        if (y + range >= NUM_OF_ROW) { length_y = NUM_OF_ROW * CELL_SIZE.second - starting_pos_y; }

        QGraphicsRectItem* range_to_be_drawn = scene.addRect(QRect(starting_pos_x, starting_pos_y, length_x, length_y), QPen(Qt::black), QBrush(Qt::NoBrush));
        drawn_range = range_to_be_drawn;
    }
};

