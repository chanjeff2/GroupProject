#include "Bestiary.h"
#include "ui_Bestiary.h"
#include <qDebug>


BestiaryWindow::BestiaryWindow(QWidget *parent)
    : QWidget(parent) , ui(new Ui::BestiaryWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);

    icon = scene.addPixmap(QPixmap());

    //QGraphicsRectItem* bounds = scene.addRect( QRect(0,0,40,40)) ;
    //ui->graphicsView->fitInView(bounds);

    ui->textBrowser->setFontPointSize(12);
}

BestiaryWindow::~BestiaryWindow() {
    delete ui;
}

void BestiaryWindow::showEvent(QShowEvent * show_event) {
    //ui->playerGrid->fitInView(player_scene.sceneRect(),Qt::KeepAspectRatio);
    //ui->opponentGrid->fitInView(opponent_scene.sceneRect(), Qt::KeepAspectRatio);
    QGraphicsRectItem* bounds = scene.addRect(QRect(0,0,120,120));
    bounds->setVisible(false);
    ui->graphicsView->fitInView(bounds,Qt::KeepAspectRatio);
}

void BestiaryWindow::on_Regular_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/RegularStudent Purchase.png").scaled(120,120));
    ui->textBrowser->setText("Regular Student"
                             "\n\nType: Normal"
                             "\n\nDescription: Do assignemts by ownself, like an idiot. Cheap to hire one due to its efficiency.");
}

void BestiaryWindow::on_Arts_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/ArtsStudent Purchase.png").scaled(120,120));
    ui->textBrowser->setText("Arts Student"
                             "\n\nType: Normal"
                             "\n\nDescription: Basically a student that is good at writing and literature. Good at writing essays and reports. Dislikes science and technology stuff however. Hmm... Then why they enroll into HKUST?"
                             "\n\nEffective against: Essays, ELPA and FYP"
                             "\n\nweak against: STEM-related homeworks/exams");
}
void BestiaryWindow::on_Wolfram_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Wolfram Purchase.png").scaled(120,120));
    ui->textBrowser->setText("WolframAlpha"
                             "\n\nType: Normal"
                             "\n\nDescription: This computational engine can smash every single math-related assignments in it's sight. But when it comes to non-math-related field..."
                             "\n\nEffective against: Math-related assignments"
                             "\n\nWeak against: Non-math-related assignments");
}
void BestiaryWindow::on_Hacker_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Hackerman Purchase.png").scaled(120,120));
    ui->textBrowser->setText("Hackerman"
                             "\n\nType: Slow"
                             "\n\nDescription: Hacks and modifies the content of the assignment. This leaves the assignment no choice but to extend its deadline. But encrypted ones are too hard for them to hack."
                             "\n\nEffective against: Quick assignments"
                             "\n\nWeak against: Encrypted assignments");
}
void BestiaryWindow::on_Calculator_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Calculator Purchase.png").scaled(120,120));
    ui->textBrowser->setText("Calculator"
                             "\n\nType: Armor Piercing"
                             "\n\nDescription: The game changer brought to us by CASIO technologies. Good at solving most questions, as long as it is allowed to use. Also, you may not want to use it in writing essays."
                             "\n\nSpecial: Has an aura that weakens 50% of enemies' AP in range, does not work on enemies that are weak against."
                             "\n\nWeak against: Maths exam, Essays, ELPA");
}
void BestiaryWindow::on_Nerd_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Nerd Purchase.png").scaled(120,120));
    ui->textBrowser->setText("GPA 4.3 Student"
                             "\n\nType: Multi-Attack"
                             "\n\nDescription: The smart nerd. So smart that can do many assignments at once. But he always get caught by Murphy's Law so he always make mistakes in his assignment."
                             "\n\nEffective against: Grouped assignments"
                             "\n\nWeak against: Assignments with high AP");
}
void BestiaryWindow::on_Ghostwriter_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Ghostwriter Purchase.png").scaled(120,120));
    ui->textBrowser->setText("Ghostwriter"
                             "\n\nType: Sniper"
                             "\n\nDescription: The marksman that persues 'Justice'. Effective against exams, but just not the final ones. When the proctors found it out, your GPA will be in big big troubule. >:)"
                             "\n\nEffective against: Non-final Examinations"
                             "\n\nWeak against: Final examinations");
}
void BestiaryWindow::on_Chegg_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Chegg Purchase.png").scaled(120,120));
    ui->textBrowser->setText("Chegg"
                             "\n\nType: Ultimate"
                             "\n\nDescription: The ultimate platform gathered many elites. Might be able to take students out of misery, only if you have some money..."
                             "\nDoes devestating damage to a single enemy. Has long cooldown however.");
}

