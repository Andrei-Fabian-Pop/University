//
// Created by andre on 16/04/2022.
//

#ifndef A8_9_ANDREIFABIANPOP_WATCHLIST_H
#define A8_9_ANDREIFABIANPOP_WATCHLIST_H

#include <vector>
#include "../Repository/Repository.h"

template <typename TElement>
class WatchList {
protected:
    std::vector<TElement> watchList;
    int current {};
    std::string filename;
public:

    friend class Repository<TElement>;
    explicit WatchList();

    int add(const TElement& element);
    int removeByPos(int position);
    void remove(TElement& element);

    void play();
    void next();
    TElement& getCurrent();

    bool search(const TElement &e);
    void setWatchList(const std::vector<TElement>& newWatchList);

    // return types
    std::vector<TElement> getAll() const { return this->watchList; };
    TElement& operator[](int index);
    int getSize() { return this->watchList.size(); };

    void readWatchlist();

    virtual void saveToFile() = 0;
    virtual void openApp() = 0;
};

template<typename TElement>
int WatchList<TElement>::add(const TElement& element) {
    if (!this->search(element)) {
        return 0;
    } else {
        this->watchList.push_back(element);
        return 1;
    }
}

template<typename TElement>
int WatchList<TElement>::removeByPos(int position) {
    this->watchList.erase(this->watchList.begin() + position);
    return 1;
}

template<typename TElement>
void WatchList<TElement>::remove(TElement &element) {
    int pos, iteratorPosition = -1;
    std::for_each(this->watchList.begin(),
                  this->watchList.end(),
                  [&pos, &iteratorPosition, &element](const TElement& m) {
                        ++iteratorPosition;
                      if (element.get_title() == m.get_title() && element.get_presenter() == m.get_presenter() && element.get_link() == m.get_link())
                          pos = iteratorPosition;
                      });
    this->removeByPos(pos);
}

template<typename TElement>
void WatchList<TElement>::play() {
    if (!this->watchList.empty()) {
        this->watchList[this->current].executeLink();
    }
}

template<typename TElement>
void WatchList<TElement>::next() {
    if (this->current + 1 == this->watchList.size())
    {
        this->current = 0;
        return;
    }
    this->current++;
}

template<typename TElement>
TElement &WatchList<TElement>::getCurrent() {
    return this->watchList[this->current];
}

template<typename TElement>
bool WatchList<TElement>::search(const TElement &e) {
    bool val = true;
    std::for_each(this->watchList.begin(), this->watchList.end(), [&](const TElement& element) -> void {
        if (element.get_title() == e.get_title() && element.get_presenter() == e.get_presenter() && element.get_link() == e.get_link()) {
            val = false;
        }
    });
    return val;
}

template<typename TElement>
void WatchList<TElement>::setWatchList(const std::vector<TElement> &newWatchList) {
    this->watchList = newWatchList;
}

template<typename TElement>
TElement &WatchList<TElement>::operator[](int index) {
    return this->watchList[index];
}

template<typename TElement>
void WatchList<TElement>::readWatchlist() {
    std::ifstream f(this->filename);

    if (!f.is_open()) {
        throw FileException("Error. Could not open the file.");
    } else {
        Tutorial tutorial;
        while (f >> tutorial) {
            if (tutorial.get_likes() != -1) {
                this->add(tutorial);
            }
        }
        f.close();
    }
}

template<typename TElement>
WatchList<TElement>::WatchList() = default;

#endif //A8_9_ANDREIFABIANPOP_WATCHLIST_H
