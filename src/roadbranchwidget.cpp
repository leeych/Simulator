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
    closeLightSlot();
    setFixedSize(550,550);
}

RoadBranchWidget::~RoadBranchWidget()
{
    qDeleteAll(pixmap_list_);
    qDeleteAll(detector_pixmap_list_);
    qDeleteAll(sidewalk_pixmap_list_);
}

void RoadBranchWidget::laneDetectorcmbItemSelectedSlot(int)
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

void RoadBranchWidget::sidewalkcmbItemSelectedSlot(int)
{
    QComboBox *cmb = qobject_cast<QComboBox *>(sender());
    if (cmb == NULL || cmb->currentText() == "-")
    {
        return;
    }
    QList<int> sidewalk_id_list;
    int sidewalk_idx = -1;
    for (int i = 0; i < sidewalk_cmb_list_.size(); i++)
    {
        if (cmb != sidewalk_cmb_list_.at(i))
        {
            sidewalk_id_list.append(sidewalk_cmb_list_.at(i)->currentText().toInt());
        }
        else
        {
            sidewalk_idx = i;
        }
    }
    if (sidewalk_id_list.contains(cmb->currentText().toInt()))
    {
        QMessageBox::information(this, STRING_TIP, STRING_UI_ASSIGNED + STRING_UI_OTHER + STRING_UI_SIDEWALK, STRING_OK);
        int count = cmb->count();
        cmb->setCurrentIndex(count-1);
        return;
    }
//    emit laneIndexSignal();
}

void RoadBranchWidget::flashTimerTimeoutSlot()
{
    updateLaneLight(curr_index_, Red);
}

void RoadBranchWidget::laneIndexSlot(int index, int color)
{
    curr_index_ = index;
    updateLaneLight(curr_index_, LightColor(color));
}

void RoadBranchWidget::closeLightSlot()
{
    for (int i = 0; i < lane_light_list_.size(); i++)
    {
        lane_light_list_.at(i)->hide();
    }
    foreach (QLabel *label, sidewalk_light_label_list_) {
        label->hide();
    }
}

void RoadBranchWidget::enableLaneIdCmbSlot(bool enable)
{
    for (int i = 0; i < lane_cmb_list_.size(); i++)
    {
        lane_cmb_list_.at(i)->setEnabled(enable);
    }
}

void RoadBranchWidget::showDetectorSlot(int id, int color, bool show)
{
    if (id >= 12)
    {
        showSidewalkDetector((SidewalkId)id, show);
    }
    else
    {
        showLaneDetector(id, (LightColor)color, show);
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
    initSidewalkDetectorList();

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
        connect(lane_cmb_list_.at(i), SIGNAL(activated(int)), this, SLOT(laneDetectorcmbItemSelectedSlot(int)));
    }
    foreach (QComboBox *cmb, sidewalk_cmb_list_) {
        connect(cmb, SIGNAL(activated(int)), this, SLOT(sidewalkcmbItemSelectedSlot(int)));
    }
    connect(flash_timer_, SIGNAL(timeout()), this, SLOT(flashTimerTimeoutSlot()));
}
// 13-1: 127,174 13-2: 127,351
// 14-1: 174,130 14-2: 346,130
// 15-1: 393,175 15-2: 393,350
// 16-1: 174,395 16-2: 344,396
void RoadBranchWidget::initLaneDetectorList()
{
    QStringList item_list;
    for (int i = 1; i <= 48; i++)
    {
        item_list.append(QString::number(i));
    }
    item_list.append(QString::number(57));
    item_list.append(QString::number(58));
    item_list.append(QString::number(59));
    item_list.append(QString::number(60));
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

    detector_rect_list_ << QRect(323,485,24,24) << QRect(37,320,24,24) << QRect(202,33,24,24) << QRect(485,200,24,24)
                        << QRect(359,485,24,24) << QRect(37,356,24,24) << QRect(166,33,24,24) << QRect(485,163,24,24)
                        << QRect(285,485,24,24) << QRect(37,285,24,24) << QRect(237,33,24,24) << QRect(485,234,24,24);
    for (int i = 0; i < detector_rect_list_.size()*2; i++)
    {
        QLabel *label = new QLabel(this);
        label->hide();
        detector_label_list_.append(label);
    }
    QString dir = MUtility::getImagesDir();
    for (int i = 0; i < 12; i++)
    {
        detector_label_list_.at(i)->setGeometry(detector_rect_list_.at(i));
        detector_label_list_.at(i)->setPixmap(QPixmap(dir + "detector_green_img.png"));
    }
    for (int i = 12; i < 24; i++)
    {
        detector_label_list_.at(i)->setGeometry(detector_rect_list_.at(i-12));
        detector_label_list_.at(i)->setPixmap(QPixmap(dir + "detector_red_img.png"));
    }
}

