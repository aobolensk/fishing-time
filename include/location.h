#ifndef INCLUDE_LOCATION_H_
#define INCLUDE_LOCATION_H_
#include <QVector>

class MainWindow;

class Location {
private:
    const QString *name;
    QVector <QString> fish;
public:
    Location(const QString &locName = "", const QVector <QString> &fishList = {});
    ~Location() = default;
    const QString &getName() const;
    const QString &getFish(int index) const;
    int getFishCount() const;
    static QVector <Location> initializeLocations(MainWindow *w);
};

#endif  // INCLUDE_LOCATION_H_
