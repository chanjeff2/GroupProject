#include "Bestiary.h"
#include "ui_Bestiary.h"
#include <qDebug>


BestiaryWindow::BestiaryWindow(QWidget *parent)
    : QWidget(parent) , ui(new Ui::BestiaryWindow){

    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);

    icon = scene.addPixmap(QPixmap());

    //QGraphicsRectItem* bounds = scene.addRect( QRect(0,0,40,40)) ;
    //ui->graphicsView->fitInView(bounds);
}

BestiaryWindow::~BestiaryWindow() {}

void BestiaryWindow::showEvent(QShowEvent * show_event) {
    //ui->playerGrid->fitInView(player_scene.sceneRect(),Qt::KeepAspectRatio);
    //ui->opponentGrid->fitInView(opponent_scene.sceneRect(), Qt::KeepAspectRatio);
    QGraphicsRectItem* bounds = scene.addRect(QRect(0,0,160,160));
    bounds->setVisible(false);
    ui->graphicsView->fitInView(bounds,Qt::KeepAspectRatio);
}

void BestiaryWindow::on_Regular_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/RegularStudent Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Normal"
                             "\nDescription: Do assignemts by ownself, like an idiot. Cheap to hire one due to its efficiency.");
}

void BestiaryWindow::on_Arts_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/ArtsStudent Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Normal"
                             "\nDescription: Basically a student that is good at writing and literature. Good at writing essays and reports. Dislikes science and technology stuff however. Hmm… Then why they enroll into HKUST?"
                             "\neffective against: Essays, ELPA and FYP"
                             "\nweak against: STEM-related homeworks/exams");
}
void BestiaryWindow::on_Wolfram_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/ArtsStudent Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Normal"
                             "\nDescription: This computational engine can smash every single math-related assignments in it’s sight. But when it comes to non-math-related field…"
                             "\neffective against: math-related assignments"
                             "\nweak against: non-math-related assignments");
}
void BestiaryWindow::on_Hacker_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Hackerman Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Slow (Aura)"
                             "\nDescription: Hacks and modifies the content of the assignment. This leaves the assignment no choice but to extend its deadline. But encrypted ones are too hard for them to hack. Surprisingly they have no knowledge in doing programming assignments."
                             "\nEffective against: Quick assignments"
                             "\nWeak against: Encrypted assignments");
}
void BestiaryWindow::on_Calculator_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Calculator Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Normal"
                             "\nDescription: The game changer brought to us by CASIO technologies. Good at solving most questions, as long as it is allowed to use. Also, you may not want to use it in writing essays."
                             "\nSpecial: Has an aura that weakens 50% of enemies’ AP in range, does not work on enemies that are weak against"
                             "\nWeak against: Maths exam, Essays, ELPA");
}
void BestiaryWindow::on_Nerd_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Nerd Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Aura (Attacks all enemies in range)"
                             "\nDescription: The smart nerd. So smart that can do many assignments at once. But he always get caught by Murphy’s Law so he always make mistakes in his assignment."
                             "\nEffective against: Grouped assignments"
                             "\nWeak against: Assignments with high AP");
}
void BestiaryWindow::on_Ghostwriter_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Ghostwriter Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Sniper"
                             "\nDescription: The marksman that persues “Justice”. Effective against exams, but just not the final ones. When the proctors found it out, your GPA will be in big big troubule. >:)"
                             "\nEffective against: Non-final Examinations"
                             "\nWeak against: Final examinations");
}
void BestiaryWindow::on_Chegg_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Chegg Purchase.png").scaled(160,160));
    ui->textBrowser->setText("Type: Ultimate"
                             "\nDescription: The ultimate platform gathered many elites. Might be able to take students out of misery, only if you have some money…"
                             "\nAbility: Eliminates all assignments in one cell. Examinations (and other bosses) are immune to this skill (Has cooldown to prevent spamming).");
}

