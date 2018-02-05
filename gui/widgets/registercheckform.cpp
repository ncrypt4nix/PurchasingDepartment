#include "registercheckform.h"
#include "ui_registercheckform.h"

using namespace gui;

RegisterCheckForm::RegisterCheckForm(QWidget *parent) :
    PaymentDocumentHandBookViewManager(parent),
    ui(new Ui::RegisterCheckForm)
{
    ui->setupUi(this);
    providersBox = ui->providersBox;
    subdivisionsBox = ui->subdivisionsBox;
    responsiblesBox = ui->responsiblesBox;
    sourcesFinancingBox = ui->sourcesFinancingBox;
    paymentDocumentBox = ui->paymentDocumentBox;
}

RegisterCheckForm::~RegisterCheckForm()
{
    delete ui;
}

void RegisterCheckForm::setCheckObj(const logics::CheckObject &value)
{
    checkObj = value;
    ui->numberEdit->setText(checkObj.getNumber());
    ui->registrationDateEdit->setDate(checkObj.getRegistrationDate());
    ui->checkDateEdit->setDate(checkObj.getCheckDate());
    ui->sumSpinBox->setValue(checkObj.getSum());
    ui->descriptionEdit->setText(checkObj.getDescription());
    ui->numberChecksBox->setValue(checkObj.getNumberChecks());
    ui->providersBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::PROVIDERS_INDEX).key(
                            checkObj.getProviderId()));
    ui->subdivisionsBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).key(
                            checkObj.getSubdivisionId()));
    ui->responsiblesBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX).key(
                            checkObj.getResponsibleId()));
    ui->sourcesFinancingBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).key(
                            checkObj.getSourceFinancingId()));
    ui->paymentDocumentBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::PAYMENT_DOCUMENTS_INDEX).key(
                            checkObj.getPaymentDocumentId()));
    ui->completenessBox->setCurrentIndex(checkObj.getCompleteness());
    currentState = (checkObj.isEmpty()) ? States::NewCheck : States::OldCheck;
    if (currentState == States::NewCheck)
        ui->exportButton->setHidden(true);
    else
        ui->exportButton->setHidden(false);
}

void RegisterCheckForm::resetOldData()
{
    PaymentDocumentHandBookViewManager::resetOldData();
    ui->numberEdit->clear();
    ui->registrationDateEdit->setDate(QDate::currentDate());
    ui->checkDateEdit->setDate(QDate::currentDate());
    ui->sumSpinBox->clear();
    ui->numberChecksBox->clear();
    ui->descriptionEdit->clear();
    ui->completenessBox->setCurrentIndex(0);
}

bool RegisterCheckForm::saveCheckObj()
{
    changeDataCheckObj();
    if (currentState == States::OldCheck)
        return checkObj.save();
    else
    {
        currentState = States::OldCheck;
        ui->exportButton->setHidden(false);
        checkObj.add();
        return true;
    }
}

void RegisterCheckForm::changeDataCheckObj()
{
    checkObj.setNumber(ui->numberEdit->text());
    checkObj.setRegistrationDate(ui->registrationDateEdit->date());
    checkObj.setCheckDate(ui->checkDateEdit->date());
    checkObj.setSum(ui->sumSpinBox->value());
    checkObj.setDescription(ui->descriptionEdit->text());
    checkObj.setNumberChecks(ui->numberChecksBox->value());
    auto foo = ui->completenessBox->currentIndex();
    checkObj.setCompleteness((foo >= 0 ? foo : 0));
    checkObj.setProviderId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PROVIDERS_INDEX).value(
                        ui->providersBox->currentText()));
    checkObj.setSubdivisionId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).value(
                        ui->subdivisionsBox->currentText()));
    checkObj.setResponsibleId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX).value(
                        ui->responsiblesBox->currentText()));
    checkObj.setSourceFinancingId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).value(
                        ui->sourcesFinancingBox->currentText()));
    checkObj.setPaymentDocumentId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PAYMENT_DOCUMENTS_INDEX).value(
                        ui->paymentDocumentBox->currentText()));
}

void gui::RegisterCheckForm::on_okButton_clicked()
{
    if (!checkData())
    {
        createExceptionMessageBox(tr("Неккоректно введены данные или не заполнены некоторые поля"));
        return;
    }
    if (!saveCheckObj())
    {
        createErrorMessageBox(tr("Произошла ошибка записи!"));
        return;
    }
    hide();
    emit okClicked();
}

void gui::RegisterCheckForm::on_closeButton_clicked()
{
    hide();
}

void gui::RegisterCheckForm::on_exportButton_clicked()
{
    QString filePath = createSaveFileNameExcelMessageBox();
    if (filePath.isEmpty())
        return;
    if (!checkObj.saveToExcel(filePath))
        createErrorMessageBox(tr("Ошибка записи файла."));
}

void gui::RegisterCheckForm::on_paymentDocumentHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::PAYMENT_DOCUMENTS_INDEX);
}

void gui::RegisterCheckForm::on_providersHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::PROVIDERS_INDEX);
}

void gui::RegisterCheckForm::on_subdivisionsHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX);
}

void gui::RegisterCheckForm::on_responsiblesHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX);
}

void gui::RegisterCheckForm::on_sourcesFinancingHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX);
}
