#include "contractobject.h"

using namespace logics;

const QString ContractObject::REGISTER_CONTRACTS = "register_contracts";
const QString ContractObject::REGISTER_CONTRACTS_CHECKS = "checks_register_contracts";
const QList<uint> ContractObject::columnsHidden = {0, 6};

const QString ContractObject::CONTRACT_NUMBER_STR = tr("№ Договора");
const QString ContractObject::CONTRACTS_SUM_STR = tr("Сумма");
const QString ContractObject::DISBURSED_STR = tr("Освоено");
const QString ContractObject::BALANCE_STR = tr("Остаток");
const QString ContractObject::START_DATE_STR = tr("Дата Начала");
const QString ContractObject::END_DATE_STR = tr("Дата Окончания");
const QString ContractObject::PROVIDERS_STR = tr("Поставщик Услуг");
const QString ContractObject::SUBDIVISIONS_STR = tr("Подразделение-Заказчик");
const QString ContractObject::RESPONSIBLES_STR = tr("Ответственные лица");
const QString ContractObject::SOURCE_FINANCINGS_STR = tr("Источники финансирования");
const QString ContractObject::COMMENT_STR = tr("Комментарий");
const QString ContractObject::CONCLUSION_DATE_STR = tr("Дата заключения договора");
const QString ContractObject::DATE_REGISTRATION_STR = tr("Дата регистрации");
const QString ContractObject::COMPLETENESS_STR = tr("Завершенность");
const QString ContractObject::CHECK_NUMBER_STR = tr("№ счета");
const QString ContractObject::REGISTRATION_DATE_STR = tr("Дата регистрации");
const QString ContractObject::CHECK_DATE_STR = tr("Дата счета");
const QString ContractObject::CHECK_SUM_STR = tr("Сумма счета");
const QString ContractObject::DESCRIPTION_STR = tr("Описание");

ContractObject::ContractObject(QObject *parent)
    : RegisterObjectAbstract(parent)
{
    registerName = REGISTER_CONTRACTS;
    checkTableName = REGISTER_CONTRACTS_CHECKS;
}

ContractObject::ContractObject(const ContractObject &other)
    : RegisterObjectAbstract(other.parent())
{
    copyData(other);
}

QString ContractObject::getNumber() const
{
    return number;
}

void ContractObject::setNumber(const QString &value)
{
    number = value;
}

double ContractObject::getSum() const
{
    return sum;
}

void ContractObject::setSum(double value)
{
    sum = value;
}

QDate ContractObject::getStartDate() const
{
    return startDate;
}

void ContractObject::setStartDate(const QDate &value)
{
    startDate = value;
}

QDate ContractObject::getEndDate() const
{
    return endDate;
}

void ContractObject::setEndDate(const QDate &value)
{
    endDate = value;
}

uint ContractObject::getProviderId() const
{
    return providerId;
}

void ContractObject::setProviderId(const uint &value)
{
    providerId = value;
}

uint ContractObject::getSubdivisionId() const
{
    return subdivisionId;
}

void ContractObject::setSubdivisionId(const uint &value)
{
    subdivisionId = value;
}

uint ContractObject::getResponsibleId() const
{
    return responsibleId;
}

void ContractObject::setResponsibleId(const uint &value)
{
    responsibleId = value;
}

uint ContractObject::getSourceFinancingId() const
{
    return sourceFinancingId;
}

void ContractObject::setSourceFinancingId(const uint &value)
{
    sourceFinancingId = value;
}

QString ContractObject::getComment() const
{
    return comment;
}

void ContractObject::setComment(const QString &value)
{
    comment = value;
}

QString ContractObject::getRegisterName() const
{
    return registerName;
}

void ContractObject::setRegisterName(const QString &value)
{
    registerName = value;
}
QString ContractObject::getCheckTableName() const
{
    return checkTableName;
}

void ContractObject::setCheckTableName(const QString &value)
{
    checkTableName = value;
}

QDate ContractObject::getConclusionDate() const
{
    return conclusionDate;
}

void ContractObject::setConclusionDate(const QDate &value)
{
    conclusionDate = value;
}

QDate ContractObject::getRegistrationDate() const
{
    return registrationDate;
}

void ContractObject::setRegistrationDate(const QDate &value)
{
    registrationDate = value;
}

bool ContractObject::getCompleteness() const
{
    return completeness;
}

void ContractObject::setCompleteness(bool value)
{
    completeness = value;
}

