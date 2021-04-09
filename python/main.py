import sys
import random
import pandas as pd
from PySide6 import QtCore, QtGui
from PySide6.QtWidgets import (
    QApplication, QWidget, QGridLayout, QHBoxLayout, QVBoxLayout,
    QLabel, QPushButton, QComboBox, QListWidget, QListWidgetItem, QLineEdit,
    QLCDNumber, QStackedWidget, QSpinBox
)

W, H = 800, 400

data = pd.read_csv('../words_data.csv').ffill()

GROUPS = data['Group'].unique()
MODES = data.drop(columns='Group').columns


class Page1Widget(QWidget):
    
    def __init__(self):
        super().__init__()

        # Create Widgets
        self.dropdown_quest = QComboBox()
        self.dropdown_quest.addItems(MODES)
        self.dropdown_quest.setCurrentText("Romaji")
        self.dropdown_ans = QComboBox()
        self.dropdown_ans.addItems(MODES)
        self.spinbox_level = QSpinBox()
        self.spinbox_level.setMinimum(1)
        self.spinbox_level.setMaximum(2)

        self.list_groups = QListWidget(FixedWidth=W * .6)
        for group_name in GROUPS:
            item = QListWidgetItem(group_name)
            item.setCheckState(QtCore.Qt.Unchecked)
            self.list_groups.addItem(item)

        # Make Layout
        self.sub_layout = QVBoxLayout()
        self.sub_layout.addWidget(QLabel('Question:'))
        self.sub_layout.addWidget(self.dropdown_quest)
        self.sub_layout.addWidget(QLabel('Answer:'))
        self.sub_layout.addWidget(self.dropdown_ans)
        self.sub_layout.addWidget(QLabel('Level:'))
        self.sub_layout.addWidget(self.spinbox_level)

        self.layout = QHBoxLayout(self)
        self.layout.addLayout(self.sub_layout)
        self.layout.addWidget(self.list_groups)


class Page2Widget(QWidget):
    def __init__(self):
        super().__init__()

        self.layout = QHBoxLayout(self)
        self.ans_buttons = []
        for i in range(3):
            self.ans_buttons.append(QPushButton(FixedHeight=70))
            self.layout.addWidget(self.ans_buttons[i])


class Page3Widget(QWidget):
    def __init__(self):
        super().__init__()

        self.line_edit = QLineEdit()

        self.layout = QGridLayout(self)
        self.layout.addWidget(self.line_edit)


class MainWidget(QWidget):
    data = None
    current_question = None
    current_correct_answer = None
    buttons_choices = None
    question_mode = None
    answer_mode = None
    correct_questions = 0
    total_questions = 0

    def __init__(self):
        super().__init__()

        # Create Widgets
        self.question = QLabel("Press Start")
        self.question.setAlignment(QtCore.Qt.AlignCenter)
        self.question.setFont(QtGui.QFont("", 30))

        self.label_correct = QLabel()
        self.label_correct.setAlignment(QtCore.Qt.AlignCenter)

        self.button_quit = QPushButton("Quit", Visible=False)
        self.button_start = QPushButton("Start")
        lcd_height = 40
        self.lcd_total = QLCDNumber(SegmentStyle=QLCDNumber.Flat, FixedHeight=lcd_height)
        self.lcd_score = QLCDNumber(SegmentStyle=QLCDNumber.Flat, FixedHeight=lcd_height)

        self.stack = QStackedWidget()
        self.page1 = Page1Widget()
        self.page2 = Page2Widget()
        self.page3 = Page3Widget()
        self.stack.addWidget(self.page1)
        self.stack.addWidget(self.page2)
        self.stack.addWidget(self.page3)

        # Make Layout
        self.layout = QGridLayout(self)
        self.layout.addWidget(self.question, 2, 0, 1, 2)
        self.layout.addWidget(self.label_correct, 1, 0, 1, 2)
        self.layout.addWidget(self.lcd_total, 0, 0)
        self.layout.addWidget(self.lcd_score, 0, 1)
        self.layout.addWidget(self.stack, 3, 0, 1, 2)
        self.layout.addWidget(self.button_quit, 4, 0)
        self.layout.addWidget(self.button_start, 4, 1)

        # Connect Callbacks
        self.button_quit.clicked.connect(self.on_quit_pressed)
        self.button_start.clicked.connect(self.on_start_pressed)
        self.page2.ans_buttons[0].clicked.connect(self.on_ans_button0_clicked)
        self.page2.ans_buttons[1].clicked.connect(self.on_ans_button1_clicked)
        self.page2.ans_buttons[2].clicked.connect(self.on_ans_button2_clicked)
        self.page3.line_edit.returnPressed.connect(self.on_answer_given)

    def update_questions_from_selection(self):
        selected_groups = []
        for i in range(self.page1.list_groups.count()):
            item = self.page1.list_groups.item(i)
            if item.checkState():
                selected_groups.append(item.text())
        if len(selected_groups) == 0:
            self.data = data
        else:
            self.data = data.loc[data['Group'].isin(selected_groups), :]

    def on_quit_pressed(self):
        self.button_start.setVisible(True)
        self.button_quit.setVisible(False)
        self.question.clear()
        self.stack.setCurrentIndex(0)

    def on_start_pressed(self):
        self.update_questions_from_selection()
        self.button_start.setVisible(False)
        self.button_quit.setVisible(True)
        self.total_questions = -1
        self.correct_questions = 0
        self.stack.setCurrentIndex(int(self.page1.spinbox_level.text()))
        self.question_mode = MODES[self.page1.dropdown_quest.currentIndex()]
        self.answer_mode = MODES[self.page1.dropdown_ans.currentIndex()]
        self.update_question()

    def update_score(self):
        self.lcd_total.display(self.total_questions)
        self.lcd_score.display(self.correct_questions)

    def update_question(self):
        self.total_questions += 1
        self.update_score()
        picked_questions = self.data.sample(frac=1).iloc[:3]
        self.current_question = picked_questions.iloc[0]
        self.current_correct_answer = self.current_question[self.answer_mode]

        self.question.setText(self.current_question[self.question_mode])

        self.buttons_choices = list(picked_questions[self.answer_mode])
        random.shuffle(self.buttons_choices)
        for button, answer in zip(self.page2.ans_buttons, self.buttons_choices):
            button.setText(answer)

    def correct_answer(self):
        self.correct_questions += 1
        self.label_correct.setText("Correct!")
        self.label_correct.setStyleSheet("QLabel { background-color : green;}")

    def wrong_answer(self):
        wrong_string = (f"Wrong: {self.current_question[self.question_mode]} "
                        f"= {self.current_correct_answer}")
        self.label_correct.setText(wrong_string)
        self.label_correct.setStyleSheet("QLabel { background-color : red;}")

    def on_answer_given(self):
        given_answer = self.page3.line_edit.text()
        if given_answer == self.current_correct_answer:
            self.correct_answer()
        else:
            self.wrong_answer()
        self.question.setText(self.page3.line_edit.text())
        self.page3.line_edit.clear()
        self.update_question()

    def after_button_clicked(self, ans_id):
        if self.buttons_choices[ans_id] == self.current_correct_answer:
            self.correct_answer()
        else:
            self.wrong_answer()
        self.update_question()

    def on_ans_button0_clicked(self):
        self.after_button_clicked(0)

    def on_ans_button1_clicked(self):
        self.after_button_clicked(1)

    def on_ans_button2_clicked(self):
        self.after_button_clicked(2)


if __name__ == "__main__":
    app = QApplication([])

    widget = MainWidget()
    widget.resize(W, H)
    widget.show()

    sys.exit(app.exec_())
