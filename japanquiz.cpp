#include "japanquiz.h"
#include "ui_japanquiz.h"
#include "words_data.h"
#include <QtDebug>
#include <QRandomGenerator>
#include <algorithm>
#include <QKeyEvent>

// Variables

QStringList mykeys = {};
QString currentKey = "";
QStringList selectedKeys = {};
int totalQuestions = -1;
int correctQuestions = 0;
int questMode = 0;
int ansMode = 0;


JapanQuiz::JapanQuiz(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::JapanQuiz)
{
    ui->setupUi(this);
    ui->quitButton->hide();
    ui->stackedWidget->setCurrentWidget(ui->startPage);

    QStringListIterator it(groupMap.keys());
    while (it.hasNext()) {
        QListWidgetItem *listItem = new QListWidgetItem(it.next(), ui->listWidget);
        listItem->setCheckState(Qt::Unchecked);
        ui->listWidget->addItem(listItem);
    }
}

JapanQuiz::~JapanQuiz() {
    delete ui;
}


// Functions

void JapanQuiz::update_questions_from_selection() {
    mykeys.clear();
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        QListWidgetItem* item = ui->listWidget->item(i);
        if (item->checkState())
            mykeys.append(groupMap[item->text()]);
    }
    if (mykeys.size() == 0)
        mykeys = ansMap.keys();
}

void JapanQuiz::update_score() {
    ui->lcdScore->display(correctQuestions);
    ui->lcdTotal->display(totalQuestions);
}

void JapanQuiz::update_question() {
    // TODO: update score inside here
    totalQuestions++;
    update_score();

    std::random_shuffle(mykeys.begin(), mykeys.end());
    currentKey = mykeys[0];
    selectedKeys = mykeys.mid(0, 3);
    std::random_shuffle(selectedKeys.begin(), selectedKeys.end());

    questMode = ui->dropDownQuest->currentIndex();
    ansMode = ui->dropDownAns->currentIndex();

    ui->labelQuestion->setText(ansMap[currentKey][questMode]);

    ui->ansButton1->setText(ansMap[selectedKeys[0]][ansMode]);
    ui->ansButton2->setText(ansMap[selectedKeys[1]][ansMode]);
    ui->ansButton3->setText(ansMap[selectedKeys[2]][ansMode]);
}

void JapanQuiz::on_startButton_clicked() {
    update_questions_from_selection();
    correctQuestions = 0;
    totalQuestions = -1;
    update_question();
    ui->quitButton->show();
    ui->stackedWidget->setCurrentIndex(ui->spinBoxLevel->value());
}

void JapanQuiz::correct_answer() {
    correctQuestions++;
    ui->labelCorrect->setText("Correct!");
    ui->labelCorrect->setStyleSheet("QLabel { background-color : green;}");
}

void JapanQuiz::wrong_answer() {
    QString wrongString = "Wrong: ";
    wrongString = wrongString + ansMap[currentKey][questMode] + " = " + ansMap[currentKey][ansMode];

    ui->labelCorrect->setText(wrongString);
    ui->labelCorrect->setStyleSheet("QLabel { background-color : red;}");
}

void JapanQuiz::on_lineEditAnswer_returnPressed() {
    QString inputText = ui->lineEditAnswer->text();
    QString currentAnswer = ansMap[currentKey][questMode];

    if (QString::compare(inputText, currentAnswer, Qt::CaseInsensitive) == 0)
        correct_answer();
    else
        wrong_answer();
    ui->lineEditAnswer->clear();
    update_question();
}

void JapanQuiz::after_button_clicked(int ansId) {
    if (QString::compare(selectedKeys[ansId], currentKey, Qt::CaseInsensitive) == 0)
        correct_answer();
    else
        wrong_answer();
    update_question();
}

void JapanQuiz::on_ansButton1_clicked() {
    after_button_clicked(0);
}

void JapanQuiz::on_ansButton2_clicked() {
    after_button_clicked(1);
}

void JapanQuiz::on_ansButton3_clicked() {
    after_button_clicked(2);
}

void JapanQuiz::on_quitButton_clicked() {
    ui->stackedWidget->setCurrentWidget(ui->startPage);
    ui->quitButton->hide();
}

void JapanQuiz::keyPressEvent(QKeyEvent *e) {
    if (ui->stackedWidget->currentIndex() == 1)
        switch ((char)e->key()) {
        case '1':
            after_button_clicked(0);
        case '2':
            after_button_clicked(1);
        case '3':
            after_button_clicked(2);
        }
}

