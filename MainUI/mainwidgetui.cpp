#include "mainwidgetui.h"
#include "ui_mainwidgetui.h"

#include <QDebug>

class MainWidgetUI::MainWidgetUIPrivate
{
public:
    QButtonGroup *toolButtonGroup = nullptr;
    QButtonGroup *LTESupportBWButtonGroup = nullptr;
    QButtonGroup *NRSupportBWButtonGroup = nullptr;
    QButtonGroup *NRSubcarrierSpacingButtonGroup = nullptr;
    QButtonGroup *NRBandChannelRasterButtonGroup = nullptr;

    QList<QRadioButton *> gsmRadioButtonList;
    QList<QRadioButton *> tdscdmaRadioButtonList;
    QList<QRadioButton *> cdmaRadioButtonList;
    QList<QRadioButton *> wcdmaRadioButtonList;
    QList<QRadioButton *> lteRadioButtonList;
    QList<QRadioButton *> nrRadioButtonList;

    QButtonGroup *gsmButtonGroup = nullptr;
    QButtonGroup *tdscdmaButtonGroup = nullptr;
    QButtonGroup *cdmaButtonGroup = nullptr;
    QButtonGroup *wcdmaButtonGroup = nullptr;
    QButtonGroup *lteButtonGroup = nullptr;
    QButtonGroup *nrButtonGroup = nullptr;

    FlowLayout *gsmBandflowLayout = nullptr;
    FlowLayout *tdscdmaBandflowLayout = nullptr;
    FlowLayout *cdmaBandflowLayout = nullptr;
    FlowLayout *wcdmaBandflowLayout = nullptr;
    FlowLayout *lteBandflowLayout = nullptr;
    FlowLayout *nrBandflowLayout = nullptr;

    QVariantList gsmValueVariantList;
    QVariantList tdscdmaValueVariantList;
    QVariantList cdmaValueVariantList;
    QVariantList wcdmaValueVariantList;
    QVariantList lteValueVariantList;
    QVariantList nrValueVariantList;

    qint32 curruntSubcarrierSpacingid = 0;
    qint32 curruntBandChannelRasterid = 0;
    qint32 curruntBandWidthid = 0;
};

MainWidgetUI::MainWidgetUI(QWidget *parent) :
    QWidget(parent),
    d(new MainWidgetUIPrivate),
    ui(new Ui::MainWidgetUI)
{
    ui->setupUi(this);

    CustomSql::connect("customdb.db");

    gsmBandRadioButtonCreat("GSMBandInfo");
    tdscdmaBandRadioButtonCreat("TDSCDMABandInfo");
    cdmaBandRadioButtonCreat("CDMABandInfo");
    wcdmaBandRadioButtonCreat("WCDMABandInfo");
    lteBandRadioButtonCreat("LTEBandInfo");
    nrBandRadioButtonCreat("NRBandInfo");

    toolButtonGroupCreate();
    supportBWButtonGroupCreate();

    FrequencyCalculatorInit();
}

MainWidgetUI::~MainWidgetUI()
{
    delete ui;
}

void MainWidgetUI::toolButtonGroupCreate(void)
{
    d->toolButtonGroup = new QButtonGroup(this);
    d->toolButtonGroup->setObjectName(QStringLiteral("toolButtonGroup"));
    d->toolButtonGroup->setExclusive(true);

    d->toolButtonGroup->addButton(ui->NRBandTB, 0);
    d->toolButtonGroup->addButton(ui->LTEBandTB, 1);
    d->toolButtonGroup->addButton(ui->WCDMABandTB, 2);
    d->toolButtonGroup->addButton(ui->CDMABandTB, 3);
    d->toolButtonGroup->addButton(ui->TDSCDMABandTB, 4);
    d->toolButtonGroup->addButton(ui->GSMBandTB, 5);

    connect(d->toolButtonGroup,    QOverload<int>::of(&QButtonGroup::buttonClicked),
            ui->BandStackedWidget, QOverload<int>::of(&QStackedWidget::setCurrentIndex));
    connect(d->toolButtonGroup,    QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWidgetUI::changeBandWidthUI);
}

void MainWidgetUI::changeBandWidthUI(int curruntid)
{
    if(curruntid == 0)
        ui->BandWidthStackedWidget->setCurrentIndex(0);
    else
        ui->BandWidthStackedWidget->setCurrentIndex(1);

    switch (curruntid) {
        case 0: BandInformationInit_Show(d->nrValueVariantList);break;
        case 1: BandInformationInit_Show(d->lteValueVariantList);break;
        case 2: BandInformationInit_Show(d->wcdmaValueVariantList);break;
        case 3: BandInformationInit_Show(d->cdmaValueVariantList);break;
        case 4: BandInformationInit_Show(d->tdscdmaValueVariantList);break;
        case 5: BandInformationInit_Show(d->gsmValueVariantList);break;
        default: break;
    }
}

void MainWidgetUI::supportBWButtonGroupCreate(void)
{
    d->LTESupportBWButtonGroup = new QButtonGroup(this);
    d->LTESupportBWButtonGroup->setObjectName(QStringLiteral("LTESupportBWButtonGroup"));
    d->LTESupportBWButtonGroup->setExclusive(true);

    d->LTESupportBWButtonGroup->addButton(ui->LTE_1_4MHz, 0);
    d->LTESupportBWButtonGroup->addButton(ui->LTE_3MHz, 1);
    d->LTESupportBWButtonGroup->addButton(ui->LTE_5MHz, 2);
    d->LTESupportBWButtonGroup->addButton(ui->LTE_10MHz, 3);
    d->LTESupportBWButtonGroup->addButton(ui->LTE_15MHz, 4);
    d->LTESupportBWButtonGroup->addButton(ui->LTE_20MHz, 5);

    connect(d->LTESupportBWButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWidgetUI::changeBandWidth);

    d->NRSupportBWButtonGroup = new QButtonGroup(this);
    d->NRSupportBWButtonGroup->setObjectName(QStringLiteral("NRSupportBWButtonGroup"));
    d->NRSupportBWButtonGroup->setExclusive(true);

    d->NRSupportBWButtonGroup->addButton(ui->NR_5MHz, 0);
    d->NRSupportBWButtonGroup->addButton(ui->NR_10MHz, 1);
    d->NRSupportBWButtonGroup->addButton(ui->NR_15MHz, 2);
    d->NRSupportBWButtonGroup->addButton(ui->NR_20MHz, 3);
    d->NRSupportBWButtonGroup->addButton(ui->NR_25MHz, 4);
    d->NRSupportBWButtonGroup->addButton(ui->NR_30MHz, 5);
    d->NRSupportBWButtonGroup->addButton(ui->NR_40MHz, 6);
    d->NRSupportBWButtonGroup->addButton(ui->NR_50MHz, 7);
    d->NRSupportBWButtonGroup->addButton(ui->NR_60MHz, 8);
    d->NRSupportBWButtonGroup->addButton(ui->NR_80MHz, 9);
    d->NRSupportBWButtonGroup->addButton(ui->NR_90MHz, 10);
    d->NRSupportBWButtonGroup->addButton(ui->NR_100MHz, 11);
    d->NRSupportBWButtonGroup->addButton(ui->NR_200MHz, 12);
    d->NRSupportBWButtonGroup->addButton(ui->NR_400MHz, 13);

    connect(d->NRSupportBWButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWidgetUI::changeBandWidth);

    d->NRBandChannelRasterButtonGroup = new QButtonGroup(this);
    d->NRBandChannelRasterButtonGroup->setObjectName(QStringLiteral("NRBandChannelRasterButtonGroup"));
    d->NRBandChannelRasterButtonGroup->setExclusive(true);

    d->NRBandChannelRasterButtonGroup->addButton(ui->NR15KHzChannelRaster, 0);
    d->NRBandChannelRasterButtonGroup->addButton(ui->NR30KHzChannelRaster, 1);
    d->NRBandChannelRasterButtonGroup->addButton(ui->NR60KHzChannelRaster, 2);
    d->NRBandChannelRasterButtonGroup->addButton(ui->NR100KHzChannelRaster, 3);
    d->NRBandChannelRasterButtonGroup->addButton(ui->NR120KHzChannelRaster, 4);

    connect(d->NRBandChannelRasterButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWidgetUI::changeNRBandChannelRaster);

    d->NRSubcarrierSpacingButtonGroup = new QButtonGroup(this);
    d->NRSubcarrierSpacingButtonGroup->setObjectName(QStringLiteral("NRSubcarrierSpacingButtonGroup"));
    d->NRSubcarrierSpacingButtonGroup->setExclusive(true);

    d->NRSubcarrierSpacingButtonGroup->addButton(ui->NR15KHzSpacing, 0);
    d->NRSubcarrierSpacingButtonGroup->addButton(ui->NR30KHzSpacing, 1);
    d->NRSubcarrierSpacingButtonGroup->addButton(ui->NR60KHzSpacing, 2);
    d->NRSubcarrierSpacingButtonGroup->addButton(ui->NR120KHzSpacing, 3);

    connect(d->NRSubcarrierSpacingButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            this, &MainWidgetUI::changeNRSubcarrierSpacing);
}

void MainWidgetUI::gsmBandRadioButtonCreat(const QString &dbTable)
{
    d->gsmBandflowLayout = new FlowLayout(15,45,10);

    d->gsmButtonGroup = new QButtonGroup(this);
    d->gsmButtonGroup->setObjectName(QStringLiteral("gsmButtonGroup"));
    d->gsmButtonGroup->setExclusive(true);

    QVariantList listvar =CustomSql::sqlRowData(dbTable,"Band_Name");

    for(int i = 0; i< listvar.count(); i++) {
        d->gsmRadioButtonList<<new QRadioButton(this);
        d->gsmRadioButtonList[i]->setFixedSize(125, 25);
        d->gsmRadioButtonList[i]->setText(listvar.at(i).toString());

        d->gsmButtonGroup->addButton(d->gsmRadioButtonList[i], i);
        d->gsmBandflowLayout->addWidget(d->gsmRadioButtonList[i]);
    }
    ui->GSMBandWidget->setLayout(d->gsmBandflowLayout);

    d->gsmRadioButtonList[0]->setChecked(true);
    d->gsmValueVariantList = CustomSql::sqlcolumnData("GSMBandInfo", 0);

    connect(d->gsmButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            [=](int id){
                d->gsmValueVariantList = CustomSql::sqlcolumnData("GSMBandInfo", id);
                BandInformationInit_Show(d->gsmValueVariantList);
            });
}

