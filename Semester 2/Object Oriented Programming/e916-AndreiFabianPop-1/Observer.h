//
// Created by andrew on 12/06/22.
//

#ifndef E916_ANDREIFABIANPOP_1_OBSERVER_H
#define E916_ANDREIFABIANPOP_1_OBSERVER_H

#include <vector>

class Observer {
public:
    virtual void update() = 0;
};

class Subject {
private:
    std::vector<Observer*> list;
public:
    void addObserver(Observer* o) { this->list.push_back(o); }
    void notify();
};


#endif //E916_ANDREIFABIANPOP_1_OBSERVER_H
