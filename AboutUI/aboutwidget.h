#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include <QToolButton>

#include "aboutwidgetui.h"
#include "customwidget.h"

class AboutWidget : public CustomWidget
{
    Q_OBJECT

public:
    explicit AboutWidget(QWidget *parent = nullptr);
    ~AboutWidget();

public:
    void titleBarCustomCreate(void);

private:
    class AboutWidgetPrivate;
    const QScopedPointer<AboutWidgetPrivate> d;
};

#endif // ABOUTWIDGET_H
