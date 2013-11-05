#ifndef DETECTORIDEDITWIDGET_H
#define DETECTORIDEDITWIDGET_H

#include <QWidget>
#include <QDialog>
//#include "detectoriddelegate.h"

class QTableWidget;
class QLabel;
class QComboBox;
class QPushButton;
class QTableWidgetItem;

class DetectorIdDelegate;

class DetectorIdEditWidget : public QDialog
{
    Q_OBJECT
public:
    explicit DetectorIdEditWidget(QWidget *parent = 0);
    ~DetectorIdEditWidget();

signals:

public slots:
    void OnOkButtonClicked();
    void OnCancelButtonClicked();
    void OnTableItemEditedSlot(QTableWidgetItem*);

private:
    void initPage();
    void initSignalSlots();

    void initTable();
    void initTableHeader();
    void initTableItem();

private:
    DetectorIdDelegate *table_delegate_;
    QTableWidget *detector_id_table_;
    QLabel *tip_label_, *note_label_;

    QPushButton *ok_button_, *cancel_button_;

    QList<QComboBox *> lane_cmb_list_;
    QList<QComboBox *> pedestrian_cmb_list_;
};

#endif // DETECTORIDEDITWIDGET_H
