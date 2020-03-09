#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QProcess>
#include "aboutmenu.h"
#include "errorwidget.h"
#include "utils.h"

void FT_ERROR::ft_assert(QString place, QString text) {
    QFile errorLog("error.log");
    if (errorLog.open(QFile::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream f(&errorLog);
        f << "Assertion failed at " << place << ": " << text << endl;
        f << ErrorWidget::getStacktrace();
        f << "-----------------------------------\n"
            "Version: " TOSTRING(COMMIT_HASH) "\n"
            "OS: " + AboutMenu::getSystemInfo() + "\n"
            "Compiler: " + AboutMenu::getCompilerInfo() + "\n";
        qApp->exit(1);
        QStringList newArgs = {
            "--err"
        };
        errorLog.close();
        if (!QProcess::startDetached(qApp->arguments()[0], newArgs)) {
            qCritical() << "Failed to open error window!";
            errorLog.open(QFile::ReadOnly);
            qCritical().noquote() << f.readAll();
        }
    }
    exit(1);
}

int ft_utils::toInt(const QKeySequence &obj) {
    return obj[0];
}
