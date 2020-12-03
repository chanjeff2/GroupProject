#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "src/main/clickableview.h"

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <cmath>

float GAME_SPEED = 1.0;

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
    resource_layout_manager.NotEnoughResources = ui->Warning;

    // Refresh the intial resource
    resource_layout_manager.updateResource(STARTING_RESOURCE);
    resource_layout_manager.updateResourceCapacity(RESOURCE_CAPACITY[0]);
    resource_layout_manager.updateResourceNeededToUpg(game_grid.resourceManager.getResourceRequiredForUpgradeCapacity());

	// link manager with layout manager
	game_grid.gpaManager.setLayoutManager(&gpa_layout_manager);
	game_grid.weekManager.setLayoutManager(&week_layout_manager);
	game_grid.resourceManager.setLayoutManager(&resource_layout_manager);

    // Misc stuff
	ui->graphicsView->fitInView(QRect(0, 0, NUM_OF_COL*2, NUM_OF_ROW*2), Qt::KeepAspectRatio);
	QTimer::singleShot(500, [&] {
        ui->graphicsView->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
	});
    week_layout_manager.SkipWeek->setEnabled(false);
    ui->Warning->setVisible(false);
    ui->Warning->setStyleSheet(QStringLiteral("QLabel{color: rgb(255, 0, 0);}"));

    // Connect signals from different files
    connect(ui->graphicsView, &ClickableView::mouseClicked, this, &MainWindow::map_clicked);
    connect(ui->graphicsView, &ClickableView::mouseHovered, this, &MainWindow::map_hovered);
    connect(&game_grid.gpaManager, &GPAManager::game_over, this, &MainWindow::game_over_process);
    connect(&game_grid.weekManager, &WeekManager::game_beaten, this, &MainWindow::game_beaten_process);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BuyRegular_clicked() {
    if (!game_started || sell_mode) return;
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
    if (!game_started || sell_mode) return;
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
    if (!game_started || sell_mode) return;
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
    if (!game_started || sell_mode) return;
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
    if (!game_started || sell_mode) return;
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
    if (!game_started || sell_mode) return;
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
    if (!game_started || sell_mode) return;
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
    if (!game_started || sell_mode) return;
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
    if (!game_started) return;
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
    if (!game_started) return;
    if (game_grid.resourceManager.getResource() >= game_grid.resourceManager.getResourceRequiredForUpgradeCapacity()) {
        game_grid.resourceManager.upgradeResourceCapacity();
        if (tower_selected != TowerType::None) {
            // If not enough resources, auto cancel buy tower
            if (game_grid.resourceManager.getResource() < TOWER_PRICES[static_cast<int>(tower_selected)]) {
                ui->Warning->setText("Not enough resources. Buy cancelled");
                ui->Warning->setVisible(true);
                QTimer::singleShot(750, [&]{
                    ui->Warning->setVisible(false);
                });

                delete drawn_range;
                drawn_range = nullptr;
                delete previewed_tower;
                previewed_tower = nullptr;
                tower_selected = TowerType::None;
                ui->CancelBuy->setEnabled(false);
            }
        }
    } else {
        resource_layout_manager.indicateNotEnoughResource();
    }
}

void MainWindow::on_Bestiary_clicked() {
    bestiary_window.show();
}

void MainWindow::on_LoadMap_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Map file"), ".", tr("Text Files (*.txt)"));
    qDebug() << "Map Info: " << filename;  // You can use qDebug() for debug info
    if (filename == "") return;
    else {
        // Notify users the map has loaded
        ui->Warning->setText("Map loaded!");
        ui->Warning->setVisible(true);
		QTimer::singleShot(2000 / GAME_SPEED, [&]{
            ui->Warning->setVisible(false);
        });

		game_grid.loadMap(filename.toStdString());
    }
	ui->graphicsView->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_ResetMap_clicked() {
    game_grid.loadMap();
    ui->graphicsView->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);

    ui->Warning->setText("Map resetted!");
    ui->Warning->setVisible(true);
	QTimer::singleShot(2000 / GAME_SPEED, [&]{
        ui->Warning->setVisible(false);
    });
};

