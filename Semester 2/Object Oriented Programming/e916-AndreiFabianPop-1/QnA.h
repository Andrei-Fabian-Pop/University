//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_QNA_H
#define E916_ANDREIFABIANPOP_1_QNA_H

#include <vector>
#include "Quastion.h"
#include "Answer.h"
#include "Observer.h"
#include <algorithm>

class QnA : public Subject {
private:
    std::vector<Question> q;
    std::vector<Answer> a;
public:
    QnA(const std::vector<Question> &q, const std::vector<Answer> &a);
    ~QnA();

    [[nodiscard]] const std::vector<Question> &getQ() const;

    [[nodiscard]] const std::vector<Answer> &getA() const;

    void addQ(const Question& ques) { this->q.push_back(ques); sorta(); this->notify(); };

    void sorta();
};


#endif //E916_ANDREIFABIANPOP_1_QNA_H
