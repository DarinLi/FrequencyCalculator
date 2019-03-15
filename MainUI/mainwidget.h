#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QToolButton>
#include <QEvent>

#include <QTranslator>

#include "mainwidgetui.h"
#include "customwidget.h"
#include "aboutwidget.h"

#include "appversions.h"

class MainWidget : public CustomWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;

public:
    void titleBarCustomCreate(void);
    void titleBarMenuSettingsCreate(void);
    void setStyleSheet(const QString &stytle = "./theme/brightblack.qss");
    void setTranslator(const QString &qmFile = "./translations/qt_zh_CN.qm");

private slots:
    void changeTheme(void);
    void openAboutUI(void);

private:
    class MainWidgetPrivate;
    const QScopedPointer<MainWidgetPrivate> d;
};

#endif // MAINWIDGET_H
