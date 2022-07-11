//
// Created by andrew on 12/06/22.
//

#include <iostream>
#include <fstream>
#include "QnA.h"

QnA::QnA(const std::vector<Question> &q, const std::vector<Answer> &a) : q(q), a(a) {}

const std::vector<Question> &QnA::getQ() const {
    return q;
}

const std::vector<Answer> &QnA::getA() const {
    return a;
}

void QnA::sorta() {
    std::sort(this->q.begin(), this->q.end(), [&](Question q1, Question q2) -> bool {
        int ans1=0, ans2=0;
        for (const auto& an: this->a) {
            if (an.getQid() == q1.getId())
                ++ans1;

            if (an.getQid() == q2.getId())
                ++ans2;
        }
        return ans1 > ans2;
    });
}

QnA::~QnA() {
    std::ofstream g("questions.txt");
    if (!g.is_open()) {
        std::cout << "g not open\n";
    }
    for (const auto& ques : this->q) {
        g << ques.getId() << "," << ques.getText() << "," << ques.getUserName() << "\n";
    }

    g.close();
    std::ofstream h("answeres.txt");
    if (!h.is_open()) {
        std::cout << "h not open\n";
    }
    for (const auto& ans: this->a) {
        h << ans.getId() << "," << ans.getQid() << "," << ans.getUserName() << "," << ans.getText() << "," << ans.getNrVotes() << "\n";
    }
    h.close();
}
