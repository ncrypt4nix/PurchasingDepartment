#include "findobjectabstract.h"

using namespace logics;

/* FindObjectAbstract */

FindObjectAbstract::FindObjectAbstract(QObject *parent) :
    QObject(parent)
{}

/* FindField */

FindObjectAbstract::FindField::FindField()
{}

bool FindObjectAbstract::FindField::isChanged() const
{
    return changed;
}

QVariant FindObjectAbstract::FindField::getFindValue() const
{
    return findValue;
}

void FindObjectAbstract::FindField::setFindValue(const QVariant &value)
{
    findValue = value;
    changed = true;
}

