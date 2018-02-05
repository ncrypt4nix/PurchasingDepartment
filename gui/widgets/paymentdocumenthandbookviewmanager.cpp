#include "paymentdocumenthandbookviewmanager.h"

using namespace gui;

PaymentDocumentHandBookViewManager::PaymentDocumentHandBookViewManager(QWidget *parent)
    : HandBookViewManager(parent)
{
}

void PaymentDocumentHandBookViewManager::setHandBookManager(logics::HandBookManager *value)
{
    HandBookViewManager::setHandBookManager(value);
    connect(handBookManager, SIGNAL(paymentDocumentsChanged()), this, SLOT(paymentDocumentChange()));
    paymentDocumentChange();
}

void PaymentDocumentHandBookViewManager::resetOldData()
{
    HandBookViewManager::resetOldData();
    paymentDocumentBox->setCurrentIndex(DEFAULT_VALUE);
}

bool PaymentDocumentHandBookViewManager::checkData()
{
    if (!HandBookViewManager::checkData()
            || paymentDocumentBox->currentIndex() == DEFAULT_VALUE)
        return false;
    return true;
}

void PaymentDocumentHandBookViewManager::paymentDocumentChange()
{
    changeBox(paymentDocumentBox, logics::HandBookManager::ModelIndex::PAYMENT_DOCUMENTS_INDEX);
}
