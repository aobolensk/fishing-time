#ifndef INCLUDE_TEXTEDITLOG_H_
#define INCLUDE_TEXTEDITLOG_H_
#include <QTextEdit>
#include "log.h"

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

#endif  // INCLUDE_TEXTEDITLOG_H_
