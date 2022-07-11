//
// Created by andrew on 26/05/22.
//

#ifndef T3_ANDREIFABIANPOP_GUI_H
#define T3_ANDREIFABIANPOP_GUI_H

#include <vector>
#include <string>

#include <QWidget>
#include "Repository.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Repository repository1, QWidget *parent = nullptr);

    ~GUI() override;

private:
    Ui::GUI *ui;
    Repository repository;

    void writeList();
    void connectUI();

    void lineEditChanged();
    void similarityLine();
};


#endif //T3_ANDREIFABIANPOP_GUI_H
