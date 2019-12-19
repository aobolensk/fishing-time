#include <QSettings>
#include "aboutmenu.h"
#include "game.h"
#include "utils.h"

AboutMenu::AboutMenu(Game *game) :
        Menu(game, nullptr, true) {
    this->setLayout(grid);
    this->setFixedSize(this->width(), this->height());

    QSettings settings;
    if (!this->restoreGeometry(settings.value("aboutWindowGeometry").toByteArray())) {
        this->game->logger.error("Unable to restore about window geometry. Loading defaults...");
        this->setGeometry(QRect(QPoint(200, 200), QSize(320, 240)));
    }

    grid->addWidget(&descriptionLabel, 0, 0, 1, 3);
    descriptionLabel.setVisible(false);
    descriptionLabel.setWordWrap(true);
    descriptionLabel.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    descriptionLabel.setTextFormat(Qt::RichText);
    descriptionLabel.setOpenExternalLinks(true);

    grid->addWidget(&backButton, 1, 1);
    backButton.setVisible(false);
    backButton.setEnabled(false);
    connect(&backButton, SIGNAL(released()), this, SLOT(backFunction()));
}

QString AboutMenu::getAboutInfo() {
    return game->str.aboutDescription.arg(
        "https://github.com/gooddoog/fishing-time/",
        this->getSystemInfo(),
        this->getCompilerInfo(),
        "<a href='https://github.com/gooddoog/fishing-time/blob/master/LICENSE'>MIT</a>"
    );
}

QString AboutMenu::getSystemInfo() {
    return QSysInfo::prettyProductName() + " " +
           QSysInfo::kernelType() + " " +
           QSysInfo::kernelVersion() + " " +
           QSysInfo::currentCpuArchitecture();
}

QString AboutMenu::getCompilerInfo() {
    return
        #ifdef __clang__
        "clang++ " TOSTRING(__clang_major__) "." TOSTRING(__clang_minor__) "." TOSTRING(__clang_patchlevel__)
        #elif _MSC_FULL_VER
        "MSVC " TOSTRING(_MSC_FULL_VER)
        #elif __GNUC__
        "g++ " TOSTRING(__GNUC__) "." TOSTRING(__GNUC_MINOR__) "." TOSTRING(__GNUC_PATCHLEVEL__)
        #else
        "unknown"
        #endif
    ;
}

void AboutMenu::display() {
    this->pre_display();

    this->setWindowTitle(game->str.fishingTime + ": " + game->str.about);
    this->setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
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
    this->pre_hide();

    descriptionLabel.setVisible(false);

    backButton.setVisible(false);
    backButton.setEnabled(false);
}

AboutMenu::~AboutMenu() {

}
