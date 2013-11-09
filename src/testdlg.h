#ifndef TESTDLG_H
#define TESTDLG_H

#include <QDialog>

class QPushButton;
class QLineEdit;
class QComboBox;
class RoadBranchWidget;

class TestDlg : public QDialog
{
    Q_OBJECT
public:
    explicit TestDlg(QWidget *parent = 0);
    void setPtr(RoadBranchWidget *ptr);

signals:
    void showChannelLightSignal(int channel_id, int color);
    void showLaneDetectorSignal(int id, int color, bool show);
    void showSidewalkDetectorSignal(int id, int color, bool show);
    void sendNetworkByteArray(QByteArray &array);

public slots:
    void OnOKButtonClicked();
    void OnOffButtonClicked();

    void OnLaneDetectorButtonClicked();
    void OnCancelLDetectorButtonClicked();
    void OnSidewalkDetectorButtonClicked();
    void OnCancelSDetectorButtonClicked();

    void OnGenDataButtonClicked();
    void OnReadDataButtonClicked();

private:
    void initPage();
    void initSignalSlots();

private:
    QPushButton *ok_button_, *off_button_;
    QPushButton *lane_detector_button_, *cancel_lane_d_button_, *sidewalk_detector_button_, *cancel_sidewalk_d_button_;
    QPushButton *gen_data_button_, *read_test_button_;
    QComboBox *color_cmb_;
    QComboBox *channel_id_cmb_;

    RoadBranchWidget *widget_;
};

#endif // TESTDLG_H
