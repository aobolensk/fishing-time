#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_
#include <QVariantMap>

class Game;

enum class InventoryType {
    POPUP, BUILTIN
};

enum class ColorTheme {
    LIGHT, DARK
};


class Config {
public: /* Constants */
    static const int MIN_AUTO_SAVE_PERIOD = 1;
    static const int MAX_AUTO_SAVE_PERIOD = 120;
    static const int STATISTICS_UPDATE_PERIOD = 1000;
    static const int MAX_INPUT_HISTORY_SIZE = 128;
    static const int SELLERS_COUNT = 3;
    static const int SLOTS_COUNT = 9;
    static const int NETS_TIMER_INTERVAL = 5 * 60 * 1000;
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