bool ContractObject::save() const
{
    QSqlQuery query;
    query.prepare("UPDATE " + registerName + " "
                                             "SET contract_number = :contract_number,"
                  "contracts_sum = :contracts_sum,"
                  "start_date = :start_date,"
                  "end_date = :end_date,"
                  "provider_id = :provider_id,"
                  "conclusion_date = :conclusion_date,"
                  "date_registration = :date_registration,"
                  "subdivision_id = :subdivision_id,"
                  "responsible_id = :responsible_id,"
                  "source_financing_id = :source_financing_id,"
                  "completeness = :completeness,"
                  "comment = :comment "
                  "WHERE contract_id = :contract_id");
    query.bindValue(":contract_number", number);
    query.bindValue(":contracts_sum", sum);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);
    query.bindValue(":conclusion_date", conclusionDate);
    query.bindValue(":date_registration", registrationDate);
    query.bindValue(":provider_id", providerId);
    query.bindValue(":subdivision_id", subdivisionId);
    query.bindValue(":responsible_id", responsibleId);
    query.bindValue(":source_financing_id", sourceFinancingId);
    query.bindValue(":completeness", completeness);
    query.bindValue(":comment", comment);
    query.bindValue(":contract_id", id);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool ContractObject::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO " + registerName + " "
                  "(contract_number, contracts_sum, start_date, end_date, conclusion_date, date_registration, provider_id,"
                  "subdivision_id, responsible_id, source_financing_id, completeness, comment) "
                  "VALUES (:contract_number, :contracts_sum, :start_date, :end_date, :conclusion_date, :date_registration,"
                  ":provider_id, :subdivision_id, :responsible_id, :source_financing_id, :completeness, :comment)"
                );
    query.bindValue(":contract_number", number);
    query.bindValue(":contracts_sum", sum);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);
    query.bindValue(":conclusion_date", conclusionDate);
    query.bindValue(":date_registration", registrationDate);
    query.bindValue(":provider_id", providerId);
    query.bindValue(":subdivision_id", subdivisionId);
    query.bindValue(":responsible_id", responsibleId);
    query.bindValue(":source_financing_id", sourceFinancingId);
    query.bindValue(":completeness", completeness);
    query.bindValue(":comment", comment);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    id = query.lastInsertId().toUInt();
    return true;
}

QSqlTableModel *ContractObject::getModel() const
{
    /* Почему этот класс не следит за памятью модели, не помню. Сам в а*уе */
    QSqlTableModel *checkTable = new QSqlTableModel;
    checkTable->setTable(checkTableName);
    checkTable->select();
    checkTable->setFilter(QString("contract_id = %1").arg(id));
    QStringList columnNames;
    columnNames << CHECK_NUMBER_STR
                << REGISTRATION_DATE_STR
                << CHECK_DATE_STR
                << CHECK_SUM_STR
                << DESCRIPTION_STR;
    for (int i = 0; i < columnNames.size(); i++)
        checkTable->setHeaderData(i + 1, Qt::Horizontal, columnNames.at(i));
    checkTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
    return checkTable;
}

ContractObject &ContractObject::operator=(const ContractObject &other)
{
    if (this == &other)
        return *this;
    copyData(other);
    return *this;
}

bool ContractObject::update()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM " + registerName + " WHERE contract_id = " + QString::number(id)))
    {
        qDebug() << query.lastError();
        return false;
    }
    QSqlRecord record = query.record();
    if (!query.next())
    {
        qDebug() << query.lastError();
        return false;
    }

    number = query.value(record.indexOf("contract_number")).toString();
    sum = query.value(record.indexOf("contracts_sum")).toDouble();
    startDate = query.value(record.indexOf("start_date")).toDate();
    endDate = query.value(record.indexOf("end_date")).toDate();
    conclusionDate = query.value(record.indexOf("conclusion_date")).toDate();
    registrationDate = query.value(record.indexOf("date_registration")).toDate();
    providerId = query.value(record.indexOf("provider_id")).toUInt();
    subdivisionId = query.value(record.indexOf("subdivision_id")).toUInt();
    responsibleId = query.value(record.indexOf("responsible_id")).toUInt();
    sourceFinancingId = query.value(record.indexOf("source_financing_id")).toUInt();
    completeness = query.value(record.indexOf("completeness")).toBool();
    comment = query.value(record.indexOf("comment")).toString();

    return true;
}

void ContractObject::copyData(const ContractObject &other)
{
    RegisterObjectAbstract::copyData(other);
    number = other.number;
    sum = other.sum;
    startDate = other.startDate;
    endDate = other.endDate;
    providerId = other.providerId;
    subdivisionId = other.subdivisionId;
    responsibleId = other.responsibleId;
    sourceFinancingId = other.sourceFinancingId;
    comment = other.comment;
    completeness = other.completeness;
    registrationDate = other.registrationDate;
    conclusionDate = other.conclusionDate;
    registerName = other.registerName;
}