void RoadBranchWidget::initLightStatus()
{
    light_rect_list_ << QRect(200,433,36,32) << QRect(84,200,32,36) << QRect(315,85,36,32) << QRect(432,313,32,36)
                     << QRect(238,433,36,32) << QRect(84,238,32,36) << QRect(277,85,36,32) << QRect(432,275,32,36)
                     << QRect(162,433,36,32) << QRect(84,162,32,36) << QRect(353,85,36,32) << QRect(432,351,32,36);

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
    for (int i = 0; i < 12; i++)
    {
        QLabel *label = new QLabel(this);
        label->setGeometry(light_rect_list_.at(i));
        label->hide();
        lane_light_list_.append(label);
    }

    QString dir = MUtility::getImagesDir();
    pixmap_list_ << new QPixmap(dir + "g_1.bmp") << new QPixmap(dir + "g_2.bmp") << new QPixmap(dir + "g_3.bmp") << new QPixmap(dir + "g_4.bmp")
                 << new QPixmap(dir + "g_4.bmp") << new QPixmap(dir + "g_1.bmp") << new QPixmap(dir + "g_2.bmp") << new QPixmap(dir + "g_3.bmp")
                 << new QPixmap(dir + "g_2.bmp") << new QPixmap(dir + "g_3.bmp") << new QPixmap(dir + "g_4.bmp") << new QPixmap(dir + "g_1.bmp")
                 << new QPixmap(dir + "r_1.bmp") << new QPixmap(dir + "r_2.bmp") << new QPixmap(dir + "r_3.bmp") << new QPixmap(dir + "r_4.bmp")
                 << new QPixmap(dir + "r_4.bmp") << new QPixmap(dir + "r_1.bmp") << new QPixmap(dir + "r_2.bmp") << new QPixmap(dir + "r_3.bmp")
                 << new QPixmap(dir + "r_2.bmp") << new QPixmap(dir + "r_3.bmp") << new QPixmap(dir + "r_4.bmp") << new QPixmap(dir + "r_1.bmp")
                 << new QPixmap(dir + "y_1.bmp") << new QPixmap(dir + "y_2.bmp") << new QPixmap(dir + "y_3.bmp") << new QPixmap(dir + "y_4.bmp")
                 << new QPixmap(dir + "y_4.bmp") << new QPixmap(dir + "y_1.bmp") << new QPixmap(dir + "y_2.bmp") << new QPixmap(dir + "y_3.bmp")
                 << new QPixmap(dir + "y_2.bmp") << new QPixmap(dir + "y_3.bmp") << new QPixmap(dir + "y_4.bmp") << new QPixmap(dir + "y_1.bmp");
    for (int i = 0; i < 12; i++)
    {
        lane_light_list_.at(i)->setPixmap(*pixmap_list_.at(i));
        lane_light_list_.at(i+12)->setPixmap(*pixmap_list_.at(i+12));
        lane_light_list_.at(i+12*2)->setPixmap(*pixmap_list_.at(i+12*2));
    }
}

void RoadBranchWidget::initSidewalkDetectorList()
{
    for (int i = 0; i < 8; i++)
    {
        QLabel *label = new QLabel(this);
        label->hide();
        sidewalk_label_list_.append(label);
    }
    sidewalk_rect_list_ << QRect(127,174,24,24) << QRect(174,130,24,24) << QRect(393,175,24,24) << QRect(174,395,24,24)
                        << QRect(127,351,24,24) << QRect(350,130,24,24) << QRect(393,350,24,24) << QRect(350,395,24,24);
    QString dir = MUtility::getImagesDir();
    sidewalk_pixmap_list_ << new QPixmap(dir + "detector_green_img.png");// << new QPixmap(dir + "detector_red_img.png");

    for (int i = 0; i < 8; i++)
    {
        sidewalk_label_list_.at(i)->setGeometry(sidewalk_rect_list_.at(i));
    }
    for (int i = 0; i < 8; i++)
    {
        sidewalk_label_list_.at(i)->setPixmap(*sidewalk_pixmap_list_.at(0));
    }

    sidewalk_cmb_rect_list_ << QRect(154,178,36,22) << QRect(174,156,36,22) << QRect(358,178,36,22) << QRect(174,374,36,22)
                            << QRect(154,351,36,22) << QRect(350,156,36,22) << QRect(358,351,36,22) << QRect(345,374,36,22);

    for (int i = 0; i < 8; i++)
    {
        QComboBox *cmb = new QComboBox(this);
        for (int j = 49; j < 57; j++ )
        {
            cmb->addItem(QString::number(j));
        }
        cmb->addItem("-");
        cmb->setGeometry(sidewalk_cmb_rect_list_.at(i));
        cmb->setCurrentIndex(i);
        sidewalk_cmb_list_.append(cmb);
    }

    sidewalk_light_rect_list_ << QRect(133,148,18,18) << QRect(148,132,18,18) << QRect(397,149,18,18) << QRect(147,400,18,18)
                              << QRect(133,383,18,18) << QRect(383,132,18,18) << QRect(397,384,18,18) << QRect(382,400,18,18);
    for (int i = 0; i < 8; i++)
    {
        QLabel *label = new QLabel(this);
        label->hide();
        label->setGeometry(sidewalk_light_rect_list_.at(i));
        sidewalk_light_label_list_.append(label);
    }
    for (int i = 0; i < 8; i++)
    {
        QLabel *label = new QLabel(this);
        label->hide();
        label->setGeometry(sidewalk_light_rect_list_.at(i));
        sidewalk_light_label_list_.append(label);
    }
    for (int i = 0; i < 8; i++)
    {
        sidewalk_light_label_list_.at(i)->setPixmap(QPixmap(dir + "circle_g_img.bmp"));
        sidewalk_light_label_list_.at(i+8)->setPixmap(QPixmap(dir + "circle_r_img.bmp"));
    }
}

