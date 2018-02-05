#include "handbook.h"

using namespace logics;

const QString HandBookManager::PROVIDERS_OBJECT_NAME = "ProvidersHandBook";
const QString HandBookManager::SUBDIVISIONS_OBJECT_NAME = "SubdivisionsHandBook";
const QString HandBookManager::RESPONSIBLES_OBJECT_NAME = "ResponsiblesHandBook";
const QString HandBookManager::SOURCES_FINANCING_OBJECT_NAME = "SourcesFinancingHandBook";
const QString HandBookManager::PAYMENT_DOCUMENTS_OBJECT_NAME = "PaymentDocumentsHandBook";
const QString HandBookManager::PROCUREMENT_METHODS_OBJECT_NAME = "ProcurementMethodsHandBook";

HandBookManager::HandBookManager(QObject *parent)
    : QObject(parent)
{
    providers = new ProvidersHandBook(this);
    subdivisions = new SubdivisionsHandBook(this);
    responsibles = new ResponsiblesHandBook(this);
    sourcesFinancing = new SourcesFinancingHandBook(this);
    paymentDocuments = new PaymentDocumentsHandBook(this);
    procurementMethods = new ProcurementMethodsHandBook(this);

    if (!providers->modelInitialization()
            || !subdivisions->modelInitialization()
            || !responsibles->modelInitialization()
            || !sourcesFinancing->modelInitialization()
            || !paymentDocuments->modelInitialization()
            || !procurementMethods->modelInitialization())
        throw exceptions::TableModelException::ERROR_MODEL_INIT;

    providers->setObjectName(PROVIDERS_OBJECT_NAME);
    subdivisions->setObjectName(SUBDIVISIONS_OBJECT_NAME);
    responsibles->setObjectName(RESPONSIBLES_OBJECT_NAME);
    sourcesFinancing->setObjectName(SOURCES_FINANCING_OBJECT_NAME);
    paymentDocuments->setObjectName(PAYMENT_DOCUMENTS_OBJECT_NAME);
    procurementMethods->setObjectName(PROCUREMENT_METHODS_OBJECT_NAME);

    connect(providers, SIGNAL(mapHandBookChanged()), this, SLOT(modelChanged()));
    connect(subdivisions, SIGNAL(mapHandBookChanged()), this, SLOT(modelChanged()));
    connect(responsibles, SIGNAL(mapHandBookChanged()), this, SLOT(modelChanged()));
    connect(sourcesFinancing, SIGNAL(mapHandBookChanged()), this, SLOT(modelChanged()));
    connect(paymentDocuments, SIGNAL(mapHandBookChanged()), this, SLOT(modelChanged()));
    connect(procurementMethods, SIGNAL(mapHandBookChanged()), this, SLOT(modelChanged()));
}

QSqlTableModel *HandBookManager::getCurrentModel() const
{
    return currentModel;
}

QSqlTableModel *HandBookManager::getModelIndex(const ModelIndex &modelIndex)
{
    if (!setCurrentModel(modelIndex))
        throw exceptions::TableModelException::ERROR_ABSENCE_MODEL;
    return currentModel;
}

int HandBookManager::getColumnIdIndex() const
{
    return currentModel->COLUMN_ID_INDEX;
}

bool HandBookManager::setCurrentModel(const ModelIndex &modelIndex)
{
    try
    {
        currentModel = getModelInIndex(modelIndex);
    }
    catch (exceptions::TableModelException &tm_exc)
    {
        qDebug() << tm_exc.getErrorMessage();
        return false;
    }
    return true;
}

bool HandBookManager::removeRow(const uint &row) const
{
    if (!currentModel->removeRows(row, 1) || !currentModel->submitAll())
    {
        currentModel->revertAll();
        qDebug() << currentModel->lastError();
        return false;
    }
    return true;
}

bool HandBookManager::updateModel() const
{
    if (!currentModel->select())
    {
        qDebug() << currentModel->lastError();
        return false;
    }
    return currentModel->updateMap();
}

bool HandBookManager::addRow(const QString &value) const
{
    if (value.isEmpty())
        return false;
    QString foundValue = value.toLower();
    for(int i = 0; i < currentModel->rowCount(); i++)
    {
        QModelIndex index = currentModel->index(i, currentModel->COLUMN_VALUE_INDEX);
        if(currentModel->data(index).toString().toLower() == foundValue)
            return false;
    }

    if (!currentModel->insertRow(0)
            || !currentModel->setData(currentModel->index(0, currentModel->COLUMN_VALUE_INDEX), value)
            || !currentModel->submitAll())
    {
        qDebug() << currentModel->lastError();
        return false;
    }
    return true;
}

void HandBookManager::setFilter(const QString value)
{
    currentModel->setApproximateFilter(value);
}

void HandBookManager::cancelFilter()
{
    currentModel->setApproximateFilter("");
}

QMap<QString, uint> HandBookManager::getMapHandBook(const ModelIndex &modelIndex) const
{
    return getModelInIndex(modelIndex)->getMapHandBook();
}

HandBookAbstract *HandBookManager::getModelInIndex(const ModelIndex &modelIndex) const
{
    if (modelIndex == ModelIndex::PROVIDERS_INDEX)
        return providers;
    else if (modelIndex == ModelIndex::SUBDIVISIONS_INDEX)
        return subdivisions;
    else if (modelIndex == ModelIndex::RESPONSIBLES_INDEX)
        return responsibles;
    else if (modelIndex == ModelIndex::SOURCES_FINANCING_INDEX)
        return sourcesFinancing;
    else if (modelIndex == ModelIndex::PAYMENT_DOCUMENTS_INDEX)
        return paymentDocuments;
    else if (modelIndex == ModelIndex::PROCUREMENT_METHODS_INDEX)
        return procurementMethods;
    else
        throw exceptions::TableModelException::ERROR_ABSENCE_MODEL;
}

void HandBookManager::modelChanged()
{
    QString objName =  sender()->objectName();
    if (objName == PROVIDERS_OBJECT_NAME)
        emit providersChanged();
    else if (objName == SUBDIVISIONS_OBJECT_NAME)
        emit subdivisionsChanged();
    else if (objName == RESPONSIBLES_OBJECT_NAME)
        emit responsiblesChanged();
    else if (objName == SOURCES_FINANCING_OBJECT_NAME)
        emit sourcesFinancingChanged();
    else if (objName == PAYMENT_DOCUMENTS_OBJECT_NAME)
        emit paymentDocumentsChanged();
    else if (objName == PROCUREMENT_METHODS_OBJECT_NAME)
        emit procurementMethodsChanged();
    else
        qDebug() << tr("Отсутствующий обьект в списке обработки обьектов модели");
}
