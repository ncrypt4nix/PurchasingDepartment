#include "tablestyleditemdelegate.h"

using namespace gui;

const QString TableStyledItemDelegate::DATE_FORMAT = "dd.MM.yyyy";

TableStyledItemDelegate::TableStyledItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

void TableStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.data().type() == QVariant::Type::Date
            || index.data().type() == QVariant::Type::Double)
    {
        QStyledItemDelegate::paint(painter, option, QModelIndex());
        drawText(painter, option, index);
    }
    else
        QStyledItemDelegate::paint(painter, option, index);
}

void TableStyledItemDelegate::drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QString text = index.data().toString();
    if (index.data().type() == QVariant::Type::Date)
        text = index.data().toDate().toString(DATE_FORMAT);
    else if (index.data().type() == QVariant::Type::Double)
        text = QString::number(index.data().toDouble(), 'f', 2);

    painter->drawText(option.rect, option.displayAlignment, text);
}
