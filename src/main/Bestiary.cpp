#include "Bestiary.h"
#include "ui_Bestiary.h"


BestiaryWindow::BestiaryWindow(QWidget *parent)
    : QWidget(parent) , ui(new Ui::BestiaryWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);

    this->setWindowTitle("UST Students vs. Assignments - Bestiary");

    icon = scene.addPixmap(QPixmap());

    //QGraphicsRectItem* bounds = scene.addRect( QRect(0,0,40,40)) ;
    //ui->graphicsView->fitInView(bounds);
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
    ui->textBrowser->setHtml("<center><b><h2>Regular Student</b></center>"
                             "<b>Type:</b> Normal<br><br>"
                             "<b>Description:</b> Do assignemts by ownself, like an <s>idiot</s>. Cheap to hire one due to its efficiency.");
}

void BestiaryWindow::on_Arts_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/ArtsStudent Purchase.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Arts Student</b></center>"
                             "<b>Type:</b> Normal<br><br>"
                             "<b>Description:</b> Basically a student that is good at writing and literature. Good at writing essays and reports. Dislikes science and technology stuff however. Hmm... Then why they enroll into HKUST?<br><br>"
                             "<b>Effective against:</b> Essays, ELPA and FYP<br><br>"
                             "<b>Weak against:</b> STEM-related homeworks/exams");
}
void BestiaryWindow::on_Wolfram_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Wolfram Purchase.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>WolframAlpha</b></center>"
                             "<b>Type:</b> Normal<br><br>"
                             "<b>Description:</b> This computational engine can smash every single math-related assignments in it's sight. But when it comes to non-math-related field...<br><br>"
                             "<b>Effective against:</b> Math-related assignments<br><br>"
                             "<b>Weak against:</b> Non-math-related assignments");
}
void BestiaryWindow::on_Hacker_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Hackerman Purchase.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Hackerman</b></center>"
                             "<b>Type:</b> Slow<br><br>"
                             "<b>Description:</b> Hacks and modifies the content of the assignment. This leaves the assignment no choice but to extend its deadline. But encrypted ones are too hard for them to hack.<br><br>"
                             "<b>Effective against:</b> Quick assignments<br><br>"
                             "<b>Weak against:</b> Encrypted assignments");
}
void BestiaryWindow::on_Calculator_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Calculator Purchase.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Calculator</b></center>"
                             "<b>Type:</b> Armor Piercing<br><br>"
                             "<b>Description:</b> The game changer brought to us by CASIO technologies. Good at solving most questions, as long as it is allowed to use. Also, you may not want to use it in writing essays.<br><br>"
                             "<b>Special:</b> Has an aura that weakens 50% of enemies' AP in range, does not work on enemies that are weak against.<br><br>"
                             "<b>Weak against:</b> Maths exam, Essays, ELPA");
}
void BestiaryWindow::on_Nerd_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Nerd Purchase.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>GPA 4.3 Student</b></center>"
                             "<b>Type:</b> Multi-Attack<br><br>"
                             "<b>Description:</b> The smart nerd. So smart that can do many assignments at once. But he always get caught by Murphy's Law so he always make mistakes in his assignment.<br><br>"
                             "<b>Effective against:</b> Grouped assignments<br><br>"
                             "<b>Weak against:</b> Assignments with high AP");
}
void BestiaryWindow::on_Ghostwriter_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Ghostwriter Purchase.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Ghostwriter</b></center>"
                             "<b>Type:</b> Sniper<br><br>"
                             "<b>Description:</b> The marksman that persues 'Justice'. Effective against exams, but just not the final ones. When the proctors found it out, your GPA will be in <b>big big</b> troubule. >:)<br><br>"
                             "<b>Effective against:</b> Non-final Examinations<br><br>"
                             "<b>Weak against:</b> Final examinations");
}
void BestiaryWindow::on_Chegg_clicked() {
    icon->setPixmap(QPixmap(":/res/res/towers_images/Chegg Purchase.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Chegg</b></center>"
                             "<b>Type:</b> Ultimate<br><br>"
                             "<b>Description:</b> The ultimate platform gathered many elites. Might be able to take students out of misery, only if you have some money...<br>"
                             "Does devestating damage to a single enemy. Has long cooldown however.");
}

void BestiaryWindow::on_NormalHW_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/NormalHW Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Normal Assignments</b></center>"
                             "<b>Creep type:</b> Normal<br><br>"
                             "<b>Description:</b> Just a regular assignment you have.");
}
void BestiaryWindow::on_Essay_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Essay Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Essays</b></center>"
                             "<b>Creep type:</b> Tough (High HP and armor)<br><br>"
                             "<b>Description:</b> Common LANG homework you all have to do. However, this time is Turnitin approved. But wait, you don't need a calculator for it right?<br><br>"
                             "<b>Immune to calculators</b>");
}
void BestiaryWindow::on_EncryptedHW_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Encrypted Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Encrypted Assignments</b></center>"
                             "<b>Creep type:</b> Immune (to slowness)<br><br>"
                             "<b>Description:</b> An encrypted homework that you cannot modify the content, so homework modification won't help you extend the deadline this time!<br><br>"
                             "<b>Immune to homework modifiers</b>");
}
void BestiaryWindow::on_GroupProj_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/GpPrj Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Group Projects</b></center>"
                             "<b>Creep type:</b> Group (High enemy count, but low HP & AP) <br><br>"
                             "<b>Description:</b> As it suggested, it is a 'Group' Project. So it is not a surprise if they come in groups. Maybe the smart guys can help here.<br><br>"
                             "<b>Weakness:</b> GPA 4.3 Student");
}
void BestiaryWindow::on_Webwork_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW1 Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Mathematics Homeworks</b></center>"
                             "<center><b><h3>WeBWorK</b></center>"
                             "<b>Creep type:</b> Armored (Reduced damage)<br><br>"
                             "<b>Description:</b> Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators.<br>"
                             "Developed by the University of Rochester. Not sure why the B and K are capitalized here.<br><br>"
                             "<b>Weakness:</b> WolframAlpha, Calculators");
}
void BestiaryWindow::on_Classviva_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW2 Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Mathematics Homeworks</b></center>"
                             "<center><b><h3>Classviva</b></center>"
                             "<b>Creep type:</b> Armored (Reduced damage)<br><br>"
                             "<b>Description:</b> Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators.<br>"
                             "Rumors said that its server is composed of a total of 6942 potatoes. No wonder why it always crashes and disliked by many UST students.<br><br>"
                             "<b>Weakness:</b> WolframAlpha, Calculators");
}

