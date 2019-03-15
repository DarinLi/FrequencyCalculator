#include "customwidget.h"

class CustomWidget::CustomWidgetPrivate
{
public:
    QLabel *iconLabel = nullptr;
    QLabel *titleLabel = nullptr;

    QWidget *titleBar = nullptr;

    QVBoxLayout *layout = nullptr;
    QHBoxLayout *titleBarLayout = nullptr;
    QVBoxLayout *contentLayout = nullptr;

    int titleBarHeight = 30;
};

CustomWidget::CustomWidget(QWidget *parent) :
    QDialog(parent),
    d(new CustomWidgetPrivate)
{
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    this->setObjectName(QStringLiteral("customwidget"));

    frameLessWidget.activateOn(this);

    d->layout = new QVBoxLayout(this);
    d->layout->addWidget(d->titleBar = new QWidget);
    d->layout->addLayout(d->contentLayout = new QVBoxLayout, 1);

    d->layout->setSpacing(0);
    d->layout->setMargin(0);
    d->contentLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    d->titleBar->setObjectName(QStringLiteral("titlebar"));
    d->titleBar->setAutoFillBackground(true);
    d->titleBar->setFixedHeight(d->titleBarHeight);

    d->titleBarLayout = new QHBoxLayout(d->titleBar);
    d->titleBarLayout->setContentsMargins(QMargins(5, 0, 5, 0));
    d->titleBarLayout->setSpacing(0);

    d->titleBarLayout->addWidget(d->iconLabel = new QLabel);
    d->iconLabel->setScaledContents(true);
    d->iconLabel->setFixedSize(16, 16);

    d->titleBarLayout->addSpacing(8);
    d->titleBarLayout->addWidget(d->titleLabel = new QLabel, 2);
    d->titleLabel->setObjectName(QStringLiteral("titlelabel"));

    setMinimumSize(200, 200);
}

CustomWidget::~CustomWidget()
{

}

void CustomWidget::setWindowTitle(const QString &title)
{
    d->titleLabel->setText(title);
}

void CustomWidget::setWindowIcon(const QPixmap &icon)
{
    d->iconLabel->setPixmap(icon);
}

void CustomWidget::setTitleBarHeight(const int height)
{
    d->titleBarHeight = height;
}

int CustomWidget::titleBarHeight() const
{
    return d->titleBarHeight;
}

QString CustomWidget::setWindowTitle() const
{
    return d->titleLabel->text();
}

QPixmap CustomWidget::icon() const
{
    return *d->iconLabel->pixmap();
}

QHBoxLayout* CustomWidget::titleBarLayout() const
{
    return d->titleBarLayout;
}

QVBoxLayout* CustomWidget::contentLayout() const
{
    return d->contentLayout;
}

void CustomWidget::setFixedSize(const QSize &size)
{
    resize(size);
    frameLessWidget.setWidgetResizable(false);
}

void CustomWidget::setFixedSize(int w, int h)
{
    resize(w, h);
    frameLessWidget.setWidgetResizable(false);
}
