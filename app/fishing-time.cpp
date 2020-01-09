#include <QApplication>
#include <QCommandLineParser>
#include <QElapsedTimer>
#include <QSettings>
#include <QStringList>
#include <csignal>
#include "game.h"
#include "errorwidget.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    QApplication::setOrganizationName("gooddoog");
    QApplication::setOrganizationDomain("github.com/gooddoog/fishing-time");
    QApplication::setApplicationName("Fishing Time");
    QApplication::setApplicationVersion(TOSTRING(COMMIT_HASH));
    QCommandLineParser parser;
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption errorOption(QStringList() << "e" << "err" << "error", "Shows last error message.");
    parser.addOption(errorOption);
    QCommandLineOption resetOption(QStringList() << "r" << "reset", "Resets game settings.");
    parser.addOption(resetOption);
    QStringList args;
    for (int i = 0; i < argc; ++i) {
        args.append(argv[i]);
    }
    parser.parse(args);
    if (parser.isSet(errorOption)) {
        return ErrorWidget::launchViewer(&argc, &argv);
    }
    if (parser.isSet(resetOption)) {
        QSettings settings;
        settings.clear();
        return 0;
    }
    QApplication app(argc, argv);
    parser.process(args);
    signal(SIGSEGV, ErrorWidget::signalHandler);
    QString config = "config.json";
    QElapsedTimer timer;
    timer.start();
    Game game(nullptr, config);
    game.logger.info("Game loaded in " + QString::number(timer.elapsed()) + " milliseconds");
    game.show();
    return app.exec();
}
