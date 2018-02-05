#include "tableregistercontractsmodel.h"

using namespace logics;

TableRegisterContractsModel::TableRegisterContractsModel(QObject *parent)
    : TableModelAbstract(parent)
{}

bool TableRegisterContractsModel::modelInitialization()
{
    if (!setStartQueryState())
        return false;
    setColumnIdNumber(0);
    columnEndDateNumber = 6;
    QStringList columnNames;
    columnNames << tr("№")
               << ContractObject::CONTRACT_NUMBER_STR
               << ContractObject::CONTRACTS_SUM_STR
               << ContractObject::DISBURSED_STR
               << ContractObject::BALANCE_STR
               << ContractObject::START_DATE_STR
               << ContractObject::END_DATE_STR
               << ContractObject::CONCLUSION_DATE_STR
               << ContractObject::DATE_REGISTRATION_STR
               << ContractObject::PROVIDERS_STR
               << ContractObject::SOURCE_FINANCINGS_STR
               << ContractObject::SUBDIVISIONS_STR
               << ContractObject::RESPONSIBLES_STR
               << ContractObject::COMPLETENESS_STR
               << ContractObject::COMMENT_STR;
    setCompletenessNumber(13);

    for (int i = 0; i < columnNames.size(); i++)
        model->setHeaderData(i, Qt::Horizontal, columnNames.at(i));

    return isNotValidLastError("Инициализация модели");
}

bool TableRegisterContractsModel::deleteColumn(const QModelIndex& index) const
{
    auto contractId = index.sibling(index.row(), getColumnIdNumber()).data().toInt();
    QSqlQuery query;
    query.prepare("DELETE FROM register_contracts WHERE contract_id = :contract_id");
    query.bindValue(":contract_id", contractId);
    query.exec();
    return isNotValidLastError(query, "Ошибка удаления");
}

bool TableRegisterContractsModel::setStartQueryState() const
{
    model->setQuery("SELECT contracts.contract_id,"
                            "contracts.contract_number,"
                            "contracts.contracts_sum,"
                            "SUM(checks.check_sum) mastered,"   //Освоенно
                            "(contracts.contracts_sum - SUM(checks.check_sum)) residue,"    //Остаток
                            "contracts.start_date,"
                            "contracts.end_date,"
                            "contracts.conclusion_date,"
                            "contracts.date_registration,"
                            "providers.provider,"
                            "sources_financing.source_financing,"
                            "subdivisions.subdivision,"
                            "responsibles.responsible,"
                            "contracts.completeness,"
                            "contracts.comment "
                    "FROM register_contracts AS contracts "
                    "INNER JOIN providers "
                    "ON contracts.provider_id = providers.provider_id "

                    "INNER JOIN subdivisions "
                    "ON contracts.subdivision_id = subdivisions.subdivision_id "
                    "INNER JOIN responsibles "
                    "ON contracts.responsible_id = responsibles.responsible_id "
                    "INNER JOIN sources_financing "
                    "ON contracts.source_financing_id = sources_financing.source_financing_id "

                    "LEFT JOIN checks_register_contracts AS checks "
                    "ON contracts.contract_id = checks.contract_id "
                    "GROUP BY contracts.contract_id;");
    return isNotValidLastError("Установка начального состояния модели");
}

FindObjectAbstract *TableRegisterContractsModel::getFindObject()
{
    return new FindObjectContract;
}

uint TableRegisterContractsModel::getColumnEndDateNumber() const
{
    return columnEndDateNumber;
}