void BestiaryWindow::on_MathPaperwork_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathHW3 Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Mathematics Homeworks</b></center>"
                             "<center><b><h3>Maths Paper Work</b></center>"
                             "<b>Creep type:</b> Armored (Reduced damage)<br><br>"
                             "<b>Description:</b> Mental Abuse To Humans as we said. Very difficult for students, but not for online tools and calculators.<br>"
                             "Just a regular Maths Homework sent as pdf format. Answering anything will make your professor ask 'WHAT A COINCIDENCE?!'.<br><br>"
                             "<b>Weakness:</b> WolframAlpha, Calculators");
}
void BestiaryWindow::on_CppFile_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/COMPLab Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>COMP Labs</b></center>"
                             "<center><b><h3>C++ Files</b></center>"
                             "<b>Creep type:</b> Normal<br><br>"
                             "<b>Description:</b> Something that looks welcoming, but later you will know.<br>"
                             "Obviously that it is where the magic occurs.");
}
void BestiaryWindow::on_HFile_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/COMPLab2 Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>COMP Labs</b></center>"
                             "<center><b><h3>Header Files</b></center>"
                             "<b>Creep type:</b> Normal<br><br>"
                             "<b>Description:</b> Something that looks welcoming, but later you will know.<br>"
                             "The thing that keeps your program nice and organized.");
}
void BestiaryWindow::on_PA_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PA Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Programming Assignment</b></center>"
                             "<b>Creep type:</b> Tough + Grouped (High HP/AP, and comes in many)<br><br>"
                             "<b>Description:</b> The thing that takes a lot of your time to finish.");
}
void BestiaryWindow::on_Desmond_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Desmond Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Desmond</b></center>"
                             "<b>Creep type:</b> Boss<br><br>"
                             "<b>Description:</b> Our dearest professor. A good guy na!<br><br>"
                             "<b>Weakness:</b> Too perfect to have one ;)");
}
void BestiaryWindow::on_PaperPopQuiz_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PopQuiz1 Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Pop Quizzes</b></center>"
                             "<center><b><h3>Paper Pop Quiz</b></center>"
                             "<b>Creep type:</b> Fast (Faster than normal)<br><br>"
                             "<b>Description:</b> The thing that students may not aware of. Maybe creating a mistake on the question helps?<br>"
                             "Luckily it is just True or False questions. They are weak!<br><br>"
                             "<b>Weakness:</b> Homework modifier (Slow towers)");
}

