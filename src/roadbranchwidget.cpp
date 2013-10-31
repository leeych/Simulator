#include "roadbranchwidget.h"
#include "macrostrings.h"
#include "mutility.h"

#include <QBrush>
#include <QBitmap>
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>
#include <QPoint>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

RoadBranchWidget::RoadBranchWidget(QWidget *parent) :
    QWidget(parent)
{
    flash_timer_ = new QTimer(this);
    curr_index_ = 0;
    initPage();
    initSignalSlots();
    setFixedSize(550,550);
}

RoadBranchWidget::~RoadBranchWidget()
{
    qDeleteAll(pixmap_list_);
}

void RoadBranchWidget::cmbItemSelectedSlot(int)
{
    QComboBox *cmb = qobject_cast<QComboBox *>(sender());
    if (cmb == NULL || cmb->currentText() == "-")
    {
        return;
    }
    QList<int> lane_id_list;
    int lane_index = -1;
    for (int i = 0; i < lane_cmb_list_.size(); i++)
    {
        if (cmb != lane_cmb_list_.at(i))
        {
            lane_id_list.append(lane_cmb_list_.at(i)->currentText().toInt());
        }
        else
        {
            lane_index = i;
        }
    }
    if (lane_id_list.contains(cmb->currentText().toInt()))
    {
        QMessageBox::information(this, STRING_TIP, STRING_UI_ASSIGNED + STRING_UI_OTHER + STRING_UI_LANE, STRING_OK);
        int count = cmb->count();
        cmb->setCurrentIndex(count - 1);
        return;
    }
    emit laneIndexSignal(lane_index+1);
}

void RoadBranchWidget::flashTimerTimeoutSlot()
{
    updateFlashLight(curr_index_, Red);
}

void RoadBranchWidget::laneIndexSlot(int index, int color)
{
    curr_index_ = index;
    updateFlashLight(curr_index_, LightColor(color));
}

void RoadBranchWidget::closeLightSlot()
{
    for (int i = 0; i < lane_light_list_.size(); i++)
    {
        lane_light_list_.at(i)->hide();
    }
}

void RoadBranchWidget::enableLaneIdCmbSlot(bool enable)
{
    for (int i = 0; i < lane_cmb_list_.size(); i++)
    {
        lane_cmb_list_.at(i)->setEnabled(enable);
    }
}

void RoadBranchWidget::resizeEvent(QResizeEvent *)
{
}

void RoadBranchWidget::initPage()
{
    QString dir = MUtility::getImagesDir();
    dir += "bg.png";
    QPalette pal = this->palette();
    QPixmap pixmap(dir);
    this->resize(pixmap.size());
    pal.setBrush(QPalette::Background, QBrush(pixmap));
    this->setMask(pixmap.mask());
    pal.setColor(QPalette::Base, QColor(234, 246, 254));
    setPalette(pal);
    setAutoFillBackground(true);

    initLaneList();
    initLightStatus();

    QString qss =
            "QComboBox{border-style:none;background-color:rgb(101,101,101); color:red; text-align:center;}"
            "QComboBox:hover{border:1px solid}"
            "QComboBox::drop-down{"
            "border-style: none;background-color:rgb(101,101,101);width:1px;}";
    setStyleSheet(qss);
}

void RoadBranchWidget::initSignalSlots()
{
    for (int i = 0; i < lane_cmb_list_.size(); i++)
    {
        connect(lane_cmb_list_.at(i), SIGNAL(activated(int)), this, SLOT(cmbItemSelectedSlot(int)));
    }
    connect(flash_timer_, SIGNAL(timeout()), this, SLOT(flashTimerTimeoutSlot()));
}

