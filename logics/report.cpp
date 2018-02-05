#include "report.h"

using namespace logics;

Report::Report(QObject *parent) : QObject(parent)
{}

Report::ReportData Report::reportContract(const QDate &date)
{
    QSqlQuery query;
    QDate startDate = QDate(date.year(), date.month(), 1);
    QDate endDate = QDate(date.year(), date.month(), date.daysInMonth());
    query.prepare("SELECT SUM(contracts_sum) AS sum, COUNT(*) AS count_data "
                  "FROM register_contracts "
                  "WHERE conclusion_date BETWEEN :start_date AND :end_date;");
    query.bindValue(":start_date", startDate.toString(Qt::ISODate));
    query.bindValue(":end_date", endDate.toString(Qt::ISODate));
    query.exec();
    QSqlRecord record = query.record();
    query.next();
    if (!isNotValidLastError(query, tr("Отчет реестра договоров")))
        throw exceptions::DataBaseException(exceptions::DataBaseException::ERROR_QUERY);
    return { query.value(record.indexOf("sum")).toDouble(), query.value(record.indexOf("count_data")).toInt() };
}

Report::ReportData Report::reportCheck(const QDate &date)
{
    QSqlQuery query;
    QDate startDate = QDate(date.year(), date.month(), 1);
    QDate endDate = QDate(date.year(), date.month(), date.daysInMonth());
    query.prepare("SELECT sum(check_sum) AS sum, COUNT(*) AS count_data "
                  "FROM register_checks  "
                  "WHERE check_date BETWEEN :start_date AND :end_date;");
    query.bindValue(":start_date", startDate.toString(Qt::ISODate));
    query.bindValue(":end_date", endDate.toString(Qt::ISODate));
    query.exec();
    QSqlRecord record = query.record();
    query.next();
    if (!isNotValidLastError(query, tr("Отчет реестра договоров")))
        throw exceptions::DataBaseException(exceptions::DataBaseException::ERROR_QUERY);
    return { query.value(record.indexOf("sum")).toDouble(), query.value(record.indexOf("count_data")).toInt() };
}

Report::ReportData Report::reportProcurementMethods(const QDate &date)
{
    QSqlQuery query;
    QDate startDate = QDate(date.year(), date.month(), 1);
    QDate endDate = QDate(date.year(), date.month(), date.daysInMonth());
    query.prepare("SELECT sum(contracts_sum) AS sum, COUNT(*) AS count_data "
                  "FROM contracts_register_procurement_methods  "
                  "WHERE conclusion_date BETWEEN :start_date AND :end_date;");
    query.bindValue(":start_date", startDate.toString(Qt::ISODate));
    query.bindValue(":end_date", endDate.toString(Qt::ISODate));
    query.exec();
    QSqlRecord record = query.record();
    query.next();
    if (!isNotValidLastError(query, tr("Отчет реестра договоров")))
        throw exceptions::DataBaseException(exceptions::DataBaseException::ERROR_QUERY);
    return { query.value(record.indexOf("sum")).toDouble(), query.value(record.indexOf("count_data")).toInt() };
}

Report::ReportData Report::reportContractAndCheck(const QDate &date)
{
    return reportContract(date) + reportCheck(date);
}

Report::ReportData Report::reportAll(const QDate &date)
{
    return reportContract(date) + reportCheck(date) + reportProcurementMethods(date);
}

bool Report::isNotValidLastError(const QSqlQuery &query, const QString &operation)
{
    if (query.lastError().isValid())
    {
        qDebug() << operation << ": " << query.lastError();
        return false;
    }
    return true;
}

Report::ReportData Report::ReportData::operator+(const Report::ReportData other) const
{
    return { sum + other.sum, count + other.count };
}
