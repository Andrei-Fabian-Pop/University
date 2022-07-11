//
// Created by andre on 16/04/2022.
//

#ifndef A8_9_ANDREIFABIANPOP_CSV_WATCHLIST_H
#define A8_9_ANDREIFABIANPOP_CSV_WATCHLIST_H

#include <fstream>

#include "WatchList.h"
#include "../Domain/Tutorial.h"


template <typename TElement>
class CSV_WatchList : public WatchList<TElement> {
public:
    explicit CSV_WatchList(const std::string& filename);
    ~CSV_WatchList();

    void saveToFile() override;
    void openApp() override;
};

template <typename TElement>
CSV_WatchList<TElement>::CSV_WatchList(const std::string& filename) {
    this->filename = filename;
}

template <typename TElement>
CSV_WatchList<TElement>::~CSV_WatchList() = default;

template <typename TElement>
void CSV_WatchList<TElement>::saveToFile() {
    std::ofstream g("watchlist.csv");
    for (const auto &tutorial : this->watchList) {
        g << tutorial;
    }
    g.close();
}

template <typename TElement>
void CSV_WatchList<TElement>::openApp() {
    system("open watchlist.csv");
}

#endif //A8_9_ANDREIFABIANPOP_CSV_WATCHLIST_H