void RoadBranchWidget::initLaneList()
{
    QStringList item_list;
    for (int i = 1; i <= 60; i++)
    {
        item_list.append(QString::number(i));
    }
    item_list.append("-");
    for (int i = 0; i < 12; i++)
    {
        QComboBox *cmb = new QComboBox(this);
        cmb->addItems(item_list);
        lane_cmb_list_.append(cmb);
    }

    cmb_rect_list_ << QRect(194, 504, 38, 26) << QRect(9,199,38,26) << QRect(317,20,38,26) << QRect(500,321,38,26)
                      << QRect(235,504,38,26) << QRect(9,243,38,26) << QRect(275,20,38,26) << QRect(500,280,38,26)
                      << QRect(151,504,38,26) << QRect(9,157,38,26) << QRect(357,20,38,26) << QRect(500,363,38,26);
    for (int i = 0; i < 12; i++)
    {
        lane_cmb_list_.at(i)->setGeometry(cmb_rect_list_.at(i));
        lane_cmb_list_.at(i)->setCurrentIndex(i);
    }
}

void RoadBranchWidget::initLightStatus()
{

    light_rect_list_ << QRect(193,460,38,38) << QRect(52,195,38,38) << QRect(316,53,38,38) << QRect(459,318,38,38)
                     << QRect(234,460,38,38) << QRect(52,236,38,38) << QRect(276,53,38,38) << QRect(459,278,38,38)
                     << QRect(153,460,38,38) << QRect(52,155,38,38) << QRect(357,53,38,38) << QRect(459,359,38,38);

    for (int i = 0; i < 12; i++)
    {
        QLabel *light_label = new QLabel(this);
        light_label->setGeometry(light_rect_list_.at(i));
        light_label->hide();
        lane_light_list_.append(light_label);
    }
    for (int i = 0; i < 12; i++)
    {
        QLabel *label = new QLabel(this);
        label->setGeometry(light_rect_list_.at(i));
        label->hide();
        lane_light_list_.append(label);
    }

    QString dir = MUtility::getImagesDir();
    pixmap_list_ << new QPixmap(dir + "dg_img.bmp") << new QPixmap(dir + "lg_img.bmp") << new QPixmap(dir + "tg_img.bmp") << new QPixmap(dir + "rg_img.bmp")
                 << new QPixmap(dir + "rg_img.bmp") << new QPixmap(dir + "dg_img.bmp") << new QPixmap(dir + "lg_img.bmp") << new QPixmap(dir + "tg_img.bmp")
                 << new QPixmap(dir + "lg_img.bmp") << new QPixmap(dir + "tg_img.bmp") << new QPixmap(dir + "rg_img.bmp") << new QPixmap(dir + "dg_img.bmp")
                 << new QPixmap(dir + "dr_img.bmp") << new QPixmap(dir + "lr_img.bmp") << new QPixmap(dir + "tr_img.bmp") << new QPixmap(dir + "rr_img.bmp")
                 << new QPixmap(dir + "rr_img.bmp") << new QPixmap(dir + "dr_img.bmp") << new QPixmap(dir + "lr_img.bmp") << new QPixmap(dir + "tr_img.bmp")
                 << new QPixmap(dir + "lr_img.bmp") << new QPixmap(dir + "tr_img.bmp") << new QPixmap(dir + "rr_img.bmp") << new QPixmap(dir + "dr_img.bmp");
    for (int i = 0; i < 12; i++)
    {
        lane_light_list_.at(i)->setPixmap(*pixmap_list_.at(i));
        lane_light_list_.at(i+12)->setPixmap(*pixmap_list_.at(i+12));
    }
}

QList<int>& RoadBranchWidget::getLaneIdList()
{
    lane_id_list_.clear();
    for (int i = 0; i < lane_cmb_list_.size(); i++)
    {
        int id = lane_cmb_list_.at(i)->currentText().toInt();
        lane_id_list_.append(id);
    }
    return lane_id_list_;
}

void RoadBranchWidget::updateFlashLight(int index, LightColor color)
{
    if (index < 0 || index >= 12)
    {
        return;
    }
    for (int i = 0; i < 24; i++)
    {
        lane_light_list_.at(i)->hide();
    }
    if (color == Red)
    {
        index += 12;
    }
    lane_light_list_.at(index)->show();
}
