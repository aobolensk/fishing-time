#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_
#include <QVariantMap>
#include <QByteArray>

class Game;

enum class InventoryType {
    POPUP, BUILTIN
};

enum class ColorTheme {
    LIGHT, DARK
};

const int MIN_AUTO_SAVE_PERIOD = 1;
const int MAX_AUTO_SAVE_PERIOD = 120;

class Config {
private:
    Game *game;
    bool isReady = false;
public:
    Config(Game *game = nullptr);
    ~Config() = default;
    void deserialize(const QVariantMap &map);
    QJsonObject serialize() const;
    void applyColorTheme(ColorTheme theme);
};

#endif  // INCLUDE_CONFIG_H_
