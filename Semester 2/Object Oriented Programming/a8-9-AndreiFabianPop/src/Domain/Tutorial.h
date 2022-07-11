//
// Created by andre on 19/03/2022.
//

#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <cstring>
#include <utility>
#include <string>
#include <vector>
#include <sstream>

class Tutorial {
private:
    std::string title;
    std::string presenter;
    int duration_minutes;
    int duration_seconds;
    int likes;
    std::string link;

    static std::vector<std::string> tokenize(const std::string& str, char delimiter);
public:
    explicit Tutorial();
    explicit Tutorial(std::string title, std::string presenter, int duration_minutes, int duration_seconds,
                      int likes, std::string link);
    ~Tutorial();

    Tutorial(const Tutorial& t);

    std::string get_title() const;
    void set_title(std::string new_title);

    std::string get_presenter() const;
    void set_presenter(std::string new_presenter);

    int get_duration_minutes() const;
    void set_duration_minutes(int minutes);

    int get_duration_seconds() const;
    void set_duration_seconds(int seconds);

    int get_likes() const;
    void set_likes(int new_likes);

    std::string get_link() const;
    void set_link(std::string new_link);

    void executeLink();

    friend std::istream& operator>>(std::istream& istream, Tutorial& tutorial);
    friend std::ostream& operator<<(std::ostream& ostream, const Tutorial& tutorial);
};
