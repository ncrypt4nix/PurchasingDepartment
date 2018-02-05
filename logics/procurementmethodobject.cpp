#include "procurementmethodobject.h"

using namespace logics;

/*! \brief  */
const QString ProcurementMethodObject::NUMBER_NOTICE_STR = tr("№ извещения");
const QString ProcurementMethodObject::NOTICE_DATE_STR = tr("Дата измещения");
const QString ProcurementMethodObject::PROCUREMENT_OBJECT_STR = tr("Предмет закупки");
const QString ProcurementMethodObject::STARTING_PRICE_STR = tr("Начальная (максимальная) цена договора");
const QString ProcurementMethodObject::START_DATE_DEADLINE_STR = tr("Дата начала срока подачи заявок");
const QString ProcurementMethodObject::END_DATE_DEADLINE_STR = tr("Дата окончания срока подачи заявок");
const QString ProcurementMethodObject::OPENING_ENVELOPES_DATE_STR = tr("Дата протокола вскрытия конвертов");
const QString ProcurementMethodObject::SUMMARIZING_DATE_STR = tr("Дата протокола рассмотрения подведения итогов");
const QString ProcurementMethodObject::PROCUREMENT_METHODS_STR = tr("Способы закупки");
const QString ProcurementMethodObject::PROCEDURE_COMPLETE_STR = tr("Статус");
const QString ProcurementMethodObject::SMP_STR = tr("СМП");
const QString ProcurementMethodObject::DATE_REGISTRATION_STR = tr("Дата регистрации");
const QString ProcurementMethodObject::COMPLETENESS = tr("Завершенность");

ProcurementMethodObject::ProcurementMethodObject(QObject *parent) :
    RegisterObjectAbstract(parent)
{}

bool ProcurementMethodObject::save() const
{
    QSqlQuery query;
    query.prepare("UPDATE register_procurement_methods "
                  "SET number_notice = :number_notice,"
                  "notice_date = :notice_date,"
                  "procurement_object = :procurement_object,"
                  "starting_price = :starting_price,"
                  "start_date_deadline = :start_date_deadline,"
                  "end_date_deadline = :end_date_deadline,"
                  "opening_envelopes_date = :opening_envelopes_date,"
                  "summarizing_date = :summarizing_date,"
                  "procedure_complete = :procedure_complete,"
                  "smp = :smp,"
                  "completeness = :completeness,"
                  "date_registration = :date_registration,"
                  "procurement_method_id = :procurement_method_id "
                  "WHERE register_procurement_method_id = :register_procurement_method_id");

    query.bindValue(":number_notice", numberNotice);
    query.bindValue(":notice_date", noticeDate);
    query.bindValue(":procurement_object", procurementObject);
    query.bindValue(":starting_price", startingPrice);
    query.bindValue(":start_date_deadline", startDateDeadline);
    query.bindValue(":end_date_deadline", endDateDeadline);
    query.bindValue(":opening_envelopes_date", openingEnvelopesDate);
    query.bindValue(":summarizing_date", summarizingDate);
    query.bindValue(":procedure_complete", procedureComplete);
    query.bindValue(":smp", smp);
    query.bindValue(":completeness", completeness);
    query.bindValue(":date_registration", registrationDate);
    query.bindValue(":procurement_method_id", procurementMethodId);
    query.bindValue(":register_procurement_method_id", id);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    return true;
}

bool ProcurementMethodObject::add()
{
    QSqlQuery query;
    query.prepare("INSERT INTO register_procurement_methods "
                  "(number_notice, notice_date, procurement_object, starting_price, start_date_deadline, end_date_deadline,"
                  "opening_envelopes_date, summarizing_date, procedure_complete, smp, completeness, date_registration, procurement_method_id) "
                  "VALUES (:number_notice, :notice_date, :procurement_object, :starting_price, :start_date_deadline, :end_date_deadline,"
                  ":opening_envelopes_date, :summarizing_date, :procedure_complete, :smp, :completeness, :date_registration, :procurement_method_id)"
                );
    query.bindValue(":number_notice", numberNotice);
    query.bindValue(":notice_date", noticeDate);
    query.bindValue(":procurement_object", procurementObject);
    query.bindValue(":starting_price", startingPrice);
    query.bindValue(":start_date_deadline", startDateDeadline);
    query.bindValue(":end_date_deadline", endDateDeadline);
    query.bindValue(":opening_envelopes_date", openingEnvelopesDate);
    query.bindValue(":summarizing_date", summarizingDate);
    query.bindValue(":procedure_complete", procedureComplete);
    query.bindValue(":smp", smp);
    query.bindValue(":completeness", completeness);
    query.bindValue(":date_registration", registrationDate);
    query.bindValue(":procurement_method_id", procurementMethodId);
    if (!query.exec())
    {
        qDebug() << query.lastError();
        return false;
    }
    changeId(query.lastInsertId().toUInt());
    return true;
}

