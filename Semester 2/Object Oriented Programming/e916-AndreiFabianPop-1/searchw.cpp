//
// Created by andrew on 12/06/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_SearchW.h" resolved

#include "searchw.h"
#include "ui_SearchW.h"


SearchW::SearchW(QnA& qna1, QWidget *parent) :
        QWidget(parent), ui(new Ui::SearchW), qna(qna1) {
    ui->setupUi(this);

    connect();
}

SearchW::~SearchW() {
    delete ui;
}

void SearchW::populate(const Question& q) {
    if (this->ui->lineEdit->text().isEmpty()) {
        this->ui->listWidget->clear();
        return;
    }
    this->ui->listWidget->clear();
    this->ui->listWidget->addItem(QString::fromStdString(std::to_string(q.getId()) + " " + q.getText() + ": " + q.getUserName()));

    this->ui->listWidget->addItem(QString("-------------------------"));

    std::vector<Answer> an;
    for (const auto& ans : this->qna.getA()) {
        if (ans.getQid() == q.getId()) {
            an.push_back(ans);
        }
    }
    std::sort(an.begin(), an.end(), [&](const Answer& a1, const Answer& a2) -> bool {
        if (a1.getNrVotes() > a2.getNrVotes()) {
            return true;
        }
        return false;
    });
    unsigned long maxx = 3;
    for (int i = 0; i < std::min(an.size(), maxx); ++i) {
        this->ui->listWidget->addItem(
                QString::fromStdString(std::to_string(an[i].getId()) + ". qid: " + std::to_string(an[i].getQid()) + " by " + an[i].getUserName() + ": " + an[i].getText() + ", voted " + std::to_string(an[i].getNrVotes()))
                );
    }
}

void SearchW::connect() {
    QObject::connect(this->ui->lineEdit, &QLineEdit::textChanged, this, [&]() {
        Question best;
        int sim = 0;
        for (const auto& question : this->qna.getQ()) {
            int aux = similarity(question, this->ui->lineEdit->text().toStdString());
            if (aux > sim) {
                sim = aux;
                best = question;
            }
        }

        populate(best);
    });
}

int SearchW::similarity(const Question& q1, std::string q2) {
    int sz=0;
    for (int i = 0; i < std::max(q1.toString().size(), q2.size()); ++i) {
        if (q1.toString()[i] == q2[i]) {
            ++sz;
        }
    }
    return sz;
}

void SearchW::update() {
    this->ui->listWidget->clear();
    this->ui->listWidget->addItem(QString("Questions updated"));
}
