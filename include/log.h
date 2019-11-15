#ifndef INCLUDE_LOG_H_
#define INCLUDE_LOG_H_
#include <QTextEdit>

class Game;

class Log {
protected:
    Game *game;
    QString getTimestamp();
public:
    virtual void debug(const QString &message) = 0;
    virtual void info(const QString &message) = 0;
    virtual void warning(const QString &message) = 0;
    virtual void error(const QString &message) = 0;
    virtual void debugT(const QString &message) = 0;
    virtual void infoT(const QString &message) = 0;
    virtual void warningT(const QString &message) = 0;
    virtual void errorT(const QString &message) = 0;
    virtual void write(const QString &message) = 0;
    virtual void writeln(const QString &message) = 0;
    virtual void setColor(const QString &color) = 0;
    virtual void resetColor() = 0;
    Log(Game *game);
    ~Log() = default;
};

class TextEditLog : public Log {
private:
    QTextEdit *console;
public:
    virtual void debug(const QString &message) override;
    virtual void info(const QString &message) override;
    virtual void warning(const QString &message) override;
    virtual void error(const QString &message) override;
    virtual void debugT(const QString &message) override;
    virtual void infoT(const QString &message) override;
    virtual void warningT(const QString &message) override;
    virtual void errorT(const QString &message) override;
    virtual void write(const QString &message) override;
    virtual void writeln(const QString &message) override;
    virtual void setColor(const QString &color) override;
    virtual void resetColor() override;
    TextEditLog(Game *game, QTextEdit *logField);
    ~TextEditLog() = default;
};

#endif  // INCLUDE_LOG_H_
