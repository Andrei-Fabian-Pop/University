//
// Created by andrew on 26/05/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GUI.h" resolved

#include "gui.h"

#include <utility>
#include <iostream>
#include "ui_GUI.h"


GUI::GUI(Repository repository1, QWidget *parent) :
        QWidget(parent), ui(new Ui::GUI), repository(std::move(repository1)) {
    ui->setupUi(this);
    this->writeList();
    this->connectUI();
}

GUI::~GUI() {
    delete ui;
}

void GUI::writeList() {
    this->ui->listWidget->clear();
    std::vector<Document> all = this->repository.getAll();
    for (auto & doc: all) {
        std::string keywords;
        for (auto & key: doc.getKeywords()) {
            keywords += key + " , ";
        }
        this->ui->listWidget->addItem(QString::fromStdString(doc.getName() + " | " + keywords + " | " + doc.getContent()));
    }
}

void GUI::connectUI() {
    QObject::connect(this->ui->lineEdit, &QLineEdit::textChanged, this, &GUI::lineEditChanged);
    QObject::connect(this->ui->listWidget, &QListWidget::itemSelectionChanged, this, &GUI::similarityLine);
}

void GUI::lineEditChanged() {
    std::vector<Document> all = this->repository.getAll();
    std::string line = this->ui->lineEdit->text().toStdString();
    this->ui->listWidget->clear();

    if (this->ui->lineEdit->text().isEmpty()) {
        writeList();
        return;
    }

    for (auto & doc: all) {
        bool found = false;
        for (auto& key : doc.getKeywords()) {
            if (key.find(line) != std::string::npos) {
                found = true;
                break;
            }
        }
        if (doc.getName().find(line) != std::string::npos || doc.getContent().find(line) != std::string::npos || found) {
            std::string keywords;
            for (auto & key: doc.getKeywords()) {
                keywords += key + " , ";
            }
            this->ui->listWidget->addItem(QString::fromStdString(doc.getName() + " | " + keywords + " | " + doc.getContent()));
        }
    }
}

void GUI::similarityLine() {
    std::string string = this->ui->listWidget->currentItem()->text().toStdString();
    std::string filter = this->ui->lineEdit->text().toStdString();
    unsigned int len = string.length(), common=0;
    for (int i = 0; i < len; ++i) {
        if (string[i] == filter[i]) {
            ++common;
        } else {
            break;
        }
    }
    if (common == 0) {
        this->ui->lineEdit_2->setText(QString::fromStdString("No match"));
    } else {
        this->ui->lineEdit_2->setText(QString::fromStdString(std::to_string((float)(common)/(float)(len))));
    }
}
