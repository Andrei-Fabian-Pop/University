//
// Created by andrew on 07/05/22.
//

#include "GUI.h"

GUI::GUI(const Service& serv, QWidget * parent) : service(serv), QWidget(parent) {
    this->initGUI();
    this->connectSignalsAndSlots();
    this->writeTutorialList();
    this->writePlaylistList();
}

void GUI::initGUI() {
    auto layout = new QHBoxLayout(this);

    auto leftSide = new QWidget();
    auto leftLayout = new QVBoxLayout(leftSide);

    auto middle = new QWidget();
    auto middleLayout = new QVBoxLayout(middle);

    auto right = new QWidget();
    auto rightLayout = new QVBoxLayout(right);

    // left side - list
    this->tutorialList = new QListWidget;
    this->tutorialList->setSelectionMode(QAbstractItemView::SingleSelection);
    leftLayout->addWidget(this->tutorialList);

    // right side - info + buttons
    auto rightSide = new QWidget;
    auto vLayout = new QVBoxLayout(rightSide);

    // tutorial information : right side
    auto tutorialDataWidget = new QWidget;
    auto formLayout = new QFormLayout(tutorialDataWidget);

    // tutorial fields
    this->titleEdit = new QLineEdit;
    this->presenterEdit = new QLineEdit;
    this->durationMinutesEdit = new QLineEdit;
    this->durationSecondsEdit = new QLineEdit;
    this->likesEdit = new QLineEdit;
    this->linkEdit = new QLineEdit;

    this->filterLineEdit = new QLineEdit;

    // label tutorial fields
    auto titleLabel = new QLabel("&Title: "); titleLabel->setBuddy(this->titleEdit);
    auto presenterLabel = new QLabel("&Presenter: "); presenterLabel->setBuddy(this->presenterEdit);
    auto durationMinutesLabel = new QLabel("&Minutes: "); durationMinutesLabel->setBuddy(this->durationMinutesEdit);
    auto durationSecondsLabel = new QLabel("&Seconds: "); durationSecondsLabel->setBuddy(this->durationSecondsEdit);
    auto likesLabel = new QLabel("&Likes: "); likesLabel->setBuddy(this->likesEdit);
    auto linkLabel = new QLabel("&Link: "); linkLabel->setBuddy(this->linkEdit);

    auto filterLabel = new QLabel("&Filter: "); filterLabel->setBuddy(this->filterLineEdit);

    // add labels to the form
    formLayout->addRow(filterLabel, this->filterLineEdit);

    formLayout->addRow(titleLabel, this->titleEdit);
    formLayout->addRow(presenterLabel, this->presenterEdit);
    formLayout->addRow(durationMinutesLabel, this->durationMinutesEdit);
    formLayout->addRow(durationSecondsLabel, this->durationSecondsEdit);
    formLayout->addRow(likesLabel, this->likesEdit);
    formLayout->addRow(linkLabel, this->linkEdit);

    // add widget to leftLayout
    vLayout->addWidget(tutorialDataWidget);

    // buttons right side
    auto buttonsWidget = new QWidget;
    auto hLayout = new QHBoxLayout(buttonsWidget);

    // create buttons for all functions
    this->addTutorialButton = new QPushButton("Add Tutorial");
    this->deleteTutorialButton = new QPushButton("Delete Tutorial");
    this->updateTutorialButton = new QPushButton("Update tutorial");
    this->filterTutorialButton = new QPushButton("Filter by presenter");

    this->nextPlaylistButton = new QPushButton("Next");
    this->playPlaylistButton = new QPushButton("Play");
    this->openWatchlistButton = new QPushButton("Open Watchlist");
    this->saveWatchlistButton = new QPushButton("Save Watchlist");

    // add buttons to leftLayout
    hLayout->addWidget(this->addTutorialButton);
    hLayout->addWidget(this->deleteTutorialButton);
    hLayout->addWidget(this->updateTutorialButton);
    hLayout->addWidget(this->filterTutorialButton);

    // add buttons widget to right leftLayout
    vLayout->addWidget(buttonsWidget);

    // add everything to the left layout
    leftLayout->addWidget(this->tutorialList);
    leftLayout->addWidget(rightSide);

    // middle layout
    this->addToPlaylistButton = new QPushButton(">");
    middleLayout->addWidget(this->addToPlaylistButton);


    // right layout
    // right field = playlist
    this->playlist = new QListWidget;
    this->playlist->setSelectionMode(QAbstractItemView::SingleSelection);
    rightLayout->addWidget(this->playlist);

    // right buttons
    auto rightButtonsWidget = new QWidget();
    auto rightButtons = new QHBoxLayout(rightButtonsWidget);
    rightButtons->addWidget(this->nextPlaylistButton);
    rightButtons->addWidget(this->playPlaylistButton);
    rightButtons->addWidget(this->openWatchlistButton);
    rightButtons->addWidget(this->saveWatchlistButton);

    // add right side together
    rightLayout->addWidget(rightButtonsWidget);

    // add to layout
    layout->addWidget(leftSide);
    layout->addWidget(middle);
    layout->addWidget(right);


    // extras
    QLinearGradient colorGradient = QLinearGradient(0, 0, QWidget::width(), QWidget::height());
    colorGradient.setSpread(QGradient::RepeatSpread);
    colorGradient.setColorAt(0, QColor(128,128,255));
    colorGradient.setColorAt(1, QColor(0,0,0,255));
    QBrush colorBrush = QBrush(colorGradient);

    QPalette qPalette;
    qPalette.setBrush(QPalette::Base, colorBrush);
    this->playlist->setPalette(qPalette);
}

