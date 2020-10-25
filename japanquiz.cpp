#include "japanquiz.h"
#include "ui_japanquiz.h"
#include "words_data.h"
#include <QtDebug>
#include <QRandomGenerator>
#include <algorithm>

// Variables

QStringList mykeys = {};
QString currentKey = "";
QStringList selectedKeys = {};
int totalQuestions = -1;
int correctQuestions = 0;


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
    qDebug() << correctQuestions << " / " << totalQuestions;
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

    int gameMode = ui->dropDownMode->currentIndex();
    ui->labelQuestion->setText(ansMap[currentKey][gameMode]);

    ui->ansButton1->setText(ansMap[selectedKeys[0]][gameMode]);
    ui->ansButton2->setText(ansMap[selectedKeys[1]][gameMode]);
    ui->ansButton3->setText(ansMap[selectedKeys[2]][gameMode]);
}

void JapanQuiz::on_startButton_clicked() {
    update_questions_from_selection();
    correctQuestions = 0;
    totalQuestions = -1;
    update_question();
    ui->quitButton->show();
    ui->stackedWidget->setCurrentIndex(ui->spinBoxLevel->value());
}

void JapanQuiz::on_lineEditAnswer_returnPressed() {

    QString inputText = ui->lineEditAnswer->text();
    QString currentAnswer = currentKey;

    if (QString::compare(inputText, currentAnswer, Qt::CaseInsensitive) == 0)
        correctQuestions++;
    ui->lineEditAnswer->clear();
    update_question();
}

void JapanQuiz::after_button_clicked(int ansId) {
    if (QString::compare(selectedKeys[ansId], currentKey, Qt::CaseInsensitive) == 0)
        correctQuestions++;
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
