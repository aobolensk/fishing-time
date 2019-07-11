#include "mainmenu.h"
#include "mainwindow.h"

MainMenu::MainMenu(MainWindow *w, QGridLayout *g) :
        window(w),
        grid(g) {
    grid->addWidget(&startButton, 0, 1);
    startButton.setVisible(false);
    startButton.setEnabled(false);
    connect(&startButton, SIGNAL(released()), this, SLOT(startFunction()));

    grid->addWidget(&exitButton, 1, 1);
    exitButton.setVisible(false);
    exitButton.setEnabled(false);
    connect(&exitButton, SIGNAL(released()), this, SLOT(exitFunction()));

    grid->addWidget(&languageSelector, 1, 2);
    for (int i = 0; i < window->str.languages.size(); ++i) {
        languageSelector.addItem(window->str.languages[i]);
    }
    qDebug() << (int)window->activeLanguage;
    connect(&languageSelector, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        [this](int index){
            window->activeLanguage = (Language)index;
            window->str.setLanguage(window->activeLanguage);
            this->hide();
            this->display();
        });
    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);
}

void MainMenu::display() {
    startButton.setText(window->str.start);
    startButton.setVisible(true);
    startButton.setEnabled(true);

    exitButton.setText(window->str.exit);
    exitButton.setVisible(true);
    exitButton.setEnabled(true);

    languageSelector.setCurrentIndex((int)window->activeLanguage);
    languageSelector.setVisible(true);
    languageSelector.setEnabled(true);
}

void MainMenu::startFunction() {
    this->hide();
    window->loginMenu.display();
}

void MainMenu::exitFunction() {
    this->hide();
    QApplication::quit();
}

void MainMenu::hide() {
    startButton.setVisible(false);
    startButton.setEnabled(false);

    exitButton.setVisible(false);
    exitButton.setEnabled(false);

    languageSelector.setVisible(false);
    languageSelector.setEnabled(false);
}

MainMenu::~MainMenu() {
    
}
