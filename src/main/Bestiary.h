#ifndef BESTIARY_H
#define BESTIARY_H

#include <QWidget>
#include <QGraphicsView>
#include <QTextBrowser>

class BestiaryWindow : public QWidget {
    Q_OBJECT
public:
    BestiaryWindow(QWidget *parent = nullptr);
    ~BestiaryWindow();

private slots:

    // Towers
    void on_Regular_clicked();
    void on_Arts_clicked();
    void on_Wolfram_clicked();
    void on_Hacker_clicked();
    void on_Calculator_clicked();
    void on_Nerd_clicked();
    void on_Ghostwriter_clicked();
    void on_Chegg_clicked();

    // Enemies
    void on_NormalHW_clicked();
    void on_Essay_clicked();
    void on_EncryptedHW_clicked();
    void on_GroupProj_clicked();
    void on_Webwork_clicked();
    void on_Classviva_clicked();

    void on_MathPaperwork_clicked();
    void on_CppFile_clicked();
    void on_HFile_clicked();
    void on_PA_clicked();
    void on_Desmond_clicked();
    void on_PaperPopQuiz_clicked();

    void on_IPRS_clicked();
    void on_Midterm_clicked();
    void on_MathExam_clicked();
    void on_FINAL_clicked();
    void on_ELPA_clicked();
    void on_FYP_clicked();

    // Exit Bestiary
    void on_ExitBestiary_clicked();

};

#endif // BESTIARY_H
