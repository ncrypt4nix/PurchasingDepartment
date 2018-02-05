#include "findobjectprocurementmethod.h"

using namespace logics;

FindObjectProcurementMethod::FindObjectProcurementMethod(QObject *parent) :
    FindObjectContract(parent)
{}


QString logics::FindObjectProcurementMethod::getFindQuery() const
{
    QString query = "SELECT reg_proc_meth.register_procurement_method_id,"
                        "reg_proc_meth.number_notice,"
                        "reg_proc_meth.notice_date,"
                        "reg_proc_meth.procurement_object,"
                        "reg_proc_meth.starting_price,"
                        "reg_proc_meth.start_date_deadline,"
                        "reg_proc_meth.end_date_deadline,"
                        "reg_proc_meth.opening_envelopes_date,"
                        "reg_proc_meth.summarizing_date,"
                        "procurement_methods.procurement_method,"
                        "reg_proc_meth.procedure_complete,"
                        "reg_proc_meth.date_registration,"
                        "reg_proc_meth.smp,"
                        "reg_proc_meth.completeness "
                    "FROM register_procurement_methods AS reg_proc_meth "
                    "INNER JOIN procurement_methods "
                    "ON reg_proc_meth.procurement_method_id = procurement_methods.procurement_method_id "
                    "LEFT JOIN contracts_register_procurement_methods AS contracts "
                    "ON reg_proc_meth.register_procurement_method_id = contracts.register_procurement_method_id "
                    "WHERE ";

    if (numberNotice.isChanged())
        query += QString("reg_proc_meth.number_notice LIKE '%%1%' AND ").arg(numberNotice.getFindValue().toString());

    if (noticeDateFrom.isChanged() && noticeDateTo.isChanged())
        query += QString("reg_proc_meth.notice_date BETWEEN '%1' AND '%2' AND ")
                .arg(noticeDateFrom.getFindValue().toString())
                .arg(noticeDateTo.getFindValue().toString());
    else if (noticeDateFrom.isChanged())
        query += QString("reg_proc_meth.notice_date >= '%1' AND ").arg(noticeDateFrom.getFindValue().toString());
    else if (noticeDateTo.isChanged())
        query += QString("reg_proc_meth.notice_date <= '%1' AND ").arg(noticeDateTo.getFindValue().toString());

    if (procurementObject.isChanged())
        query += QString("reg_proc_meth.procurement_object LIKE '%%1%' AND ").arg(procurementObject.getFindValue().toString());

    if (startingPriceFrom.isChanged() && startingPriceTo.isChanged())
        query += QString("reg_proc_meth.starting_price BETWEEN %1 AND %2 AND ")
                .arg(startingPriceFrom.getFindValue().toDouble())
                .arg(startingPriceTo.getFindValue().toDouble());
    else if (startingPriceFrom.isChanged())
        query += QString("reg_proc_meth.starting_price >= %1 AND ").arg(startingPriceFrom.getFindValue().toDouble());
    else if (startingPriceTo.isChanged())
        query += QString("reg_proc_meth.starting_price <= %1 AND ").arg(startingPriceTo.getFindValue().toDouble());

    if (startDateDeadlineFrom.isChanged() && startDateDeadlineTo.isChanged())
        query += QString("reg_proc_meth.start_date_deadline BETWEEN '%1' AND '%2' AND ")
                .arg(startDateDeadlineFrom.getFindValue().toString())
                .arg(startDateDeadlineTo.getFindValue().toString());
    else if (startDateDeadlineFrom.isChanged())
        query += QString("reg_proc_meth.start_date_deadline >= '%1' AND ").arg(startDateDeadlineFrom.getFindValue().toString());
    else if (startDateDeadlineTo.isChanged())
        query += QString("reg_proc_meth.start_date_deadline <= '%1' AND ").arg(startDateDeadlineTo.getFindValue().toString());

    if (endDateDeadlineFrom.isChanged() && endDateDeadlineTo.isChanged())
        query += QString("reg_proc_meth.end_date_deadline BETWEEN '%1' AND '%2' AND ")
                .arg(endDateDeadlineFrom.getFindValue().toString())
                .arg(endDateDeadlineTo.getFindValue().toString());
    else if (endDateDeadlineFrom.isChanged())
        query += QString("reg_proc_meth.end_date_deadline >= '%1' AND ").arg(endDateDeadlineFrom.getFindValue().toString());
    else if (endDateDeadlineTo.isChanged())
        query += QString("reg_proc_meth.end_date_deadline <= '%1' AND ").arg(endDateDeadlineTo.getFindValue().toString());

    if (openingEnvelopesDateFrom.isChanged() && openingEnvelopesDateTo.isChanged())
        query += QString("reg_proc_meth.opening_envelopes_date BETWEEN '%1' AND '%2' AND ")
                .arg(openingEnvelopesDateFrom.getFindValue().toString())
                .arg(openingEnvelopesDateTo.getFindValue().toString());
    else if (openingEnvelopesDateFrom.isChanged())
        query += QString("reg_proc_meth.opening_envelopes_date >= '%1' AND ").arg(openingEnvelopesDateFrom.getFindValue().toString());
    else if (openingEnvelopesDateTo.isChanged())
        query += QString("reg_proc_meth.opening_envelopes_date <= '%1' AND ").arg(openingEnvelopesDateTo.getFindValue().toString());

    if (summarizingDateFrom.isChanged() && summarizingDateTo.isChanged())
        query += QString("reg_proc_meth.summarizing_date BETWEEN '%1' AND '%2' AND ")
                .arg(summarizingDateFrom.getFindValue().toString())
                .arg(summarizingDateTo.getFindValue().toString());
    else if (summarizingDateFrom.isChanged())
        query += QString("reg_proc_meth.summarizing_date >= '%1' AND ").arg(summarizingDateFrom.getFindValue().toString());
    else if (summarizingDateTo.isChanged())
        query += QString("reg_proc_meth.summarizing_date <= '%1' AND ").arg(summarizingDateTo.getFindValue().toString());
    if (procedureComplete.isChanged())
        query += QString("reg_proc_meth.procedure_complete = %1 AND ").arg(procedureComplete.getFindValue().toBool());

    if (registrationDateRPMFrom.isChanged() && registrationDateRPMTo.isChanged())
        query += QString("reg_proc_meth.date_registration BETWEEN '%1' AND '%2' AND ")
                .arg(registrationDateRPMFrom.getFindValue().toString())
                .arg(registrationDateRPMTo.getFindValue().toString());
    else if (registrationDateRPMFrom.isChanged())
        query += QString("reg_proc_meth.date_registration >= '%1' AND ").arg(registrationDateRPMFrom.getFindValue().toString());
    else if (registrationDateRPMTo.isChanged())
        query += QString("reg_proc_meth.date_registration <= '%1' AND ").arg(registrationDateRPMTo.getFindValue().toString());

    if (smp.isChanged())
        query += QString("reg_proc_meth.smp = %1 AND ").arg(smp.getFindValue().toBool());
    if (completenessRPM.isChanged())
        query += QString("reg_proc_meth.completeness = %1 AND ").arg(completenessRPM.getFindValue().toBool());
    if (procurementMethodId.isChanged())
        query += QString("reg_proc_meth.procurement_method_id = %1 AND ").arg(procurementMethodId.getFindValue().toUInt());

    //Поиск по контракту
    if (contractNumber.isChanged())
        query += QString("contracts.contract_number LIKE '%%1%' AND ").arg(contractNumber.getFindValue().toString());
    if (contractsSumFrom.isChanged() && contractsSumTo.isChanged())
        query += QString("contracts.contracts_sum BETWEEN %1 AND %2 AND ")
                .arg(contractsSumFrom.getFindValue().toDouble())
                .arg(contractsSumTo.getFindValue().toDouble());
    else if (contractsSumFrom.isChanged())
        query += QString("contracts.contracts_sum >= %1 AND ").arg(contractsSumFrom.getFindValue().toDouble());
    else if (contractsSumTo.isChanged())
        query += QString("contracts.contracts_sum <= %1 AND ").arg(contractsSumTo.getFindValue().toDouble());
    if (startDateFrom.isChanged() && startDateTo.isChanged())
        query += QString("contracts.start_date BETWEEN '%1' AND '%2' AND ")
                .arg(startDateFrom.getFindValue().toString())
                .arg(startDateTo.getFindValue().toString());
    else if (startDateFrom.isChanged())
        query += QString("contracts.start_date >= '%1' AND ").arg(startDateFrom.getFindValue().toString());
    else if (startDateTo.isChanged())
        query += QString("contracts.start_date <= '%1' AND ").arg(startDateTo.getFindValue().toString());
    if (endDateFrom.isChanged() && endDateTo.isChanged())
        query += QString("contracts.end_date BETWEEN '%1' AND '%2' AND ")
                .arg(endDateFrom.getFindValue().toString())
                .arg(endDateTo.getFindValue().toString());
    else if (endDateFrom.isChanged())
        query += QString("contracts.end_date >= '%1' AND ").arg(endDateFrom.getFindValue().toString());
    else if (endDateTo.isChanged())
        query += QString("contracts.end_date <= '%1' AND ").arg(endDateTo.getFindValue().toString());
    if (conclusionDateFrom.isChanged() && conclusionDateTo.isChanged())
        query += QString("contracts.conclusion_date BETWEEN '%1' AND '%2' AND ")
                .arg(conclusionDateFrom.getFindValue().toString())
                .arg(conclusionDateTo.getFindValue().toString());
    else if (conclusionDateFrom.isChanged())
        query += QString("contracts.conclusion_date >= '%1' AND ").arg(conclusionDateFrom.getFindValue().toString());
    else if (conclusionDateTo.isChanged())
        query += QString("contracts.conclusion_date <= '%1' AND ").arg(conclusionDateTo.getFindValue().toString());
    if (registrationDateFrom.isChanged() && registrationDateTo.isChanged())
        query += QString("contracts.date_registration BETWEEN '%1' AND '%2' AND ")
                .arg(registrationDateFrom.getFindValue().toString())
                .arg(registrationDateTo.getFindValue().toString());
    else if (registrationDateFrom.isChanged())
        query += QString("contracts.date_registration >= '%1' AND ").arg(registrationDateFrom.getFindValue().toString());
    else if (registrationDateTo.isChanged())
        query += QString("contracts.date_registration <= '%1' AND ").arg(registrationDateTo.getFindValue().toString());
    if (providerId.isChanged())
        query += QString("contracts.provider_id = %1 AND ").arg(providerId.getFindValue().toUInt());
    if (subdivisionId.isChanged())
        query += QString("contracts.subdivision_id = %1 AND ").arg(subdivisionId.getFindValue().toUInt());
    if (responsibleId.isChanged())
        query += QString("contracts.responsible_id = %1 AND ").arg(responsibleId.getFindValue().toUInt());
    if (sourceFinancingId.isChanged())
        query += QString("contracts.source_financing_id = %1 AND ").arg(sourceFinancingId.getFindValue().toUInt());
    if (completeness.isChanged())
        query += QString("contracts.completeness = %1 AND ").arg(completeness.getFindValue().toBool());
    if (comment.isChanged())
        query += QString("contracts.comment LIKE '%%1%' AND ").arg(comment.getFindValue().toString());

    query.remove(query.lastIndexOf("AND"), 3);
    query += "GROUP BY reg_proc_meth.register_procurement_method_id;";
    return query;
}

