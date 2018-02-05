#include "completenessstyleditemdelegate.h"

using namespace gui;

uint CompletenessStyledItemDelegate::completenessNumber = 0;

CompletenessStyledItemDelegate::CompletenessStyledItemDelegate(QObject *parent)
    : TableStyledItemDelegate(parent)
{}

void CompletenessStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    paintWithoutText(painter, option, index);
    painter->save();
    painter->setPen(Qt::black);
    if (index.column() == static_cast<int>(getCompletenessNumber()))
        drawText(painter, option, index);
    else
        TableStyledItemDelegate::drawText(painter, option, index);
    painter->restore();
}

uint CompletenessStyledItemDelegate::getCompletenessNumber()
{
    return completenessNumber;
}

void CompletenessStyledItemDelegate::setCompletenessNumber(const uint &value)
{
    completenessNumber = value;
}

void CompletenessStyledItemDelegate::drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setPen(Qt::black);
    if (index.column() == static_cast<int>(getCompletenessNumber()))
    {
        QString text = index.data().toBool() ? tr("Завершенный") : tr("Действующий");
        painter->drawText(option.rect, option.displayAlignment, text);
    }
    else
        TableStyledItemDelegate::drawText(painter, option, index);
    painter->restore();
}

void CompletenessStyledItemDelegate::paintWithoutText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());
    else
    {
        QBrush brush = option.backgroundBrush;
        QColor color(0, 0, 0);
        if (index.sibling(index.row(), completenessNumber).data().toBool())
            color = {255, 255, 255};
        else
            color = {0, 255, 0};
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        painter->setPen(Qt::black);
        brush.setColor(color);
        painter->fillRect(option.rect, brush);
    }
    painter->restore();
}
