//
// Created by andrew on 26/05/22.
//

#include <QApplication>
#include <QPushButton>

#include "gui.h"
#include "Repository.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    Repository repository;
    repository.read();

    GUI gui(repository);
    gui.show();

    return QApplication::exec();
}