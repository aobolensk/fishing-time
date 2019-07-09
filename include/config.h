#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_
#include <QVariantMap>
#include <QByteArray>

enum class Language;

class Config {
private:
    bool isReady = false;
public:
    Language language = (Language)0;
public:
    Config() = default;
    ~Config() = default;
    void deserialize(const QVariantMap &map);
    QByteArray serialize() const;
};

#endif  // INCLUDE_CONFIG_H_
