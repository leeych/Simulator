#ifndef ROADBRANCHWIDGET_H
#define ROADBRANCHWIDGET_H

#include <QWidget>
#include <QList>
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
    QList<int> &getLaneIdList();

    enum LightColor
    {
        Green,
        Red
    };

signals:
    void laneIndexSignal(int);

public slots:
    void cmbItemSelectedSlot(int);
    void flashTimerTimeoutSlot();
    void laneIndexSlot(int index, int color);
    void closeLightSlot();
    void enableLaneIdCmbSlot(bool enable);

private:
    void resizeEvent(QResizeEvent *);

private:
    void initPage();
    void initSignalSlots();
    void initLaneList();
    void initLightStatus();

    void updateFlashLight(int index, LightColor color);

private:
    QList<QComboBox *> lane_cmb_list_;
    QList<QRect> cmb_rect_list_;
    QList<QRect> light_rect_list_;
    QList<QLabel *> lane_light_list_;
    QList<QPixmap *> pixmap_list_;
    QList<int> lane_id_list_;

    QTimer *flash_timer_;
    int curr_index_;        // [1,12] origin index of the roadbranch in realtime monitor

};

#endif // ROADBRANCHWIDGET_H
