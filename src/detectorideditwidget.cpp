#include "detectorideditwidget.h"
#include "detectoriddelegate.h"
#include "macrostrings.h"
#include "utilmacros.h"

#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QHeaderView>
#include <QPalette>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

DetectorIdEditWidget::DetectorIdEditWidget(QWidget *parent) :
    QDialog(parent)
{
    initPage();
    initSignalSlots();
    resize(650, 260);

    table_delegate_ = new DetectorIdDelegate(detector_id_table_);
    detector_id_table_->setItemDelegate(table_delegate_);
}

DetectorIdEditWidget::~DetectorIdEditWidget()
{

}

void DetectorIdEditWidget::OnOkButtonClicked()
{
    close();
}

void DetectorIdEditWidget::OnCancelButtonClicked()
{
    close();
}

void DetectorIdEditWidget::OnTableItemEditedSlot(QTableWidgetItem *item)
{
    if (item == NULL)
    {
        return;
    }
    int row_cnt = detector_id_table_->rowCount();
    int col_cnt = detector_id_table_->columnCount();
    QList<int> detector_id_list;
    for (int i = 0; i < row_cnt; i++)
    {
        for (int j = 0; j < col_cnt; j++)
        {
            int detector_id = detector_id_table_->item(i,j)->text().toInt();
            detector_id_list.append(detector_id);
        }
    }
    int id = item->text().toInt();
    if (detector_id_list.contains(id))
    {
        QMessageBox::information(this, STRING_TIP, STRING_UI_ASSIGNED + STRING_UI_OTHER + STRING_UI_LANE, STRING_OK);
        item->setText("-");
        return;
    }
}

void DetectorIdEditWidget::initPage()
{
    setWindowTitle(STRING_UI_DETECTOR_ID_EDIT_TITLE);
    note_label_ = new QLabel(STRING_UI_DETECTOR_ID_EDIT_TITLE);
    tip_label_ = new QLabel;

    initTable();
    initTableItem();

    ok_button_ = new QPushButton(STRING_OK);
    cancel_button_ = new QPushButton(STRING_CANCEL);
    QHBoxLayout *button_hlayout = new QHBoxLayout;
    button_hlayout->addStretch(2);
    button_hlayout->addWidget(ok_button_);
    button_hlayout->addWidget(cancel_button_);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(note_label_);
    vlayout->addWidget(detector_id_table_);
    vlayout->addLayout(button_hlayout);
    setLayout(vlayout);
}

void DetectorIdEditWidget::initSignalSlots()
{
    connect(ok_button_, SIGNAL(clicked()), this, SLOT(OnOkButtonClicked()));
    connect(cancel_button_, SIGNAL(clicked()), this, SLOT(OnCancelButtonClicked()));
    connect(detector_id_table_, SIGNAL(itemDoubleClicked(QTableWidgetItem*)), this, SLOT(OnTableItemEditedSlot(QTableWidgetItem*)));
}

void DetectorIdEditWidget::initTable()
{
    detector_id_table_ = new QTableWidget(this);
//    detector_id_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    detector_id_table_->setSelectionBehavior(QTableWidget::SelectRows);
    detector_id_table_->setSelectionMode(QAbstractItemView::SingleSelection);
    SET_HEADER_CLICKABLE(detector_id_table_, horizontal, false)
    SET_HEADER_CLICKABLE(detector_id_table_, vertical, false)

    QPalette pal;
    pal.setColor(QPalette::Base, QColor(233, 246, 254));
    detector_id_table_->setPalette(pal);
//    detector_id_table_->verticalHeader()->setHidden(true);
    detector_id_table_->clearFocus();
    detector_id_table_->setContextMenuPolicy(Qt::CustomContextMenu);
    initTableHeader();
}

void DetectorIdEditWidget::initTableHeader()
{
    detector_id_table_->setColumnCount(5);
    detector_id_table_->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    detector_id_table_->setColumnWidth(0, 120);
    detector_id_table_->setColumnWidth(1, 120);
    detector_id_table_->setColumnWidth(2, 120);
    detector_id_table_->setColumnWidth(3, 120);
    detector_id_table_->setColumnWidth(4, 120);
    QStringList headers;
    headers << STRING_UI_LANE + "1" << STRING_UI_LANE + "2" << STRING_UI_LANE + "3"
            << STRING_UI_SIDEWALK + "1" << STRING_UI_SIDEWALK + "2";
    detector_id_table_->setHorizontalHeaderLabels(headers);
    headers.clear();
    headers << STRING_UI_EAST << STRING_UI_SOUTH << STRING_UI_WEST << STRING_UI_NORTH;
    detector_id_table_->setRowCount(4);
    detector_id_table_->setRowHeight(0, 40);
    detector_id_table_->setRowHeight(1, 40);
    detector_id_table_->setRowHeight(2, 40);
    detector_id_table_->setRowHeight(3, 40);
    detector_id_table_->setVerticalHeaderLabels(headers);
    detector_id_table_->setShowGrid(true);
    QString qss = "QHeaderView::section{background-color: rgb(184, 219, 255)}";
    detector_id_table_->verticalHeader()->setStyleSheet(qss);
    detector_id_table_->horizontalHeader()->setStyleSheet(qss);

    SET_HEADER_CLICKABLE(detector_id_table_, horizontal, false)
    SET_HEADER_CLICKABLE(detector_id_table_, vertical, false)
            //    detector_id_table_->horizontalHeader()->setStretchLastSection(true);
}

void DetectorIdEditWidget::initTableItem()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            QTableWidgetItem *item = new QTableWidgetItem;
            item->setText(QString::number(i));
            detector_id_table_->setItem(i, j, item);
        }
    }
}
