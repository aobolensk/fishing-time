#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_
#include <QVariantMap>
#include <QByteArray>

class MainWindow;

class Config {
private:
    MainWindow *window;
    bool isReady = false;
public:
    Config(MainWindow *w = nullptr);
    ~Config() = default;
    void deserialize(const QVariantMap &map);
    QByteArray serialize() const;
};

#endif  // INCLUDE_CONFIG_H_
