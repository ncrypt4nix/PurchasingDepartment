#include "procurementmethodshandbookviewmanager.h"

using namespace gui;

ProcurementMethodsHandBookViewManager::ProcurementMethodsHandBookViewManager(QWidget *parent) :
    HandBookViewManagerAbstract(parent)
{
}

void ProcurementMethodsHandBookViewManager::setHandBookManager(logics::HandBookManager *value)
{
    HandBookViewManagerAbstract::setHandBookManager(value);
    connect(handBookManager, SIGNAL(procurementMethodsChanged()), this, SLOT(procurementMethodsChange()));
    procurementMethodsChange();
}

void ProcurementMethodsHandBookViewManager::resetOldData()
{
    procurementMethodsBox->setCurrentIndex(DEFAULT_VALUE);
}

bool ProcurementMethodsHandBookViewManager::checkData()
{
    if (procurementMethodsBox->currentIndex() == DEFAULT_VALUE)
        return false;
    return true;
}

void ProcurementMethodsHandBookViewManager::procurementMethodsChange()
{
    changeBox(procurementMethodsBox, logics::HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX);
}
