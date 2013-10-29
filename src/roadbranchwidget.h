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

class RoadBranchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoadBranchWidget(QWidget *parent = 0);
    ~RoadBranchWidget();

signals:

public slots:

private:
    void resizeEvent(QResizeEvent *);

private:
    void initPage();
    void initLaneList();
    void initLightStatus();

private:
    QList<QComboBox *> lane_cmb_list_;
    QList<QRect> rect_list_;
    QList<QLabel *> lane_light_list_;

};

#endif // ROADBRANCHWIDGET_H
