#ifndef ROADBRANCHWIDGET_H
#define ROADBRANCHWIDGET_H

#include <QWidget>
#include <QList>
#include <QMap>
#include <QRect>

class QLineEdit;
class QPushButton;
class QLabel;
class QPixmap;
class QComboBox;
class QTimer;

class RoadBranchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoadBranchWidget(QWidget *parent = 0);
    ~RoadBranchWidget();
    QList<int> &getLaneDetectorIdList();
    QList<int> &getSidewalkDetectorIdList();
    QMap<int,int> &getLaneDetectorIdIndexMap();
    QMap<int,int> &getSidewalkDetectorIdIndexMap();
//    QMap<int,int> getLightIdIndexMap();

    enum LightColor
    {
        Red = 0,
        Yellow,
        Green,
        Off,
        Invalid
    };
    enum SidewalkId
    {
        SId_13 = 13,
        SId_14,
        SId_15,
        SId_16
    };

signals:
    void laneIndexSignal(int);
    void redDetectorSignal(int detector_id);

public slots:
    void laneDetectorcmbItemSelectedSlot(int);
    void sidewalkcmbItemSelectedSlot(int);
    void flashTimerTimeoutSlot();
    void laneIndexSlot(int index, int color);
    void closeLightSlot();
    void enableDetectorIdCmbSlot(bool enable);
    void showDetectorSlot(int id, int color, bool show);

private:
    void initPage();
    void initSignalSlots();
    void initLaneDetectorList();
    void initLightStatus();
    void initSidewalkDetectorList();

    void initLightList();

    void updateLaneLight(int id, LightColor color);

    void showLaneDetector(int id, LightColor color, bool show);
    void showSidewalkDetector(int index, bool show);

private:
    QList<QRect> light_rect_list_;
    QList<QLabel *> lane_light_list_;
    QList<QPixmap *> pixmap_list_;

    QList<int> lane_detector_id_list_;
    QList<QComboBox *> lane_cmb_list_;
    QList<QRect> cmb_rect_list_;

    QList<QRect> sidewalk_light_rect_list_;
    QList<QLabel *> sidewalk_light_label_list_;

    QTimer *flash_timer_;
    int curr_index_;        // [1,12] origin index of the roadbranch in realtime monitor

    QList<QRect> detector_rect_list_;
    QList<QLabel *> detector_label_list_;
    QList<QPixmap *> detector_pixmap_list_;

    QList<QLabel *> sidewalk_label_list_;
    QList<QPixmap *> sidewalk_pixmap_list_;
    QList<QRect> sidewalk_rect_list_;
    QList<QComboBox *> sidewalk_cmb_list_;
    QList<QRect> sidewalk_cmb_rect_list_;

    QList<int> sidewalk_detector_id_list_;

    // QMap<int id, int index>
    QMap<int, int> light_map_;
    QMap<int, int> lane_detector_map_;
    QMap<int, int> sidewalk_detector_map_;

};

#endif // ROADBRANCHWIDGET_H
