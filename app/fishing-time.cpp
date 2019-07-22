#include <QApplication>
#include <QDebug>
#include "game.h"
#include "user.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QString config = "config.json";
    if (argc >= 2)
        config = argv[1];
    Game game(nullptr, config);
    game.show();
    return app.exec();
}
