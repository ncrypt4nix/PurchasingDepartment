#include "checkobject.h"

using namespace logics;

const QString CheckObject::CHECK_NUMBER_STR = tr("№ счета");
const QString CheckObject::REGISTRATION_DATE_STR = tr("Дата регистрации");
const QString CheckObject::CHECK_DATE_STR = tr("Дата счета");
const QString CheckObject::CHECK_SUM_STR = tr("Сумма счета");
const QString CheckObject::DESCRIPTION_STR = tr("Описание");
const QString CheckObject::NUMBER_CHECKS_STR = tr("Колличество чеков");
const QString CheckObject::PROVIDERS_STR = tr("Поставщики товаров/услуг");
const QString CheckObject::SUBDIVISIONS_STR = tr("Подразделение-заказчик");
const QString CheckObject::RESPONSIBLES_STR = tr("Ответственные лица");
const QString CheckObject::SOURCE_FINANCINGS_STR = tr("Источники финансирования");
const QString CheckObject::PAYMENT_DOCUMENTS_STR = tr("Платежные документы");
const QString CheckObject::COMPLETENESS = tr("Завершенность");

CheckObject::CheckObject(QObject *parent) :
    RegisterObjectAbstract(parent)
{}

QString CheckObject::getNumber() const
{
    return number;
}

void CheckObject::setNumber(const QString &value)
{
    number = value;
}

QDate CheckObject::getRegistrationDate() const
{
    return registrationDate;
}

void CheckObject::setRegistrationDate(const QDate &value)
{
    registrationDate = value;
}

QDate CheckObject::getCheckDate() const
{
    return checkDate;
}

void CheckObject::setCheckDate(const QDate &value)
{
    checkDate = value;
}

double CheckObject::getSum() const
{
    return sum;
}

void CheckObject::setSum(double value)
{
    sum = value;
}

QString CheckObject::getDescription() const
{
    return description;
}

void CheckObject::setDescription(const QString &value)
{
    description = value;
}

uint CheckObject::getNumberChecks() const
{
    return numberChecks;
}

void CheckObject::setNumberChecks(const uint &value)
{
    numberChecks = value;
}

uint CheckObject::getProviderId() const
{
    return providerId;
}

void CheckObject::setProviderId(const uint &value)
{
    providerId = value;
}

uint CheckObject::getSubdivisionId() const
{
    return subdivisionId;
}

void CheckObject::setSubdivisionId(const uint &value)
{
    subdivisionId = value;
}

uint CheckObject::getResponsibleId() const
{
    return responsibleId;
}

void CheckObject::setResponsibleId(const uint &value)
{
    responsibleId = value;
}

uint CheckObject::getSourceFinancingId() const
{
    return sourceFinancingId;
}

void CheckObject::setSourceFinancingId(const uint &value)
{
    sourceFinancingId = value;
}

uint CheckObject::getPaymentDocumentId() const
{
    return paymentDocumentId;
}

void CheckObject::setPaymentDocumentId(const uint &value)
{
    paymentDocumentId = value;
}

bool CheckObject::save() const
{
    QSqlQuery query;
    query.prepare("UPDATE register_checks "
                  "SET check_number = :check_number,"
                  "registration_date = :registration_date,"
                  "check_date = :check_date,"
                  "check_sum = :check_sum,"
                  "description = :description,"
                  "number_checks = :number_checks,"
                  "provider_id = :provider_id,"
                  "subdivision_id = :subdivision_id,"
                  "responsible_id = :responsible_id,"
                  "source_financing_id = :source_financing_id,"
                  "payment_document_id = :payment_document_id,"
                  "completeness = :completeness "
                  "WHERE check_id = :check_id");

    query.bindValue(":check_number", number);
    query.bindValue(":registration_date", registrationDate);
    query.bindValue(":check_date", checkDate);
    query.bindValue(":check_sum", sum);
    query.bindValue(":description", description);
    query.bindValue(":number_checks", numberChecks);
    query.bindValue(":provider_id", providerId);
    query.bindValue(":subdivision_id", subdivisionId);
    query.bindValue(":responsible_id", responsibleId);
    query.bindValue(":source_financing_id", sourceFinancingId);
    query.bindValue(":payment_document_id", paymentDocumentId);
    query.bindValue(":completeness", completeness);
    query.bindValue(":check_id", id);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool CheckObject::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO register_checks "
                  "(check_number, registration_date, check_date, check_sum, description, number_checks,"
                  "provider_id, subdivision_id, responsible_id, source_financing_id, payment_document_id, completeness) "
                  "VALUES (:check_number, :registration_date, :check_date, :check_sum, :description, :number_checks,"
                  ":provider_id, :subdivision_id, :responsible_id, :source_financing_id, :payment_document_id, :completeness)"
                );
    query.bindValue(":check_number", number);
    query.bindValue(":registration_date", registrationDate);
    query.bindValue(":check_date", checkDate);
    query.bindValue(":check_sum", sum);
    query.bindValue(":description", description);
    query.bindValue(":number_checks", numberChecks);
    query.bindValue(":provider_id", providerId);
    query.bindValue(":subdivision_id", subdivisionId);
    query.bindValue(":responsible_id", responsibleId);
    query.bindValue(":source_financing_id", sourceFinancingId);
    query.bindValue(":payment_document_id", paymentDocumentId);
    query.bindValue(":completeness", completeness);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    id = query.lastInsertId().toUInt();
    return true;
}

