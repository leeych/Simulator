#ifndef DETECTORIDEDITWIDGET_H
#define DETECTORIDEDITWIDGET_H

#include <QWidget>

class QTableWidget;
class QLabel;
class QComboBox;
class QPushButton;

class DetectorIdEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DetectorIdEditWidget(QWidget *parent = 0);
    ~DetectorIdEditWidget();

signals:

public slots:

private:
    void initPage();
    void initSignalSlots();

    void initTable();
    void initTableHeader();

private:
    QTableWidget *detector_id_table_;
    QLabel *tip_label_, *note_label_;

    QPushButton *ok_button_, *cancel_button_;
};

#endif // DETECTORIDEDITWIDGET_H
