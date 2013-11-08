#include "testdlg.h"
#include "macrostrings.h"
#include "roadbranchwidget.h"

#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>

#define DETECTOR_TEST_MACRO(signal) \
    int id = channel_id_cmb_->currentText().toInt(); \
    int color = color_cmb_->currentIndex(); \
    int index = -1; \
    QMap<int,int> temp_map; \
    if (id > 48 && id < 57) \
    { \
        temp_map = widget_->getSidewalkDetectorIdIndexMap(); \
        index = temp_map.value(id); \
    } \
    else \
    { \
        temp_map = widget_->getLaneDetectorIdIndexMap(); \
        index = temp_map.value(id); \
    } \
    emit signal;

#define LIGHT_TEST_MACRO(signal) \
    int id = channel_id_cmb_->currentText().toInt(); \
    int color = color_cmb_->currentIndex(); \
    emit signal;


TestDlg::TestDlg(QWidget *parent) :
    QDialog(parent)
{
    initPage();
    initSignalSlots();
}

void TestDlg::setPtr(RoadBranchWidget *ptr)
{
    widget_ = ptr;
}

void TestDlg::OnOKButtonClicked()
{
    LIGHT_TEST_MACRO(showChannelLightSignal(id, color))
#if 0
    int id = channel_id_cmb_->currentText().toInt();
    int color = color_cmb_->currentIndex();
    int index = -1;
    QMap<int,int> temp_map;
    if (id > 48 && id < 57)
    {
        temp_map = widget_->getSidewalkDetectorIdIndexMap();
        index = temp_map.value(id);
    }
    else
    {
        temp_map = widget_->getLaneDetectorIdIndexMap();
        index = temp_map.value(id);
    }
    emit showChannelLightSignal(id, color);
#endif
}

void TestDlg::OnOffButtonClicked()
{
    int id = channel_id_cmb_->currentText().toInt();
    int color = 3;
    emit showChannelLightSignal(id, color);
}

void TestDlg::OnLaneDetectorButtonClicked()
{
    DETECTOR_TEST_MACRO(showLaneDetectorSignal(index, color, true))
}

void TestDlg::OnCancelLDetectorButtonClicked()
{
    DETECTOR_TEST_MACRO(showLaneDetectorSignal(index, color, false))
}

void TestDlg::OnSidewalkDetectorButtonClicked()
{
    DETECTOR_TEST_MACRO(showSidewalkDetectorSignal(index, color, true))
}

void TestDlg::OnCancelSDetectorButtonClicked()
{
    DETECTOR_TEST_MACRO(showSidewalkDetectorSignal(index, color, false))
}

void TestDlg::initPage()
{
    ok_button_ = new QPushButton(STRING_OK);
    off_button_ = new QPushButton(STRING_CANCEL);
    lane_detector_button_ = new QPushButton("Lane");
    cancel_lane_d_button_ = new QPushButton("L cancel");
    sidewalk_detector_button_ = new QPushButton("Sidewalk");
    cancel_sidewalk_d_button_ = new QPushButton("S cancel");

    color_cmb_ = new QComboBox;
    color_cmb_->addItem("Red");
    color_cmb_->addItem("Yellow");
    color_cmb_->addItem("Green");
    color_cmb_->addItem("Off");
    channel_id_cmb_ = new QComboBox;
    for (int i = 0; i < 60; i++)
    {
        channel_id_cmb_->addItem(QString::number(i+1));
    }
    channel_id_cmb_->addItem("-");

    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(channel_id_cmb_, 0, 0, 1, 1);
    glayout->addWidget(color_cmb_, 0, 1, 1, 1);
    glayout->addWidget(ok_button_, 1, 0, 1, 1);
    glayout->addWidget(off_button_, 1, 1, 1, 1);

    glayout->addWidget(lane_detector_button_, 2, 0, 1, 1);
    glayout->addWidget(cancel_lane_d_button_, 2, 1, 1, 1);
    glayout->addWidget(sidewalk_detector_button_, 3, 0, 1, 1);
    glayout->addWidget(cancel_sidewalk_d_button_, 3, 1, 1, 1);

    setLayout(glayout);
}

void TestDlg::initSignalSlots()
{
    connect(ok_button_, SIGNAL(clicked()), this, SLOT(OnOKButtonClicked()));
    connect(off_button_, SIGNAL(clicked()), this, SLOT(OnOffButtonClicked()));

    connect(lane_detector_button_, SIGNAL(clicked()), this, SLOT(OnLaneDetectorButtonClicked()));
    connect(cancel_lane_d_button_, SIGNAL(clicked()), this, SLOT(OnCancelLDetectorButtonClicked()));
    connect(sidewalk_detector_button_, SIGNAL(clicked()), this, SLOT(OnSidewalkDetectorButtonClicked()));
    connect(cancel_sidewalk_d_button_, SIGNAL(clicked()), this, SLOT(OnCancelSDetectorButtonClicked()));
}
