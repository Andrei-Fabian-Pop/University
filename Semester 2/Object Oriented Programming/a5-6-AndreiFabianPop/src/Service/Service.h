//
// Created by andre on 19/03/2022.
//

#pragma once
#include "../Repository/Repository.h"
#include "../Domain/Tutorial.h"

class Service {
    private:
        Repository<Tutorial> mainDatabase;
        Repository<Tutorial> watchList;
    public:
        explicit Service(const Repository<Tutorial>& repository);
        ~Service();

        int add(std::string title, std::string presenter, int duration_minutes, int duration_seconds, int likes, std::string link);
        int remove(int index);
        int update(int index, int field_index, std::string string_field, int int_field);
        Repository<Tutorial> get_all() const;
        bool valid_index(int index) const;

        std::vector<Tutorial> get_by_presenter(const std::string& presenter);
        Repository<Tutorial> get_watchList() const;
        int add_to_playlist(const Tutorial& tutorial);
        int remove_from_playlist(int index);
        void like(int index);
};
