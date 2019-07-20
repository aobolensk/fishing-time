#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_
#include <QVariantMap>
#include <QByteArray>

class Game;

class Config {
private:
    Game *game;
    bool isReady = false;
public:
    Config(Game *game = nullptr);
    ~Config() = default;
    void deserialize(const QVariantMap &map);
    QByteArray serialize() const;
};

#endif  // INCLUDE_CONFIG_H_
