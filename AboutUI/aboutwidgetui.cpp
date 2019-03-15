#include "aboutwidgetui.h"
#include "ui_aboutwidgetui.h"

AboutWidgetUI::AboutWidgetUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidgetUI)
{
    ui->setupUi(this);

    ui->icoLabel->setScaledContents(true);
    ui->icoLabel->setPixmap(QPixmap("./logo/aboutlogo.ico"));

    ui->updataContentTextEdit->setReadOnly(true);

    ui->versionsLabel->setText(QStringLiteral("Version ") + APPVersions +
                                   QStringLiteral(" ") + APPRunStatus);
}

AboutWidgetUI::~AboutWidgetUI()
{
    delete ui;
}

void AboutWidgetUI::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QPushButton* AboutWidgetUI::aboutWidgetCloseButton() const
{
    return ui->closeButton;
}
