#include <QApplication>
#include <QElapsedTimer>
#include <QSettings>
#include <csignal>
#include "game.h"
#include "errorwidget.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    QApplication::setOrganizationName("gooddoog");
    QApplication::setOrganizationDomain("github.com/gooddoog/fishing-time");
    QApplication::setApplicationName("Fishing Time");
    if (argc == 2 && !strcmp(argv[1], "--help")) {
        qDebug() << "Usage:";
        qDebug() << argv[0] << "        - start the game";
        qDebug() << argv[0] << "--err   - show last error message";
        qDebug() << argv[0] << "--reset - reset game settings";
        return 0;
    }
    if (argc == 2 && !strcmp(argv[1], "--err")) {
        return ErrorWidget::launchViewer(&argc, &argv);
    }
    if (argc == 2 && !strcmp(argv[1], "--reset")) {
        QSettings settings;
        settings.clear();
        return 0;
    }
    signal(SIGSEGV, ErrorWidget::signalHandler);
    QApplication app(argc, argv);
    QString config = "config.json";
    if (argc >= 2)
        config = argv[1];
    QElapsedTimer timer;
    timer.start();
    Game game(nullptr, config);
    game.logger.info("Game loaded in " + QString::number(timer.elapsed()) + " milliseconds");
    game.show();
    return app.exec();
}
