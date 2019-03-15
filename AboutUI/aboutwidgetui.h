#ifndef ABOUTWIDGETUI_H
#define ABOUTWIDGETUI_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>
#include <QPushButton>
#include <QPixmap>

#include "appversions.h"

namespace Ui {
class AboutWidgetUI;
}

class AboutWidgetUI : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWidgetUI(QWidget *parent = nullptr);
    ~AboutWidgetUI() override;

public:
    QPushButton* aboutWidgetCloseButton() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::AboutWidgetUI *ui;
};

#endif // ABOUTWIDGETUI_H
