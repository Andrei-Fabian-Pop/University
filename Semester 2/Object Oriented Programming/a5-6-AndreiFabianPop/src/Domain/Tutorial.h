//
// Created by andre on 19/03/2022.
//

#pragma once
#pragma warning(disable:4996)
#include <iostream>
#include <cstring>

class Tutorial {
    private:
        std::string title;
        std::string presenter;
        unsigned int duration_minutes;
        unsigned int duration_seconds;
        unsigned int likes;
        std::string link;
    public:
        explicit Tutorial();
        explicit Tutorial(std::string title, std::string presenter, unsigned int duration_minutes, unsigned int duration_seconds,
                          unsigned int likes, std::string link);
        ~Tutorial();

        Tutorial(const Tutorial& t);

        std::string get_title() const;
        void set_title(std::string new_title);

        std::string get_presenter() const;
        void set_presenter(std::string new_presenter);

        unsigned int get_duration_minutes() const;
        void set_duration_minutes(unsigned int minutes);

        unsigned int get_duration_seconds() const;
        void set_duration_seconds(unsigned int seconds);

        unsigned int get_likes() const;
        void set_likes(unsigned int new_likes);

        std::string get_link() const;
        void set_link(std::string new_link);
};
