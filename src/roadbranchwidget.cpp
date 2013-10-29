#include "roadbranchwidget.h"
#include "mutility.h"
#include <QBrush>
#include <QBitmap>
#include <QFrame>
#include <QLineEdit>
#include <QComboBox>
#include <QPoint>
#include <QLabel>

#include <QAbstractItemView>

RoadBranchWidget::RoadBranchWidget(QWidget *parent) :
    QWidget(parent)
{
    initPage();
}

RoadBranchWidget::~RoadBranchWidget()
{

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

    QString qss = /*"QComboBox::hover:drop-down{border-style:none;}"*/
            "QComboBox{border-style:none;background-color:rgb(101,101,101);}"
            "QComboBox::item{color: #ffffff;}"
            "QComboBox:hover{border:1px solid}"
            "QComboBox::drop-down{"
            "border-style: none;background-color:rgb(101,101,101);max-width:1px;}"
            "QComboBox QAbstractItemView::drop-down{max-width:1px;}";
    setStyleSheet(qss);
}

void RoadBranchWidget::initLaneList()
{
    QStringList item_list;
    for (int i = 1; i <= 60; i++)
    {
        item_list.append(QString::number(i));
    }
    for (int i = 0; i < 12; i++)
    {
        QComboBox *cmb = new QComboBox(this);
        QAbstractItemView *view = cmb->view();
        view->setDropIndicatorShown(false);

        cmb->addItems(item_list);
        lane_cmb_list_.append(cmb);
    }

    QRect rect(197, 504, 33, 26);
    rect_list_.append(rect);
    rect.setRect(6,199,33,26);
    rect_list_.append(rect);
    rect.setRect(320,20,33,26);
    rect_list_.append(rect);
    rect.setRect(502,321,33,26);
    rect_list_.append(rect);
    rect.setRect(238,504,33,26);
    rect_list_.append(rect);
    rect.setRect(6,243,33,26);
    rect_list_.append(rect);
    rect.setRect(278,20,33,26);
    rect_list_.append(rect);
    rect.setRect(502,280,33,26);
    rect_list_.append(rect);
    rect.setRect(154,504,33,26);
    rect_list_.append(rect);
    rect.setRect(6,157,33,26);
    rect_list_.append(rect);
    rect.setRect(360,20,33,26);
    rect_list_.append(rect);
    rect.setRect(502,363,33,26);
    rect_list_.append(rect);

    for (int i = 0; i < 12; i++)
    {
        lane_cmb_list_.at(i)->setGeometry(rect_list_.at(i));
    }
}

void RoadBranchWidget::initLightStatus()
{
    for (int i = 0; i < 12; i++)
    {
        QLabel *light_label = new QLabel(this);
        lane_light_list_.append(light_label);
    }

    QString dir = MUtility::getImagesDir();
    QList<QPixmap*> pixmap_list;
    pixmap_list << new QPixmap(dir + "dd_img.bmp") << new QPixmap(dir + "ld_img.bmp");
    lane_light_list_.at(0)->setPixmap(QPixmap(dir + "dd_img.bmp"));
}