void MainWidgetUI::tdscdmaBandRadioButtonCreat(const QString &dbTable)
{
    d->tdscdmaBandflowLayout = new FlowLayout(15,25,10);

    d->tdscdmaButtonGroup = new QButtonGroup(this);
    d->tdscdmaButtonGroup->setObjectName(QStringLiteral("tdscdmaButtonGroup"));
    d->tdscdmaButtonGroup->setExclusive(true);

    QVariantList listvar =CustomSql::sqlRowData(dbTable,"Band_Name");

    for(int i = 0; i< listvar.count(); i++) {
        d->tdscdmaRadioButtonList<<new QRadioButton(this);
        d->tdscdmaRadioButtonList[i]->setFixedSize(135, 25);
        d->tdscdmaRadioButtonList[i]->setText(listvar.at(i).toString());

        d->tdscdmaButtonGroup->addButton(d->tdscdmaRadioButtonList[i], i);
        d->tdscdmaBandflowLayout->addWidget(d->tdscdmaRadioButtonList[i]);
    }
    ui->TDSCDMABandWidget->setLayout(d->tdscdmaBandflowLayout);

    d->tdscdmaRadioButtonList[0]->setChecked(true);
    d->tdscdmaValueVariantList = CustomSql::sqlcolumnData("TDSCDMABandInfo", 0);

    connect(d->tdscdmaButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            [=](int id){
                d->tdscdmaValueVariantList = CustomSql::sqlcolumnData("TDSCDMABandInfo", id);
                BandInformationInit_Show(d->tdscdmaValueVariantList);
            });
}

void MainWidgetUI::cdmaBandRadioButtonCreat(const QString &dbTable)
{
    d->cdmaBandflowLayout = new FlowLayout(15,45,10);

    d->cdmaButtonGroup = new QButtonGroup(this);
    d->cdmaButtonGroup->setObjectName(QStringLiteral("cdmaButtonGroup"));
    d->cdmaButtonGroup->setExclusive(true);

    QVariantList listvar =CustomSql::sqlRowData(dbTable,"Band_Name");

    for(int i = 0; i< listvar.count(); i++) {
        d->cdmaRadioButtonList<<new QRadioButton(this);
        d->cdmaRadioButtonList[i]->setFixedSize(125, 25);
        d->cdmaRadioButtonList[i]->setText(listvar.at(i).toString());

        d->cdmaButtonGroup->addButton(d->cdmaRadioButtonList[i], i);
        d->cdmaBandflowLayout->addWidget(d->cdmaRadioButtonList[i]);
    }
    ui->CDMABandWidget->setLayout(d->cdmaBandflowLayout);

    d->cdmaRadioButtonList[0]->setChecked(true);
    d->cdmaValueVariantList = CustomSql::sqlcolumnData("CDMABandInfo", 0);

    connect(d->cdmaButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            [=](int id){
                d->cdmaValueVariantList = CustomSql::sqlcolumnData("CDMABandInfo", id);
                BandInformationInit_Show(d->cdmaValueVariantList);
            });

    int bandid = CustomSql::sqlcolumnID(dbTable, "CDMA BC2");
    d->cdmaRadioButtonList[bandid]->setEnabled(false);
    bandid = CustomSql::sqlcolumnID(dbTable, "CDMA BC3");
    d->cdmaRadioButtonList[bandid]->setEnabled(false);
    bandid = CustomSql::sqlcolumnID(dbTable, "CDMA BC5");
    d->cdmaRadioButtonList[bandid]->setEnabled(false);
    bandid = CustomSql::sqlcolumnID(dbTable, "CDMA BC11");
    d->cdmaRadioButtonList[bandid]->setEnabled(false);
    bandid = CustomSql::sqlcolumnID(dbTable, "CDMA BC12");
    d->cdmaRadioButtonList[bandid]->setEnabled(false);
}

void MainWidgetUI::wcdmaBandRadioButtonCreat(const QString &dbTable)
{
    d->wcdmaBandflowLayout = new FlowLayout(15,45,10);

    d->wcdmaButtonGroup = new QButtonGroup(this);
    d->wcdmaButtonGroup->setObjectName(QStringLiteral("wcdmaButtonGroup"));
    d->wcdmaButtonGroup->setExclusive(true);

    QVariantList listvar =CustomSql::sqlRowData(dbTable,"Band_Name");

    for(int i = 0; i< listvar.count(); i++) {
        d->wcdmaRadioButtonList<<new QRadioButton(this);
        d->wcdmaRadioButtonList[i]->setFixedSize(125, 25);
        d->wcdmaRadioButtonList[i]->setText(listvar.at(i).toString());

        d->wcdmaButtonGroup->addButton(d->wcdmaRadioButtonList[i], i);
        d->wcdmaBandflowLayout->addWidget(d->wcdmaRadioButtonList[i]);
    }
    ui->WCDMABandWidget->setLayout(d->wcdmaBandflowLayout);

    d->wcdmaRadioButtonList[0]->setChecked(true);
    d->wcdmaValueVariantList = CustomSql::sqlcolumnData("WCDMABandInfo", 0);

    connect(d->wcdmaButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            [=](int id){
                d->wcdmaValueVariantList = CustomSql::sqlcolumnData("WCDMABandInfo", id);
                BandInformationInit_Show(d->wcdmaValueVariantList);
            });
}

void MainWidgetUI::lteBandRadioButtonCreat(const QString &dbTable)
{
    d->lteBandflowLayout = new FlowLayout(5,0,5);

    d->lteButtonGroup = new QButtonGroup(this);
    d->lteButtonGroup->setObjectName(QStringLiteral("lteButtonGroup"));
    d->lteButtonGroup->setExclusive(true);

    QVariantList listvar =CustomSql::sqlRowData(dbTable,"Band_Name");

    for(int i = 0; i< listvar.count(); i++) {
        d->lteRadioButtonList<<new QRadioButton(this);
        d->lteRadioButtonList[i]->setFixedSize(79, 25);
        d->lteRadioButtonList[i]->setText(listvar.at(i).toString());

        d->lteButtonGroup->addButton(d->lteRadioButtonList[i], i);
        d->lteBandflowLayout->addWidget(d->lteRadioButtonList[i]);
    }
    ui->LTEBandWidget->setLayout(d->lteBandflowLayout);

    d->lteRadioButtonList[0]->setChecked(true);
    d->lteValueVariantList = CustomSql::sqlcolumnData("LTEBandInfo", 0);

    connect(d->lteButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            [=](int id){
                d->lteValueVariantList = CustomSql::sqlcolumnData("LTEBandInfo", id);
                BandInformationInit_Show(d->lteValueVariantList);
            });

    int bandid = CustomSql::sqlcolumnID(dbTable, "LTE B15");
    d->lteRadioButtonList[bandid]->setEnabled(false);
    bandid = CustomSql::sqlcolumnID(dbTable, "LTE B16");
    d->lteRadioButtonList[bandid]->setEnabled(false);
    //bandid = CustomSql::sqlcolumnID(dbTable, "LTE B32");
    //d->lteRadioButtonList[bandid]->setEnabled(false);
}

void MainWidgetUI::nrBandRadioButtonCreat(const QString &dbTable)
{
    d->nrBandflowLayout = new FlowLayout(5,0,5);

    d->nrButtonGroup = new QButtonGroup(this);
    d->nrButtonGroup->setObjectName(QStringLiteral("nrButtonGroup"));
    d->nrButtonGroup->setExclusive(true);

    QVariantList listvar =CustomSql::sqlRowData(dbTable,"Band_Name");

    for(int i = 0; i< listvar.count(); i++) {
        d->nrRadioButtonList<<new QRadioButton(this);
        d->nrRadioButtonList[i]->setFixedSize(79, 25);
        d->nrRadioButtonList[i]->setText(listvar.at(i).toString());

        d->nrButtonGroup->addButton(d->nrRadioButtonList[i], i);
        d->nrBandflowLayout->addWidget(d->nrRadioButtonList[i]);
    }
    ui->NRBandWidget->setLayout(d->nrBandflowLayout);

    d->nrRadioButtonList[0]->setChecked(true);
    d->nrValueVariantList = CustomSql::sqlcolumnData("NRBandInfo", 0);

    connect(d->nrButtonGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            [=](int id){
                d->nrValueVariantList = CustomSql::sqlcolumnData("NRBandInfo", id);
                BandInformationInit_Show(d->nrValueVariantList);
            });
}

void MainWidgetUI::changeBandWidth(int curruntid)
{
    QVariantList varlist;
    d->curruntBandWidthid = curruntid;

    switch (ui->BandStackedWidget->currentIndex()) {
        case 0 : varlist = d->nrValueVariantList;break;
        case 1 : varlist = d->lteValueVariantList;break;
        case 2 : varlist = d->wcdmaValueVariantList;break;
        case 3 : varlist = d->cdmaValueVariantList;break;
        case 4 : varlist = d->tdscdmaValueVariantList;break;
        case 5 : varlist = d->gsmValueVariantList;break;
        default: break;
    }

    if(varlist.at(1).toString() == "NR") {
        //NR
        BER_Show(varlist, curruntid);
        BERConfig_Show(varlist, curruntid);
        ChannelTP_Show(varlist, curruntid);
    } else if (varlist.at(1).toString() == "LTE") {
        BER_Show(varlist, curruntid);
        BERConfig_Show(varlist, curruntid);
        ChannelTP_Show(varlist, curruntid);
    } else {
        BER_Show(varlist, curruntid);
    }
}