void RoadBranchWidget::initLightList()
{

}

QList<int> &RoadBranchWidget::getLaneDetectorIdList()
{
//    lane_detector_id_list_.clear();
    QList<int> empty_list;
    lane_detector_id_list_.swap(empty_list);
    for (int i = 0; i < lane_cmb_list_.size(); i++)
    {
        int id = lane_cmb_list_.at(i)->currentText().toInt();
        lane_detector_id_list_.append(id);
    }
    return lane_detector_id_list_;
}

QList<int> &RoadBranchWidget::getSidewalkDetectorIdList()
{
    sidewalk_detector_id_list_.clear();
    for (int i = 0; i < sidewalk_cmb_list_.size(); i++)
    {
        int id = sidewalk_cmb_list_.at(i)->currentText().toInt();
        sidewalk_detector_id_list_.append(id);
    }
    return sidewalk_detector_id_list_;
}

QMap<int, int> &RoadBranchWidget::getLaneDetectorIdIndexMap()
{
    lane_detector_map_.clear();
    getLaneDetectorIdList();
    for (int i = 0; i < lane_detector_id_list_.size(); i++)
    {
        lane_detector_map_.insert(lane_detector_id_list_.at(i), i);
    }
    return lane_detector_map_;
}

QMap<int, int> &RoadBranchWidget::getSidewalkDetectorIdIndexMap()
{
    sidewalk_detector_map_.clear();
    getSidewalkDetectorIdList();
    for (int i = 0; i < sidewalk_detector_id_list_.size(); i++)
    {
        sidewalk_detector_map_.insert(sidewalk_detector_id_list_.at(i), i+12);
    }
    return sidewalk_detector_map_;
}

void RoadBranchWidget::updateLaneLight(int id, LightColor color)
{
    if (id < 0)
    {
        return;
    }
    int index = id;
    if (id <= 12)
    {
        index = id - 1;
        switch(color)
        {
        case Green:
            lane_light_list_.at(index+12)->hide();
            lane_light_list_.at(index+12*2)->hide();
            lane_light_list_.at(index)->show();
            break;
        case Red:
            lane_light_list_.at(index)->hide();
            lane_light_list_.at(index+12*2)->hide();
            lane_light_list_.at(index+12)->show();
            break;
        case Yellow:
            lane_light_list_.at(index)->hide();
            lane_light_list_.at(index+12)->hide();
            lane_light_list_.at(index+12*2)->show();
            break;
        case Off:
            lane_light_list_.at(index)->hide();
            lane_light_list_.at(index+12)->hide();
            lane_light_list_.at(index+12*2)->hide();
            break;
        default:
            break;
        }
    }
    else if (id <= 16)
    {
        index = id-13;
        switch (color)
        {
        case Green:
            sidewalk_light_label_list_.at(index+8)->hide();
            sidewalk_light_label_list_.at(index+8+4)->hide();
            sidewalk_light_label_list_.at(index)->show();
            sidewalk_light_label_list_.at(index+4)->show();
            break;
        case Red:
            sidewalk_light_label_list_.at(index)->hide();
            sidewalk_light_label_list_.at(index+4)->hide();
            sidewalk_light_label_list_.at(index+8)->show();
            sidewalk_light_label_list_.at(index+8+4)->show();
            break;
        case Yellow:
            break;
        case Off:
            sidewalk_light_label_list_.at(index)->hide();
            sidewalk_light_label_list_.at(index+4)->hide();
            sidewalk_light_label_list_.at(index+8)->hide();
            sidewalk_light_label_list_.at(index+8+4)->hide();
            break;
        default:
            break;
        }
    }
}

void RoadBranchWidget::showLaneDetector(int index, RoadBranchWidget::LightColor color, bool show)
{
    if (index < 0 || index >= 12)
    {
        return;
    }
    switch (color)
    {
    case Green:
        detector_label_list_.at(index+12)->hide();
        detector_label_list_.at(index)->setVisible(show);
        break;
    case Red:
        detector_label_list_.at(index)->hide();
        detector_label_list_.at(index+12)->setVisible(show);
        break;
    case Yellow:
        break;
    case Off:
        detector_label_list_.at(index)->hide();
        detector_label_list_.at(index+12)->hide();
        break;
    default:/*
        detector_label_list_.at(index)->hide();
        detector_label_list_.at(index+12)->hide();*/
        break;
    }
}

void RoadBranchWidget::showSidewalkDetector(int index, bool show)
{
    index -= 12;
    sidewalk_label_list_.at(index)->setVisible(show);
//    sidewalk_label_list_.at(index+4)->setVisible(show);
}
