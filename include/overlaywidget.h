#ifndef INCLUDE_OVERLAY_H_
#define INCLUDE_OVERLAY_H_
#include <QHBoxLayout>
#include <QLabel>

class OverlayWidget : public QWidget {
private:
    Q_OBJECT
public:
    OverlayWidget(QWidget *parent);
    ~OverlayWidget();
    void setText(const QString &newText);
    QString getText();
private:
    QLabel text;
    QHBoxLayout layout;
};

#endif  // INCLUDE_OVERLAY_H_
