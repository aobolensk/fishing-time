#ifndef INCLUDE_FILELOG_H_
#define INCLUDE_FILELOG_H_
#include <QFile>
#include <QTextStream>
#include "log.h"

class FileLog : public Log {
private:
    QFile *file;
    QTextStream *fs;
public:
    void open(const QString &filePath);
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
    FileLog(Game *game);
    ~FileLog() override;
};

#endif  // INCLUDE_FILELOG_H_
