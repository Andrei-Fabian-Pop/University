//
// Created by andrew on 07/05/22.
//

#ifndef A8_9_ANDREIFABIANPOP_GUI_H
#define A8_9_ANDREIFABIANPOP_GUI_H

#include <qwidget.h>
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

#include <exception>
#include <utility>
#include <algorithm>

#include "../Service/Service.h"
#include "../ExceptionsAndValidators/Validator.h"
#include "../ExceptionsAndValidators/Exception.h"

class GUI : public QWidget {
    Q_OBJECT
private:
    Service service;

    QListWidget* tutorialList{};
    QListWidget* playlist{};

    QLineEdit* titleEdit{};
    QLineEdit* presenterEdit{};
    QLineEdit* durationMinutesEdit{};
    QLineEdit* durationSecondsEdit{};
    QLineEdit* likesEdit{};
    QLineEdit* linkEdit{};

    QLineEdit* filterLineEdit{};

    QPushButton* addTutorialButton{};
    QPushButton* deleteTutorialButton{};
    QPushButton* updateTutorialButton{};
    QPushButton* filterTutorialButton{};
    QPushButton* addToPlaylistButton{};
    QPushButton* playPlaylistButton{};
    QPushButton* nextPlaylistButton{};
    QPushButton* openWatchlistButton{};
    QPushButton* saveWatchlistButton{};

    void inline initGUI();
    void inline connectSignalsAndSlots();

    int getSelectedListIndex();
    int getSelectedPlaylistIndex();

    void writeTutorialList();
    void writePlaylistList();
    void listItemChanged();

    void addTutorialHandler();
    void deleteTutorialHandler();
    void updateTutorialHandler();

    void addToPlaylistHandler();

    void playPlaylistHandler();
    void nextPlaylistHandler();
    void openWatchlistHandler();
    void saveWatchlistHandler();
public:
    explicit GUI(const Service& serv, QWidget * parent=nullptr);

signals:
    void tutorialUpdateSignal();
    void playlistUpdateSignal();
    void addTutorialSignal(std::string title, std::string presenter, int durationMinutes, int durationSeconds, int likes, std::string link);
    void textChanged(const QString&);

public slots:
    void addTutorial(const std::string &title, const std::string &presenter, int durationMinutes, int durationSeconds, int likes, const std::string & link);
    void filterSlot(const QString& qString);
};


#endif //A8_9_ANDREIFABIANPOP_GUI_H