void BestiaryWindow::on_IPRS_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/PopQuiz2 Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Pop Quizzes</b></center>"
                             "<center><b><h3>iPRS</b></center>"
                             "<b>Creep type:</b> Fast (Faster than normal)<br><br>"
                             "<b>Description:</b> The thing that students may not aware of. Maybe creating a mistake on the question helps?<br>"
                             "Just a few question and your GPA will fall. Wait... The question asks you what is the MTR station between Shek Kip Mei and Lok Fu, but the options are Diamond Hill and Kowloon Bay, hmm...<br><br>"
                             "<b>Weakness:</b> Homework modifier (Slow towers)");
}
void BestiaryWindow::on_Midterm_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/Midterm Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Midterm Examinations</b></center>"
                             "<b>Creep type:</b> Boss<br><br>"
                             "<b>Description:</b> Despite the fact that the paper is purely MC questions, it is hard. You may want a ghostwriter to help with it?<br><br>"
                             "<b>Weakness:</b> Ghostwriters<br><br>"
                             "<b>Immune to Online Tools</b>");
}
void BestiaryWindow::on_MathExam_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/MathsExam Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Mathematics Examinations</b></center>"
                             "<b>Creep type:</b> Boss<br><br>"
                             "<b>Description:</b> Calculators are banned?! W H Y ? This is a MATH exam after all!<br><br>"
                             "<b>Weakness:</b> Ghostwriters<br><br>"
                             "<b>Immune to Calculators</b>");
}
void BestiaryWindow::on_FINAL_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/FinalExam Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Final Examinations</b></center>"
                             "<b>Creep type:</b> Boss<br><br>"
                             "<b>Description:</b> A perfect examination. Even ghostwriters can't help you now. Make sure no ghostwriters is nearby, or it will <b>rage</b>.<br><br>"
                             "<b>Special:</b> double HP and speed when inside Ghostwriters' range");
}
void BestiaryWindow::on_ELPA_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/ELPA Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>ELPA</b></center>"
                             "<b>Creep type:</b> Boss<br><br>"
                             "<b>Description:</b> Your best 5-in-1 nightmare. Sure that it is tough and futile for calculators.<br><br>"
                             "<b>Immune to Calculators</b>");
}
void BestiaryWindow::on_FYP_clicked() {
    icon->setPixmap(QPixmap(":/res/res/enemies_images/FYP Bestiary.png").scaled(120,120));
    ui->textBrowser->setHtml("<center><b><h2>Final Year Project</b></center>"
                             "<b>Creep type:</b> Boss<br><br>"
                             "<b>Description:</b> The thing you cannot avoid. Nothing helps you now.<br><br>"
                             "<b>Immune to ghostwriters and online tools</b>");
}

void BestiaryWindow::on_ExitBestiary_clicked() {
    this->close();
}
