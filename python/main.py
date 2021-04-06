import sys
import random
import pandas as pd
from PySide6 import QtCore, QtWidgets, QtGui

data = pd.read_csv('../words_data.csv')


class MyWidget(QtWidgets.QWidget):

    current_question = None
    question_mode = 'Romaji'
    answer_mode = 'English'
    correct_questions = 0
    total_questions = 0

    def __init__(self):
        super().__init__()

        self.line_edit = QtWidgets.QLineEdit()
        # noinspection PyArgumentList
        self.question = QtWidgets.QLabel(text="Hello World",
                                         alignment=QtCore.Qt.AlignCenter)
        question_font = QtGui.QFont("", 24)
        self.question.setFont(question_font)
        self.lcd_total = QtWidgets.QLCDNumber()
        self.lcd_score = QtWidgets.QLCDNumber()

        self.layout = QtWidgets.QGridLayout(self)
        self.layout.addWidget(self.question, 1, 0, 1, 2)
        self.layout.addWidget(self.line_edit, 2, 0, 1, 2)
        self.layout.addWidget(self.lcd_total, 0, 0)
        self.layout.addWidget(self.lcd_score, 0, 1)

        self.line_edit.returnPressed.connect(self.on_answer_given)

        self.update_question()

    def update_score(self):
        self.lcd_total.display(self.total_questions)
        self.lcd_score.display(self.correct_questions)

    def update_question(self):
        self.total_questions += 1
        self.update_score()
        self.current_question = data.sample(frac=1).iloc[0]
        self.question.setText(self.current_question[self.question_mode])

    def correct_answer(self):
        self.correct_questions += 1
    # ui->labelCorrect->setText("Correct!");
    # ui->labelCorrect->setStyleSheet("QLabel { background-color : green;}");

    def wrong_answer(self):
        pass
    # wrongString = "Wrong: ";
    # wrongString = wrongString + ansMap[currentKey][questMode] + " = " + ansMap[currentKey][ansMode];
    # ui->labelCorrect->setText(wrongString);
    # ui->labelCorrect->setStyleSheet("QLabel { background-color : red;}");

    def on_answer_given(self):
        given_answer = self.line_edit.text()
        correct_answer = self.current_question[self.answer_mode]
        if given_answer == correct_answer:
            self.correct_answer()
        else:
            self.wrong_answer()
        self.question.setText(self.line_edit.text())
        self.line_edit.clear()
        self.update_question()


if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    widget = MyWidget()
    widget.resize(400, 300)
    widget.show()

    sys.exit(app.exec_())
