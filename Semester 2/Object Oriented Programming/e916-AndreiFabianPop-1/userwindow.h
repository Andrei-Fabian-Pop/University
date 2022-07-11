//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_USERWINDOW_H
#define E916_ANDREIFABIANPOP_1_USERWINDOW_H

#include <QWidget>
#include "User.h"
#include "QnA.h"
#include "Observer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class UserWindow; }
QT_END_NAMESPACE

class UserWindow : public QWidget, public Observer {
Q_OBJECT

public:
    explicit UserWindow(User user1, QnA &qna1, QWidget *parent = nullptr);

    ~UserWindow() override;

    void populateAnswers();
    void populateQuestions();
    void connect();

    void update() override;
private:
    Ui::UserWindow *ui;

    User user;
    QnA &qna;
};


#endif //E916_ANDREIFABIANPOP_1_USERWINDOW_H
