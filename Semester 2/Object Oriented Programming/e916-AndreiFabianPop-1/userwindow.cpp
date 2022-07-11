//
// Created by andrew on 12/06/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_UserWindow.h" resolved

#include "userwindow.h"

#include <utility>
#include <iostream>
#include "ui_UserWindow.h"


UserWindow::UserWindow(User user1, QnA &qna1, QWidget *parent) : QWidget(parent), ui(new Ui::UserWindow), user(std::move(user1)), qna(qna1) {
    ui->setupUi(this);
    this->setWindowTitle(QCoreApplication::translate("ProgrammerWindow", user.getName().c_str(), nullptr));

    this->qna.addObserver(this);
    this->populateQuestions();
    this->connect();
}

UserWindow::~UserWindow() {
    delete ui;
}

void UserWindow::populateQuestions() {
    this->ui->listWidget->clear();

    for (const auto &item: this->qna.getQ()) {
        this->ui->listWidget->addItem(QString::fromStdString(
                std::to_string(item.getId()) + " " + item.getText() + ": " + item.getUserName()));
    }
}

void UserWindow::connect() {
    QObject::connect(this->ui->pushButton, &QPushButton::clicked, this, [&]() {
        if (this->ui->lineEdit->text().isEmpty()) {
            return;
        }
        Question question((int)this->qna.getQ().size(), this->ui->lineEdit->text().toStdString(), this->user.getName());
        qna.addQ(question);
    });

    QObject::connect(this->ui->listWidget, &QListWidget::itemSelectionChanged, this, [&]() {
        this->populateAnswers();
    });

    QObject::connect(this->ui->listWidget_2, &QListWidget::itemSelectionChanged, this, [&]() {
        this->ui->spinBox->setValue(this->qna.getA()[this->ui->listWidget_2->currentRow()].getNrVotes());
    });

    QObject::connect(this->ui->spinBox, &QSpinBox::valueChanged, this, [&]() {
        if (this->ui->listWidget_2->currentItem()) {
            int newn = this->qna.getA()[this->ui->listWidget_2->currentRow()].getNrVotes() + 1;
            auto& question = (Answer &) this->qna.getA()[this->ui->listWidget_2->currentRow()];
            question.setNrVotes(newn);
            this->ui->spinBox->setDisabled(true);
            this->populateAnswers();
        }
    });
}

void UserWindow::update() {
    this->populateQuestions();
}

void UserWindow::populateAnswers() {
    this->ui->listWidget_2->clear();
    Question q;
    for (const auto &qu: this->qna.getQ()) {
        if (qu.toString() == this->ui->listWidget->currentItem()->text().toStdString()) {
            q = qu;
        }
    }

    std::vector<Answer> an;
    for (const auto &ans: this->qna.getA()) {
        if (ans.getQid() == q.getId()) {
            an.push_back(ans);
        }
    }

    for (auto &i: an) {
        this->ui->listWidget_2->addItem(
                QString::fromStdString(
                        std::to_string(i.getId()) + ". qid: " + std::to_string(i.getQid()) + " by " + i.getUserName() +
                        ": " + i.getText() + ", voted " + std::to_string(i.getNrVotes()))
        );
    }

    int index = 0;
    for (auto &i: an) {
        if (i.getUserName() == this->user.getName())
            this->ui->listWidget_2->item(index)->setBackground(Qt::yellow);
        ++index;
    }
}