void FindObjectProcurementMethod::setNumberNotice(const QString &value)
{
    numberNotice.setFindValue(value);
}

void FindObjectProcurementMethod::setNoticeDateFrom(const QDate &value)
{
    noticeDateFrom.setFindValue(value);
}

void FindObjectProcurementMethod::setNoticeDateTo(const QDate &value)
{
    noticeDateTo.setFindValue(value);
}

void FindObjectProcurementMethod::setProcurementObject(const QString &value)
{
    procurementObject.setFindValue(value);
}

void FindObjectProcurementMethod::setStartingPriceFrom(const double &value)
{
    startingPriceFrom.setFindValue(value);
}

void FindObjectProcurementMethod::setStartingPriceTo(const double &value)
{
    startingPriceTo.setFindValue(value);
}

void FindObjectProcurementMethod::setStartDateDeadlineFrom(const QDate &value)
{
    startDateDeadlineFrom.setFindValue(value);
}

void FindObjectProcurementMethod::setStartDateDeadlineTo(const QDate &value)
{
    startDateDeadlineTo.setFindValue(value);
}

void FindObjectProcurementMethod::setEndDateDeadlineFrom(const QDate &value)
{
    endDateDeadlineFrom.setFindValue(value);
}

void FindObjectProcurementMethod::setEndDateDeadlineTo(const QDate &value)
{
    endDateDeadlineTo.setFindValue(value);
}

