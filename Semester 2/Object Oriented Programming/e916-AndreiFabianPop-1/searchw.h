//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_SEARCHW_H
#define E916_ANDREIFABIANPOP_1_SEARCHW_H

#include <QWidget>
#include "QnA.h"
#include "Observer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SearchW; }
QT_END_NAMESPACE

class SearchW : public QWidget, public Observer {
Q_OBJECT

public:
    explicit SearchW(QnA &qna1, QWidget *parent = nullptr);

    ~SearchW() override;

private:
    Ui::SearchW *ui;
    QnA &qna;

    void populate(const Question& q);
    void connect();

    int similarity(const Question& q1, std::string q2);

    void update() override;
};


#endif //E916_ANDREIFABIANPOP_1_SEARCHW_H
