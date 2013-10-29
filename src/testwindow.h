#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <QWidget>
#include <QList>
#include "win_qextserialport.h"

class QTextEdit;
class QTextBrowser;
class QPushButton;
class QLineEdit;
class QComboBox;

class RoadBranchWidget;

class TestWindow : public QWidget
{
    Q_OBJECT
public:
    explicit TestWindow(QWidget *parent = 0);

signals:

public slots:
    void openMyComSlot();
    void closeMyComSlot();
    void sendMsgSlot();
    void readMyComSlot();


private:
    void initPage();
    void initLaneList();
    void initSignalSlots();

private:
    QTextBrowser *txt_browser_;

    QPushButton *open_button_, *close_button_, *send_msg_button_;
    QLineEdit *msg_lineedit_;

    Win_QextSerialPort *my_com_;
    RoadBranchWidget *road_branch_widget_;

    QList<QComboBox *> lane_cmb_list_;
    QList<QRect> rect_list_;

};

#endif // TESTWINDOW_H
