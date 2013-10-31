#include "testwindow.h"
#include "macrostrings.h"
#include "serialdata.h"
#include "mutility.h"

#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QLabel>
#include <QTime>
#include <QDateTime>
#include <QTimer>
#include <QDebug>

TestWindow::TestWindow(QWidget *parent) :
    QWidget(parent)
{
    struct PortSettings my_com_setting = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 500};
    my_com_ = new Win_QextSerialPort("com1", my_com_setting, QextSerialBase::EventDriven);
    curr_lane_index_ = 0;
    curr_lane_id_ = 0;
    serial_status_ = false;
    send_msg_timer_ = new QTimer(this);
    timer_ = new QTimer(this);
    need_leave_ = false;

    setWindowTitle(STRING_UI_WINDOW_TITLE);
    initPage();
    initSignalSlots();
    setFixedSize(824,606);
    start_button_->setEnabled(false);
}

TestWindow::~TestWindow()
{
    if (timer_ != NULL)
    {
        delete timer_;
        timer_ = NULL;
    }
}

void TestWindow::startSimulatorToggledSlot(bool checked)
{
    if (!checkLaneId())
    {
        start_button_->setChecked(!checked);
        return;
    }
    if (checked)
    {
        emit enableLaneIdCmbSignal(false);
        start_button_->setText(STRING_UI_STOP);
        int secs = timespan_spinbox_->value();
        send_msg_timer_->start(secs*1000);

        QTime t = QTime::currentTime();
        qsrand(t.msec() + t.second()*1000);
        curr_lane_index_ = qrand() % 12;
        emit laneIndexSignal(curr_lane_index_, RoadBranchWidget::Green);
        packComData(curr_lane_index_);
//        test();
        int sz = my_com_->write(com_array_);
        if (need_leave_)
        {
            timer_->start(qrand() % 1000 + 1000);
        }
        txt_edit_->insertPlainText(QString(com_array_.toHex())+"\n");
//        qDebug() << sz;
//        dumpComData();
    }
    else
    {
        start_button_->setText(STRING_UI_START);
        send_msg_timer_->stop();
        timer_->stop();
        emit enableLaneIdCmbSignal(true);
//        emit closeLightSignal();
        road_branch_widget_->closeLightSlot();
    }
}

void TestWindow::sendMsgTimerTimeOutSlot()
{
    if (timer_->isActive())
    {
        return;
    }
    qDebug() << "send msg time out";
    startSimulatorToggledSlot(true);
}

void TestWindow::timerTimeOutSlot()
{
    timer_->stop();
    com_array_[1] = 0x02 + '\0';
    char ms[4] = {'\0'};
    int secs = QDateTime::currentDateTime().toTime_t();
    memcpy(ms, &secs, sizeof(secs));
    com_array_[3] = ms[0];
    com_array_[4] = ms[1];
    txt_edit_->insertPlainText(QString(com_array_.toHex())+"\n");
    emit laneIndexSignal(curr_lane_index_, RoadBranchWidget::Red);
    int sz = my_com_->write(com_array_);
//    qDebug() << "leave timer time out" << endl << sz;
//    dumpComData();
}

void TestWindow::openSerialTriggeredSlot(bool checked)
{
    if (checked)
    {
        open_close_button_->setText(STRING_UI_CLOSE + STRING_UI_SERIALPORT);
        bool status = my_com_->open(QIODevice::ReadWrite);
        serial_status_ = status;
        if (!status)
        {
            QMessageBox::information(this, STRING_TIP, STRING_UI_SERIALPORT + STRING_UI_OPEN + STRING_FAILED, STRING_OK);
            open_close_button_->setChecked(false);
            return;
        }
        else
        {
            open_tip_label_->setText("<font color=\"Red\">OK</font>");
            start_button_->setEnabled(true);
        }
    }
    else
    {
        open_close_button_->setText(STRING_UI_OPEN + STRING_UI_SERIALPORT);
        if (start_button_->isChecked())
        {
            startSimulatorToggledSlot(false);
        }
        my_com_->close();
        open_tip_label_->clear();
        start_button_->setEnabled(false);
    }
}

void TestWindow::closeEvent(QCloseEvent *)
{
    if (timer_->isActive())
    {
        timer_->stop();
    }
    if (send_msg_timer_->isActive())
    {
        send_msg_timer_->stop();
    }
}