void MainWidgetUI::changeNRSubcarrierSpacing(int curruntid)
{
    QVariantList varlist = d->nrValueVariantList;
    d->curruntSubcarrierSpacingid = curruntid;

    if(ui->BandStackedWidget->currentIndex() == 0) {
        BandWidth_Show(varlist, varlist.at(3).toInt());
        BER_Show(varlist, varlist.at(3).toInt());
        BERConfig_Show(varlist, varlist.at(3).toInt());
        ChannelTP_Show(varlist, varlist.at(3).toInt());
    }
}

void MainWidgetUI::changeNRBandChannelRaster(int curruntid)
{
    QVariantList varlist = d->nrValueVariantList;
    d->curruntBandChannelRasterid = curruntid;

    if(ui->BandStackedWidget->currentIndex() == 0) {
        ChannelTP_Show(varlist, d->curruntBandWidthid);
    }
}

void MainWidgetUI::FrequencyCalculatorInit(void)
{
    connect(ui->TXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetTXStartFreqValue(int)));
    connect(ui->RXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetRXStartFreqValue(int)));
    connect(ui->TXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetTXStopFreqValue(int)));
    connect(ui->RXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetRXStopFreqValue(int)));

    connect(ui->TXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetRXStartChannelValue(int)));
    connect(ui->RXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetTXStartChannelValue(int)));
    connect(ui->TXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetRXStopChannelValue(int)));
    connect(ui->RXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetTXStopChannelValue(int)));

    BandInformationInit_Show(d->nrValueVariantList);
}

void MainWidgetUI::SetTXStartFreqValue(int channelvalue)
{
    ui->TXStartFreqValue->setText(FreqValue_Set(channelvalue, 0));
}

void MainWidgetUI::SetRXStartFreqValue(int channelvalue)
{
    ui->RXStartFreqValue->setText(FreqValue_Set(channelvalue, 1));
}

void MainWidgetUI::SetTXStopFreqValue(int channelvalue)
{
    ui->TXStopFreqValue->setText(FreqValue_Set(channelvalue, 0));
}

void MainWidgetUI::SetRXStopFreqValue(int channelvalue)
{
    ui->RXStopFreqValue->setText(FreqValue_Set(channelvalue, 1));
}

void MainWidgetUI::SetTXStartChannelValue(int channelvalue)
{
    int curruntchannelbackup = 0;

    if(ChannelRange_Set(channelvalue, &curruntchannelbackup, 1))
        ui->RXStartChannelValue->setValue(curruntchannelbackup);
    else
        ui->TXStartChannelValue->setValue(ChannelValue_Set(channelvalue, 0));
}

void MainWidgetUI::SetRXStartChannelValue(int channelvalue)
{
    int curruntchannelbackup = 0;

    if(ChannelRange_Set(channelvalue, &curruntchannelbackup, 1))
        ui->TXStartChannelValue->setValue(curruntchannelbackup);
    else
        ui->RXStartChannelValue->setValue(ChannelValue_Set(channelvalue, 1));
}

void MainWidgetUI::SetTXStopChannelValue(int channelvalue)
{
    int curruntchannelbackup = 0;

    if(ChannelRange_Set(channelvalue, &curruntchannelbackup, 0))
        ui->RXStopChannelValue->setValue(curruntchannelbackup);
    else
        ui->TXStopChannelValue->setValue(ChannelValue_Set(channelvalue, 0));
}

void MainWidgetUI::SetRXStopChannelValue(int channelvalue)
{
    int curruntchannelbackup = 0;

    if(ChannelRange_Set(channelvalue, &curruntchannelbackup, 0))
        ui->TXStopChannelValue->setValue(curruntchannelbackup);
    else
        ui->RXStopChannelValue->setValue(ChannelValue_Set(channelvalue, 1));
}

QString MainWidgetUI::FreqValue_Set(int curruntchannel, bool sta)
{
    QVariantList varlist;

    double freqvalue = 0.0;
    int Start_Channel = 0;
    double Start_Frequency = 0.0;
    double signalratio = 0.0;
    char deccode = 0;

    switch (ui->BandStackedWidget->currentIndex()) {
        case 0 : varlist = d->nrValueVariantList;break;
        case 1 : varlist = d->lteValueVariantList;break;
        case 2 : varlist = d->wcdmaValueVariantList;break;
        case 3 : varlist = d->cdmaValueVariantList;break;
        case 4 : varlist = d->tdscdmaValueVariantList;break;
        case 5 : varlist = d->gsmValueVariantList;break;
        default: break;
    }

    if(varlist.at(1).toString() == "NR") {
        Start_Frequency = varlist.at(12 + sta).toDouble();
        Start_Channel = varlist.at(14 + sta).toInt();

        if(Start_Frequency >= 24500.0) signalratio = 0.06;
        else if(Start_Frequency >= 3000.0) signalratio = 0.015;
        else signalratio = 0.005;

        freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*signalratio + Start_Frequency;

        return QString::number(freqvalue, 'f', 3);
    } else if (varlist.at(1).toString() == "LTE") {
        Start_Frequency = varlist.at(5 + sta).toDouble();
        Start_Channel = varlist.at(7 + sta).toInt();
        freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*0.1 + Start_Frequency;

        return QString::number(freqvalue, 'f', 1);
    } else if (varlist.at(1).toString() == "WCDMA" || varlist.at(1).toString() == "TDSCDMA") {
        Start_Frequency = varlist.at(4 + sta).toDouble();
        Start_Channel = varlist.at(6 + sta).toInt();
        freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*0.2 + Start_Frequency;

        return QString::number(freqvalue, 'f', 1);
    } else if (varlist.at(1).toString() == "CDMA") {
        Start_Frequency = varlist.at(4 + sta).toDouble();
        Start_Channel = varlist.at(6 + sta).toInt();

        if(varlist.at(2).toString() == "CDMA BC0") {
            if(curruntchannel <= 799)
                freqvalue = (static_cast<double>(curruntchannel - Start_Channel + 1023))*0.03 + Start_Frequency;
            else
                freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*0.03 + Start_Frequency;

            deccode = 2;

        } else if(varlist.at(2).toString() == "CDMA BC10") {
            if(sta) signalratio = 84.0;
            else signalratio = 90.0;

            if(curruntchannel >= 720)
                freqvalue = (static_cast<double>(curruntchannel - Start_Channel - 720))*0.025 + Start_Frequency + signalratio;
            else
                freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*0.025 + Start_Frequency;

            deccode = 3;

        } else {
            freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*0.05 + Start_Frequency;
            deccode = 2;
        }

        return QString::number(freqvalue, 'f', deccode);
    } else if (varlist.at(1).toString() == "GSM") {
        Start_Frequency = varlist.at(4 + sta).toDouble();
        Start_Channel = varlist.at(6 + sta).toInt();

        if(varlist.at(2).toString() == "E-GSM 900") {
            if(curruntchannel <= 124)
                freqvalue = (static_cast<double>(curruntchannel - Start_Channel + 1024))*0.2 + Start_Frequency;
            else
                freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*0.2 + Start_Frequency;
        } else {
            freqvalue = (static_cast<double>(curruntchannel - Start_Channel))*0.2 + Start_Frequency;
        }

        return QString::number(freqvalue, 'f', 1);
    }

    return "0.0";
}

int MainWidgetUI::ChannelValue_Set(int curruntchannel, bool sta)
{
    QVariantList varlist;

    int TX_Start_Channel = 0, RX_Start_Channel = 0;
    int ratiocompensate = 0;

    switch (ui->BandStackedWidget->currentIndex()) {
        case 0 : varlist = d->nrValueVariantList;break;
        case 1 : varlist = d->lteValueVariantList;break;
        case 2 : varlist = d->wcdmaValueVariantList;break;
        case 3 : varlist = d->cdmaValueVariantList;break;
        case 4 : varlist = d->tdscdmaValueVariantList;break;
        case 5 : varlist = d->gsmValueVariantList;break;
        default: break;
    }

    if(varlist.at(1).toString() == "NR") {
        TX_Start_Channel = varlist.at(14).toInt();
        RX_Start_Channel = varlist.at(15).toInt();

        if(sta) return (curruntchannel - TX_Start_Channel + RX_Start_Channel);
        else    return (curruntchannel - RX_Start_Channel + TX_Start_Channel);
    } else if (varlist.at(1).toString() == "LTE") {//LTE
        TX_Start_Channel = varlist.at(7).toInt();
        RX_Start_Channel = varlist.at(8).toInt();

        if(sta) return (curruntchannel - TX_Start_Channel + RX_Start_Channel);
        else    return (curruntchannel - RX_Start_Channel + TX_Start_Channel);
    }else { //WCDMA CDMA TDSCDMA GSM
        TX_Start_Channel = varlist.at(6).toInt();
        RX_Start_Channel = varlist.at(7).toInt();

        if(varlist.at(2).toString() == "CDMA BC0") {
            ratiocompensate = 1023;
            if(curruntchannel == 1024) {curruntchannel = 1; return curruntchannel;}
            if(curruntchannel == 0) {curruntchannel = 1023; return curruntchannel;}
        }

        if(varlist.at(2).toString() == "E-GSM 900") {
            ratiocompensate = 1024;
            if(curruntchannel == 1024) {curruntchannel = 0; return curruntchannel;}
            if(curruntchannel == -1) {curruntchannel = 1023; return curruntchannel;}
        }

        if(sta) return (curruntchannel < 1024 ? (curruntchannel - TX_Start_Channel + RX_Start_Channel) :
                       (curruntchannel - TX_Start_Channel + RX_Start_Channel - ratiocompensate));
        else    return (curruntchannel < 1024 ? (curruntchannel - RX_Start_Channel + TX_Start_Channel) :
                       (curruntchannel - RX_Start_Channel + TX_Start_Channel - ratiocompensate));
    }
}

