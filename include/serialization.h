#ifndef INCLUDE_SERIALIZATION_H_
#define INCLUDE_SERIALIZATION_H_
#include <QString>

template <typename T>
static QString toString(const T &data) {
    QTemporaryFile f;
    f.open();
    QDataStream out(&f);
    out << data;
    f.flush();
    f.close();
    f.open();
    QTextStream in(&f);
    QString result = in.readAll();
    f.close();
    return result;
}

template <typename T>
static void fromString(T &data, const QString &str) {
    QTemporaryFile f;
    f.open();
    QTextStream out(&f);
    out << str;
    f.close();
    f.open();
    QDataStream in(&f);
    in >> data;
    f.close();
}

#endif  // INCLUDE_SERIALIZATION_H_
