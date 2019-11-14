#include <QApplication>
#include <QDateTime>
#include <QMessageBox>
#include <QSettings>
#include "logger.h"
#include "game.h"

Logger::Logger(Game *game) :
    Menu(game, nullptr),
    log(game, &console) {
    QSettings settings;
    if (!this->restoreGeometry(settings.value("loggerGeometry").toByteArray())) {
        qDebug() << "Unable to restore console window geometry. Loading defaults...";
        this->setGeometry(QRect(QPoint(200, 100), QSize(360, 480)));
    }

    grid->addWidget(&console, 0, 0);
    console.setReadOnly(true);
}

void Logger::closeEvent(QCloseEvent *event) {
    if (game->isHidden() && game->console.isHidden()) {
        QMessageBox::StandardButton closeResult =
            QMessageBox::question(this, game->str.fishingTime, game->str.exitConfirmation,
            QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);
        if (closeResult != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
            QApplication::quit();
        }
    } else {
        this->hide();
    }
}

void Logger::debug(const QString &message) {
    if (game->loggerLevel == LoggerLevel::DEBUG) {
        this->log.debugT(message);
    }
}

void Logger::info(const QString &message) {
    this->log.infoT(message);
}

void Logger::warning(const QString &message) {
    this->log.warningT(message);
}

void Logger::error(const QString &message) {
    this->log.errorT(message);
}

void Logger::display() {
    this->setWindowTitle(game->str.fishingTime + ": " + game->str.console);
    this->setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
    this->show();

    displayed = true;
}

void Logger::hide() {
    this->QWidget::hide();
    displayed = false;
}
