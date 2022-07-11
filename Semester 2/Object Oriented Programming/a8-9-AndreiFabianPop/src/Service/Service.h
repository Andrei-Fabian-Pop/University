//
// Created by andre on 19/03/2022.
//

#pragma once
#include "../Repository/Repository.h"
#include "../Repository/WatchList.h"
#include "../Domain/Tutorial.h"
#include "../ExceptionsAndValidators/Validator.h"
#include "../ExceptionsAndValidators/Exception.h"
#include "../Repository/CSV_WatchList.h"
#include "../Repository/HTML_WatchList.h"

class Service {
private:
    Repository<Tutorial> mainDatabase;
    WatchList<Tutorial>* watchList;
    std::string databaseType;
public:
    explicit Service(const Repository<Tutorial>& repository, WatchList<Tutorial>* wl, std::string databaseType);
    ~Service();

    int add(std::string title, std::string presenter, int duration_minutes, int duration_seconds, int likes, std::string link);
    int remove(int index);
    int update(int index, int field_index, std::string string_field, int int_field);
    int updateFull(int index, std::string title, std::string presenter, int duration_minutes, int duration_seconds, int likes, std::string link);
    Repository<Tutorial> get_all() const;
    bool valid_index(int index) const;
    int get_index(const std::string& title, const std::string& presenter, const std::string& link);

    WatchList<Tutorial>* get_by_presenter(const std::string& presenter);
    std::vector<Tutorial> get_watchList();
    int add_to_playlist(const Tutorial& tutorial);
    int remove_from_playlist(int index);
    void like(int index);

    void saveWatchlist();
    void openWatchlist();
};