void inline GUI::connectSignalsAndSlots() {
    // When the repo is updated, re-populate the list
    QObject::connect(this, &GUI::tutorialUpdateSignal, this, &GUI::writeTutorialList);
    QObject::connect(this, &GUI::playlistUpdateSignal, this, &GUI::writePlaylistList);

    // select item in list
    QObject::connect(this->tutorialList, &QListWidget::itemSelectionChanged, this, [this](){this->listItemChanged();});

    // add button connections
    QObject::connect(this->addTutorialButton, &QPushButton::clicked, this, &GUI::addTutorialHandler);
    QObject::connect(this->deleteTutorialButton, &QPushButton::clicked, this, &GUI::deleteTutorialHandler);
    QObject::connect(this->updateTutorialButton, &QPushButton::clicked, this, &GUI::updateTutorialHandler);
//    QObject::connect(this->filterTutorialButton, &QPushButton::clicked, this, &GUI::filterSlot);

    QObject::connect(this->addToPlaylistButton, &QPushButton::clicked, this, &GUI::addToPlaylistHandler);

    QObject::connect(this->nextPlaylistButton, &QPushButton::clicked, this, &GUI::nextPlaylistHandler);
    QObject::connect(this->playPlaylistButton, &QPushButton::clicked, this, &GUI::playPlaylistHandler);
    QObject::connect(this->openWatchlistButton, &QPushButton::clicked, this, &GUI::openWatchlistHandler);
    QObject::connect(this->saveWatchlistButton, &QPushButton::clicked, this, &GUI::saveWatchlistHandler);

    // connect addTutorial signal to addTutorial slot
    QObject::connect(this->filterLineEdit, &QLineEdit::textChanged, this, &GUI::filterSlot);

    QObject::connect(this, SIGNAL(addTutorialSignal(std::string, std::string, int, int, int, std::string)), this,
                     SLOT(addTutorial(const std::string &, const std::string &, int, int, int, const std::string &)));
}

void GUI::writeTutorialList() {
    if (this->service.get_all().getSize() > 0) {
        this->tutorialList->clear();
    }

    for (const auto& tutorial : this->service.get_all().get_all()) {
        QString itemString = QString::fromStdString(
                tutorial.get_title() + ", by" + tutorial.get_presenter() + ", " +
                std::to_string(tutorial.get_duration_minutes()) + ":" + std::to_string(tutorial.get_duration_seconds()) + ", " +
                std::to_string(tutorial.get_likes()) + " likes, " + tutorial.get_link());
        auto item = new QListWidgetItem(itemString);
        this->tutorialList->addItem(item);
    }

    if (this->service.get_all().getSize() > 0) {
        this->tutorialList->setCurrentRow(0);
    }
}

void GUI::listItemChanged() {
    int index = this->getSelectedListIndex();
    if (index == -1) {
        return;
    }

    if (index >= this->service.get_all().getSize())
        return;

    Tutorial tutorial = this->service.get_all()[index];

    this->titleEdit->setText(QString::fromStdString(tutorial.get_title()));
    this->presenterEdit->setText(QString::fromStdString(tutorial.get_presenter()));
    this->durationMinutesEdit->setText(QString::fromStdString(std::to_string(tutorial.get_duration_minutes())));
    this->durationSecondsEdit->setText(QString::fromStdString(std::to_string(tutorial.get_duration_seconds())));
    this->likesEdit->setText(QString::fromStdString(std::to_string(tutorial.get_likes())));
    this->linkEdit->setText(QString::fromStdString(tutorial.get_link()));
}

int GUI::getSelectedListIndex() {
    if (this->service.get_all().getSize() == 0) {
        return -1;
    }
    QModelIndexList index = this->tutorialList->selectionModel()->selectedIndexes();
    if (index.empty()) {
        this->titleEdit->clear();
        this->presenterEdit->clear();
        this->durationMinutesEdit->clear();
        this->durationSecondsEdit->clear();
        this->likesEdit->clear();
        this->linkEdit->clear();
        return -1;
    }

    int idx = index.at(0).row();

    return idx;
}