void MainWindow::on_StartGame_clicked() {
    QString filename = QFileDialog::getOpenFileName(this, tr("Open Waves file"), ".", tr("Text Files (*.txt)"));
    qDebug() << "Wave Info: " << filename;  // You can use qDebug() for debug info
    if (filename == "") return;
    else {
        if (!game_grid.weekManager.loadEnemy(filename.toStdString())) {
            // failed to load valid data from enemy file
			ui->Warning->setText("Invalid Enemy Data!");
			ui->Warning->setVisible(true);
			QTimer::singleShot(2000 / GAME_SPEED, [&]{
				ui->Warning->setVisible(false);
			});
            return;
        }

        // Notify users the game has started
        ui->Warning->setText("Game Started!");
        ui->Warning->setVisible(true);
		QTimer::singleShot(2000 / GAME_SPEED, [&]{
            ui->Warning->setVisible(false);
        });

        // Notify managers the game has started
        game_grid.gpaManager.toggle_game_started(true);
        game_grid.weekManager.toggle_game_started(true);
        game_started = true;

        // Initialize stuff
        game_grid.weekManager.prepareForNextWeek(); // start week
        week_layout_manager.SkipWeek->setEnabled(true);

        // Disable buttons
        ui->StartGame->setEnabled(false);
        ui->LoadMap->setEnabled(false);
        ui->ResetMap->setEnabled(false);
    }
}

void MainWindow::on_SkipWeek_clicked() {
    week_layout_manager.TimeLeft->setText("Time left:");
    game_grid.weekManager.skipToNextWeek();
}

void MainWindow::map_clicked(int x, int y) {
    qDebug() << x << y;
	if (!game_started || !game_grid.isValidCoordinate(x, y))
		return;

	if (sell_mode) {
		// delete aura
		drawn_range = nullptr;
		game_grid.removeTower(x, y);
		return;
	}

	if (tower_selected == TowerType::None)
		return;

	// If not enough resources, auto cancel buy tower
	if (game_grid.resourceManager.getResource() < TOWER_PRICES[static_cast<int>(tower_selected)]) {
		ui->Warning->setText("Not enough resources. Buy cancelled");
		ui->Warning->setVisible(true);
		QTimer::singleShot(750, [&]{
			ui->Warning->setVisible(false);
		});
		delete previewed_tower;
		previewed_tower = nullptr;
		tower_selected = TowerType::None;
		ui->CancelBuy->setEnabled(false);
		return;
	}

	// perform place tower, prompt Invalid Placement if failed
	if (!game_grid.placeTower(x, y, tower_selected)) {
		ui->Warning->setText("Invalid Placement");
		ui->Warning->setVisible(true);
		QTimer::singleShot(750, [&]{
			ui->Warning->setVisible(false);
		});
        return;
	}

	// If not enough resources, auto cancel buy next tower
    if (game_grid.resourceManager.getResource() < TOWER_PRICES[static_cast<int>(tower_selected)]) {
		delete previewed_tower;
		previewed_tower = nullptr;
		tower_selected = TowerType::None;
		ui->CancelBuy->setEnabled(false);
	}

	// remove preview range
    drawn_range->setVisible(false);
	drawn_range = nullptr;
};