void BestiaryWindow::on_NormalHW_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/NormalHW Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Normal Assignments"
                             "\n\nCreep type: Normal"
                             "\n\nDescription: Just a regular assignment you have.");
}
void BestiaryWindow::on_Essay_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Essay Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Essays"
                             "\n\nCreep type: Tough (High HP and armor)"
                             "\n\nDescription: Common LANG homework you all have to do. However, this time is Turnitin approved. But wait, you don't need a calculator for it right?"
                             "\n\nImmune to calculators");
}
void BestiaryWindow::on_EncryptedHW_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Encrypted Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Encrypted Assignments"
                             "\n\nCreep type: Immune (to slowness)"
                             "\n\nDescription: An encrypted homework that you cannot modify the content, so homework modification won't help you extend the deadline this time!"
                             "\n\nImmune to homework modifiers");
}
void BestiaryWindow::on_GroupProj_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/GpPrj Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Group Projects"
                             "\n\nCreep type: Group (High enemy count, but low HP & AP)"
                             "\n\nDescription: As it suggested, it is a 'Group' Project. So it is not a surprise if they come in groups. Maybe the smart guys can help here."
                             "\n\nWeakness: GPA 4.3 Student");
}
void BestiaryWindow::on_Webwork_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW1 Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Mathematics Homeworks - WeBWorK"
                             "\n\nCreep type: Armored (Reduced damage)"
                             "\n\nDescription: MATH. Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators."
                             "\nDeveloped by the University of Rochester. Not sure why the B and K are capitalized here."
                             "\n\nWeakness: WolframAlpha, Calculators");
}
void BestiaryWindow::on_Classviva_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW2 Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Mathematics Homeworks - Classviva"
                             "\n\nCreep type: Armored (Reduced damage)"
                             "\n\nDescription: MATH. Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators."
                             "\nRumors said that its server is composed of a total of 6942 potatoes. No wonder why it always crash and disliked by many UST students."
                             "\n\nWeakness: WolframAlpha, Calculators");
}

void BestiaryWindow::on_MathPaperwork_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW3 Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Mathematics Homeworks - Maths Paper Work"
                             "\n\nCreep type: Armored (Reduced damage)"
                             "\n\nDescription: MATH. Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators."
                             "\nJust a regular Maths Homework sent as pdf format. Answering anything will make your professor ask 'WHAT A COINCIDENCE?!'."
                             "\n\nWeakness: WolframAlpha, Calculators");
}
void BestiaryWindow::on_CppFile_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/COMPLab Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("COMP Labs - C++ Files"
                             "\n\nCreep Type: Normal"
                             "\n\nDescription: Something that looks welcoming, but later you will know."
                             "\nObviously that it is where the magic occurs.");
}
void BestiaryWindow::on_HFile_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/COMPLab2 Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("COMP Labs - Header Files"
                             "\n\nCreep Type: Normal"
                             "\n\nDescription: Something that looks welcoming, but later you will know."
                             "\nThe thing that keeps your program nice and organized.");
}
void BestiaryWindow::on_PA_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PA Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Programming Assignment"
                             "\n\nCreep Type: Tough + Grouped (High HP/AP, and comes in many)"
                             "\n\nDescription: Takes a lot of your time to finish, so high HP and Armor.");
}
void BestiaryWindow::on_Desmond_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Desmond Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Desmond"
                             "\n\nCreep type: Boss"
                             "\n\nDescription: spawns new COMP Labs, Programming Asisgnments and additional classes as he advances."
                             "\n\nWeakness: Too perfect to have one ;)");
}
void BestiaryWindow::on_PaperPopQuiz_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PopQuiz1 Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Pop Quizzes - Paper Pop Quiz"
                             "\n\nCreep type: Fast (Faster than normal)"
                             "\n\nDescription: The thing that students may not aware of. Maybe creating a mistake on the question helps?"
                             "\nLuckily it is just True or False questions. They are weak!"
                             "\n\nWeakness: Homework modifier (Slow towers)");
}

void BestiaryWindow::on_IPRS_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PopQuiz2 Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("iPRS"
                             "\n\nCreep type: Fast (Faster than normal)"
                             "\n\nDescription: The thing that students may not aware of. Maybe creating a mistake on the question helps?"
                             "\nJust a few question and your GPA will fall. Wait... The question asks you what is the MTR station between Shek Kip Mei and Lok Fu, but the options are Diamond Hill and Kowloon Bay, hmm..."
                             "\n\nWeakness: Homework modifier (Slow towers)");
}
void BestiaryWindow::on_Midterm_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Midterm Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Midterm Examinations"
                             "\n\nCreep type: Boss"
                             "\n\nDescription: Despite the fact that the paper is purely MC questions, it is hard. You may want a ghostwriter to help with it?"
                             "\n\nWeakness: Ghostwriters"
                             "\n\nImmune to Online Tools");
}
void BestiaryWindow::on_MathExam_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathsExam Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Mathematics Examinations"
                             "\n\nCreep type: Boss"
                             "\n\nDescription: Calculators are banned?! W H Y ? This is a MATH exam after all!"
                             "\n\nWeakness: Ghostwriters"
                             "\n\nImmune to Calculators");
}
void BestiaryWindow::on_FINAL_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/FinalExam Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Final Examinations"
                             "\n\nCreep type: Boss"
                             "\n\nDescription: A perfect examination. Even ghostwriters can't help you now. Make sure no ghostwriters is nearby, or it will rage."
                             "\n\nSpecial: double HP and speed when inside Ghostwriters' range");
}
void BestiaryWindow::on_ELPA_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/ELPA Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("ELPA"
                             "\n\nCreep type: Boss(es) (Split)"
                             "\n\nDescription: Your best 5-in-1 nightmare. Sure that it is tough and futile for calculators."
                             "\n\nImmune to Calculators");
}
void BestiaryWindow::on_FYP_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/FYP Bestiary.png").scaled(120,120));
    ui->textBrowser->setText("Final Year Project"
                             "\n\nCreep type: Boss"
                             "\n\nDescription: The thing you cannot avoid. Nothing helps you now."
                             "\n\nImmune to ghostwriters and online tools");
}

void BestiaryWindow::on_ExitBestiary_clicked() {
    this->close();
}
