#ifndef JAPANQUIZ_H
#define JAPANQUIZ_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class JapanQuiz; }
QT_END_NAMESPACE

class JapanQuiz : public QMainWindow
{
    Q_OBJECT

public:
    JapanQuiz(QWidget *parent = nullptr);
    ~JapanQuiz();

private slots:
    void on_lineEditAnswer_returnPressed();

    void on_startButton_clicked();

    void on_quitButton_clicked();

    void on_ansButton1_clicked();

    void on_ansButton2_clicked();

    void on_ansButton3_clicked();

private:
    Ui::JapanQuiz *ui;

    void update_questions_from_selection();
    void update_score();
    void update_question();
    void correct_answer();
    void wrong_answer();
    void after_button_clicked(int ansId);

};
#endif // JAPANQUIZ_H