bool MainWidgetUI::ChannelRange_Set(int curruntchannel, int *curruntchannelbackup, char sta)
{
    QVariantList varlist;

    char channelsta = 0;

    switch (ui->BandStackedWidget->currentIndex()) {
        case 0 : varlist = d->nrValueVariantList;break;
        case 1 : varlist = d->lteValueVariantList;break;
        case 2 : varlist = d->wcdmaValueVariantList;break;
        case 3 : varlist = d->cdmaValueVariantList;break;
        case 4 : varlist = d->tdscdmaValueVariantList;break;
        case 5 : varlist = d->gsmValueVariantList;break;
        default: break;
    }

    if(varlist.at(2).toString() == "E-GSM 900")
        channelsta = 1;
    else if (varlist.at(2).toString() == "CDMA BC0")
        channelsta = 2;
    else
        return 0;

    if(channelsta == 1) {
        if(curruntchannel > 124 && curruntchannel <975){
            if(sta) *curruntchannelbackup = 975;
            else *curruntchannelbackup = 124;
            return 1;
        }
    }else if(channelsta == 2) {
        if(curruntchannel > 799 && curruntchannel <991){
            if(sta) *curruntchannelbackup = 991;
            else *curruntchannelbackup = 799;
            return 1;
        }
    }
    return 0;
}

void MainWidgetUI::BandInformationInit_Show(QVariantList &bandinfo)
{
    disconnect(ui->TXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetRXStartChannelValue(int)));
    disconnect(ui->RXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetTXStartChannelValue(int)));
    disconnect(ui->TXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetRXStopChannelValue(int)));
    disconnect(ui->RXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetTXStopChannelValue(int)));

    Information_Show(bandinfo);
    NRBandChannelRaster_Show(bandinfo, bandinfo.at(10).toInt());
    NRSubcarrierSpacing_Show(bandinfo, bandinfo.at(8).toInt());
    BandWidth_Show(bandinfo, bandinfo.at(3).toInt());
    BER_Show(bandinfo, bandinfo.at(3).toInt());
    BERConfig_Show(bandinfo, bandinfo.at(3).toInt());
    ChannelTP_Show(bandinfo, bandinfo.at(3).toInt());
    TRXTP_Show(bandinfo);

    connect(ui->TXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetRXStartChannelValue(int)));
    connect(ui->RXStartChannelValue, SIGNAL(valueChanged(int)), this, SLOT(SetTXStartChannelValue(int)));
    connect(ui->TXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetRXStopChannelValue(int)));
    connect(ui->RXStopChannelValue,  SIGNAL(valueChanged(int)), this, SLOT(SetTXStopChannelValue(int)));
}

void MainWidgetUI::Information_Show(QVariantList &bandinfo)
{
    if(bandinfo.at(1).toString() == "NR") {
        ui->Information_Name_Value->setText(bandinfo.at(22).toString());
        ui->Information_Area_Value->setText(bandinfo.at(23).toString());
    } else if(bandinfo.at(1).toString() == "LTE") {
        ui->Information_Name_Value->setText(bandinfo.at(12).toString());
        ui->Information_Area_Value->setText(bandinfo.at(13).toString());
    } else {
        ui->Information_Name_Value->setText(bandinfo.at(10).toString());
        ui->Information_Area_Value->setText(bandinfo.at(11).toString());
    }
}

void MainWidgetUI::NRBandChannelRaster_Show(QVariantList &bandinfo, int bandchannelrasterid)
{
    if(bandinfo.at(1).toString() == "NR") {
        QList<int> bandchannelrasterstr;
        QString BandChannelRaster = bandinfo.at(11).toString();
        d->curruntBandChannelRasterid = bandchannelrasterid;

        for(int i = 0; i < 5; i++) {
            bandchannelrasterstr << BandChannelRaster.section(",", i, i, QString::SectionDefault).toInt();
            switch (i) {
                case 0 : bandchannelrasterstr.at(i)?ui->NR15KHzChannelRaster->setEnabled(true) :ui->NR15KHzChannelRaster->setEnabled(false);break;
                case 1 : bandchannelrasterstr.at(i)?ui->NR30KHzChannelRaster->setEnabled(true) :ui->NR30KHzChannelRaster->setEnabled(false);break;
                case 2 : bandchannelrasterstr.at(i)?ui->NR60KHzChannelRaster->setEnabled(true) :ui->NR60KHzChannelRaster->setEnabled(false);break;
                case 3 : bandchannelrasterstr.at(i)?ui->NR100KHzChannelRaster->setEnabled(true):ui->NR100KHzChannelRaster->setEnabled(false);break;
                case 4 : bandchannelrasterstr.at(i)?ui->NR120KHzChannelRaster->setEnabled(true):ui->NR120KHzChannelRaster->setEnabled(false);break;
                default : break;
            }
        }
        switch (bandchannelrasterid) {
            case 0 : ui->NR15KHzChannelRaster->setChecked(true);break;
            case 1 : ui->NR30KHzChannelRaster->setChecked(true);break;
            case 2 : ui->NR60KHzChannelRaster->setChecked(true);break;
            case 3 : ui->NR100KHzChannelRaster->setChecked(true);break;
            case 4 : ui->NR120KHzChannelRaster->setChecked(true);break;
            default : break;
        }
    } else if(bandinfo.at(1).toString() == "LTE" || bandinfo.at(1).toString() == "WCDMA") {
        ui->NR15KHzChannelRaster->setEnabled(false);
        ui->NR30KHzChannelRaster->setEnabled(false);
        ui->NR60KHzChannelRaster->setEnabled(false);
        ui->NR100KHzChannelRaster->setEnabled(true);
        ui->NR100KHzChannelRaster->setChecked(true);
        ui->NR120KHzChannelRaster->setEnabled(false);
    } else {
        ui->NR15KHzChannelRaster->setEnabled(false);
        ui->NR30KHzChannelRaster->setEnabled(false);
        ui->NR60KHzChannelRaster->setEnabled(false);
        ui->NR100KHzChannelRaster->setEnabled(false);
        ui->NR100KHzChannelRaster->setChecked(true);
        ui->NR120KHzChannelRaster->setEnabled(false);
    }
}

void MainWidgetUI::NRSubcarrierSpacing_Show(QVariantList &bandinfo, int subcarrierspacingid)
{
    if(bandinfo.at(1).toString() == "NR") {
        QList<int> SubcarrierSpacingstr;
        QString SubcarrierSpacing = bandinfo.at(9).toString();
        d->curruntSubcarrierSpacingid = subcarrierspacingid;

        for(int i = 0; i < 4; i++) {
            SubcarrierSpacingstr << SubcarrierSpacing.section(",", i, i, QString::SectionDefault).toInt();
            switch (i) {
                case 0 : SubcarrierSpacingstr.at(i)?ui->NR15KHzSpacing->setEnabled(true) :ui->NR15KHzSpacing->setEnabled(false);break;
                case 1 : SubcarrierSpacingstr.at(i)?ui->NR30KHzSpacing->setEnabled(true) :ui->NR30KHzSpacing->setEnabled(false);break;
                case 2 : SubcarrierSpacingstr.at(i)?ui->NR60KHzSpacing->setEnabled(true) :ui->NR60KHzSpacing->setEnabled(false);break;
                case 3 : SubcarrierSpacingstr.at(i)?ui->NR120KHzSpacing->setEnabled(true):ui->NR120KHzSpacing->setEnabled(false);break;
                default : break;
            }
        }
        switch (subcarrierspacingid) {
            case 0 : ui->NR15KHzSpacing->setChecked(true);break;
            case 1 : ui->NR30KHzSpacing->setChecked(true);break;
            case 2 : ui->NR60KHzSpacing->setChecked(true);break;
            case 3 : ui->NR120KHzSpacing->setChecked(true);break;
            default : break;
        }
    } else if(bandinfo.at(1).toString() == "LTE") {
        ui->NR15KHzSpacing->setEnabled(true);
        ui->NR15KHzSpacing->setChecked(true);
        ui->NR30KHzSpacing->setEnabled(false);
        ui->NR60KHzSpacing->setEnabled(false);
        ui->NR120KHzSpacing->setEnabled(false);
    } else {
        ui->NR15KHzSpacing->setEnabled(false);
        ui->NR15KHzSpacing->setChecked(true);
        ui->NR30KHzSpacing->setEnabled(false);
        ui->NR60KHzSpacing->setEnabled(false);
        ui->NR120KHzSpacing->setEnabled(false);
    }
}

