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
