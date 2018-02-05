#include "findobjectcheck.h"

using namespace logics;

FindObjectCheck::FindObjectCheck(QObject *parent) :
    FindObjectAbstract(parent)
{}

QString FindObjectCheck::getFindQuery() const
{
    QString query = "SELECT checks.check_id,"
                        "checks.check_number,"
                        "payment_documents.payment_document,"
                        "checks.registration_date,"
                        "checks.check_date,"
                        "checks.check_sum,"
                        "checks.description,"
                        "checks.number_checks,"
                        "providers.provider,"
                        "subdivisions.subdivision,"
                        "responsibles.responsible,"
                        "sources_financing.source_financing,"
                        "checks.completeness "
                    "FROM register_checks AS checks "
                    "INNER JOIN providers "
                    "ON checks.provider_id = providers.provider_id "
                    "INNER JOIN subdivisions "
                    "ON checks.subdivision_id = subdivisions.subdivision_id "
                    "INNER JOIN responsibles "
                    "ON checks.responsible_id = responsibles.responsible_id "
                    "INNER JOIN sources_financing "
                    "ON checks.source_financing_id = sources_financing.source_financing_id "
                    "INNER JOIN payment_documents "
                    "ON checks.payment_document_id = payment_documents.payment_document_id "
                    "WHERE ";
    if (checkNumber.isChanged())
        query += QString("checks.check_number LIKE '%%1%' AND ").arg(checkNumber.getFindValue().toString());

    if (registrationDateFrom.isChanged() && registrationDateTo.isChanged())
        query += QString("checks.registration_date BETWEEN '%1' AND '%2' AND ")
                .arg(registrationDateFrom.getFindValue().toString())
                .arg(registrationDateTo.getFindValue().toString());
    else if (registrationDateFrom.isChanged())
        query += QString("checks.registration_date >= '%1' AND ").arg(registrationDateFrom.getFindValue().toString());
    else if (registrationDateTo.isChanged())
        query += QString("checks.registration_date <= '%1' AND ").arg(registrationDateTo.getFindValue().toString());

    if (checkDateFrom.isChanged() && checkDateTo.isChanged())
        query += QString("checks.check_date BETWEEN '%1' AND '%2' AND ")
                .arg(checkDateFrom.getFindValue().toString())
                .arg(checkDateTo.getFindValue().toString());
    else if (checkDateFrom.isChanged())
        query += QString("checks.check_date >= '%1' AND ").arg(checkDateFrom.getFindValue().toString());
    else if (checkDateTo.isChanged())
        query += QString("checks.check_date <= '%1' AND ").arg(checkDateTo.getFindValue().toString());

    if (checkSumFrom.isChanged() && checkSumTo.isChanged())
        query += QString("checks.check_sum BETWEEN %1 AND %2 AND ")
                .arg(checkSumFrom.getFindValue().toDouble())
                .arg(checkSumTo.getFindValue().toDouble());
    else if (checkSumFrom.isChanged())
        query += QString("checks.check_sum >= %1 AND ").arg(checkSumFrom.getFindValue().toDouble());
    else if (checkSumTo.isChanged())
        query += QString("checks.check_sum <= %1 AND ").arg(checkSumTo.getFindValue().toDouble());

    if (numberChecksFrom.isChanged() && numberChecksTo.isChanged())
        query += QString("checks.number_checks BETWEEN %1 AND %2 AND ")
                .arg(numberChecksFrom.getFindValue().toUInt())
                .arg(numberChecksTo.getFindValue().toUInt());
    else if (numberChecksFrom.isChanged())
        query += QString("checks.number_checks >= %1 AND ").arg(numberChecksFrom.getFindValue().toUInt());
    else if (numberChecksTo.isChanged())
        query += QString("checks.number_checks <= %1 AND ").arg(numberChecksTo.getFindValue().toUInt());

    if (description.isChanged())
        query += QString("checks.description LIKE '%%1%' AND ").arg(description.getFindValue().toString());
    if (providerId.isChanged())
        query += QString("checks.provider_id = %1 AND ").arg(providerId.getFindValue().toUInt());
    if (subdivisionId.isChanged())
        query += QString("checks.subdivision_id = %1 AND ").arg(subdivisionId.getFindValue().toUInt());
    if (responsibleId.isChanged())
        query += QString("checks.responsible_id = %1 AND ").arg(responsibleId.getFindValue().toUInt());
    if (sourceFinancingId.isChanged())
        query += QString("checks.source_financing_id = %1 AND ").arg(sourceFinancingId.getFindValue().toUInt());
    if (paymentDocumentId.isChanged())
        query += QString("checks.payment_document_id = %1 AND ").arg(paymentDocumentId.getFindValue().toUInt());
    if (completeness.isChanged())
        query += QString("checks.completeness = %1 AND ").arg(completeness.getFindValue().toBool());
    query.remove(query.lastIndexOf("AND"), 3);
    return query;
}

void FindObjectCheck::setCheckNumber(const QString &value)
{
    checkNumber.setFindValue(value);
}

void FindObjectCheck::setRegistrationDateFrom(const QDate &value)
{
    registrationDateFrom.setFindValue(value);
}

void FindObjectCheck::setRegistrationDateTo(const QDate &value)
{
    registrationDateTo.setFindValue(value);
}

void FindObjectCheck::setCheckDateFrom(const QDate &value)
{
    checkDateFrom.setFindValue(value);
}

void FindObjectCheck::setCheckDateTo(const QDate &value)
{
    checkDateTo.setFindValue(value);
}

void FindObjectCheck::setCheckSumFrom(const double &value)
{
    checkSumFrom.setFindValue(value);
}

void FindObjectCheck::setCheckSumTo(const double &value)
{
    checkSumTo.setFindValue(value);
}

void FindObjectCheck::setNumberChecksFrom(const uint &value)
{
    numberChecksFrom.setFindValue(value);
}

void FindObjectCheck::setNumberChecksTo(const uint &value)
{
    numberChecksTo.setFindValue(value);
}

void FindObjectCheck::setDescription(const QString &value)
{
    description.setFindValue(value);
}

void FindObjectCheck::setProviderId(const uint &value)
{
    providerId.setFindValue(value);
}

void FindObjectCheck::setSubdivisionId(const uint &value)
{
    subdivisionId.setFindValue(value);
}

void FindObjectCheck::setResponsibleId(const uint &value)
{
    responsibleId.setFindValue(value);
}

void FindObjectCheck::setSourceFinancingId(const uint &value)
{
    sourceFinancingId.setFindValue(value);
}

void FindObjectCheck::setPaymentDocumentId(const uint &value)
{
    paymentDocumentId.setFindValue(value);
}

void FindObjectCheck::setCompleteness(const bool &value)
{
    completeness.setFindValue(value);
}
