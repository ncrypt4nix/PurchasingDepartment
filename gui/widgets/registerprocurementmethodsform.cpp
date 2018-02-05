#include "registerprocurementmethodsform.h"
#include "ui_registerprocurementmethodsform.h"

using namespace gui;

RegisterProcurementMethodsForm::RegisterProcurementMethodsForm(QWidget *parent) :
    ProcurementMethodsHandBookViewManager(parent),
    ui(new Ui::RegisterProcurementMethodsForm)
{
    ui->setupUi(this);
    procurementMethodsBox = ui->procurementMethodBox;
}

RegisterProcurementMethodsForm::~RegisterProcurementMethodsForm()
{
    delete ui;
}

void RegisterProcurementMethodsForm::setProcurementMethodObj(const logics::ProcurementMethodObject &value)
{
    procurementMethodObj = value;
    ui->numberNoticeEdit->setText(procurementMethodObj.getNumberNotice());
    ui->noticeDateEdit->setDate(procurementMethodObj.getNoticeDate());
    ui->procurementObjectEdit->setText(procurementMethodObj.getProcurementObject());
    ui->startingPriceSpinBox->setValue(procurementMethodObj.getStartingPrice());
    ui->startDateDeadlineEdit->setDate(procurementMethodObj.getStartDateDeadline());
    ui->endDateDeadlineEdit->setDate(procurementMethodObj.getEndDateDeadline());
    ui->openingEnvelopesDateEdit->setDate(procurementMethodObj.getOpeningEnvelopesDate());
    ui->summarizingDateEdit->setDate(procurementMethodObj.getSummarizingDate());
    ui->procedureCompleteBox->setCurrentIndex(procurementMethodObj.getProcedureComplete());
    ui->registrationDateEdit->setDate(procurementMethodObj.getRegistrationDate());
    ui->smpBox->setCurrentIndex(procurementMethodObj.getSmp());
    ui->completenessBox->setCurrentIndex(procurementMethodObj.getCompleteness());
    ui->procurementMethodBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX).key(
                            procurementMethodObj.getProcurementMethodId()));
    if (procurementMethodObj.isEmpty())
        changeState(States::NewProcurementMethod);
    else if(procurementMethodObj.getContractProcurementMethodObject()->isEmpty())
        changeState(States::OldProcurementMethod);
    else
        changeState(States::OldAllProcurementMethod);
}

void RegisterProcurementMethodsForm::resetOldData()
{
    ProcurementMethodsHandBookViewManager::resetOldData();
    ui->numberNoticeEdit->clear();
    ui->noticeDateEdit->setDate(QDate::currentDate());
    ui->procurementObjectEdit->clear();
    ui->startingPriceSpinBox->clear();
    ui->startDateDeadlineEdit->setDate(QDate::currentDate());
    ui->endDateDeadlineEdit->setDate(QDate::currentDate());
    ui->openingEnvelopesDateEdit->setDate(QDate::currentDate());
    ui->summarizingDateEdit->setDate(QDate::currentDate());
    ui->registrationDateEdit->setDate(QDate::currentDate());
    ui->procedureCompleteBox->setCurrentIndex(0);
    ui->smpBox->setCurrentIndex(0);
    ui->completenessBox->setCurrentIndex(0);
}

void RegisterProcurementMethodsForm::setHandBookManager(logics::HandBookManager *value)
{
    ProcurementMethodsHandBookViewManager::setHandBookManager(value);
    ui->ContractInformationWidget->setHandBookManager(value);
}

void RegisterProcurementMethodsForm::setHandBookForm(HandBookForm *value)
{
    ProcurementMethodsHandBookViewManager::setHandBookForm(value);
    ui->ContractInformationWidget->setHandBookForm(value);
}

bool RegisterProcurementMethodsForm::saveProcurementMethodObj()
{
    changeDataProcurementMethodObj();
    if (currentState ==States::NewProcurementMethod)
    {
        if (!procurementMethodObj.add())
            return false;
        changeState(States::OldProcurementMethod);
        return true;
    }
    else if (currentState == States::OldProcurementMethod)
        return procurementMethodObj.save();
    else if (currentState == States::OldAddContractProcurementMethod)
    {
        if (!procurementMethodObj.save())
            return false;
        if (!ui->ContractInformationWidget->saveContractObj())
            return false;
        changeState(States::OldAllProcurementMethod);
        return true;
    }
    else
    {
        if (!procurementMethodObj.save())
            return false;
        return ui->ContractInformationWidget->saveContractObj();
    }
}

void RegisterProcurementMethodsForm::changeDataProcurementMethodObj()
{
    procurementMethodObj.setNumberNotice(ui->numberNoticeEdit->text());
    procurementMethodObj.setNoticeDate(ui->noticeDateEdit->date());
    procurementMethodObj.setProcurementObject(ui->procurementObjectEdit->text());
    procurementMethodObj.setStartingPrice(ui->startingPriceSpinBox->value());
    procurementMethodObj.setStartDateDeadline(ui->startDateDeadlineEdit->date());
    procurementMethodObj.setEndDateDeadline(ui->endDateDeadlineEdit->date());
    procurementMethodObj.setOpeningEnvelopesDate(ui->openingEnvelopesDateEdit->date());
    procurementMethodObj.setSummarizingDate(ui->summarizingDateEdit->date());
    procurementMethodObj.setRegistrationDate(ui->registrationDateEdit->date());
    auto procedureComplete = ui->procedureCompleteBox->currentIndex();
    auto smp = ui->smpBox->currentIndex();
    auto completeness = ui->completenessBox->currentIndex();
    procurementMethodObj.setCompleteness((completeness >= 0 ? completeness : 0));
    procurementMethodObj.setProcedureComplete((procedureComplete >= 0 ? procedureComplete : 0));
    procurementMethodObj.setSmp((smp >= 0 ? smp : 0));
    procurementMethodObj.setProcurementMethodId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX).value(
                                                    ui->procurementMethodBox->currentText()));
}