ContractProcurementMethodObject *ProcurementMethodObject::getContractProcurementMethodObject()
{
    return &contractObj;
}

bool ProcurementMethodObject::changeId(const uint &id)
{
    if (!RegisterObjectAbstract::changeId(id))
        return false;
    return contractObj.setRegisterProcurementMethodId(id);
}

ProcurementMethodObject &ProcurementMethodObject::operator=(const ProcurementMethodObject &other)
{
    if (this == &other)
    {
        return *this;
    }
    copyData(other);
    return *this;
}

bool ProcurementMethodObject::update()
{
    QSqlQuery query;
    if (!query.exec("SELECT * FROM register_procurement_methods WHERE register_procurement_method_id = " + QString::number(id)))
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

    numberNotice = query.value(record.indexOf("number_notice")).toString();
    noticeDate = query.value(record.indexOf("notice_date")).toDate();
    procurementObject = query.value(record.indexOf("procurement_object")).toString();
    startingPrice = query.value(record.indexOf("starting_price")).toDouble();
    startDateDeadline = query.value(record.indexOf("start_date_deadline")).toDate();
    endDateDeadline = query.value(record.indexOf("end_date_deadline")).toDate();
    openingEnvelopesDate = query.value(record.indexOf("opening_envelopes_date")).toDate();
    summarizingDate = query.value(record.indexOf("summarizing_date")).toDate();
    procedureComplete = query.value(record.indexOf("procedure_complete")).toBool();
    smp = query.value(record.indexOf("smp")).toBool();
    completeness = query.value(record.indexOf("completeness")).toBool();
    registrationDate = query.value(record.indexOf("date_registration")).toDate();
    procurementMethodId = query.value(record.indexOf("procurement_method_id")).toUInt();

    return true;
}

bool ProcurementMethodObject::getCompleteness() const
{
    return completeness;
}

void ProcurementMethodObject::setCompleteness(bool value)
{
    completeness = value;
}

QDate ProcurementMethodObject::getRegistrationDate() const
{
    return registrationDate;
}

void ProcurementMethodObject::setRegistrationDate(const QDate &value)
{
    registrationDate = value;
}

bool ProcurementMethodObject::getSmp() const
{
    return smp;
}

void ProcurementMethodObject::setSmp(bool value)
{
    smp = value;
}

void ProcurementMethodObject::copyData(const ProcurementMethodObject &other)
{
    RegisterObjectAbstract::copyData(other);
    numberNotice = other.numberNotice;
    noticeDate = other.noticeDate;
    procurementObject = other.procurementObject;
    startingPrice = other.startingPrice;
    startDateDeadline = other.startDateDeadline;
    endDateDeadline = other.endDateDeadline;
    openingEnvelopesDate = other.openingEnvelopesDate;
    summarizingDate = other.summarizingDate;
    procedureComplete = other.procedureComplete;
    procurementMethodId = other.procurementMethodId;
    smp = other.smp;
    completeness = other.completeness;
    registrationDate = other.registrationDate;
    contractObj.copyData(other.contractObj);
}

QString ProcurementMethodObject::headerExcel() const
{
    QStringList tempList;
    tempList    << NUMBER_NOTICE_STR
                << NOTICE_DATE_STR
                << PROCUREMENT_OBJECT_STR
                << STARTING_PRICE_STR
                << START_DATE_DEADLINE_STR
                << END_DATE_DEADLINE_STR
                << OPENING_ENVELOPES_DATE_STR
                << SUMMARIZING_DATE_STR
                << PROCUREMENT_METHODS_STR
                << PROCEDURE_COMPLETE_STR
                << SMP_STR
                << COMPLETENESS
                << DATE_REGISTRATION_STR;
    return RegisterObjectAbstract::headerExcel(tempList);
}

QString ProcurementMethodObject::headerExtendedExcel() const
{
    QStringList tempList;
    tempList    << NUMBER_NOTICE_STR
                << NOTICE_DATE_STR
                << PROCUREMENT_OBJECT_STR
                << STARTING_PRICE_STR
                << START_DATE_DEADLINE_STR
                << END_DATE_DEADLINE_STR
                << OPENING_ENVELOPES_DATE_STR
                << SUMMARIZING_DATE_STR
                << PROCUREMENT_METHODS_STR
                << PROCEDURE_COMPLETE_STR
                << SMP_STR
                << COMPLETENESS
                << DATE_REGISTRATION_STR
                << ContractProcurementMethodObject::CONTRACT_NUMBER_STR
                << ContractProcurementMethodObject::CONTRACTS_SUM_STR
                << ContractProcurementMethodObject::DISBURSED_STR
                << ContractProcurementMethodObject::BALANCE_STR
                << ContractProcurementMethodObject::START_DATE_STR
                << ContractProcurementMethodObject::END_DATE_STR
                << ContractProcurementMethodObject::PROVIDERS_STR
                << ContractProcurementMethodObject::SOURCE_FINANCINGS_STR
                << ContractProcurementMethodObject::SUBDIVISIONS_STR
                << ContractProcurementMethodObject::RESPONSIBLES_STR
                << ContractProcurementMethodObject::COMMENT_STR
                << ContractProcurementMethodObject::CHECK_NUMBER_STR
                << ContractProcurementMethodObject::REGISTRATION_DATE_STR
                << ContractProcurementMethodObject::CHECK_DATE_STR
                << ContractProcurementMethodObject::CHECK_SUM_STR
                << ContractProcurementMethodObject::DESCRIPTION_STR;
    return RegisterObjectAbstract::headerExcel(tempList);
}

