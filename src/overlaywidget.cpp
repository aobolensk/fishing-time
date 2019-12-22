#include "overlaywidget.h"

OverlayWidget::OverlayWidget(QWidget *parent) :
    QWidget(parent),
    text(this),
    layout(QHBoxLayout(this)) {
    layout.addWidget(&text);
    layout.addStretch(1);
    this->resize(parent->size());
    layout.setAlignment(Qt::AlignLeft | Qt::AlignTop);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAttribute(Qt::WA_TransparentForMouseEvents);
    QPalette palette = text.palette();
    palette.setBrush(QPalette::Text, QColor(128, 128, 128, 100));
    palette.setBrush(QPalette::WindowText, QColor(128, 128, 128, 100));
    QFont font = text.font();
    font.setPointSize(10);
    text.setFont(font);
    text.setPalette(palette);
}

void OverlayWidget::setText(const QString &newText) {
    text.setText(newText);
}

QString OverlayWidget::getText() {
    return text.text();
}

OverlayWidget::~OverlayWidget() {

}