CheckObject &CheckObject::operator=(const CheckObject &other)
{
    if (this == &other)
    {
        return *this;
    }
    copyData(other);
    return *this;
}

bool CheckObject::update()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM register_checks WHERE check_id = " + QString::number(id)))
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

    number = query.value(record.indexOf("check_number")).toString();
    registrationDate = query.value(record.indexOf("registration_date")).toDate();
    checkDate = query.value(record.indexOf("check_date")).toDate();
    sum = query.value(record.indexOf("check_sum")).toDouble();
    description = query.value(record.indexOf("description")).toString();
    numberChecks = query.value(record.indexOf("number_checks")).toUInt();
    providerId = query.value(record.indexOf("provider_id")).toUInt();
    subdivisionId = query.value(record.indexOf("subdivision_id")).toUInt();
    responsibleId = query.value(record.indexOf("responsible_id")).toUInt();
    sourceFinancingId = query.value(record.indexOf("source_financing_id")).toUInt();
    paymentDocumentId = query.value(record.indexOf("payment_document_id")).toUInt();
    completeness = query.value(record.indexOf("completeness")).toBool();

    return true;
}

bool CheckObject::getCompleteness() const
{
    return completeness;
}

void CheckObject::setCompleteness(bool value)
{
    completeness = value;
}

void CheckObject::copyData(const CheckObject &other)
{
    RegisterObjectAbstract::copyData(other);
    number = other.number;
    registrationDate = other.registrationDate;
    checkDate = other.checkDate;
    sum = other.sum;
    description = other.description;
    numberChecks = other.numberChecks;
    providerId = other.providerId;
    subdivisionId = other.subdivisionId;
    responsibleId = other.responsibleId;
    sourceFinancingId = other.sourceFinancingId;
    paymentDocumentId = other.paymentDocumentId;
    completeness = other.completeness;
}

QString CheckObject::headerExcel() const
{
    QStringList tempList;
    tempList    << CHECK_NUMBER_STR
                << PAYMENT_DOCUMENTS_STR
                << REGISTRATION_DATE_STR
                << CHECK_DATE_STR
                << CHECK_SUM_STR
                << DESCRIPTION_STR
                << NUMBER_CHECKS_STR
                << PROVIDERS_STR
                << SUBDIVISIONS_STR
                << RESPONSIBLES_STR
                << SOURCE_FINANCINGS_STR
                << COMPLETENESS;
    return RegisterObjectAbstract::headerExcel(tempList);
}

QString CheckObject::headerExtendedExcel() const
{
    return headerExcel();
}

QString CheckObject::rowDataExcel() const
{
    QStringList tempList;
    tempList    << number
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::PAYMENT_DOCUMENTS_INDEX).key(paymentDocumentId)
                << registrationDate.toString(DATE_FORMAT)
                << checkDate.toString(DATE_FORMAT)
                << QString::number(sum)
                << description
                << QString::number(numberChecks)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::PROVIDERS_INDEX).key(providerId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).key(subdivisionId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::RESPONSIBLES_INDEX).key(responsibleId)
                << handBookManager->getMapHandBook(HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).key(sourceFinancingId)
                << ((completeness) ? "Завершен" : "Незавершен");
    return RegisterObjectAbstract::rowDataExcel(tempList);
}

QString CheckObject::rowDataExtendedExcel() const
{
    return rowDataExcel();
}
