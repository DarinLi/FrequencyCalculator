#ifndef MAINWIDGETUI_H
#define MAINWIDGETUI_H

#include <QWidget>
#include <QStyleOption>
#include <QPainter>

#include <QSettings>
#include <QRadioButton>
#include <QButtonGroup>

#include "flowlayout.h"
#include "customsql.h"

namespace Ui {
class MainWidgetUI;
}

class MainWidgetUI : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidgetUI(QWidget *parent = nullptr);
    ~MainWidgetUI() override;

public:
    void toolButtonGroupCreate(void);
    void supportBWButtonGroupCreate(void);

    void gsmBandRadioButtonCreat(const QString &);
    void tdscdmaBandRadioButtonCreat(const QString &);
    void cdmaBandRadioButtonCreat(const QString &);
    void wcdmaBandRadioButtonCreat(const QString &);
    void lteBandRadioButtonCreat(const QString &);
    void nrBandRadioButtonCreat(const QString &);

    void FrequencyCalculatorInit(void);
    void BandInformationInit_Show(QVariantList &);

    void Information_Show(QVariantList &);
    void NRBandChannelRaster_Show(QVariantList &, int);
    void NRSubcarrierSpacing_Show(QVariantList &, int);
    void BandWidth_Show(QVariantList &, int);
    void BER_Show(QVariantList &, int);
    void BERConfig_Show(QVariantList &, int);
    void ChannelTP_Show(QVariantList &, int);
    void TRXTP_Show(QVariantList &);

    QVariant iniFilesValueRead(const QString &, const QString &);
    void iniFilesSetValue(const QString &, const QString &, const QVariant &);

private:
    QString FreqValue_Set(int, bool);
    int ChannelValue_Set(int, bool);
    bool ChannelRange_Set(int, int *, char);
    void aa(int *tmp);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void changeBandWidthUI(int);
    void changeBandWidth(int);
    void changeNRSubcarrierSpacing(int);
    void changeNRBandChannelRaster(int);

    void SetTXStartFreqValue(int);
    void SetRXStartFreqValue(int);
    void SetTXStopFreqValue(int);
    void SetRXStopFreqValue(int);

    void SetTXStartChannelValue(int);
    void SetRXStartChannelValue(int);
    void SetTXStopChannelValue(int);
    void SetRXStopChannelValue(int);

private:
    class MainWidgetUIPrivate;
    const QScopedPointer<MainWidgetUIPrivate> d;

private:
    Ui::MainWidgetUI *ui;
};

#endif // MAINWIDGETUI_H
