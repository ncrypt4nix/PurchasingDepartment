#include "contacttablestyleditemdelegate.h"

using namespace gui;

uint ContactTableStyledItemDelegate::numberDate = 0;
uint ContactTableStyledItemDelegate::numberId = 0;
int ContactTableStyledItemDelegate::DIFFERENCES_DAYS = 3;

ContactTableStyledItemDelegate::ContactTableStyledItemDelegate(QObject *parent)
    : CompletenessStyledItemDelegate(parent)
{}

void ContactTableStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    DIFFERENCES_DAYS = logics::SettingApp::getSettingApp().getWarningExpirationContract();
    painter->save();
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());
    else
    {
        QBrush brush = option.backgroundBrush;
        QDate dateInColumn = index.sibling(index.row(), numberDate).data().toDate();
        uint idColumn = index.sibling(index.row(), numberId).data().toUInt();
        bool checkId = logics::InformationEndContracts::checkId(idColumn);
        QColor color(0, 0, 0);
        if (QDate::currentDate() > dateInColumn && !checkId)
            color = {255, 255, 255};
        else if ((dateInColumn.addDays(-DIFFERENCES_DAYS) <= QDate::currentDate()
                 && !logics::InformationEndContracts::deletedId(idColumn))
                 || checkId)
        {
            color = {255, 0, 0};
            if (!checkId)
            {
                logics::InformationEndContracts::addId(idColumn);
                logics::InformationEndContracts::save();
            }
        }
        else
            color = {0, 255, 0};
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        painter->setPen(Qt::black);
        brush.setColor(color);
        painter->fillRect(option.rect, brush);
    }
    CompletenessStyledItemDelegate::drawText(painter, option, index);
    painter->restore();
}

void ContactTableStyledItemDelegate::setNumberDate(const uint &value)
{
    numberDate = value;
}

uint ContactTableStyledItemDelegate::getNumberDate()
{
    return numberDate;
}

uint ContactTableStyledItemDelegate::getNumberId()
{
    return numberId;
}

void ContactTableStyledItemDelegate::setNumberId(const uint &value)
{
    numberId = value;
}

