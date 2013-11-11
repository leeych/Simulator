#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <QDateTime>
#include "roadbranchwidget.h"
#include "win_qextserialport.h"
#include "tscparam.h"
#include "mdatabase.h"
#include "phasehandler.h"

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
class SyncCommand;

class TestDlg;


typedef struct BeginMonitorTag
{
    unsigned char channel_id;
    unsigned char status;
}BeginMonitorInfo;

typedef struct CountDownTag
{
    unsigned char ctrl_mode;
    unsigned char stage_id;
    unsigned char light_corlor;
    unsigned char light_time;
    unsigned int phase_ids;
}CountDownInfo;

typedef struct RedYellowGreenTag
{
    unsigned char red;
    unsigned char yellow;
    unsigned char green;

    RedYellowGreenTag() :
        red(0), yellow(0), green(0)
    {}

}RYGArray;

typedef struct LightStatusTag
{
    RYGArray lights[4];
    unsigned char work_mode;
    unsigned char plan_id;
    unsigned int phase_id;
}LightStatusInfo;


class SimulatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimulatorWidget(QWidget *parent = 0);
    ~SimulatorWidget();
    void initialize();

    enum LightColor
    {
        Red = 0,
        Yellow,
        Green,
        Off,
        Invalid
    };

signals:
    void showLightSignal(int index, int color);
    void closeLightSignal();
    void enableDetectorIdCmbSignal(bool);
    void showLaneDetectorSignal(int index, int color, bool show);

public slots:
    void startSimulatorToggledSlot(bool);
    void sendMsgTimerTimeOutSlot();
    void timerTimeOutSlot();
    void openSerialTriggeredSlot(bool);

    void detectorEditButtonClicked();
    void connectButtonClicked();

    void connectEstablishedSlot();
    void disconnectedSlot();
    void connectErrorSlot(const QString&);

    void onCmdGetVerIdSlot(QByteArray &array);
    void onCmdReadConfigFileSlot(QByteArray &array);
    void onCmdParseParam(QByteArray &array);

    void connTimerTimeoutSlot();
    void signalerTimerTimeoutSlot();
    void countDownTimerTimeoutSlot();

protected:
    void closeEvent(QCloseEvent *);
    void timerEvent(QTimerEvent *);

private:
    void initPage();
    void initSignalSlots();
    void initComSettingLayout();
    void initRoadbranchLayout();
    void initScheduleInfoLayout();

    void initCtrlModeDesc();
    bool initTscParam();
    void updateScheduleInfo();
    unsigned char getPhaseType(unsigned char phase_id);
    bool checkLaneId();
    void packComData(int lane_index);
    void initMyComSetting();
    QString formatComData(const QByteArray &array);
    void enableComSetting(bool enable);
    void initPreDetectorColorList();
    void initRedDetectorFlagList();

    bool checkPackage(QByteArray &array);
    bool parseConfigContent(QByteArray &array);
    bool parseBeginMonitorContent(QByteArray &array);
    bool parseLightStatusContent(QByteArray &array);
    bool parseCountDownContent(QByteArray &array);
    bool parseTSCTimeContent(QByteArray &array);
    bool parseAllLightOnContent(QByteArray &array);

    bool parseDetectorFlowContent(QByteArray &array);
    bool parseDetectorFaultContent(QByteArray &array);
    bool parseDriverStatusContent(QByteArray &array);
    bool parseRealTimeFlowContent(QByteArray &array);
    bool parseDriverRealtimeStatusContent(QByteArray &array);
    bool parseLightRealTimeStatusContent(QByteArray &array);

    void simualtorComdataDispatcher();
    void updateDetectorStatus(int detector_index);
    QString phaseBitsDesc(unsigned int phase_ids);
    void dumpComData();
    void test();

private:
    struct PortSettings my_com_setting_;

    QByteArray com_array_;
    int curr_lane_idx_;
    int curr_lane_id_;
    RoadBranchWidget::LightColor curr_color_;
    bool serial_status_;

    QTimer *send_msg_timer_;
    QTimer *timer_;
    bool need_leave_;
    QList<int> lane_id_list_;

    QString ip_;
    int port_;
    QString cfg_file_;
    bool conn_status_;
    int ver_check_id_;  // version check timer id
    bool is_inited_;    // tsc time update flag
    int ui_timer_id_;   // used for signaler time
    bool is_uitimer_started_;

    SyncCommand *sync_cmd_;
    TSCParam tsc_param_;
    QByteArray recv_array_;
    QByteArray cfg_array_;

    QTimer *conn_timer_;
    QTimer *signaler_timer_, *count_down_timer_;
    QDateTime date_time_;

    unsigned char curr_stage_id_;
    unsigned char total_stage_count_;
    unsigned char count_down_secs_;
    unsigned char count_down_light_;

    unsigned char sec_count_;

    BeginMonitorInfo begin_monitor_info_;
    CountDownInfo count_down_info_;
    LightStatusInfo light_status_info_;
    typedef struct ChannelStatusInfoTag
    {
        QVector<LightColor> channel_vec;
        unsigned char work_mode;
        unsigned char stage_id;
        unsigned int phase_id;
    }ChannelStatusInfo;

    ChannelStatusInfo channel_status_info_;
    ChannelStatusInfo channel_status_bak_;  // used for revert lights' status

    QMap<unsigned char, QString> ctrl_mode_desc_map_;
    QList<int> phase_id_list_;
    int pre_lane_idx_;
    QList<RoadBranchWidget::LightColor> pre_detector_color_list_;
    QList<int> detector_red_flag_list_;

    MDatabase *db_ptr_;
    PhaseHandler *phase_handler_;
    bool is_first_;
    bool is_first_send_;

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

    DetectorIdEditWidget *detector_edit_dlg_;
    QLineEdit *ip_lineedit_, *port_lineedit_;
    QLabel *conn_tip_label_;

    TestDlg *test_dlg_;

};

#endif // TESTWINDOW_H
