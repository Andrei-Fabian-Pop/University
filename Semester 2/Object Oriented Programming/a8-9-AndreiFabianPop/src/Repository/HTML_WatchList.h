//
// Created by andre on 16/04/2022.
//

#ifndef A8_9_ANDREIFABIANPOP_HTML_WATCHLIST_H
#define A8_9_ANDREIFABIANPOP_HTML_WATCHLIST_H

#include <fstream>

#include "WatchList.h"
#include "../Domain/Tutorial.h"

template <typename TElement>
class HTML_WatchList : public WatchList<TElement> {
public:
    explicit HTML_WatchList(const std::string& filename);
    ~HTML_WatchList();

    void saveToFile() override;
    void openApp() override;
};

template <typename TElement>
HTML_WatchList<TElement>::HTML_WatchList(const std::string& filename) {
    this->filename = filename;
}

template <typename TElement>
HTML_WatchList<TElement>::~HTML_WatchList() = default;

template <typename TElement>
void HTML_WatchList<TElement>::saveToFile() {
    std::ofstream g("watchlist.html");

    g << "<!DOCTYPE html>" << "\n";
    g << "<html lang=\"en\">" << "\n";

    g << "<head>" << "\n";
    g << "<title>Tutorial Playlist</title>" << "\n";
    g << "</head>" << "\n";

    g << "<body>" << "\n";

    g << "<table border=\"1\">" << "\n";

    g << "<tr>" << "\n";
    g << "<td>Title</td>" << "\n";
    g << "<td>Presenter</td>" << "\n";
    g << "<td>Duration Minutes</td>" << "\n";
    g << "<td>Duration Seconds</td>" << "\n";
    g << "<td>Likes</td>" << "\n";
    g << "<td>Link</td>" << "\n";
    g << "</tr>" << "\n";

    for (const auto& tutorial : this->watchList)
    {
        g << "<tr>" << "\n";

        g << "<td>" << tutorial.get_title() << "</td>" << "\n";
        g << "<td>" << tutorial.get_presenter() << "</td>" << "\n";
        g << "<td>" << tutorial.get_duration_minutes() << "</td>" << "\n";
        g << "<td>" << tutorial.get_duration_seconds() << "</td>" << "\n";
        g << "<td>" << tutorial.get_likes() << "</td>" << "\n";
        g << "<td><a href =" << tutorial.get_link() << ">Link</a></td>";

        g << "</tr>" << "\n";
    }

    g << "</table>" << "\n";

    g << "</body>" << "\n";

    g << "</html>" << "\n";
    g.close();
}

template <typename TElement>
void HTML_WatchList<TElement>::openApp() {
    std::string command = "firefox watchlist.html";
    system(command.c_str());
}


#endif //A8_9_ANDREIFABIANPOP_HTML_WATCHLIST_H