void GUI::addTutorialHandler() {
    // read data from right side form
    QString title = this->titleEdit->text();
    QString presenter = this->presenterEdit->text();
    QString durationMinutes = this->durationMinutesEdit->text();
    QString durationSeconds = this->durationSecondsEdit->text();
    QString likes = this->likesEdit->text();
    QString link = this->linkEdit->text();

    // emit the change signal
    emit addTutorialSignal(title.toStdString(), presenter.toStdString(), durationMinutes.toInt(), durationSeconds.toInt(), likes.toInt(), link.toStdString());
}

void GUI::deleteTutorialHandler() {
    int idx = this->getSelectedListIndex();

    if (idx < 0 || idx >= this->service.get_all().getSize()) {
        return;
    }

    this->service.remove(idx);

    // emit the signal updated
    emit tutorialUpdateSignal();
}

void GUI::addTutorial(const std::string &title, const std::string &presenter, int durationMinutes, int durationSeconds, int likes, const std::string & link) {

    this->service.add(title, presenter, durationMinutes, durationSeconds, likes, link);

    emit tutorialUpdateSignal();
}

void GUI::updateTutorialHandler() {
    // read data from right side form
    QString title = this->titleEdit->text();
    QString presenter = this->presenterEdit->text();
    QString durationMinutes = this->durationMinutesEdit->text();
    QString durationSeconds = this->durationSecondsEdit->text();
    QString likes = this->likesEdit->text();
    QString link = this->linkEdit->text();

    int index = this->getSelectedListIndex();

    this->service.updateFull(index, title.toStdString(), presenter.toStdString(), durationMinutes.toInt(), durationSeconds.toInt(), likes.toInt(), link.toStdString());

    emit tutorialUpdateSignal();
}

void GUI::addToPlaylistHandler() {
    int index = this->getSelectedListIndex();

    this->service.add_to_playlist(this->service.get_all()[index]);

    emit playlistUpdateSignal();
}

void GUI::playPlaylistHandler() {
    int index = this->getSelectedPlaylistIndex();
//    this->service.openWatchlist();
    this->service.get_watchList()[index].executeLink();
}

void GUI::nextPlaylistHandler() {
    int index = this->getSelectedPlaylistIndex();
    if (index + 1 < this->service.get_watchList().size()) {
        this->playlist->setCurrentRow(index + 1);
    } else {
        this->playlist->setCurrentRow(0);
    }
}

void GUI::writePlaylistList() {
    if (this->service.get_all().getSize() > 0) {
        this->playlist->clear();
    }

    for (const auto& tutorial : this->service.get_watchList()) {
        QString itemString = QString::fromStdString(
                tutorial.get_title() + ", by " + tutorial.get_presenter() + ", " +
                std::to_string(tutorial.get_duration_minutes()) + ":" + std::to_string(tutorial.get_duration_seconds()) + ", " +
                std::to_string(tutorial.get_likes()) + " likes, " + tutorial.get_link());
        auto item = new QListWidgetItem(itemString);
        this->playlist->addItem(item);
    }

    if (!this->service.get_watchList().empty()) {
        this->playlist->setCurrentRow(0);
    }
}

int GUI::getSelectedPlaylistIndex() {
    if (this->service.get_all().getSize() == 0) {
        return -1;
    }
    QModelIndexList index = this->playlist->selectionModel()->selectedIndexes();
    if (index.empty()) {
        this->titleEdit->clear();
        this->presenterEdit->clear();
        this->durationMinutesEdit->clear();
        this->durationSecondsEdit->clear();
        this->likesEdit->clear();
        this->linkEdit->clear();
        return -1;
    }

    int idx = index.at(0).row();

    return idx;
}

void GUI::filterSlot(const QString& qString) {
    std::string s = qString.toStdString();
    this->tutorialList->clear();
    for (auto &movie: this->service.get_all().get_all()) {
        if (movie.get_title().find(s) != std::string::npos) {
            QString itemString = QString::fromStdString(
                    movie.get_title() + ", by " + movie.get_presenter() + ", " +
                    std::to_string(movie.get_duration_minutes()) + ":" + std::to_string(movie.get_duration_seconds()) + ", " +
                    std::to_string(movie.get_likes()) + " likes, " + movie.get_link());
            auto item = new QListWidgetItem(itemString);
            this->tutorialList->addItem(item);
        }
    }

    if (this->tutorialList->count() > 0) {
        this->tutorialList->setCurrentRow(0);
    }
}

void GUI::openWatchlistHandler() {
    this->service.openWatchlist();
}

void GUI::saveWatchlistHandler() {
    this->service.saveWatchlist();
}