void MainWidgetUI::BandWidth_Show(QVariantList &bandinfo, int signalbwid)
{
    if(bandinfo.at(1).toString() == "NR") {
        QList<int> BWInformationstr;
        QString BandWidth = bandinfo.at(4 + d->curruntSubcarrierSpacingid).toString();
        d->curruntBandWidthid = signalbwid;

        for(int i = 0; i < 14; i++) {
            BWInformationstr << BandWidth.section(",", i, i, QString::SectionDefault).toInt();
            switch (i) {
                case 0  : BWInformationstr.at(i)?ui->NR_5MHz->setEnabled(true) :ui->NR_5MHz->setEnabled(false);break;
                case 1  : BWInformationstr.at(i)?ui->NR_10MHz->setEnabled(true):ui->NR_10MHz->setEnabled(false);break;
                case 2  : BWInformationstr.at(i)?ui->NR_15MHz->setEnabled(true):ui->NR_15MHz->setEnabled(false);break;
                case 3  : BWInformationstr.at(i)?ui->NR_20MHz->setEnabled(true):ui->NR_20MHz->setEnabled(false);break;
                case 4  : BWInformationstr.at(i)?ui->NR_25MHz->setEnabled(true):ui->NR_25MHz->setEnabled(false);break;
                case 5  : BWInformationstr.at(i)?ui->NR_30MHz->setEnabled(true):ui->NR_30MHz->setEnabled(false);break;
                case 6  : BWInformationstr.at(i)?ui->NR_40MHz->setEnabled(true):ui->NR_40MHz->setEnabled(false);break;
                case 7  : BWInformationstr.at(i)?ui->NR_50MHz->setEnabled(true):ui->NR_50MHz->setEnabled(false);break;
                case 8  : BWInformationstr.at(i)?ui->NR_60MHz->setEnabled(true):ui->NR_60MHz->setEnabled(false);break;
                case 9  : BWInformationstr.at(i)?ui->NR_80MHz->setEnabled(true):ui->NR_80MHz->setEnabled(false);break;
                case 10 : BWInformationstr.at(i)?ui->NR_90MHz->setEnabled(true):ui->NR_90MHz->setEnabled(false);break;
                case 11 : BWInformationstr.at(i)?ui->NR_100MHz->setEnabled(true):ui->NR_100MHz->setEnabled(false);break;
                case 12 : BWInformationstr.at(i)?ui->NR_200MHz->setEnabled(true):ui->NR_200MHz->setEnabled(false);break;
                case 13 : BWInformationstr.at(i)?ui->NR_400MHz->setEnabled(true):ui->NR_400MHz->setEnabled(false);break;
                default : break;
            }
        }

        switch (signalbwid) {
            case 0  : ui->NR_5MHz->setChecked(true);break;
            case 1  : ui->NR_10MHz->setChecked(true);break;
            case 2  : ui->NR_15MHz->setChecked(true);break;
            case 3  : ui->NR_20MHz->setChecked(true);break;
            case 4  : ui->NR_25MHz->setChecked(true);break;
            case 5  : ui->NR_30MHz->setChecked(true);break;
            case 6  : ui->NR_40MHz->setChecked(true);break;
            case 7  : ui->NR_50MHz->setChecked(true);break;
            case 8  : ui->NR_60MHz->setChecked(true);break;
            case 9  : ui->NR_80MHz->setChecked(true);break;
            case 10 : ui->NR_90MHz->setChecked(true);break;
            case 11 : ui->NR_100MHz->setChecked(true);break;
            case 12 : ui->NR_200MHz->setChecked(true);break;
            case 13 : ui->NR_400MHz->setChecked(true);break;
            default : break;
        }
    } else if(bandinfo.at(1).toString() == "LTE") {
        QList<int> BWInformationstr;
        QString BandWidth = bandinfo.at(4).toString();

        for(int i = 0; i < 6; i++) {
            BWInformationstr << BandWidth.section(",", i, i, QString::SectionDefault).toInt();
            switch (i) {
                case 0 : BWInformationstr.at(i) ? ui->LTE_1_4MHz->setEnabled(true) : ui->LTE_1_4MHz->setEnabled(false);break;
                case 1 : BWInformationstr.at(i) ? ui->LTE_3MHz->setEnabled(true)   : ui->LTE_3MHz->setEnabled(false);break;
                case 2 : BWInformationstr.at(i) ? ui->LTE_5MHz->setEnabled(true)   : ui->LTE_5MHz->setEnabled(false);break;
                case 3 : BWInformationstr.at(i) ? ui->LTE_10MHz->setEnabled(true)  : ui->LTE_10MHz->setEnabled(false);break;
                case 4 : BWInformationstr.at(i) ? ui->LTE_15MHz->setEnabled(true)  : ui->LTE_15MHz->setEnabled(false);break;
                case 5 : BWInformationstr.at(i) ? ui->LTE_20MHz->setEnabled(true)  : ui->LTE_20MHz->setEnabled(false);break;
                default : break;
            }
        }

        switch (signalbwid) {
            case 0 : ui->LTE_1_4MHz->setChecked(true);break;
            case 1 : ui->LTE_3MHz->setChecked(true);break;
            case 2 : ui->LTE_5MHz->setChecked(true);break;
            case 3 : ui->LTE_10MHz->setChecked(true);break;
            case 4 : ui->LTE_15MHz->setChecked(true);break;
            case 5 : ui->LTE_20MHz->setChecked(true);break;
            default : break;
        }
    } else if(bandinfo.at(1).toString() == "WCDMA") {
        ui->LTE_1_4MHz->setEnabled(false);
        ui->LTE_3MHz->setEnabled(false);

        ui->LTE_5MHz->setEnabled(true);
        ui->LTE_5MHz->setChecked(true);

        ui->LTE_10MHz->setEnabled(false);
        ui->LTE_15MHz->setEnabled(false);
        ui->LTE_20MHz->setEnabled(false);
    } else {
        ui->LTE_1_4MHz->setEnabled(false);
        ui->LTE_3MHz->setEnabled(false);

        ui->LTE_5MHz->setEnabled(false);
        ui->LTE_5MHz->setChecked(true);

        ui->LTE_10MHz->setEnabled(false);
        ui->LTE_15MHz->setEnabled(false);
        ui->LTE_20MHz->setEnabled(false);
    }
}

void MainWidgetUI::BER_Show(QVariantList &bandinfo, int signalbwid)
{
    double Signal_BER = 0.0;
    char BER_Status = 0;

    if(bandinfo.at(1).toString() == "NR") {
        switch (signalbwid) {
            case 0  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【5MHz】"));break;
            case 1  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【10MHz】"));break;
            case 2  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【15MHz】"));break;
            case 3  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【20MHz】"));break;
            case 4  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【25MHz】"));break;
            case 5  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【30MHz】"));break;
            case 6  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【40MHz】"));break;
            case 7  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【50MHz】"));break;
            case 8  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【60MHz】"));break;
            case 9  : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【80MHz】"));break;
            case 10 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【90MHz】"));break;
            case 11 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【100MHz】"));break;
            case 12 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【200MHz】"));break;
            case 13 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【400MHz】"));break;
            default : break;
        }

        Signal_BER = bandinfo.at(17).toDouble();
        if(Signal_BER == 0.0) BER_Status = 1;

        if(d->curruntSubcarrierSpacingid == 0) {//15KHz
            switch (signalbwid) {
                case 0  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER-3.2,'f', 1)));break;//5MHz
                case 1  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER,'f', 1)));break;//10MHz
                case 2  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+1.8,'f', 1)));break;//15MHz
                case 3  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+3.0,'f', 1)));break;//20MHz
                case 4  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+4.1,'f', 1)));break;//25MHz
                case 5  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+4.9,'f', 1)));break;//30MHz
                case 6  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+6.2,'f', 1)));break;//40MHz
                case 7  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+7.2,'f', 1)));break;//50MHz
                default : break;
            }
        } else if (d->curruntSubcarrierSpacingid == 1) {//30KHz
            switch (signalbwid) {
                case 1  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER-0.3,'f', 1)));break;//10MHz
                case 2  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+1.8-0.1,'f', 1)));break;//15MHz
                case 3  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+3.0-0.2,'f', 1)));break;//20MHz
                case 4  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+4.1-0.1,'f', 1)));break;//25MHz
                case 5  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+4.9-0.1,'f', 1)));break;//30MHz
                case 6  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+6.2-0.1,'f', 1)));break;//40MHz
                case 7  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+7.2-0.1,'f', 1)));break;//50MHz
                case 8  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+7.9,'f', 1)));break;//60MHz
                case 9  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+9.2,'f', 1)));break;//80MHz
                case 10 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+9.7,'f', 1)));break;//90MHz
                case 11 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+10.1,'f', 1)));break;//100MHz
                default : break;
            }
        } else if (d->curruntSubcarrierSpacingid == 2) {//60KHz
            switch (signalbwid) {
                case 1  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER-0.7,'f', 1)));break;//10MHz
                case 2  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+1.8-0.4,'f', 1)));break;//15MHz
                case 3  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+3.0-0.4,'f', 1)));break;//20MHz
                case 4  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+4.1-0.3,'f', 1)));break;//25MHz
                case 5  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+4.9-0.2,'f', 1)));break;//30MHz
                case 6  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+6.2-0.3,'f', 1)));break;//40MHz
                case 7  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+7.2-0.2,'f', 1)));break;//50MHz
                case 8  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+7.9-0.2,'f', 1)));break;//60MHz
                case 9  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+9.2,'f', 1)));break;//80MHz
                case 10 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+9.7,'f', 1)));break;//90MHz
                case 11 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+10.1,'f', 1)));break;//100MHz
                case 12 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+13.1,'f', 1)));break;//200MHz
                default : break;
            }
        } else if (d->curruntSubcarrierSpacingid == 3) {//120KHz
            switch (signalbwid) {
                case 7  : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+7.0,'f', 1)));break;//50MHz
                case 11 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+10.1,'f', 1)));break;//100MHz
                case 12 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+13.1,'f', 1)));break;//200MHz
                case 13 : ui->BerValue->setText((BER_Status?tr("0.0"):QString::number(Signal_BER+16.1,'f', 1)));break;//400MHz
                default : break;
            }
        }
    } else if(bandinfo.at(1).toString() == "LTE") {
        switch (signalbwid) {
            case 0 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【1.4MHz】"));break;
            case 1 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【3MHz】"));break;
            case 2 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【5MHz】"));break;
            case 3 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【10MHz】"));break;
            case 4 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【15MHz】"));break;
            case 5 : ui->BERGB->setTitle(QStringLiteral("灵敏度门限【20MHz】"));break;
            default : break;
        }

        Signal_BER = bandinfo.at(10).toDouble();
        if(Signal_BER == 0.0) BER_Status = 1;

        switch (signalbwid) {
            case 0 : ui->BerValue->setText((BER_Status ? tr("0.0") : QString::number(Signal_BER-7.7,'f', 1)));break;
            case 1 : ui->BerValue->setText((BER_Status ? tr("0.0") : QString::number(Signal_BER-4.7,'f', 1)));break;
            case 2 : ui->BerValue->setText((BER_Status ? tr("0.0") : QString::number(Signal_BER-3.0,'f', 1)));break;
            case 3 : ui->BerValue->setText((BER_Status ? tr("0.0") : QString::number(Signal_BER,'f', 1)));break;
            case 4 : ui->BerValue->setText((BER_Status ? tr("0.0") : QString::number(Signal_BER+1.8,'f', 1)));break;
            case 5 : ui->BerValue->setText((BER_Status ? tr("0.0") : QString::number(Signal_BER+3.0,'f', 1)));break;
            default : break;
        }
    } else if(bandinfo.at(1).toString() == "WCDMA") {
        ui->BERGB->setTitle(QStringLiteral("灵敏度门限【5MHz】"));
        ui->BerValue->setText(bandinfo.at(9).toString());
    } else {
        ui->BERGB->setTitle(QStringLiteral("灵敏度门限"));
        ui->BerValue->setText(bandinfo.at(9).toString());
    }
}

