#include "detectorideditwidget.h"
#include "macrostrings.h"
#include "utilmacros.h"

#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QComboBox>
#include <QHeaderView>

#include <QPalette>

#include <QVBoxLayout>
#include <QHBoxLayout>

DetectorIdEditWidget::DetectorIdEditWidget(QWidget *parent) :
    QWidget(parent)
{
    initPage();
    initSignalSlots();
}

DetectorIdEditWidget::~DetectorIdEditWidget()
{

}

void DetectorIdEditWidget::initPage()
{
    setWindowTitle(STRING_UI_DETECTOR_ID_EDIT_TITLE);
    note_label_ = new QLabel(STRING_UI_DETECTOR_ID_EDIT_TITLE);
    tip_label_ = new QLabel;

    initTable();

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

}

void DetectorIdEditWidget::initTable()
{
    detector_id_table_ = new QTableWidget(this);
    detector_id_table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    detector_id_table_->setSelectionBehavior(QTableWidget::SelectRows);
    detector_id_table_->setSelectionMode(QAbstractItemView::SingleSelection);
    SET_HEADER_CLICKABLE(detector_id_table_, false)

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
    headers << STRING_UI_LANE << STRING_UI_SIDEWALK;
    detector_id_table_->setHorizontalHeaderLabels(headers);
    headers.clear();
    headers << STRING_UI_EAST << STRING_UI_SOUTH << STRING_UI_WEST << STRING_UI_NORTH;
    detector_id_table_->setRowCount(4);
    detector_id_table_->setVerticalHeaderLabels(headers);
    detector_id_table_->setShowGrid(true);
    QString qss = "QHeaderView::section{background-color: rgb(184, 219, 255)}";
    detector_id_table_->verticalHeader()->setStyleSheet(qss);
    detector_id_table_->horizontalHeader()->setStyleSheet(qss);

    SET_HEADER_CLICKABLE(detector_id_table_, false)
//    detector_id_table_->horizontalHeader()->setStretchLastSection(true);
}
