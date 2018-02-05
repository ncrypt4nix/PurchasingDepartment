#include "handbookviewmanager.h"

using namespace gui;

HandBookViewManager::HandBookViewManager(QWidget *parent) 
    : HandBookViewManagerAbstract(parent)
{
}

void HandBookViewManager::setHandBookManager(logics::HandBookManager *value)
{
    HandBookViewManagerAbstract::setHandBookManager(value);
    connect(handBookManager, SIGNAL(providersChanged()), this, SLOT(providersChange()));
    connect(handBookManager, SIGNAL(subdivisionsChanged()), this, SLOT(subdivisionsChange()));
    connect(handBookManager, SIGNAL(responsiblesChanged()), this, SLOT(responsiblesChange()));
    connect(handBookManager, SIGNAL(sourcesFinancingChanged()), this, SLOT(sourcesFinancingChange()));

    providersChange();
    subdivisionsChange();
    responsiblesChange();
    sourcesFinancingChange();
}

void HandBookViewManager::resetOldData()
{
    providersBox->setCurrentIndex(DEFAULT_VALUE);
    subdivisionsBox->setCurrentIndex(DEFAULT_VALUE);
    responsiblesBox->setCurrentIndex(DEFAULT_VALUE);
    sourcesFinancingBox->setCurrentIndex(DEFAULT_VALUE);
}

bool HandBookViewManager::checkData()
{
    if (providersBox->currentIndex() == DEFAULT_VALUE
            || subdivisionsBox->currentIndex() == DEFAULT_VALUE
            || responsiblesBox->currentIndex() == DEFAULT_VALUE
            || sourcesFinancingBox->currentIndex() == DEFAULT_VALUE)
        return false;
    return true;
}

void HandBookViewManager::providersChange()
{
    changeBox(providersBox, logics::HandBookManager::ModelIndex::PROVIDERS_INDEX);
}

void HandBookViewManager::subdivisionsChange()
{
    changeBox(subdivisionsBox, logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX);
}

void HandBookViewManager::responsiblesChange()
{
    changeBox(responsiblesBox, logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX);
}

void HandBookViewManager::sourcesFinancingChange()
{
    changeBox(sourcesFinancingBox, logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX);
}
