#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include <QList>
#include <QDateTime>
#include "roadbranchwidget.h"
#include "win_qextserialport.h"

class QTextEdit;
class QTextBrowser;
class QPushButton;
class QLineEdit;
class QComboBox;
class QSpinBox;
class QLabel;
class QGroupBox;
class QLCDNumber;
class QTimer;

class DetectorIdEditWidget;

class TestWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TestWindow(QWidget *parent = 0);
    ~TestWindow();

signals:
    void laneIndexSignal(int index, int color);
    void closeLightSignal();
    void enableLaneIdCmbSignal(bool);

public slots:
    void startSimulatorToggledSlot(bool);
    void sendMsgTimerTimeOutSlot();
    void timerTimeOutSlot();
    void openSerialTriggeredSlot(bool);

    void detectorEditButtonClicked();
    void connectButtonClicked();

private:
    void closeEvent(QCloseEvent *);

private:
    void initPage();
    void initSignalSlots();
    void initComSettingLayout();
    void initRoadbranchLayout();
    void initScheduleInfoLayout();

    bool checkLaneId();
    void packComData(int lane_index);
    void initMyComSetting();
    QString formatComData(const QByteArray &array);

    void enableComSetting(bool enable);

    void dumpComData();
    void test();

private:
    struct PortSettings my_com_setting_;

    QByteArray com_array_;
    int curr_lane_index_;
    int curr_lane_id_;
    bool serial_status_;

    QTimer *send_msg_timer_;
    QTimer *timer_;
    bool need_leave_;
    QList<int> lane_id_list_;

private:
    QComboBox *port_cmb_, *baud_rate_cmb_, *data_bit_cmb_, *stop_cmb_, *parity_cmb_;
    QTextEdit *txt_edit_;
    QSpinBox *timespan_spinbox_;
    QPushButton *open_close_button_, *start_button_;
    QLabel *open_tip_label_;

    Win_QextSerialPort *my_com_;
    RoadBranchWidget *road_branch_widget_;

    QGroupBox *com_setting_grp_, *roadbranch_grp_, *schedule_grp_;

    QLabel *sched_id_label_, *event_id_label_, *start_time_label_, *cycle_time_label_;
    QLabel *ctrl_mode_label_, *stage_id_label_, *curr_phase_id_label_, *signaler_time_label_;
    QLCDNumber *count_down_lcd_;
    QPushButton *conn_button_;
    QPushButton *detector_cfg_button_;

    DetectorIdEditWidget *detector_edit_widget_;

};

#endif // TESTWINDOW_H