void RegisterProcurementMethodsForm::changeState(const RegisterProcurementMethodsForm::States &state)
{
    ui->ContractInformationWidget->setContractObj(procurementMethodObj.getContractProcurementMethodObject());
    if (state == States::NewProcurementMethod)
    {
        currentState = States::NewProcurementMethod;
        ui->ContractInformationWidget->setHidden(true);
        ui->hideContractButton->setHidden(true);
        ui->addContractButton->setHidden(true);
        ui->contractExportButton->setHidden(true);
        ui->noticeExportButton->setHidden(true);
        ui->exportButton->setHidden(true);
        ui->ContractInformationWidget->resetOldData();
    }
    else if (state == States::OldProcurementMethod)
    {
        currentState = States::OldProcurementMethod;
        ui->ContractInformationWidget->setHidden(true);
        ui->hideContractButton->setHidden(true);
        ui->addContractButton->setHidden(false);
        ui->contractExportButton->setHidden(true);
        ui->noticeExportButton->setHidden(false);
        ui->exportButton->setHidden(false);
        ui->ContractInformationWidget->resetOldData();
    }
    else if (state == States::OldAddContractProcurementMethod)
    {
        currentState = States::OldAddContractProcurementMethod;
        ui->ContractInformationWidget->setHidden(false);
        ui->hideContractButton->setHidden(true);
        ui->addContractButton->setHidden(true);
        ui->contractExportButton->setHidden(true);
        ui->noticeExportButton->setHidden(false);
        ui->exportButton->setHidden(false);
        ui->ContractInformationWidget->resetOldData();
    }
    else if (state == States::OldAllProcurementMethod)
    {
        currentState = States::OldAllProcurementMethod;
        ui->ContractInformationWidget->setHidden(false);
        ui->hideContractButton->setHidden(false);
        ui->addContractButton->setHidden(true);
        ui->contractExportButton->setHidden(false);
        ui->noticeExportButton->setHidden(false);
        ui->exportButton->setHidden(false);
    }
}

void gui::RegisterProcurementMethodsForm::on_okButton_clicked()
{
    QString invalidEntry = tr("Неккоректно введены данные или не заполнены некоторые поля");
    if (!checkData())
    {
        createExceptionMessageBox(invalidEntry);
        return;
    }
    if ((currentState == States::OldAddContractProcurementMethod
            || currentState == States::OldAllProcurementMethod)
            && !ui->ContractInformationWidget->checkData())
    {
        createExceptionMessageBox(invalidEntry);
        return;
    }
    if (!saveProcurementMethodObj())
    {
        createErrorMessageBox(tr("Произошла ошибка записи!"));
        return;
    }
    hide();
    emit okClicked();
}

void gui::RegisterProcurementMethodsForm::on_closeButton_clicked()
{
    hide();
}

void gui::RegisterProcurementMethodsForm::on_hideContractButton_clicked()
{
    if (ui->ContractInformationWidget->isHidden())
        ui->ContractInformationWidget->setHidden(false);
    else
        ui->ContractInformationWidget->setHidden(true);
}

void gui::RegisterProcurementMethodsForm::on_addContractButton_clicked()
{
    changeState(States::OldAddContractProcurementMethod);
}

void gui::RegisterProcurementMethodsForm::on_applyButton_clicked()
{
    if (!checkData() || !ui->ContractInformationWidget->checkData())
    {
        createExceptionMessageBox(tr("Неккоректно введены данные или не заполнены некоторые поля"));
        return;
    }
    if (!saveProcurementMethodObj())
    {
        createErrorMessageBox(tr("Произошла ошибка записи!"));
        return;
    }
    emit okClicked();
}

void gui::RegisterProcurementMethodsForm::on_procurementMethodHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX);
}

void gui::RegisterProcurementMethodsForm::on_exportButton_clicked()
{
    QString filePath = createSaveFileNameExcelMessageBox();
    if (filePath.isEmpty())
        return;
    if (!procurementMethodObj.saveExtendedToExcel(filePath))
        createErrorMessageBox(tr("Ошибка записи файла."));
}

void gui::RegisterProcurementMethodsForm::on_noticeExportButton_clicked()
{
    QString filePath = createSaveFileNameExcelMessageBox();
    if (filePath.isEmpty())
        return;
    if (!procurementMethodObj.saveToExcel(filePath))
        createErrorMessageBox(tr("Ошибка записи файла."));
}

void gui::RegisterProcurementMethodsForm::on_contractExportButton_clicked()
{
    QString filePath = createSaveFileNameExcelMessageBox();
    if (filePath.isEmpty())
        return;
    if (!procurementMethodObj.getContractProcurementMethodObject()->saveExtendedToExcel(filePath))
        createErrorMessageBox(tr("Ошибка записи файла."));
}
