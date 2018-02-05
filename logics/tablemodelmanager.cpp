#include "tablemodelmanager.h"

using namespace logics;

TableModelManager::TableModelManager(const RegisterModelIndex &currentModelNum, QObject *parent)
    : QObject(parent)
{
    registerContractsModel = new TableRegisterContractsModel(this);
    registerChecksModel = new TableRegisterChecksModel(this);
    registerProcurementMethodsModel = new TableRegisterProcurementMethodsModel(this);
    if (!registerContractsModel->modelInitialization()
            || !registerChecksModel->modelInitialization()
            || !registerProcurementMethodsModel->modelInitialization())
        throw exceptions::TableModelException(exceptions::TableModelException::ERROR_MODEL_INIT);
    if (!setCurrentModel(currentModelNum))
        throw exceptions::TableModelException(exceptions::TableModelException::ERROR_ABSENCE_MODEL);
}

QSqlQueryModel *TableModelManager::getCurrentModel() const
{
    return currentModel->getModel();
}

bool TableModelManager::changeModel(const RegisterModelIndex &changedModelNum)
{
    if (!setCurrentModel(changedModelNum))
        return false;
    return currentModel->setStartQueryState();
}

bool TableModelManager::deleteColumn(const QModelIndex &index) const
{
    return currentModel->deleteColumn(index);
}

bool TableModelManager::updateModel() const
{
    return currentModel->updateModel();
}

bool TableModelManager::setCurrentModel(const RegisterModelIndex &value)
{
    if (value == RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
        currentModel = registerContractsModel;
    else if (value == RegisterModelIndex::REGISTER_CHECK_MODEL_INDEX)
        currentModel = registerChecksModel;
    else if (value == RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
        currentModel = registerProcurementMethodsModel;
    else
        return false;
    modelIndex = value;
    return true;
}

TableModelManager::RegisterModelIndex TableModelManager::getModelIndex() const
{
    return modelIndex;
}

uint TableModelManager::getColumnEndDateNumber() const
{
    if (modelIndex != RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
        throw exceptions::TableModelException::USING_MODEL_ERROR;
    return registerContractsModel->getColumnEndDateNumber();
}

uint TableModelManager::getColumnCompletenessNumber() const
{
    return currentModel->getCompletenessNumber();
}

uint TableModelManager::getColumnProcedureCompleteNumber() const
{
    if (modelIndex != RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
        throw exceptions::TableModelException::USING_MODEL_ERROR;
    return registerProcurementMethodsModel->getColumnProcedureCompleteNumber();
}

uint TableModelManager::getColumnIdNumber() const
{
    return currentModel->getColumnIdNumber();
}

uint TableModelManager::getColumnSMPNumber() const
{
    if (modelIndex != RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
        throw exceptions::TableModelException::USING_MODEL_ERROR;
    return registerProcurementMethodsModel->getColumnSMPNumber();
}

bool TableModelManager::setStartState() const
{
    return currentModel->setStartQueryState();
}

FindObjectAbstract *TableModelManager::getFindObject()
{
    return currentModel->getFindObject();
}

bool TableModelManager::findQuery(FindObjectAbstract *findObj)
{
    return currentModel->findQuery(findObj);
}