void MainWidgetUI::BERConfig_Show(QVariantList &bandinfo, int signalbwid)
{
    QString BER_Config;
    QString BER_Config_Value;

    if(bandinfo.at(1).toString() == "NR") {
        BER_Config = bandinfo.at(18 + d->curruntSubcarrierSpacingid).toString();
        switch (signalbwid) {
            case 0  : BER_Config_Value = BER_Config.section(",",  0,  0, QString::SectionDefault);break;
            case 1  : BER_Config_Value = BER_Config.section(",",  1,  1, QString::SectionDefault);break;
            case 2  : BER_Config_Value = BER_Config.section(",",  2,  2, QString::SectionDefault);break;
            case 3  : BER_Config_Value = BER_Config.section(",",  3,  3, QString::SectionDefault);break;
            case 4  : BER_Config_Value = BER_Config.section(",",  4,  4, QString::SectionDefault);break;
            case 5  : BER_Config_Value = BER_Config.section(",",  5,  5, QString::SectionDefault);break;
            case 6  : BER_Config_Value = BER_Config.section(",",  6,  6, QString::SectionDefault);break;
            case 7  : BER_Config_Value = BER_Config.section(",",  7,  7, QString::SectionDefault);break;
            case 8  : BER_Config_Value = BER_Config.section(",",  8,  8, QString::SectionDefault);break;
            case 9  : BER_Config_Value = BER_Config.section(",",  9,  9, QString::SectionDefault);break;
            case 10 : BER_Config_Value = BER_Config.section(",", 10, 10, QString::SectionDefault);break;
            case 11 : BER_Config_Value = BER_Config.section(",", 11, 11, QString::SectionDefault);break;
            case 12 : BER_Config_Value = BER_Config.section(",", 12, 12, QString::SectionDefault);break;
            case 13 : BER_Config_Value = BER_Config.section(",", 13, 13, QString::SectionDefault);break;
            default : break;
        }

        ui->RBValue->setText(BER_Config_Value);
        ui->RBValue->setProperty("ColorStatus",
                                (BER_Config_Value == "Full" || BER_Config_Value == "-") ? "true" : "false");
    } else if(bandinfo.at(1).toString() == "LTE") {
        BER_Config = bandinfo.at(11).toString();
        switch (signalbwid) {
            case 0 : BER_Config_Value = BER_Config.section(",", 0, 0, QString::SectionDefault);break;
            case 1 : BER_Config_Value = BER_Config.section(",", 1, 1, QString::SectionDefault);break;
            case 2 : BER_Config_Value = BER_Config.section(",", 2, 2, QString::SectionDefault);break;
            case 3 : BER_Config_Value = BER_Config.section(",", 3, 3, QString::SectionDefault);break;
            case 4 : BER_Config_Value = BER_Config.section(",", 4, 4, QString::SectionDefault);break;
            case 5 : BER_Config_Value = BER_Config.section(",", 5, 5, QString::SectionDefault);break;
            default : break;
        }

        ui->RBValue->setText(BER_Config_Value);
        ui->RBValue->setProperty("ColorStatus",
                                (BER_Config_Value == "Full" || BER_Config_Value == "-") ? "true" : "false");
    } else {
        ui->RBValue->setText("-");
        ui->RBValue->setProperty("ColorStatus", "true");
    }

    ui->RBValue->style()->unpolish(ui->RBValue);
    ui->RBValue->style()->polish(ui->RBValue);
    ui->RBValue->update();
}

void MainWidgetUI::ChannelTP_Show(QVariantList &bandinfo, int signalbwid)
{
    bool txchanneltestplantemp = 0, rxchanneltestplantemp = 0;
    int TX_Start_Channel = 0, RX_Start_Channel = 0;
    double freqbw = 0.0;

    if(bandinfo.at(1).toString() == "NR") {
        switch (signalbwid) {
            case 0  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【5MHz】"));break;
            case 1  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【10MHz】"));break;
            case 2  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【15MHz】"));break;
            case 3  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【20MHz】"));break;
            case 4  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【25MHz】"));break;
            case 5  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【30MHz】"));break;
            case 6  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【40MHz】"));break;
            case 7  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【50MHz】"));break;
            case 8  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【60MHz】"));break;
            case 9  : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【80MHz】"));break;
            case 10 : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【90MHz】"));break;
            case 11 : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【100MHz】"));break;
            case 12 : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【200MHz】"));break;
            case 13 : ui->TestChannelGB->setTitle(QStringLiteral("测试信道【400MHz】"));break;
            default : break;
        }

        double BWTemp = 0;
        switch (signalbwid) {
            case 0  : BWTemp = 500.0; break;//5M
            case 1  : BWTemp = 1000.0;break;//10M
            case 2  : BWTemp = 1500.0;break;//15M
            case 3  : BWTemp = 2000.0;break;//20M
            case 4  : BWTemp = 2500.0;break;//25M
            case 5  : BWTemp = 3000.0;break;//30M
            case 6  : BWTemp = 4000.0;break;//40M
            case 7  : BWTemp = 5000.0;break;//50M
            case 8  : BWTemp = 6000.0;break;//60M
            case 9  : BWTemp = 8000.0;break;//80M
            case 10 : BWTemp = 9000.0;break;//90M
            case 11 : BWTemp = 10000.0;break;//100M
            case 12 : BWTemp = 20000.0;break;//200M
            case 13 : BWTemp = 40000.0;break;//400M
            default : break;
        }

        double bandrastervalue = 1.0;
        int bandchannnelcompensate = 0;
        if (d->curruntBandChannelRasterid == 4) {//120KHz
            if(bandinfo.at(2).toString() == "NR B257" || bandinfo.at(2).toString() == "NR B260")
                bandchannnelcompensate = 1;
            else
                bandchannnelcompensate = 0;
        }

        freqbw = bandinfo.at(16).toDouble();

        if(bandinfo.at(12).toDouble() == 0.0) txchanneltestplantemp = 1;
        else {TX_Start_Channel = bandinfo.at(14).toInt();txchanneltestplantemp = 0;}
        if(bandinfo.at(12).toDouble() >= 24250.0) bandrastervalue = 12.0;
        else if(bandinfo.at(12).toDouble() >= 3000.0) bandrastervalue = 3.0;
        else bandrastervalue = 1.0;

        ui->TXStartChannel->setText((txchanneltestplantemp?tr("-"):QString::number(TX_Start_Channel+static_cast<int>(BWTemp/bandrastervalue)+bandchannnelcompensate)));
        ui->TXMidChannel->setText((txchanneltestplantemp?tr("-"):QString::number(TX_Start_Channel+static_cast<int>(freqbw*100.0/bandrastervalue)+bandchannnelcompensate)));
        ui->TXEndChannel->setText((txchanneltestplantemp?tr("-"):QString::number(TX_Start_Channel+static_cast<int>((freqbw*200.0-BWTemp)/bandrastervalue)+bandchannnelcompensate)));

        if(bandinfo.at(13).toDouble() == 0.0) rxchanneltestplantemp = 1;
        else {RX_Start_Channel = bandinfo.at(15).toInt();rxchanneltestplantemp = 0;}
        if(bandinfo.at(13).toDouble() >= 24250.0) bandrastervalue = 12.0;
        else if(bandinfo.at(13).toDouble() >= 3000.0) bandrastervalue = 3.0;
        else bandrastervalue = 1.0;

        ui->RXStartChannel->setText((rxchanneltestplantemp?tr("-"):QString::number(RX_Start_Channel+static_cast<int>(BWTemp/bandrastervalue)+bandchannnelcompensate)));
        ui->RXMidChannel->setText((rxchanneltestplantemp?tr("-"):QString::number(RX_Start_Channel+static_cast<int>(freqbw*100.0/bandrastervalue)+bandchannnelcompensate)));
        ui->RXEndChannel->setText((rxchanneltestplantemp?tr("-"):QString::number(RX_Start_Channel+static_cast<int>((freqbw*200.0-BWTemp)/bandrastervalue)+bandchannnelcompensate)));
    } else if(bandinfo.at(1).toString() == "LTE") {
        int BWTemp = 0;
        switch (signalbwid) {
            case 0 : BWTemp = 7;   ui->TestChannelGB->setTitle(QStringLiteral("测试信道【1.4MHz】"));break;
            case 1 : BWTemp = 15;  ui->TestChannelGB->setTitle(QStringLiteral("测试信道【3MHz】"));break;
            case 2 : BWTemp = 25;  ui->TestChannelGB->setTitle(QStringLiteral("测试信道【5MHz】"));break;
            case 3 : BWTemp = 50;  ui->TestChannelGB->setTitle(QStringLiteral("测试信道【10MHz】"));break;
            case 4 : BWTemp = 75;  ui->TestChannelGB->setTitle(QStringLiteral("测试信道【15MHz】"));break;
            case 5 : BWTemp = 100; ui->TestChannelGB->setTitle(QStringLiteral("测试信道【20MHz】"));break;
            default : break;
        }

        freqbw = bandinfo.at(9).toDouble();

        if(bandinfo.at(5).toDouble() == 0.0) txchanneltestplantemp = 1;
        else {TX_Start_Channel = bandinfo.at(7).toInt();txchanneltestplantemp = 0;}

        ui->TXStartChannel->setText((txchanneltestplantemp?tr("-"):QString::number(TX_Start_Channel+BWTemp)));
        ui->TXMidChannel->setText((txchanneltestplantemp?tr("-"):QString::number(TX_Start_Channel+static_cast<int>(freqbw*5.0+0.5))));
        ui->TXEndChannel->setText((txchanneltestplantemp?tr("-"):QString::number(TX_Start_Channel+static_cast<int>(freqbw*10.0+0.5)-BWTemp)));

        if(bandinfo.at(6).toDouble() == 0.0) rxchanneltestplantemp = 1;
        else {RX_Start_Channel = bandinfo.at(8).toInt();rxchanneltestplantemp = 0;}

        ui->RXStartChannel->setText((rxchanneltestplantemp?tr("-"):QString::number(RX_Start_Channel+BWTemp)));
        ui->RXMidChannel->setText((rxchanneltestplantemp?tr("-"):QString::number(RX_Start_Channel+static_cast<int>(freqbw*5.0+0.5))));
        ui->RXEndChannel->setText((rxchanneltestplantemp?tr("-"):QString::number(RX_Start_Channel+static_cast<int>(freqbw*10.0+0.5)-BWTemp)));
    } else if(bandinfo.at(1).toString() == "WCDMA" || bandinfo.at(1).toString() == "TDSCDMA") {
        if(bandinfo.at(1).toString() == "WCDMA")
            ui->TestChannelGB->setTitle(QStringLiteral("测试信道【5MHz】"));
        else
            ui->TestChannelGB->setTitle(QStringLiteral("测试信道"));

        freqbw = bandinfo.at(8).toDouble();

        TX_Start_Channel = bandinfo.at(6).toInt();
        RX_Start_Channel = bandinfo.at(7).toInt();

        ui->TXStartChannel->setText(QString::number(TX_Start_Channel));
        ui->TXMidChannel->setText(QString::number(TX_Start_Channel+static_cast<int>(freqbw*2.5+0.5)));
        ui->TXEndChannel->setText(QString::number(TX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)));
        ui->RXStartChannel->setText(QString::number(RX_Start_Channel));
        ui->RXMidChannel->setText(QString::number(RX_Start_Channel+static_cast<int>(freqbw*2.5+0.5)));
        ui->RXEndChannel->setText(QString::number(RX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)));
    } else if(bandinfo.at(1).toString() == "CDMA") {
        ui->TestChannelGB->setTitle(QStringLiteral("测试信道"));
        TX_Start_Channel = bandinfo.at(6).toInt();
        RX_Start_Channel = bandinfo.at(7).toInt();
        freqbw = bandinfo.at(8).toDouble();

        double bandradio = 0;

        if (bandinfo.at(2).toString() == "CDMA BC10"){
            freqbw = 22.975;bandradio = 0.025;
        } else bandradio = 0.05;

        if (bandinfo.at(2).toString() == "CDMA BC0") {
            ui->TXStartChannel->setText("1013");
            ui->TXMidChannel->setText("384");
            ui->TXEndChannel->setText("777");
            ui->RXStartChannel->setText("1013");
            ui->RXMidChannel->setText("384");
            ui->RXEndChannel->setText("777");
        } else {
            ui->TXStartChannel->setText(QString::number(TX_Start_Channel));
            ui->TXMidChannel->setText(QString::number(TX_Start_Channel + static_cast<int>(freqbw/bandradio/2.0+0.5)));
            ui->TXEndChannel->setText(QString::number(TX_Start_Channel + static_cast<int>(freqbw/bandradio+0.5)));
            ui->RXStartChannel->setText(QString::number(RX_Start_Channel));
            ui->RXMidChannel->setText(QString::number(RX_Start_Channel + static_cast<int>(freqbw/bandradio/2.0+0.5)));
            ui->RXEndChannel->setText(QString::number(RX_Start_Channel + static_cast<int>(freqbw/bandradio+0.5)));
        }
    } else if(bandinfo.at(1).toString() == "GSM") {
        ui->TestChannelGB->setTitle(QStringLiteral("测试信道"));
        TX_Start_Channel = bandinfo.at(6).toInt();
        RX_Start_Channel = bandinfo.at(7).toInt();
        freqbw = bandinfo.at(8).toDouble();

        int gsmbwtempa = 0;

        if(bandinfo.at(2).toString() == "E-GSM 900") gsmbwtempa = 1024;
        else gsmbwtempa = 0;

        ui->TXStartChannel->setText(QString::number(TX_Start_Channel));
        ui->TXMidChannel->setText(QString::number(TX_Start_Channel + static_cast<int>(freqbw*2.5+0.5) - gsmbwtempa));
        ui->TXEndChannel->setText(QString::number(TX_Start_Channel + static_cast<int>(freqbw*5.0+0.5) - gsmbwtempa));
        ui->RXStartChannel->setText(QString::number(RX_Start_Channel));
        ui->RXMidChannel->setText(QString::number(RX_Start_Channel + static_cast<int>(freqbw*2.5+0.5) - gsmbwtempa));
        ui->RXEndChannel->setText(QString::number(RX_Start_Channel + static_cast<int>(freqbw*5.0+0.5) - gsmbwtempa));
    }
}

