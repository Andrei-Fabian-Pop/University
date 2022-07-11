//
// Created by andre on 19/03/2022.
//

#include <QApplication>
//#include <QSpinBox>
//#include <QSlider>
//#include <QHBoxLayout>

#include "UI/UI.h"
#include "Repository/Repository.h"
#include "Tests/Tests.h"
#include "Repository/CSV_WatchList.h"
#include "Repository/HTML_WatchList.h"
#include "ExceptionsAndValidators/Exception.h"
#include "Domain/Tutorial.h"
#include "GUI/GUI.h"

int main(int argc, char **argv) {
    std::string command;
    QApplication application(argc, argv);

    while (true) {
        std::cout << "Choose the type of file to open (CSV or html) or exit:";
        std::getline(std::cin, command);
        if (command == "e" || command == "exit") {
            std::cout << "Terminating program...\n";
            break;
        } else if (command == "csv" || command == "html") {
            Repository<Tutorial> repository{"repository.txt"};
            WatchList<Tutorial> *watchList;
            if (command == "csv")
                watchList = new CSV_WatchList<Tutorial>("watchlist.txt");
            else
                watchList = new HTML_WatchList<Tutorial>("watchlist.txt");
            watchList->readWatchlist();
            Service service(repository, watchList, command);


            GUI gui(service);
            gui.show();

            return QApplication::exec();
        } else {
            std::cerr << "Error. Invalid input.\n";
        }
    }
}