#include "findformprocurementmethod.h"
#include "ui_findformprocurementmethod.h"

using namespace gui;

const QDate FindFormProcurementMethod::DEFAULT_DATE = QDate(2000, 1, 1);

FindFormProcurementMethod::FindFormProcurementMethod(QWidget *parent) :
    ProcurementMethodsHandBookViewManager(parent),
    ui(new Ui::FindFormProcurementMethod)
{
    ui->setupUi(this);
    procurementMethodsBox = ui->procurementMethodBox;
}

FindFormProcurementMethod::~FindFormProcurementMethod()
{
    delete ui;
}

void FindFormProcurementMethod::resetOldData()
{
    ProcurementMethodsHandBookViewManager::resetOldData();
    ui->FindFormContractWidget->resetOldData();

    ui->numberNoticeEdit->clear();
    ui->noticeDateFromEdit->setDate(DEFAULT_DATE);
    ui->noticeDateToEdit->setDate(DEFAULT_DATE);
    ui->procurementObjectEdit->clear();
    ui->startingPriceFromSpinBox->clear();
    ui->startingPriceToSpinBox->clear();
    ui->startDateDeadlineFromEdit->setDate(DEFAULT_DATE);
    ui->startDateDeadlineToEdit->setDate(DEFAULT_DATE);
    ui->endDateDeadlineFromEdit->setDate(DEFAULT_DATE);
    ui->endDateDeadlineToEdit->setDate(DEFAULT_DATE);
    ui->openingEnvelopesDateFromEdit->setDate(DEFAULT_DATE);
    ui->openingEnvelopesDateToEdit->setDate(DEFAULT_DATE);
    ui->summarizingDateFromEdit->setDate(DEFAULT_DATE);
    ui->summarizingDateToEdit->setDate(DEFAULT_DATE);
    ui->procedureCompleteBox->setCurrentIndex(DEFAULT_VALUE);
    ui->smpBox->setCurrentIndex(DEFAULT_VALUE);
    ui->registrationDateFromEdit->setDate(DEFAULT_DATE);
    ui->registrationDateToEdit->setDate(DEFAULT_DATE);
    ui->completenessBox->setCurrentIndex(DEFAULT_VALUE);
}

void FindFormProcurementMethod::setFindObjectProcurementMethod(logics::FindObjectProcurementMethod *value)
{
    if (findObjectProcurementMethod != NULL)
        delete findObjectProcurementMethod;
    findObjectProcurementMethod = value;
    ui->FindFormContractWidget->setFindObjectContract(dynamic_cast<logics::FindObjectContract*>(findObjectProcurementMethod));
}

logics::FindObjectProcurementMethod *FindFormProcurementMethod::getFindObjectProcurementMethod()
{
    return findObjectProcurementMethod;
}

void FindFormProcurementMethod::setHandBookManager(logics::HandBookManager *value)
{
    ProcurementMethodsHandBookViewManager::setHandBookManager(value);
    ui->FindFormContractWidget->setHandBookManager(value);
}

bool FindFormProcurementMethod::checkData()
{
    if (!ui->numberNoticeEdit->text().isEmpty()
            || ui->noticeDateFromEdit->date() != DEFAULT_DATE
            || ui->noticeDateToEdit->date() != DEFAULT_DATE
            || !ui->startingPriceFromSpinBox->text().isEmpty()
            || !ui->startingPriceToSpinBox->text().isEmpty()
            || !ui->procurementObjectEdit->text().isEmpty()
            || ui->startDateDeadlineFromEdit->date() != DEFAULT_DATE
            || ui->startDateDeadlineToEdit->date() != DEFAULT_DATE
            || ui->endDateDeadlineFromEdit->date() != DEFAULT_DATE
            || ui->endDateDeadlineToEdit->date() != DEFAULT_DATE
            || ui->openingEnvelopesDateFromEdit->date() != DEFAULT_DATE
            || ui->openingEnvelopesDateToEdit->date() != DEFAULT_DATE
            || ui->summarizingDateFromEdit->date() != DEFAULT_DATE
            || ui->summarizingDateToEdit->date() != DEFAULT_DATE
            || ui->procurementMethodBox->currentIndex() != DEFAULT_VALUE
            || ui->procedureCompleteBox->currentIndex() != DEFAULT_VALUE
            || ui->smpBox->currentIndex() != DEFAULT_VALUE
            || ui->registrationDateFromEdit->date() != DEFAULT_DATE
            || ui->registrationDateToEdit->date() != DEFAULT_DATE
            || ui->completenessBox->currentIndex() != DEFAULT_VALUE)
        return true;
    return false;
}