void FindObjectProcurementMethod::setOpeningEnvelopesDateFrom(const QDate &value)
{
    openingEnvelopesDateFrom.setFindValue(value);
}

void FindObjectProcurementMethod::setOpeningEnvelopesDateTo(const QDate &value)
{
    openingEnvelopesDateTo.setFindValue(value);
}

void FindObjectProcurementMethod::setSummarizingDateFrom(const QDate &value)
{
    summarizingDateFrom.setFindValue(value);
}

void FindObjectProcurementMethod::setSummarizingDateTo(const QDate &value)
{
    summarizingDateTo.setFindValue(value);
}

void FindObjectProcurementMethod::setProcedureComplete(const bool &value)
{
    procedureComplete.setFindValue(value);
}

void FindObjectProcurementMethod::setProcurementMethodId(const uint &value)
{
    procurementMethodId.setFindValue(value);
}

void FindObjectProcurementMethod::setSmp(const bool &value)
{
    smp.setFindValue(value);
}

void FindObjectProcurementMethod::setRegistrationDateRPMFrom(const QDate &value)
{
    registrationDateRPMFrom.setFindValue(value);
}

void FindObjectProcurementMethod::setRegistrationDateRPMTo(const QDate &value)
{
    registrationDateRPMTo.setFindValue(value);
}

void FindObjectProcurementMethod::setCompletenessRPM(const bool &value)
{
    completenessRPM.setFindValue(value);
}
