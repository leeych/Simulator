#include "testwindow.h"
#include "macrostrings.h"
#include "roadbranchwidget.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>

#include <QDebug>

TestWindow::TestWindow(QWidget *parent) :
    QWidget(parent)
{
    struct PortSettings my_com_setting = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 500};
    my_com_ = new Win_QextSerialPort("com1", my_com_setting, QextSerialBase::EventDriven);

    initPage();
    initSignalSlots();
    close_button_->setEnabled(false);
    send_msg_button_->setEnabled(false);
}

void TestWindow::openMyComSlot()
{
    my_com_->open(QIODevice::ReadWrite);

    open_button_->setEnabled(false);
    close_button_->setEnabled(true);
    send_msg_button_->setEnabled(true);
}

void TestWindow::closeMyComSlot()
{
    my_com_->close();

    open_button_->setEnabled(true);
    close_button_->setEnabled(false);
    send_msg_button_->setEnabled(false);
}

void TestWindow::sendMsgSlot()
{
    QByteArray array(msg_lineedit_->text().toLocal8Bit());
    qint32 sz = my_com_->write(array);
    qDebug() << sz;
}

void TestWindow::readMyComSlot()
{
    QByteArray tmp = my_com_->readAll();
    tmp = QString(tmp).toUtf8();
    txt_browser_->insertPlainText(tmp);
}

void TestWindow::initPage()
{
    open_button_ = new QPushButton(STRING_UI_OPEN + STRING_UI_SERIALPORT);
    close_button_ = new QPushButton(STRING_UI_CLOSE + STRING_UI_SERIALPORT);
    send_msg_button_ = new QPushButton(STRING_UI_SEND);

    txt_browser_ = new QTextBrowser;
    msg_lineedit_ = new QLineEdit;

//    QVBoxLayout *io_btn_vlayout = new QVBoxLayout;
//    io_btn_vlayout->addWidget(open_button_);
//    io_btn_vlayout->addWidget(close_button_);

//    QHBoxLayout *up_hlayout = new QHBoxLayout;
//    up_hlayout->addWidget(txt_browser_);
//    up_hlayout->addLayout(io_btn_vlayout);

//    QHBoxLayout *msg_hlayout = new QHBoxLayout;
//    msg_hlayout->addWidget(msg_lineedit_);
//    msg_hlayout->addWidget(send_msg_button_);

//    QVBoxLayout *vlayout = new QVBoxLayout;
//    vlayout->addLayout(up_hlayout);
//    vlayout->addLayout(msg_hlayout);
    road_branch_widget_ = new RoadBranchWidget(this);
//    vlayout->addWidget(road_branch_widget_);

//    setLayout(vlayout);
    QPalette pal;
    pal.setColor(QPalette::Background, QColor(233, 246, 254));
    setPalette(pal);
    resize(560, 560);

//    initLaneList();
}

void TestWindow::initLaneList()
{
    QStringList item_list;
    for (int i = 1; i <= 60; i++)
    {
        item_list.append(QString::number(i));
    }
    for (int i = 0; i < 12; i++)
    {
        QComboBox *cmb = new QComboBox(this);
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
    rect.setRect(280,20,33,26);
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

void TestWindow::initSignalSlots()
{
    connect(open_button_, SIGNAL(clicked()), this, SLOT(openMyComSlot()));
    connect(close_button_, SIGNAL(clicked()), this, SLOT(closeMyComSlot()));
    connect(send_msg_button_, SIGNAL(clicked()), this, SLOT(sendMsgSlot()));
    connect(my_com_, SIGNAL(readyRead()), this, SLOT(readMyComSlot()));
}