void FindFormProcurementMethod::fillingFindObjectProcurementMethod()
{
    if (!ui->numberNoticeEdit->text().isEmpty())
        findObjectProcurementMethod->setNumberNotice(ui->numberNoticeEdit->text());
    if (ui->noticeDateFromEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setNoticeDateFrom(ui->noticeDateFromEdit->date());
    if (ui->noticeDateToEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setNoticeDateTo(ui->noticeDateToEdit->date());
    if (!ui->startingPriceFromSpinBox->text().isEmpty())
        findObjectProcurementMethod->setStartingPriceFrom(ui->startingPriceFromSpinBox->value());
    if (!ui->startingPriceToSpinBox->text().isEmpty())
        findObjectProcurementMethod->setStartingPriceTo(ui->startingPriceToSpinBox->value());
    if (!ui->procurementObjectEdit->text().isEmpty())
        findObjectProcurementMethod->setProcurementObject(ui->procurementObjectEdit->text());
    if (ui->startDateDeadlineFromEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setStartDateDeadlineFrom(ui->startDateDeadlineFromEdit->date());
    if (ui->startDateDeadlineToEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setStartDateDeadlineTo(ui->startDateDeadlineToEdit->date());
    if (ui->endDateDeadlineFromEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setEndDateDeadlineFrom(ui->endDateDeadlineFromEdit->date());
    if (ui->endDateDeadlineToEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setEndDateDeadlineTo(ui->endDateDeadlineToEdit->date());
    if (ui->openingEnvelopesDateFromEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setOpeningEnvelopesDateFrom(ui->openingEnvelopesDateFromEdit->date());
    if (ui->openingEnvelopesDateToEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setOpeningEnvelopesDateTo(ui->openingEnvelopesDateToEdit->date());
    if (ui->summarizingDateFromEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setSummarizingDateFrom(ui->summarizingDateFromEdit->date());
    if (ui->summarizingDateToEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setSummarizingDateTo(ui->summarizingDateToEdit->date());
    if (ui->registrationDateFromEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setRegistrationDateRPMFrom(ui->registrationDateFromEdit->date());
    if (ui->registrationDateToEdit->date() != DEFAULT_DATE)
        findObjectProcurementMethod->setRegistrationDateRPMTo(ui->registrationDateToEdit->date());
    if (!ui->procurementMethodBox->currentText().isEmpty())
        findObjectProcurementMethod->setProcurementMethodId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX).value(
                        ui->procurementMethodBox->currentText()));

    auto procedureComplete = ui->procedureCompleteBox->currentIndex();
    if (procedureComplete != DEFAULT_VALUE)
        findObjectProcurementMethod->setProcedureComplete(procedureComplete >= 0 ? procedureComplete : 0);

    auto smp = ui->smpBox->currentIndex();
    if (smp != DEFAULT_VALUE)
        findObjectProcurementMethod->setSmp(smp >= 0 ? smp : 0);

    auto completeness = ui->completenessBox->currentIndex();
    if (completeness != DEFAULT_VALUE)
        findObjectProcurementMethod->setCompletenessRPM(completeness >= 0 ? completeness : 0);

    ui->FindFormContractWidget->fillingFindObjectContract();
}

void gui::FindFormProcurementMethod::on_closeButton_clicked()
{
    hide();
}

void gui::FindFormProcurementMethod::on_okButton_clicked()
{
    if (!ui->FindFormContractWidget->checkData()
            && !checkData())
    {
        createExceptionMessageBox(tr("Данные не были введены."));
        return;
    }
    fillingFindObjectProcurementMethod();
    hide();
    emit okClicked();
}
