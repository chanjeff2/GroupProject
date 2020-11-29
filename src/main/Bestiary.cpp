#include "Bestiary.h"
#include "ui_Bestiary.h"

BestiaryWindow::BestiaryWindow(QWidget *parent)
    : QWidget(parent) , ui(new Ui::BestiaryWindow){
   ui->setupUi(this);
}

BestiaryWindow::~BestiaryWindow() {
    delete ui;
}

void BestiaryWindow::on_Regular_clicked() {}

void BestiaryWindow::on_Arts_clicked() {}
void BestiaryWindow::on_Wolfram_clicked() {}
void BestiaryWindow::on_Hacker_clicked() {}
void BestiaryWindow::on_Calculator_clicked() {}
void BestiaryWindow::on_Nerd_clicked() {}
void BestiaryWindow::on_Ghostwriter_clicked() {}
void BestiaryWindow::on_Chegg_clicked() {}

void BestiaryWindow::on_NormalHW_clicked() {}
void BestiaryWindow::on_Essay_clicked() {}
void BestiaryWindow::on_EncryptedHW_clicked() {}
void BestiaryWindow::on_GroupProj_clicked() {}
void BestiaryWindow::on_Webwork_clicked() {}
void BestiaryWindow::on_Classviva_clicked() {}

void BestiaryWindow::on_MathPaperwork_clicked() {}
void BestiaryWindow::on_CppFile_clicked() {}
void BestiaryWindow::on_HFile_clicked() {}
void BestiaryWindow::on_PA_clicked() {}
void BestiaryWindow::on_Desmond_clicked() {}
void BestiaryWindow::on_PaperPopQuiz_clicked() {}

void BestiaryWindow::on_IPRS_clicked() {}
void BestiaryWindow::on_Midterm_clicked() {}
void BestiaryWindow::on_MathExam_clicked() {}
void BestiaryWindow::on_FINAL_clicked() {}
void BestiaryWindow::on_ELPA_clicked() {}
void BestiaryWindow::on_FYP_clicked() {}

void BestiaryWindow::on_ExitBestiary_clicked() {
    this->close();
}
