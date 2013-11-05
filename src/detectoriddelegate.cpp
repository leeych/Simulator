#include "detectoriddelegate.h"

#include <QComboBox>

DetectorIdDelegate::DetectorIdDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *DetectorIdDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    int col = index.column();
    switch (col)
    {
    case 0:
    case 1:
    case 2:
    {
        QComboBox *cmb = new QComboBox(parent);
        for (int i = 0 ; i < 48; i++)
        {
            cmb->addItem(QString::number(i+1));
        }
        for (int i = 57; i < 61; i++)
        {
            cmb->addItem(QString::number(i));
        }
        cmb->addItem("-");
        return cmb;
    }
        break;
    case 3:
    case 4:
    {
        QComboBox *cmb = new QComboBox(parent);
        for (int i = 48 ; i < 56; i++)
        {
            cmb->addItem(QString::number(i+1));
        }
        cmb->addItem("-");
        return cmb;
    }
        break;
    default:
        return QItemDelegate::createEditor(parent, option, index);
        break;
    }
}

void DetectorIdDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int col = index.column();
    switch (col)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    {
        QComboBox *cmb = qobject_cast<QComboBox *>(editor);
        if (cmb == NULL)
        {
            return;
        }
        int i = cmb->findText(index.model()->data(index, Qt::EditRole).toString());
        cmb->setCurrentIndex(i);
    }
        break;
    default:
        return QItemDelegate::setEditorData(editor, index);
        break;
    }
}

void DetectorIdDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    int col = index.column();
    switch (col)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    {
        QComboBox *cmb = qobject_cast<QComboBox *>(editor);
        if (cmb == NULL)
        {
            return;
        }
        model->setData(index, cmb->currentText());
    }
        break;
    default:
        return QItemDelegate::setModelData(editor, model, index);
        break;
    }
}

void DetectorIdDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