void TestWindow::initPage()
{
    QGroupBox *roadbranch_grp = new QGroupBox;
    QHBoxLayout *roadbranch_hlayout = new QHBoxLayout(roadbranch_grp);
    road_branch_widget_ = new RoadBranchWidget(this);
    roadbranch_hlayout->addWidget(road_branch_widget_);
//    roadbranch_hlayout->setSizeConstraint(QLayout::SetFixedSize);
    roadbranch_grp->setLayout(roadbranch_hlayout);

    QLabel *timespan_label = new QLabel(STRING_UI_TIMESPAN + "(s):");
    timespan_spinbox_ = new QSpinBox;
    timespan_spinbox_->setValue(1);
    start_button_ = new QPushButton(STRING_UI_START);
    start_button_->setCheckable(true);
    open_close_button_ = new QPushButton(STRING_UI_OPEN + STRING_UI_SERIALPORT);
    open_close_button_->setCheckable(true);
    open_tip_label_ = new QLabel;
    open_tip_label_->setMinimumWidth(20);
    txt_edit_ = new QTextEdit;
    port_lineedit_ = new QLineEdit;
    baud_rate_lineedit_ = new QLineEdit;
    data_bit_lineedit_ = new QLineEdit;
    stop_lineedit_ = new QLineEdit;
    parity_lineedit_ = new QLineEdit;

    port_lineedit_->setText("com1");
    baud_rate_lineedit_->setText("9600");
    data_bit_lineedit_->setText("8");
    stop_lineedit_->setText("1");
    parity_lineedit_->setText("None");

    port_lineedit_->setReadOnly(true);
    baud_rate_lineedit_->setReadOnly(true);
    data_bit_lineedit_->setReadOnly(true);
    stop_lineedit_->setReadOnly(true);
    parity_lineedit_->setReadOnly(true);

    QGroupBox *illustrate_grp = new QGroupBox;
    QString dir = MUtility::getImagesDir();
    QLabel *green_label = new QLabel;
    green_label->setPixmap(QPixmap(dir + "green_arrow.png"));
    QLabel *green_tip_label = new QLabel(STRING_UI_GREEN_TIP);
    QLabel *red_label = new QLabel;
    red_label->setPixmap(QPixmap(dir + "red_arrow.png"));
    QLabel *red_tip_label = new QLabel(STRING_UI_RED_TIP);

    QGridLayout *illustrate_glayout = new QGridLayout;
    illustrate_glayout->addWidget(green_label, 0, 0, 1, 1, Qt::AlignLeft);
    illustrate_glayout->addWidget(green_tip_label, 0, 1, 1, 1, Qt::AlignLeft);
    illustrate_glayout->addWidget(red_label, 1, 0, 1, 1, Qt::AlignLeft);
    illustrate_glayout->addWidget(red_tip_label, 1, 1, 1, 1, Qt::AlignLeft);
    illustrate_grp->setLayout(illustrate_glayout);

    QGridLayout *glayout = new QGridLayout;
    glayout->addWidget(new QLabel(STRING_UI_PORT + ":"), 0, 0, 1, 1, Qt::AlignCenter);
    glayout->addWidget(new QLabel(STRING_UI_BAUDRATE + ":"), 1, 0, 1, 1, Qt::AlignCenter);
    glayout->addWidget(new QLabel(STRING_UI_DATABIT + ":"), 2, 0, 1, 1, Qt::AlignCenter);
    glayout->addWidget(new QLabel(STRING_UI_STOPBIT + ":"), 3, 0, 1, 1, Qt::AlignCenter);
    glayout->addWidget(new QLabel(STRING_UI_PARITY + ":"), 4, 0, 1, 1, Qt::AlignCenter);

    glayout->addWidget(port_lineedit_, 0, 1, 1, 1, Qt::AlignCenter);
    glayout->addWidget(baud_rate_lineedit_, 1, 1, 1, 1, Qt::AlignCenter);
    glayout->addWidget(data_bit_lineedit_, 2, 1, 1, 1, Qt::AlignCenter);
    glayout->addWidget(stop_lineedit_, 3, 1, 1, 1, Qt::AlignCenter);
    glayout->addWidget(parity_lineedit_, 4, 1, 1, 1, Qt::AlignCenter);
    QGroupBox *param_grp = new QGroupBox;
    param_grp->setLayout(glayout);

    QHBoxLayout *open_hlayout = new QHBoxLayout;
    open_hlayout->addWidget(open_close_button_, 0, Qt::AlignCenter);
    open_hlayout->addWidget(open_tip_label_, 0, Qt::AlignLeft);
    open_hlayout->addStretch(1);
    open_hlayout->addWidget(start_button_, 0, Qt::AlignCenter);

    QHBoxLayout *timespan_hlayout = new QHBoxLayout;
    timespan_hlayout->addWidget(timespan_label, 0, Qt::AlignLeft);
    timespan_hlayout->addWidget(timespan_spinbox_, 0, Qt::AlignLeft);

    QGroupBox *start_grp = new QGroupBox;
    QVBoxLayout *start_vlayout = new QVBoxLayout;
    start_vlayout->addWidget(txt_edit_);
    start_vlayout->addLayout(timespan_hlayout);
    start_vlayout->addLayout(open_hlayout);
    start_grp->setLayout(start_vlayout);

    QGroupBox *edit_grp = new QGroupBox;
    QVBoxLayout *edit_vlayout = new QVBoxLayout(edit_grp);
    edit_vlayout->addWidget(illustrate_grp);
    edit_vlayout->addStretch();
    edit_vlayout->addWidget(param_grp);
    edit_vlayout->addStretch();
    edit_vlayout->addWidget(start_grp);

    edit_grp->setLayout(edit_vlayout);

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(roadbranch_grp, 1);
    hlayout->addWidget(edit_grp, 0);
    hlayout->setStretch(0, 3);
    hlayout->setStretch(1, 1);
    setLayout(hlayout);

    QPalette pal;
    pal.setColor(QPalette::Background, QColor(233, 246, 254));
    setPalette(pal);
    QString qss = "QLineEdit{background-color:rgb(233,246,254);}";
    setStyleSheet(qss);
}

