#include "procurementmethodstablestyleditemdelegate.h"

using namespace gui;

uint ProcurementMethodsTableStyledItemDelegate::procedureCompleteNumber = 0;
uint ProcurementMethodsTableStyledItemDelegate::smpNumber = 0;

ProcurementMethodsTableStyledItemDelegate::ProcurementMethodsTableStyledItemDelegate(QObject *parent)
    : CompletenessStyledItemDelegate(parent)
{}

uint ProcurementMethodsTableStyledItemDelegate::getProcedureCompleteNumber()
{
    return procedureCompleteNumber;
}

void ProcurementMethodsTableStyledItemDelegate::setProcedureCompleteNumber(const uint &value)
{
    procedureCompleteNumber = value;
}

uint ProcurementMethodsTableStyledItemDelegate::getSmpNumber()
{
    return smpNumber;
}

void ProcurementMethodsTableStyledItemDelegate::setSmpNumber(const uint &value)
{
    smpNumber = value;
}

void ProcurementMethodsTableStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    painter->setPen(Qt::black);
    if (index.column() == static_cast<int>(getProcedureCompleteNumber()))
    {
        CompletenessStyledItemDelegate::paintWithoutText(painter, option, index);
        QString text = index.data().toBool() ? tr("Состоялась") : tr("Несостоялась");
        painter->drawText(option.rect, option.displayAlignment, text);
    }
    else if (index.column() == static_cast<int>(getSmpNumber()))
    {
        CompletenessStyledItemDelegate::paintWithoutText(painter, option, index);
        QString text = index.data().toBool() ? tr("СМП") : tr("Не СМП");
        painter->drawText(option.rect, option.displayAlignment, text);
    }
    else
        CompletenessStyledItemDelegate::paint(painter, option, index);
    painter->restore();
}
