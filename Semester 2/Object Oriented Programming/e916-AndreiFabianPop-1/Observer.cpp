//
// Created by andrew on 12/06/22.
//

#include "Observer.h"

void Subject::notify() {
    for (auto o : this->list)
        o->update();
}
