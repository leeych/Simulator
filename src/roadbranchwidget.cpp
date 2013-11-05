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

void RoadBranchWidget::initPage()
{
    QString dir = MUtility::getImagesDir();
    dir += "simulator_bg.png";
    QPalette pal = this->palette();
    QPixmap pixmap(dir);
    this->resize(pixmap.size());
    pal.setBrush(QPalette::Background, QBrush(pixmap));
    this->setMask(pixmap.mask());
    pal.setColor(QPalette::Base, QColor(234, 246, 254));
    setPalette(pal);
    setAutoFillBackground(true);

    initLaneDetectorList();
    initLightStatus();

    QString qss =
            "QComboBox{border-style:none;background-color:rgb(101,101,101); color:red; text-align:center;}"
            "QComboBox:hover{border:1px solid}"
            "QComboBox::drop-down{"
            "border-style: none;background-color:rgb(101,101,101);width:1px;}"
            "QScrollBar::handle:horizontal,vertical{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #eff6fc, stop:1 #caddec);"
            "border: 1px solid #759cb9;min-width: 10px;}";
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
// 13-1: 127,174 13-2: 127,351
// 14-1: 174,130 14-2: 341,130
// 15-1: 393,175 15-2: 393,350
// 16-1: 174,395 16-2: 339,396
void RoadBranchWidget::initLaneDetectorList()
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

    cmb_rect_list_ << QRect(318,523,36,26) << QRect(0,319,36,26) << QRect(162,1,36,26) << QRect(514,197,36,26)
                   << QRect(355,523,36,26) << QRect(0,355,36,26) << QRect(198,1,36,26) << QRect(514,161,36,26)
                   << QRect(281,523,36,26) << QRect(0,283,36,26) << QRect(234,1,36,26) << QRect(514,234,36,26);
    for (int i = 0; i < 12; i++)
    {
        lane_cmb_list_.at(i)->setGeometry(cmb_rect_list_.at(i));
        lane_cmb_list_.at(i)->setCurrentIndex(i);
    }

    detector_rect_list_ << QRect(323,485,24,24) << QRect(37,320,24,24) << QRect(202,27,24,24) << QRect(485,200,24,24)
                        << QRect(359,485,24,24) << QRect(37,356,24,24) << QRect(166,27,24,24) << QRect(485,163,24,24)
                        << QRect(285,485,24,24) << QRect(37,285,24,24) << QRect(237,27,24,24) << QRect(485,234,24,24);
    for (int i = 0; i < detector_rect_list_.size(); i++)
    {
        QLabel *label = new QLabel(this);
        detector_label_list_.append(label);
    }
    QString dir = MUtility::getImagesDir();
    for (int i = 0; i < 12; i++)
    {
        QPixmap *pixmap = new QPixmap(dir + "detector_green_img.png");
        detector_pixmap_list_.append(pixmap);
    }
    for (int i = 12; i < 24; i++)
    {
        QPixmap *pixmap = new QPixmap(dir + "detector_red_img.png");
        detector_pixmap_list_.append(pixmap);
    }

    for (int i = 0; i < 12; i++)
    {
        detector_label_list_.at(i)->setGeometry(detector_rect_list_.at(i));
    }
    for (int i = 0; i < 12; i++)
    {
        detector_label_list_.at(i)->setPixmap(*detector_pixmap_list_.at(i));
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