void TestWindow::initSignalSlots()
{
    connect(start_button_, SIGNAL(toggled(bool)), this, SLOT(startSimulatorToggledSlot(bool)));
    connect(this, SIGNAL(laneIndexSignal(int, int)), road_branch_widget_, SLOT(laneIndexSlot(int, int)));
//    connect(this, SIGNAL(closeLightSignal()), road_branch_widget_, SLOT(closeLightSlot()));
    connect(this, SIGNAL(enableLaneIdCmbSignal(bool)), road_branch_widget_, SLOT(enableLaneIdCmbSlot(bool)));
    connect(send_msg_timer_, SIGNAL(timeout()), this, SLOT(sendMsgTimerTimeOutSlot()));
    connect(timer_, SIGNAL(timeout()), this, SLOT(timerTimeOutSlot()));
    connect(open_close_button_, SIGNAL(toggled(bool)), this, SLOT(openSerialTriggeredSlot(bool)));
}

bool TestWindow::checkLaneId()
{
    QList<int> lane_id_list = road_branch_widget_->getLaneIdList();
    if (lane_id_list.contains(0))
    {
        QMessageBox::information(this, STRING_TIP, STRING_UI_EXISTS_INVALID_LANEID, STRING_OK);
        return false;
    }
    return true;
}

void TestWindow::packComData(int lane_index)
{
    com_array_.clear();
    SerialData com_data;
    QList<int> lane_id_list = road_branch_widget_->getLaneIdList();
    curr_lane_id_ = lane_id_list.at(lane_index);
    need_leave_ = false;
    if (curr_lane_id_ >= 1 && curr_lane_id_ <= 48)
    {
        com_data.type = 0x01 + '\0';
        need_leave_ = true;
    }
    else if (curr_lane_id_ <= 56)
    {
        com_data.type = 0x04 + '\0';
    }
    else if (curr_lane_id_ <= 60)
    {
        com_data.type = 0x05 + '\0';
    }
    int secs = QDateTime::currentDateTime().toTime_t();
    memcpy(com_data.ms_time, &secs, 4);

    com_array_.append(com_data.head);
    com_array_.append(com_data.type);
    com_array_.append(com_data.lane_id);
    com_array_.append(com_data.ms_time,2);
    com_array_.append(com_data.tail);

    qDebug() << "lane index:" << lane_index
             << "lane id:" << curr_lane_id_ << endl;
}

void TestWindow::dumpComData()
{
    SerialData com_data;
//    com_data.head = com_array_.at(0);
    com_data.type = com_array_.at(1);
    com_data.lane_id = com_array_.at(2);
    com_data.ms_time[0] = com_array_.at(3);
    com_data.ms_time[1] = com_array_.at(4);
//    com_data.tail = com_array_.at(5);

    int ts = 0;
    memcpy(&ts, com_data.ms_time,4);
    QString head = QString("0x%1").arg(int(com_data.head),0,16);
    QString tail = QString("0x%1").arg(int(com_data.tail),0,16);
    qDebug() << "head:" << head
             << "type:" << com_data.type - '\0'
             << "lane_id:" << com_data.lane_id - '\0'
             << "timespan:" << ts
             << "tail:" << tail
             << endl;
}

void TestWindow::test()
{
//    com_array_.clear();
//    com_array_.append("F10101ed");
    QFile file("test.dat");
    if (!file.open(QIODevice::WriteOnly))
    {
        return;
    }
    file.write(com_array_);
    file.close();
}