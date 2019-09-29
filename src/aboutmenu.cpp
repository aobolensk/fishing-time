#include <QSettings>
#include "aboutmenu.h"
#include "game.h"

AboutMenu::AboutMenu(Game *game) :
        game(game) {
    this->setLayout(&grid);

    QSettings settings;
    if (!this->restoreGeometry(settings.value("aboutWindowGeometry").toByteArray())) {
        qDebug() << "Unable to restore about window geometry. Loading defaults...";
        this->setGeometry(QRect(QPoint(200, 200), QSize(320, 240)));
    }

    grid.addWidget(&descriptionLabel, 0, 0, 1, 3);
    descriptionLabel.setVisible(false);
    descriptionLabel.setWordWrap(true);
    descriptionLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    descriptionLabel.setTextFormat(Qt::RichText);
    descriptionLabel.setTextInteractionFlags(Qt::TextBrowserInteraction);
    descriptionLabel.setOpenExternalLinks(true);

    grid.addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

QString AboutMenu::getAboutInfo() {
    return game->str.aboutDescription.arg(
        "https://github.com/gooddoog/fishing-time/",
        QSysInfo::prettyProductName() + " " +
        QSysInfo::kernelType() + " " +
        QSysInfo::kernelVersion() + " " +
        QSysInfo::currentCpuArchitecture()
    );
}

void AboutMenu::display() {
    this->setWindowTitle(game->str.fishingTime + ": " + game->str.about);
    this->setVisible(true);

    descriptionLabel.setText(getAboutInfo());
    descriptionLabel.setVisible(true);

    backButton.setText(game->str.back);
    backButton.setVisible(true);
    backButton.setEnabled(true);
}

void AboutMenu::backFunction() {
    this->hide();

    this->setVisible(false);
}

void AboutMenu::hide() {
    descriptionLabel.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

AboutMenu::~AboutMenu() {

}
