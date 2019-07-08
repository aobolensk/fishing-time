#ifndef INCLUDE_LOCATION_H_
#define INCLUDE_LOCATION_H_
#include <QVector>

class MainWindow;

class Location {
private:
    QString name;
    QVector <QString> fish;
public:
    Location(const QString &locName = "", const QVector <QString> &fishList = {});
    ~Location() = default;
    const QString &getFish(int index);
    static QVector <Location> initializeLocations(MainWindow *w);
};

#endif  // INCLUDE_LOCATION_H_
