#include <QFile>
#include <QTextStream>
#include <QProcess>
#include "utils.h"

void FT_ERROR::ft_assert(QString place, QString text) {
    QFile errorLog("error.log");
    if (errorLog.open(QFile::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream f(&errorLog);
        f << "Assertion failed at " << place << ": " << text << endl;
        f << ErrorWidget::getStacktrace();
        qApp->exit(1);
        QStringList newArgs = {
            "--err"
        };
        QProcess::startDetached(qApp->arguments()[0], newArgs);
    }
    exit(1);
}
