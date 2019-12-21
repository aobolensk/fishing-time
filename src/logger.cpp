#include <QApplication>
#include <QDateTime>
#include <QMessageBox>
#include <QScrollBar>
#include <QSettings>
#include "logger.h"
#include "game.h"

Logger::Logger(Game *game) :
    Menu(game, nullptr, true),
    log(game, &console),
    fileLog(game) {
    QSettings settings;
    if (!this->restoreGeometry(settings.value("loggerGeometry").toByteArray())) {
        qDebug() << "Unable to restore console window geometry. Loading defaults...";
        this->setGeometry(QRect(QPoint(200, 100), QSize(360, 480)));
    }

    QFont font = console.font();
    font.setFamily("Courier New");
    console.setFont(font);

    grid->addWidget(&clearButton, 0, 0);
    connect(&clearButton, &QPushButton::clicked, [this]() {
        clearFunction();
    });

    grid->addWidget(&jumpToBottomButton, 1, 0);
    connect(&jumpToBottomButton, &QPushButton::clicked, [this]() {
        jumpToBottomFunction();
    });

    grid->addWidget(&console, 2, 0);
    console.setReadOnly(true);

    console.installEventFilter(this);

    this->setFile(game->logFile);
}

void Logger::clearFunction() {
    console.setText("");
}

void Logger::jumpToBottomFunction() {
    console.verticalScrollBar()->setValue(console.verticalScrollBar()->maximum());
}

bool Logger::eventFilter(QObject *obj, QEvent *event) {
    if (this->isHidden()) return false;
    if (console.verticalScrollBar()->value() == console.verticalScrollBar()->maximum()) {
        jumpToBottomButton.hide();
    } else {
        jumpToBottomButton.show();
    }
    return QObject::eventFilter(obj, event);
}

void Logger::closeEvent(QCloseEvent *event) {
    if (game->isHidden() && game->console.isHidden()) {
        game->console.hide();
        game->logger.hide();
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
        this->fileLog.debugT(message);
        this->jumpToBottomFunction();
    }
}

void Logger::info(const QString &message) {
    this->log.infoT(message);
    this->fileLog.infoT(message);
    this->jumpToBottomFunction();
}

void Logger::warning(const QString &message) {
    this->log.warningT(message);
    this->fileLog.warningT(message);
    this->jumpToBottomFunction();
}

void Logger::error(const QString &message) {
    this->log.errorT(message);
    this->fileLog.errorT(message);
    this->jumpToBottomFunction();
}

void Logger::display() {
    this->setWindowTitle(game->str.fishingTime + ": " + game->str.console);
    this->setWindowIcon(QIcon(Config::imagesDirectory + "icon.png"));
    this->show();

    clearButton.setText(game->str.clear);

    jumpToBottomButton.setText(game->str.jumpToBottom);
    this->jumpToBottomFunction();

    displayed = true;
}

void Logger::setFile(const QString &filePath) {
    fileLog.open(filePath);
}

void Logger::hide() {
    this->QWidget::hide();
    displayed = false;
}