void MainWidgetUI::TRXTP_Show(QVariantList &bandinfo)
{
    bool txchanneltestplantemp = 0, rxchanneltestplantemp = 0;
    double TX_Start_Frequency = 0.0, RX_Start_Frequency = 0.0;
    int TX_Start_Channel = 0, RX_Start_Channel = 0;
    double freqbw = 0.0;
    double channelratio = 0.0;
    double bandrastervalue = 0.0;

    if(bandinfo.at(1).toString() == "NR") {
        TX_Start_Frequency = bandinfo.at(12).toDouble();
        RX_Start_Frequency = bandinfo.at(13).toDouble();
        TX_Start_Channel = bandinfo.at(14).toInt();
        RX_Start_Channel = bandinfo.at(15).toInt();
        freqbw = bandinfo.at(16).toDouble();

        if(TX_Start_Frequency == 0.0) txchanneltestplantemp = 1;
        else txchanneltestplantemp = 0;

        if(TX_Start_Frequency >= 24250.0) bandrastervalue = 12.0;
        else if(TX_Start_Frequency >= 3000.0) bandrastervalue = 3.0;
        else bandrastervalue = 1.0;

        ui->TXStartFreqValue->setText(QString::number(TX_Start_Frequency,'f', 3));
        ui->TXStopFreqValue->setText((txchanneltestplantemp?tr("0.0"):QString::number(TX_Start_Frequency+freqbw-0.1,'f', 3)));

        ui->TXStartChannelValue->setRange(txchanneltestplantemp ? 0 : TX_Start_Channel,
                                          txchanneltestplantemp ? 0 : (TX_Start_Channel + static_cast<int>(freqbw*200.0/bandrastervalue)-1));
        ui->TXStartChannelValue->setSingleStep(1);
        ui->TXStartChannelValue->setValue(txchanneltestplantemp ? 0 : TX_Start_Channel);
        \
        //qDebug("TXStartChannelValue:%d",ui->TXStartChannelValue->value());

        ui->TXStopChannelValue->setRange(txchanneltestplantemp  ? 0 : TX_Start_Channel,
                                         txchanneltestplantemp  ? 0 : (TX_Start_Channel + static_cast<int>(freqbw*200.0/bandrastervalue)-1));
        ui->TXStopChannelValue->setSingleStep(1);
        ui->TXStopChannelValue->setValue(txchanneltestplantemp  ? 0 : TX_Start_Channel  + static_cast<int>(freqbw*200.0/bandrastervalue)-1);

        //qDebug("TXStopChannelValue:%d",ui->TXStopChannelValue->value());

        if(RX_Start_Frequency == 0.0) rxchanneltestplantemp = 1;
        else rxchanneltestplantemp = 0;

        if(RX_Start_Frequency >= 24250.0) bandrastervalue = 12.0;
        else if(RX_Start_Frequency >= 3000.0) bandrastervalue = 3.0;
        else bandrastervalue = 1.0;

        ui->RXStartFreqValue->setText(QString::number(RX_Start_Frequency,'f', 3));
        ui->RXStopFreqValue->setText((rxchanneltestplantemp?tr("0.0"):QString::number(RX_Start_Frequency+freqbw-0.1,'f', 3)));

        ui->RXStartChannelValue->setRange(rxchanneltestplantemp ? 0 : RX_Start_Channel,
                                          rxchanneltestplantemp ? 0 : (RX_Start_Channel + static_cast<int>(freqbw*200.0/bandrastervalue)-1));
        ui->RXStartChannelValue->setSingleStep(1);
        ui->RXStartChannelValue->setValue(rxchanneltestplantemp ? 0 : RX_Start_Channel);

        ui->RXStopChannelValue->setRange(rxchanneltestplantemp  ? 0 : RX_Start_Channel,
                                         rxchanneltestplantemp  ? 0 : (RX_Start_Channel + static_cast<int>(freqbw*200.0/bandrastervalue)-1));
        ui->RXStopChannelValue->setSingleStep(1);
        ui->RXStopChannelValue->setValue(rxchanneltestplantemp  ? 0 : RX_Start_Channel  + static_cast<int>(freqbw*200.0/bandrastervalue)-1);
    } else if(bandinfo.at(1).toString() == "LTE") {
        TX_Start_Frequency = bandinfo.at(5).toDouble();
        RX_Start_Frequency = bandinfo.at(6).toDouble();
        TX_Start_Channel = bandinfo.at(7).toInt();
        RX_Start_Channel = bandinfo.at(8).toInt();
        freqbw = bandinfo.at(9).toDouble();

        if(TX_Start_Frequency == 0.0) txchanneltestplantemp = 1;
        else txchanneltestplantemp = 0;
        ui->TXStartFreqValue->setText(QString::number(TX_Start_Frequency,'f', 1));
        ui->TXStopFreqValue->setText((txchanneltestplantemp?tr("0.0"):QString::number(TX_Start_Frequency+freqbw-0.1,'f', 1)));
        ui->TXStartChannelValue->setRange(txchanneltestplantemp ? 0 : TX_Start_Channel,
                                          txchanneltestplantemp ? 0 : (TX_Start_Channel + static_cast<int>(freqbw*10.0+0.5) - 1));
        ui->TXStartChannelValue->setSingleStep(1);
        ui->TXStartChannelValue->setValue(txchanneltestplantemp ? 0 : TX_Start_Channel);
        ui->TXStopChannelValue->setRange(txchanneltestplantemp  ? 0 : TX_Start_Channel,
                                         txchanneltestplantemp  ? 0 : (TX_Start_Channel + static_cast<int>(freqbw*10.0+0.5) - 1));
        ui->TXStopChannelValue->setSingleStep(1);
        ui->TXStopChannelValue->setValue(txchanneltestplantemp  ? 0 : TX_Start_Channel  + static_cast<int>(freqbw*10.0+0.5) - 1);

        if(RX_Start_Frequency == 0.0) rxchanneltestplantemp = 1;
        else rxchanneltestplantemp = 0;
        ui->RXStartFreqValue->setText(QString::number(RX_Start_Frequency,'f', 1));
        ui->RXStopFreqValue->setText((rxchanneltestplantemp?tr("0.0"):QString::number(RX_Start_Frequency+freqbw-0.1,'f', 1)));
        ui->RXStartChannelValue->setRange(rxchanneltestplantemp ? 0 : RX_Start_Channel,
                                          rxchanneltestplantemp ? 0 : (RX_Start_Channel + static_cast<int>(freqbw*10.0+0.5) - 1));
        ui->RXStartChannelValue->setSingleStep(1);
        ui->RXStartChannelValue->setValue(rxchanneltestplantemp ? 0 : RX_Start_Channel);
        ui->RXStopChannelValue->setRange(rxchanneltestplantemp  ? 0 : RX_Start_Channel,
                                         rxchanneltestplantemp  ? 0 : (RX_Start_Channel + static_cast<int>(freqbw*10.0+0.5) - 1));
        ui->RXStopChannelValue->setSingleStep(1);
        ui->RXStopChannelValue->setValue(rxchanneltestplantemp  ? 0 : RX_Start_Channel  + static_cast<int>(freqbw*10.0+0.5) - 1);
    } else if(bandinfo.at(1).toString() == "WCDMA" || bandinfo.at(1).toString() == "TDSCDMA") {
        TX_Start_Frequency = bandinfo.at(4).toDouble();
        RX_Start_Frequency = bandinfo.at(5).toDouble();
        TX_Start_Channel = bandinfo.at(6).toInt();
        RX_Start_Channel = bandinfo.at(7).toInt();
        freqbw = bandinfo.at(8).toDouble();

        ui->TXStartFreqValue->setText(QString::number(TX_Start_Frequency,'f', 1));
        ui->TXStopFreqValue->setText(QString::number(TX_Start_Frequency+freqbw,'f', 1));
        ui->TXStartChannelValue->setRange(TX_Start_Channel, (TX_Start_Channel + static_cast<int>(freqbw*5.0+0.5)));
        ui->TXStartChannelValue->setSingleStep(1);
        ui->TXStartChannelValue->setValue(TX_Start_Channel);
        ui->TXStopChannelValue->setRange(TX_Start_Channel, (TX_Start_Channel + static_cast<int>(freqbw*5.0+0.5)));
        ui->TXStopChannelValue->setSingleStep(1);
        ui->TXStopChannelValue->setValue(TX_Start_Channel  + static_cast<int>(freqbw*10.0+0.5) - 1);

        ui->RXStartFreqValue->setText(QString::number(RX_Start_Frequency,'f', 1));
        ui->RXStopFreqValue->setText(QString::number(RX_Start_Frequency+freqbw,'f', 1));
        ui->RXStartChannelValue->setRange(RX_Start_Channel, (RX_Start_Channel + static_cast<int>(freqbw*5.0+0.5)));
        ui->RXStartChannelValue->setSingleStep(1);
        ui->RXStartChannelValue->setValue(RX_Start_Channel);
        ui->RXStopChannelValue->setRange(RX_Start_Channel, (RX_Start_Channel + static_cast<int>(freqbw*5.0+0.5)));
        ui->RXStopChannelValue->setSingleStep(1);
        ui->RXStopChannelValue->setValue(RX_Start_Channel  + static_cast<int>(freqbw*10.0+0.5) - 1);
    } else if (bandinfo.at(1).toString() == "CDMA") {
        TX_Start_Frequency = bandinfo.at(4).toDouble();
        RX_Start_Frequency = bandinfo.at(5).toDouble();
        TX_Start_Channel = bandinfo.at(6).toInt();
        RX_Start_Channel = bandinfo.at(7).toInt();
        freqbw = bandinfo.at(8).toDouble();

        int deccode = 2;
        int cdmabwtempa = 0;

        if (bandinfo.at(2).toString() == "CDMA BC0") {
            txchanneltestplantemp = 1;channelratio = 0.03;cdmabwtempa = 1023;
        } else if (bandinfo.at(2).toString() == "CDMA BC10") {
            deccode = 3;txchanneltestplantemp = 0;channelratio = 0.025;cdmabwtempa = 2880;
        } else {
            txchanneltestplantemp = 0;channelratio = 0.05;
        }

        ui->TXStartFreqValue->setText(QString::number(TX_Start_Frequency,'f', deccode));
        ui->TXStopFreqValue->setText(QString::number(TX_Start_Frequency+freqbw,'f', deccode));
        ui->RXStartFreqValue->setText(QString::number(RX_Start_Frequency,'f', deccode));
        ui->RXStopFreqValue->setText(QString::number(RX_Start_Frequency+freqbw,'f', deccode));

        if(txchanneltestplantemp == 1) {
            ui->TXStartChannelValue->setRange(-1, 1024);
            ui->TXStopChannelValue->setRange(-1, 1024);
            ui->RXStartChannelValue->setRange(-1, 1024);
            ui->RXStopChannelValue->setRange(-1, 1024);
        } else {
            ui->TXStartChannelValue->setRange(TX_Start_Channel, (TX_Start_Channel + static_cast<int>(freqbw/channelratio+0.5)-cdmabwtempa));
            ui->TXStopChannelValue->setRange(TX_Start_Channel, (TX_Start_Channel + static_cast<int>(freqbw/channelratio+0.5)-cdmabwtempa));
            ui->RXStartChannelValue->setRange(RX_Start_Channel, (RX_Start_Channel + static_cast<int>(freqbw/channelratio+0.5)-cdmabwtempa));
            ui->RXStopChannelValue->setRange(RX_Start_Channel, (RX_Start_Channel + static_cast<int>(freqbw/channelratio+0.5)-cdmabwtempa));
        }

        ui->TXStartChannelValue->setSingleStep(1);
        ui->TXStopChannelValue->setSingleStep(1);
        ui->RXStartChannelValue->setSingleStep(1);
        ui->RXStopChannelValue->setSingleStep(1);

        ui->TXStartChannelValue->setValue(TX_Start_Channel);
        ui->TXStopChannelValue->setValue(TX_Start_Channel  + static_cast<int>(freqbw/channelratio+0.5)-cdmabwtempa);
        ui->RXStartChannelValue->setValue(RX_Start_Channel);
        ui->RXStopChannelValue->setValue(RX_Start_Channel  + static_cast<int>(freqbw/channelratio+0.5)-cdmabwtempa);
    } else if (bandinfo.at(1).toString() == "GSM") {
        TX_Start_Frequency = bandinfo.at(4).toDouble();
        RX_Start_Frequency = bandinfo.at(5).toDouble();
        TX_Start_Channel = bandinfo.at(6).toInt();
        RX_Start_Channel = bandinfo.at(7).toInt();
        freqbw = bandinfo.at(8).toDouble();

        ui->TXStartFreqValue->setText(QString::number(TX_Start_Frequency,'f', 1));
        ui->TXStopFreqValue->setText(QString::number(TX_Start_Frequency+freqbw,'f', 1));
        ui->RXStartFreqValue->setText(QString::number(RX_Start_Frequency,'f', 1));
        ui->RXStopFreqValue->setText(QString::number(RX_Start_Frequency+freqbw,'f', 1));

        int gsmbwtempa = 0;

        if(bandinfo.at(2).toString() == "E-GSM 900") {
            gsmbwtempa = 1024;txchanneltestplantemp = 1;
        } else {
            gsmbwtempa = 0;txchanneltestplantemp = 0;
        }

        if(txchanneltestplantemp == 1) {
            ui->TXStartChannelValue->setRange(-1, 1024);
            ui->TXStopChannelValue->setRange(-1, 1024);
            ui->RXStartChannelValue->setRange(-1, 1024);
            ui->RXStopChannelValue->setRange(-1, 1024);
        } else {
            ui->TXStartChannelValue->setRange(TX_Start_Channel,(TX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)));
            ui->TXStopChannelValue->setRange(TX_Start_Channel,(TX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)));
            ui->RXStartChannelValue->setRange(RX_Start_Channel,(RX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)));
            ui->RXStopChannelValue->setRange(RX_Start_Channel,(RX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)));
        }

        ui->TXStartChannelValue->setSingleStep(1);
        ui->TXStopChannelValue->setSingleStep(1);
        ui->RXStartChannelValue->setSingleStep(1);
        ui->RXStopChannelValue->setSingleStep(1);

        ui->TXStartChannelValue->setValue(TX_Start_Channel);
        ui->TXStopChannelValue->setValue(TX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)-gsmbwtempa);
        ui->RXStartChannelValue->setValue(RX_Start_Channel);
        ui->RXStopChannelValue->setValue(RX_Start_Channel+static_cast<int>(freqbw*5.0+0.5)-gsmbwtempa);
    }
}

void MainWidgetUI::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QVariant MainWidgetUI::iniFilesValueRead(const QString &key1, const QString &key2)
{
    QSettings iniFileRead("./theme/ThemeConfig.ini", QSettings::IniFormat);

    return iniFileRead.value(key1 + "/" + key2);
}

void MainWidgetUI::iniFilesSetValue(const QString &key1, const QString &key2, const QVariant &value)
{
    QSettings iniFile("./theme/ThemeConfig.ini", QSettings::IniFormat);

    iniFile.setValue(key1 + "/" + key2, value);
}
