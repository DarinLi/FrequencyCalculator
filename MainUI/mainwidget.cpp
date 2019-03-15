#include "mainwidget.h"

class MainWidget::MainWidgetPrivate
{
public:
    QToolButton* menuButton = nullptr;
    QToolButton* minButton = nullptr;
    QToolButton* maxButton = nullptr;
    QToolButton* closeButton = nullptr;

    QAction *themeStytle1 = nullptr;
    QAction *themeStytle2 = nullptr;
    QAction *qAPPAbout = nullptr;

    QToolButton *menuSettingsButton = nullptr;
    QActionGroup *themeStytleGroup = nullptr;

    QMenu *Titlemenu = nullptr;
    QMenu *themeMenu = nullptr;

    QVBoxLayout *layout = nullptr;

    MainWidgetUI *m_mainWidgetUI = nullptr;
    AboutWidget *m_aboutWidget = nullptr;
};

MainWidget::MainWidget(QWidget *parent) :
    CustomWidget(parent),
    d(new MainWidgetPrivate)
{
    QString title = QStringLiteral("Frequency Calculator ") + APPVersions +
                    QStringLiteral(" ") + APPRunStatus +
                    QStringLiteral(" By DarinLi");

    setWindowTitle(title);

    setWindowIcon(QPixmap("./logo/logo.ico"));

    setTranslator();

    frameLessWidget.setTitleHeight(titleBarHeight());

    d->layout = this->contentLayout();
    d->m_mainWidgetUI = new MainWidgetUI(this);
    d->layout->addWidget(d->m_mainWidgetUI);

    setFixedSize(d->m_mainWidgetUI->width(),
                 d->m_mainWidgetUI->height() + titleBarHeight());

    titleBarCustomCreate();
    titleBarMenuSettingsCreate();

    int themevalue = d->m_mainWidgetUI->iniFilesValueRead(QStringLiteral("AppTheme"),
                                                     QStringLiteral("Theme")).toInt();
    if(themevalue == 1)
        {setStyleSheet("./theme/brightblack.qss");d->themeStytle1->setChecked(true);}
    else if(themevalue == 2)
        {setStyleSheet("./theme/skyblue.qss");d->themeStytle2->setChecked(true);}
    else
        {setStyleSheet("./theme/brightblack.qss");d->themeStytle1->setChecked(true);}
}

MainWidget::~MainWidget()
{

}

void MainWidget::setTranslator(const QString &qmFile)
{
    QTranslator *translator = new QTranslator(qApp);
    translator->load(qmFile);
    qApp->installTranslator(translator);
}

void MainWidget::setStyleSheet(const QString &stytle)
{
    QFile file(stytle);

    if (file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1Literal(file.readAll());
        qApp->setStyleSheet(qss);
        file.close();
    }
}

void MainWidget::titleBarCustomCreate(void)
{
    auto layout = this->titleBarLayout();

    layout->addWidget(d->menuButton = new QToolButton);
    d->menuButton->setObjectName(QStringLiteral("menubutton"));
    d->menuButton->setAutoRaise(true);
    d->menuButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto font = d->menuButton->font();
    font.setFamily("FontAwesome");
    font.setPixelSize(14);
    d->menuButton->setFont(font);
    d->menuButton->setText(QChar(0xf0c9));

    layout->addWidget(d->minButton = new QToolButton);
    d->minButton->setObjectName(QStringLiteral("minbutton"));
    d->minButton->setAutoRaise(true);
    d->minButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(d->minButton,   &QToolButton::clicked, this, [this] {this->showMinimized();});

    auto font1 = d->minButton->font();
    font1.setFamily("FontAwesome");
    font1.setPixelSize(12);
    d->minButton->setFont(font1);
    d->minButton->setText(QChar(0xf2d1));

    layout->addWidget(d->closeButton = new QToolButton);
    d->closeButton->setObjectName(QStringLiteral("closebutton"));
    d->closeButton->setAutoRaise(true);
    d->closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(d->closeButton, &QToolButton::clicked, this, [this] {this->close();});

    auto font2 = d->closeButton->font();
    font2.setFamily("FontAwesome");
    font2.setPixelSize(16);
    d->closeButton->setFont(font2);
    d->closeButton->setText(QChar(0xf00d));
}

void MainWidget::titleBarMenuSettingsCreate(void)
{
    d->qAPPAbout = new QAction(QStringLiteral("关于"));
    d->qAPPAbout->setObjectName(QStringLiteral("qAPPabout"));

    d->themeStytle1 = new QAction(QStringLiteral("亮黑色"));
    d->themeStytle1->setObjectName(QStringLiteral("themestytle1"));
    d->themeStytle1->setCheckable(true);

    d->themeStytle2 = new QAction(QStringLiteral("天依蓝"));
    d->themeStytle2->setObjectName(QStringLiteral("themestytle2"));
    d->themeStytle2->setCheckable(true);

    d->themeStytleGroup = new QActionGroup(this);
    d->themeStytleGroup->setObjectName(QStringLiteral("themestytlegroup"));
    d->themeStytleGroup->addAction(d->themeStytle1);
    d->themeStytleGroup->addAction(d->themeStytle2);

    d->themeMenu = new QMenu(QStringLiteral("主题"));
    d->themeMenu->addAction(d->themeStytle1);
    d->themeMenu->addAction(d->themeStytle2);

    d->Titlemenu = new QMenu();
    d->Titlemenu->addAction(d->themeMenu->menuAction());
    d->Titlemenu->addSeparator();
    d->Titlemenu->addAction(d->qAPPAbout);

    d->menuButton->setMenu(d->Titlemenu);
    d->menuButton->setPopupMode(QToolButton::InstantPopup);

    connect(d->themeStytleGroup, &QActionGroup::triggered, this, &MainWidget::changeTheme);
    connect(d->qAPPAbout, &QAction::triggered, this, &MainWidget::openAboutUI);
}

void MainWidget::changeTheme(void)
{
    if(d->themeStytle1->isChecked())
    {
        setStyleSheet("./theme/brightblack.qss");
        d->m_mainWidgetUI->iniFilesSetValue(QStringLiteral("AppTheme"),
                                       QStringLiteral("Theme"),
                                       QStringLiteral("1"));
    }
    else if(d->themeStytle2->isChecked())
    {
        setStyleSheet("./theme/skyblue.qss");
        d->m_mainWidgetUI->iniFilesSetValue(QStringLiteral("AppTheme"),
                                       QStringLiteral("Theme"),
                                       QStringLiteral("2"));
    }
}

void MainWidget::openAboutUI(void)
{
    d->m_aboutWidget = new AboutWidget(this);
    d->m_aboutWidget->setAttribute(Qt::WA_DeleteOnClose);
    if(d->m_aboutWidget != nullptr)
        d->m_aboutWidget->exec();
}
