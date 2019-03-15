#include "aboutwidget.h"

class AboutWidget::AboutWidgetPrivate
{
public:
    QToolButton *closeButton = nullptr;

    QPushButton *uiCloseButton = nullptr;

    AboutWidgetUI *m_aboutWidgetUI = nullptr;
    QVBoxLayout *layout = nullptr;
};

AboutWidget::AboutWidget(QWidget *parent) :
    CustomWidget(parent),
    d(new AboutWidgetPrivate)
{
    this->setWindowIcon(QPixmap("./logo/logo.ico"));
    this->setWindowTitle(QStringLiteral("About"));

    titleBarCustomCreate();

    frameLessWidget.setTitleHeight(titleBarHeight());
    frameLessWidget.setWidgetResizable(false);

    d->layout = this->contentLayout();
    d->m_aboutWidgetUI = new AboutWidgetUI(this);
    d->layout->addWidget(d->m_aboutWidgetUI);

    resize(d->m_aboutWidgetUI->width(), d->m_aboutWidgetUI->height() + titleBarHeight());

    d->uiCloseButton = d->m_aboutWidgetUI->aboutWidgetCloseButton();
    connect(d->uiCloseButton, &QPushButton::clicked, this, [this]{this->close();});
}

AboutWidget::~AboutWidget()
{

}

void AboutWidget::titleBarCustomCreate(void)
{
    auto layout = this->titleBarLayout();

    layout->addWidget(d->closeButton = new QToolButton);
    d->closeButton->setObjectName(QStringLiteral("closebutton"));
    d->closeButton->setAutoRaise(true);
    d->closeButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    connect(d->closeButton, &QToolButton::clicked, this, [this]{this->close();});

    auto font = d->closeButton->font();
    font.setFamily("FontAwesome");
    font.setPixelSize(16);
    d->closeButton->setFont(font);
    d->closeButton->setText(QChar(0xf00d));
}