QString ContractObject::headerExcel() const
{
    QStringList tempList;
    tempList    << CONTRACT_NUMBER_STR
                << CONTRACTS_SUM_STR
                << DISBURSED_STR
                << BALANCE_STR
                << START_DATE_STR
                << END_DATE_STR
                << CONCLUSION_DATE_STR
                << DATE_REGISTRATION_STR
                << PROVIDERS_STR
                << SOURCE_FINANCINGS_STR
                << SUBDIVISIONS_STR
                << RESPONSIBLES_STR
                << COMPLETENESS_STR
                << COMMENT_STR;
    return RegisterObjectAbstract::headerExcel(tempList);
}

QString ContractObject::headerExtendedExcel() const
{
    QStringList tempList;
    tempList    << CONTRACT_NUMBER_STR
                << CONTRACTS_SUM_STR
                << DISBURSED_STR
                << BALANCE_STR
                << START_DATE_STR
                << END_DATE_STR
                << CONCLUSION_DATE_STR
                << DATE_REGISTRATION_STR
                << PROVIDERS_STR
                << SOURCE_FINANCINGS_STR
                << SUBDIVISIONS_STR
                << RESPONSIBLES_STR
                << COMPLETENESS_STR
                << COMMENT_STR
                << CHECK_NUMBER_STR
                << REGISTRATION_DATE_STR
                << CHECK_DATE_STR
                << CHECK_SUM_STR
                << DESCRIPTION_STR;
    return RegisterObjectAbstract::headerExcel(tempList);
}

QString ContractObject::rowDataExcel() const
{
    QStringList tempList;
    QSqlTableModel *tempModel = getModel();
    double disbursed = 0.;
    for (int i = 0; i < tempModel->rowCount(); i++)
        disbursed += tempModel->index(i, CHECK_SUM_INDEX).data().toDouble();
    delete tempModel;
    tempList    << number
                << QString::number(sum)
                << QString::number(disbursed)
                << QString::number(sum - disbursed)
                << startDate.toString(DATE_FORMAT)
                << endDate.toString(DATE_FORMAT)
                << conclusionDate.toString(DATE_FORMAT)
                << registrationDate.toString(DATE_FORMAT)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::PROVIDERS_INDEX).key(providerId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).key(sourceFinancingId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).key(subdivisionId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::RESPONSIBLES_INDEX).key(responsibleId)
                << ((completeness) ? "Завершен" : "Незавершен")
                << comment;

    return RegisterObjectAbstract::rowDataExcel(tempList);
}

QString ContractObject::rowDataExtendedExcel() const
{
    return genRowDataExcel();
}

QString ContractObject::genRowDataExcel(const uint &spaces) const
{
    QStringList tempList;
    QSqlTableModel *tempModel = getModel();
    double disbursed = 0.;
    for (int i = 0; i < tempModel->rowCount(); i++)
        disbursed += tempModel->index(i, CHECK_SUM_INDEX).data().toDouble();
    int spaceSize = spaces;
    for (int i = 0; i < spaceSize; i++)
        tempList << "";
    tempList    << number
                << QString::number(sum)
                << QString::number(disbursed)
                << QString::number(sum - disbursed)
                << startDate.toString(DATE_FORMAT)
                << endDate.toString(DATE_FORMAT)
                << conclusionDate.toString(DATE_FORMAT)
                << registrationDate.toString(DATE_FORMAT)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::PROVIDERS_INDEX).key(providerId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).key(sourceFinancingId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).key(subdivisionId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::RESPONSIBLES_INDEX).key(responsibleId)
                << ((completeness) ? "Завершенный" : "Действующий")
                << comment;
    spaceSize += 14;
    QString rowesData = RegisterObjectAbstract::rowDataExcel(tempList);
    for (int i = 0; i < tempModel->rowCount(); i++)
    {
        QStringList tempCheckList;
        for (int i = 0; i < spaceSize; i++)
            tempCheckList << "";
        tempCheckList
                << tempModel->index(i, CHECK_NUMBER_INDEX).data().toString()
                << tempModel->index(i, REGISTRATION_DATE_INDEX).data().toDate().toString(DATE_FORMAT)
                << tempModel->index(i, CHECK_DATE_INDEX).data().toDate().toString(DATE_FORMAT)
                << tempModel->index(i, CHECK_SUM_INDEX).data().toString()
                << tempModel->index(i, DESCRIPTION_INDEX).data().toString();
        rowesData += RegisterObjectAbstract::rowDataExcel(tempCheckList);
    }
    delete tempModel;
    return rowesData;
}
