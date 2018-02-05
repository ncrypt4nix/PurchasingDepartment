#include "findformcontractwidget.h"
#include "ui_findformcontractwidget.h"

using namespace gui;

const QDate FindFormContractWidget::DEFAULT_DATE = QDate(2000, 1, 1);

FindFormContractWidget::FindFormContractWidget(QWidget *parent) :
    HandBookViewManager(parent),
    ui(new Ui::FindFormContractWidget)
{
    ui->setupUi(this);
    providersBox = ui->providerBox;
    subdivisionsBox = ui->subdivisionBox;
    responsiblesBox = ui->responsibleBox;
    sourcesFinancingBox = ui->sourceFinancingBox;
}

FindFormContractWidget::~FindFormContractWidget()
{
    delete ui;
}

void FindFormContractWidget::resetOldData()
{
    HandBookViewManager::resetOldData();
    ui->contractNumberEdit->clear();
    ui->contractsSumFromSpinBox->clear();
    ui->contractsSumToSpinBox->clear();
    ui->commentEdit->clear();
    ui->startDateFromEdit->setDate(DEFAULT_DATE);
    ui->startDateToEdit->setDate(DEFAULT_DATE);
    ui->endDateFromEdit->setDate(DEFAULT_DATE);
    ui->endDateToEdit->setDate(DEFAULT_DATE);
    ui->conclusionDateFromEdit->setDate(DEFAULT_DATE);
    ui->conclusionDateToEdit->setDate(DEFAULT_DATE);
    ui->registrationDateFromEdit->setDate(DEFAULT_DATE);
    ui->registrationDateToEdit->setDate(DEFAULT_DATE);
    ui->completenessBox->setCurrentIndex(DEFAULT_VALUE);
}

void FindFormContractWidget::setFindObjectContract(logics::FindObjectContract *value)
{
    findObjectContract = value;
}

logics::FindObjectContract *FindFormContractWidget::getFindObjectContract()
{
    return findObjectContract;
}

void FindFormContractWidget::fillingFindObjectContract()
{
    if (!ui->contractNumberEdit->text().isEmpty())
        findObjectContract->setContractNumber(ui->contractNumberEdit->text());
    if (!ui->contractsSumFromSpinBox->text().isEmpty())
        findObjectContract->setContractsSumFrom(ui->contractsSumFromSpinBox->value());
    if (!ui->contractsSumToSpinBox->text().isEmpty())
        findObjectContract->setContractsSumTo(ui->contractsSumToSpinBox->value());
    if (!ui->commentEdit->text().isEmpty())
        findObjectContract->setComment(ui->commentEdit->text());
    if (ui->startDateFromEdit->date() != DEFAULT_DATE)
        findObjectContract->setStartDateFrom(ui->startDateFromEdit->date());
    if (ui->startDateToEdit->date() != DEFAULT_DATE)
        findObjectContract->setStartDateTo(ui->startDateToEdit->date());
    if (ui->endDateFromEdit->date() != DEFAULT_DATE)
        findObjectContract->setEndDateFrom(ui->endDateFromEdit->date());
    if (ui->endDateToEdit->date() != DEFAULT_DATE)
        findObjectContract->setEndDateTo(ui->endDateToEdit->date());
    if (ui->conclusionDateFromEdit->date() != DEFAULT_DATE)
        findObjectContract->setConclusionDateFrom(ui->conclusionDateFromEdit->date());
    if (ui->conclusionDateToEdit->date() != DEFAULT_DATE)
        findObjectContract->setConclusionDateTo(ui->conclusionDateToEdit->date());
    if (ui->registrationDateFromEdit->date() != DEFAULT_DATE)
        findObjectContract->setRegistrationDateFrom(ui->registrationDateFromEdit->date());
    if (ui->registrationDateToEdit->date() != DEFAULT_DATE)
        findObjectContract->setRegistrationDateTo(ui->registrationDateToEdit->date());
    auto foo = ui->completenessBox->currentIndex();
    if (foo != DEFAULT_VALUE)
        findObjectContract->setCompleteness(foo >= 0 ? foo : 0);
    if (!ui->providerBox->currentText().isEmpty())
        findObjectContract->setProviderId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PROVIDERS_INDEX).value(
                        ui->providerBox->currentText()));
    if (!ui->subdivisionBox->currentText().isEmpty())
        findObjectContract->setSubdivisionId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).value(
                        ui->subdivisionBox->currentText()));
    if (!ui->responsibleBox->currentText().isEmpty())
        findObjectContract->setResponsibleId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX).value(
                        ui->responsibleBox->currentText()));
    if (!ui->sourceFinancingBox->currentText().isEmpty())
        findObjectContract->setSourceFinancingId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).value(
                                                     ui->sourceFinancingBox->currentText()));
}

void FindFormContractWidget::freeObject()
{
    if (findObjectContract != NULL)
        delete findObjectContract;
}

bool FindFormContractWidget::checkData()
{
    if (!ui->contractNumberEdit->text().isEmpty()
            || !ui->contractsSumFromSpinBox->text().isEmpty()
            || !ui->contractsSumToSpinBox->text().isEmpty()
            || !ui->commentEdit->text().isEmpty()
            || ui->startDateFromEdit->date() != DEFAULT_DATE
            || ui->startDateToEdit->date() != DEFAULT_DATE
            || ui->endDateFromEdit->date() != DEFAULT_DATE
            || ui->endDateToEdit->date() != DEFAULT_DATE
            || ui->conclusionDateFromEdit->date() != DEFAULT_DATE
            || ui->conclusionDateToEdit->date() != DEFAULT_DATE
            || ui->registrationDateFromEdit->date() != DEFAULT_DATE
            || ui->registrationDateToEdit->date() != DEFAULT_DATE
            || ui->completenessBox->currentIndex() != DEFAULT_VALUE
            || ui->providerBox->currentIndex() != DEFAULT_VALUE
            || ui->subdivisionBox->currentIndex() != DEFAULT_VALUE
            || ui->responsibleBox->currentIndex() != DEFAULT_VALUE
            || ui->sourceFinancingBox->currentIndex() != DEFAULT_VALUE)
        return true;
    return false;
}