void BestiaryWindow::on_NormalHW_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/NormalHW Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Normal"
                             "\nDescription: Just a regular assignment you have."
                             "\nConcept art:");
}
void BestiaryWindow::on_Essay_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Essay Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Tough (High HP and armor)"
                             "\nDescription: Common LANG homework you all have to do. However, this time is Turnitin approved. But wait, you don’t need a calculator for it right?"
                             "\nImmune to calculators");
}
void BestiaryWindow::on_EncryptedHW_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Encrypted Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Immune (to slowness)"
                             "\nDescription: An encrypted homework, that you cannot modify the content, so homework modification won’t help you extend the deadline this time!"
                             "\nImmune to homework modifiers");
}
void BestiaryWindow::on_GroupProj_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/GpPrj Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Group (High enemy count, but low HP & AP)"
                             "\nDescription: As it suggested, it is a “Group” Project. So it is not a surprise if they come in groups. Maybe the smart guys can help here."
                             "\nWeakness: GPA 4.3 Student");
}
void BestiaryWindow::on_Webwork_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW1 Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Armored (Reduced damage)"
                             "\nDescription: MATH. Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators."
                             "\nWeakness: WolframAlpha, Calculators");
}
void BestiaryWindow::on_Classviva_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW2 Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Armored (Reduced damage)"
                             "\nDescription: MATH. Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators."
                             "\nWeakness: WolframAlpha, Calculators");
}

void BestiaryWindow::on_MathPaperwork_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW3 Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Armored (Reduced damage)"
                             "\nDescription: MATH. Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators."
                             "\nWeakness: WolframAlpha, Calculators");
}
void BestiaryWindow::on_CppFile_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/COMPLab Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep Type: Normal"
                             "\nDescription: Something that looks welcoming, but later you will know."
                             "\nC++ Files"
                             "\nObviously that it is where the magic occurs.");
}
void BestiaryWindow::on_HFile_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/COMPLab2 Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep Type: Normal"
                             "\nDescription: Something that looks welcoming, but later you will know."
                             "\nHeader Files"
                             "\nThe thing that keeps your program nice and organized.");
}
void BestiaryWindow::on_PA_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PA Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("\nCreep Type: Tough + Grouped (High HP/AP, and comes in many)"
                             "\nDescription: Takes a lot of your time to finish, so high HP and Armor.");
}
void BestiaryWindow::on_Desmond_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Desmond Grid.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Boss"
                             "\nDescription: spawns new COMP Labs, Programming Asisgnments and additional classes as he advances."
                             "\nWeakness: None");
}
void BestiaryWindow::on_PaperPopQuiz_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PopQuiz1 Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Fast (Faster than normal)"
                             "\nDescription: The thing that students may not aware of. Maybe creating a mistake on the question helps?"
                             "\nWeakness: Homework modifier (Slow towers)"
                             "\nConcept art: (Polymorph)"
                             "\nPaper Pop Quiz"
                             "\nLuckily it is just True or False questions. They are weak!");
}

void BestiaryWindow::on_IPRS_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PopQuiz2 Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Fast (Faster than normal)"
                             "\nDescription: The thing that students may not aware of. Maybe creating a mistake on the question helps?"
                             "\niPRS"
                             "\nJust a few question and your GPA will fall. Wait… The question asks you what is the MTR station between Shek Kip Mei and Lok Fu, but the options are Diamond Hill and Kowloon Bay, hmm…");
}
void BestiaryWindow::on_Midterm_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Midterm Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Boss"
                             "\nDescription: Despite the fact that the paper is purely MC questions, it is hard. You may want a ghostwriter to help with it?"
                             "\nWeakness: Ghostwriters"
                             "\nImmune to Online Tools");
}
void BestiaryWindow::on_MathExam_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathsExam Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Boss"
                             "\nDescription: Calculators are banned?! W H Y ? This is a MATH exam after all!"
                             "\nWeakness: Ghostwriters"
                             "\nImmune to Calculators");
}
void BestiaryWindow::on_FINAL_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/FinalExam Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Boss"
                             "\nDescription: A perfect examination. Even ghostwriters can’t help you now. Make sure no ghostwriters is nearby, or it will rage."
                             "\nSpecial: double HP and speed when ghostwriter is nearby");
}
void BestiaryWindow::on_ELPA_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/ELPA Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Boss(es) (Split)"
                             "\nDescription: Your best 5-in-1 nightmare. Sure that it is tough and futile for calculators."
                             "\nImmune to Calculators");
}
void BestiaryWindow::on_FYP_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/FYP Bestiary.png").scaled(160,160));
    ui->textBrowser->setText("Creep type: Boss"
                             "\nDescription: The thing you cannot avoid. Nothing helps you now."
                             "\nImmune to ghostwriters and online tools");
}

void BestiaryWindow::on_ExitBestiary_clicked() {}