QString ProcurementMethodObject::rowDataExcel() const
{
    QStringList tempList;
    tempList << numberNotice
            << noticeDate.toString(DATE_FORMAT)
            << procurementObject
            << QString::number(startingPrice)
            << startDateDeadline.toString(DATE_FORMAT)
            << endDateDeadline.toString(DATE_FORMAT)
            << openingEnvelopesDate.toString(DATE_FORMAT)
            << summarizingDate.toString(DATE_FORMAT)
            << handBookManager->getMapHandBook(HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX).key(procurementMethodId)
            << ((procedureComplete) ? "Состоялась" : "Несостоялась")
            << ((smp) ? "СМП" : "Не СМП")
            << ((completeness) ? "Завершенный" : "Действующий")
            << registrationDate.toString(DATE_FORMAT);

    return RegisterObjectAbstract::rowDataExcel(tempList);
}

QString ProcurementMethodObject::rowDataExtendedExcel() const
{
    QStringList tempList;
    tempList << numberNotice
            << noticeDate.toString(DATE_FORMAT)
            << procurementObject
            << QString::number(startingPrice)
            << startDateDeadline.toString(DATE_FORMAT)
            << endDateDeadline.toString(DATE_FORMAT)
            << openingEnvelopesDate.toString(DATE_FORMAT)
            << summarizingDate.toString(DATE_FORMAT)
            << handBookManager->getMapHandBook(HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX).key(procurementMethodId)
            << ((procedureComplete) ? "Состоялась" : "Несостоялась")
            << ((smp) ? "СМП" : "Не СМП")
            << ((completeness) ? "Завершенный" : "Действующий")
            << registrationDate.toString(DATE_FORMAT);

    QString rowData = RegisterObjectAbstract::rowDataExcel(tempList);
    rowData += contractObj.genRowDataExcel(tempList.size());
    return rowData;
}

uint ProcurementMethodObject::getProcurementMethodId() const
{
    return procurementMethodId;
}

void ProcurementMethodObject::setProcurementMethodId(const uint &value)
{
    procurementMethodId = value;
}

bool ProcurementMethodObject::getProcedureComplete() const
{
    return procedureComplete;
}

void ProcurementMethodObject::setProcedureComplete(bool value)
{
    procedureComplete = value;
}

QDate ProcurementMethodObject::getSummarizingDate() const
{
    return summarizingDate;
}

void ProcurementMethodObject::setSummarizingDate(const QDate &value)
{
    summarizingDate = value;
}

QDate ProcurementMethodObject::getOpeningEnvelopesDate() const
{
    return openingEnvelopesDate;
}

void ProcurementMethodObject::setOpeningEnvelopesDate(const QDate &value)
{
    openingEnvelopesDate = value;
}

QDate ProcurementMethodObject::getEndDateDeadline() const
{
    return endDateDeadline;
}

void ProcurementMethodObject::setEndDateDeadline(const QDate &value)
{
    endDateDeadline = value;
}

QDate ProcurementMethodObject::getStartDateDeadline() const
{
    return startDateDeadline;
}

void ProcurementMethodObject::setStartDateDeadline(const QDate &value)
{
    startDateDeadline = value;
}

double ProcurementMethodObject::getStartingPrice() const
{
    return startingPrice;
}

void ProcurementMethodObject::setStartingPrice(double value)
{
    startingPrice = value;
}

QString ProcurementMethodObject::getProcurementObject() const
{
    return procurementObject;
}

void ProcurementMethodObject::setProcurementObject(const QString &value)
{
    procurementObject = value;
}

QDate ProcurementMethodObject::getNoticeDate() const
{
    return noticeDate;
}

void ProcurementMethodObject::setNoticeDate(const QDate &value)
{
    noticeDate = value;
}

QString ProcurementMethodObject::getNumberNotice() const
{
    return numberNotice;
}

void ProcurementMethodObject::setNumberNotice(const QString &value)
{
    numberNotice = value;
}

