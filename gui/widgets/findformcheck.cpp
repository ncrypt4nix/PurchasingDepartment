#include "findformcheck.h"
#include "ui_findformcheck.h"

using namespace gui;

const QDate FindFormCheck::DEFAULT_DATE = QDate(2000, 1, 1);

FindFormCheck::FindFormCheck(QWidget *parent) :
    PaymentDocumentHandBookViewManager(parent),
    ui(new Ui::FindFormCheck)
{
    ui->setupUi(this);
    providersBox = ui->providerBox;
    subdivisionsBox = ui->subdivisionBox;
    responsiblesBox = ui->responsibleBox;
    sourcesFinancingBox = ui->sourceFinancingBox;
    paymentDocumentBox = ui->paymentDocumentBox;
}

FindFormCheck::~FindFormCheck()
{
    delete ui;
}

void FindFormCheck::resetOldData()
{
    PaymentDocumentHandBookViewManager::resetOldData();
    ui->checkNumberEdit->clear();
    ui->registrationDateFromEdit->setDate(DEFAULT_DATE);
    ui->registrationDateToEdit->setDate(DEFAULT_DATE);
    ui->checkDateFromEdit->setDate(DEFAULT_DATE);
    ui->checkDateToEdit->setDate(DEFAULT_DATE);
    ui->checkSumFromSpinBox->clear();
    ui->checkSumToSpinBox->clear();
    ui->numberChecksFromSpinBox->clear();
    ui->numberChecksToSpinBox->clear();
    ui->descriptionEdit->clear();
    ui->completenessBox->setCurrentIndex(DEFAULT_VALUE);
}

void FindFormCheck::setFindObjectCheck(logics::FindObjectCheck *value)
{
    if (findObjectCheck != NULL)
        delete findObjectCheck;
    findObjectCheck = value;
}

logics::FindObjectCheck *FindFormCheck::getFindObjectCheck()
{
    return findObjectCheck;
}

bool FindFormCheck::checkData()
{
    if (!ui->checkNumberEdit->text().isEmpty()
            || ui->registrationDateFromEdit->date() != DEFAULT_DATE
            || ui->registrationDateToEdit->date() != DEFAULT_DATE
            || ui->checkDateFromEdit->date() != DEFAULT_DATE
            || ui->checkDateToEdit->date() != DEFAULT_DATE
            || !ui->checkSumFromSpinBox->text().isEmpty()
            || !ui->checkSumToSpinBox->text().isEmpty()
            || !ui->numberChecksFromSpinBox->text().isEmpty()
            || !ui->numberChecksToSpinBox->text().isEmpty()
            || !ui->descriptionEdit->text().isEmpty()
            || ui->providerBox->currentIndex() != DEFAULT_VALUE
            || ui->subdivisionBox->currentIndex() != DEFAULT_VALUE
            || ui->responsibleBox->currentIndex() != DEFAULT_VALUE
            || ui->sourceFinancingBox->currentIndex() != DEFAULT_VALUE
            || ui->paymentDocumentBox->currentIndex() != DEFAULT_VALUE
            || ui->completenessBox->currentIndex() != DEFAULT_VALUE)
        return true;
    return false;
}

void FindFormCheck::fillingFindObjectCheck()
{
    if (!ui->checkNumberEdit->text().isEmpty())
        findObjectCheck->setCheckNumber(ui->checkNumberEdit->text());
    if (ui->registrationDateFromEdit->date() != DEFAULT_DATE)
        findObjectCheck->setRegistrationDateFrom(ui->registrationDateFromEdit->date());
    if (ui->registrationDateToEdit->date() != DEFAULT_DATE)
        findObjectCheck->setRegistrationDateTo(ui->registrationDateToEdit->date());
    if (ui->checkDateFromEdit->date() != DEFAULT_DATE)
        findObjectCheck->setCheckDateFrom(ui->checkDateFromEdit->date());
    if (ui->checkDateToEdit->date() != DEFAULT_DATE)
        findObjectCheck->setCheckDateTo(ui->checkDateToEdit->date());
    if (!ui->checkSumFromSpinBox->text().isEmpty())
        findObjectCheck->setCheckSumFrom(ui->checkSumFromSpinBox->value());
    if (!ui->checkSumToSpinBox->text().isEmpty())
        findObjectCheck->setCheckSumTo(ui->checkSumToSpinBox->value());
    if (!ui->numberChecksFromSpinBox->text().isEmpty())
        findObjectCheck->setNumberChecksFrom(ui->numberChecksFromSpinBox->value());
    if (!ui->numberChecksToSpinBox->text().isEmpty())
        findObjectCheck->setNumberChecksTo(ui->numberChecksToSpinBox->value());
    if (!ui->descriptionEdit->text().isEmpty())
        findObjectCheck->setDescription(ui->descriptionEdit->text());
    auto foo = ui->completenessBox->currentIndex();
    if (foo != DEFAULT_VALUE)
        findObjectCheck->setCompleteness(foo >= 0 ? foo : 0);
    if (!ui->providerBox->currentText().isEmpty())
        findObjectCheck->setProviderId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PROVIDERS_INDEX).value(
                        ui->providerBox->currentText()));
    if (!ui->subdivisionBox->currentText().isEmpty())
        findObjectCheck->setSubdivisionId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).value(
                        ui->subdivisionBox->currentText()));
    if (!ui->responsibleBox->currentText().isEmpty())
        findObjectCheck->setResponsibleId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX).value(
                        ui->responsibleBox->currentText()));
    if (!ui->sourceFinancingBox->currentText().isEmpty())
        findObjectCheck->setSourceFinancingId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).value(
                        ui->sourceFinancingBox->currentText()));
    if (!ui->paymentDocumentBox->currentText().isEmpty())
        findObjectCheck->setPaymentDocumentId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PAYMENT_DOCUMENTS_INDEX).value(
                        ui->paymentDocumentBox->currentText()));
}

void gui::FindFormCheck::on_okButton_clicked()
{
    if (!checkData())
    {
        createExceptionMessageBox(tr("Данные не были введены."));
        return;
    }
    fillingFindObjectCheck();
    hide();
    emit okClicked();
}

void gui::FindFormCheck::on_closeButton_clicked()
{
    hide();
}