void MainWindow::map_hovered(int x, int y) {
	Coordinate pos = make_pair(x, y);

	if (!game_started) {
		return;
	}

	if (!game_grid.isValidCoordinate(x, y)) {
		return;
	}

	// do nothing if stay on same cell
	if (pos == this->cursorPos) {
		return;
	}

	{
		Cell *oldCell = game_grid.getCell(cursorPos);
		// hide old range indicator of existing tower
		if ( drawn_range != nullptr && oldCell->hasTower()) {
			// hide border for range
			oldCell->getTower()->showRange(false);
			drawn_range = nullptr;
		}
	}

	// update cursor position
	cursorPos = pos;

	// delete old range if previewing
	if (previewed_tower != nullptr) {
		delete drawn_range;
		drawn_range = nullptr;
		delete previewed_tower;
		previewed_tower = nullptr;
	}

    if (sell_mode) {
        // If in sell mode, show a cross instead of towers
        previewed_tower = scene.addPixmap(QPixmap(":/res/res/misc_images/SellTower"));
        previewed_tower->setZValue(static_cast<float>(Element::Selling));
        previewed_tower->setOffset(x*CELL_SIZE.first, y*CELL_SIZE.second);
    }
    if (game_grid.getCell(x, y)->hasTower()) {
		qDebug() << "MainWindow: show range indicator for existing tower at (" << x << ", " << y << ")";
        // Draw out the range
        drawn_range = game_grid.getCell(x, y)->getTower()->showRange(true);
    } else {
        // No need extra constraint for sell mode (sell mode is forced to select as None)
        if (tower_selected == TowerType::None) return;
        else {
            // Get tower datas
            // Will modify if better methods are found
            QString img_path = QString::fromStdString(TOWER_IMAGES[int(tower_selected)]);

            previewed_tower = scene.addPixmap(QPixmap(img_path));

            previewed_tower->setZValue(static_cast<float>(Element::Preview));
            previewed_tower->setOffset(x*CELL_SIZE.first, y*CELL_SIZE.second);

            previewed_tower->setOpacity(0.5);

			qDebug() << "MainWindow: show range indicator for preview at (" << x << ", " << y << ")";
            // Draw out the range
			drawn_range = this->game_grid.drawRange(tower_selected, pos);
        }
    }

    return;
};

void MainWindow::game_over_process() {
    game_grid.clearBoard();
    QString message = "You were expelled from HKUST for poor academic performance.\n";
    message += "Now you can only watch all the assignments reaching deadline.\n";
    message += "Weeks passed: ";
    message += QString::number(game_grid.weekManager.getWeek() - 1);
    message += "\n(Please wait for all the assignments move to the deadline before restart!)";

    QMessageBox::critical(this, "Game Over!", message, QMessageBox::Ok);
    game_reset();
}

void MainWindow::game_beaten_process() {
    float final_GPA = game_grid.gpaManager.getGPA();
    game_grid.clearBoard();
    if (final_GPA <= 0) return; // You cannot win if you lose all lives at the last week
    QString message = "You have passed the trials of the University of Stress and Tension!\n";
    // Check for what you get in this semester
    if (final_GPA >= 3.9) {
        message += "You got the Academic Achievement Award in this semester! GG!\n";
    } else if (final_GPA >= 3.7 && final_GPA < 3.9) {
        message += "You were on the dean's list of this semester! Good work!\n";
    } else if (final_GPA < 1.5) {
        message += "...But you were put onto the Academic Probation.\n";
    }
    message += "GPA of this semster: ";
    message += QString::number(final_GPA);
    QMessageBox::information(this, "You Win!", message, QMessageBox::Ok);
    game_reset();
}

void MainWindow::game_reset() {
    // Resets everything in the window
    game_started = false;
    tower_selected = TowerType::None;
    sell_mode = false;
    ui->TowerMode->setText("Buy Tower Mode");
    if (drawn_range != nullptr)
        drawn_range->setVisible(false);
    drawn_range = nullptr;
    delete previewed_tower; previewed_tower = nullptr;

    // Enable buttons
    ui->StartGame->setEnabled(true);
    ui->LoadMap->setEnabled(true);
    ui->ResetMap->setEnabled(true);

    // Resets the managers
    game_grid.gpaManager.manager_reset();
    game_grid.resourceManager.manager_reset();
    game_grid.weekManager.manager_reset();

	on_gameSpeed_clicked(true);
}

void MainWindow::on_gameSpeed_clicked(bool reset) {
	if (reset) {
		qDebug() << "MainWindow: set game speed to 1.0";
		GAME_SPEED = 1.0;
		ui->gameSpeed->setText("normal speed");
		return;
	}

	switch(static_cast<int>(GAME_SPEED)) {
		case 1:
			qDebug() << "MainWindow: set game speed to 5.0";
			GAME_SPEED = 5.0;
			ui->gameSpeed->setText(">");
			break;
		case 5:
			qDebug() << "MainWindow: set game speed to 10.0";
			GAME_SPEED = 10.0;
			ui->gameSpeed->setText(">>");
			break;
		default:
			qDebug() << "MainWindow: set game speed to 1.0";
			GAME_SPEED = 1.0;
			ui->gameSpeed->setText("normal speed");
	}
}
