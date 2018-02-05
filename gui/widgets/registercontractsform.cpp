#include "registercontractsform.h"
#include "ui_registercontractsform.h"

using namespace gui;

RegisterContractsForm::RegisterContractsForm(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::RegisterContractsForm)
{
    ui->setupUi(this);
    connect(ui->ContractInformationWidget, SIGNAL(changedState(ContractInformationWidget::States)),
            this, SLOT(changeHideExportButton(ContractInformationWidget::States)));
}

RegisterContractsForm::~RegisterContractsForm()
{
    delete ui;
}

void RegisterContractsForm::setHandBookManager(logics::HandBookManager *value)
{
    ui->ContractInformationWidget->setHandBookManager(value);
}

void RegisterContractsForm::setContractObj(logics::ContractObject *value)
{
    ui->ContractInformationWidget->setContractObj(value);
    idContract = value->getId();
    if (logics::InformationEndContracts::checkId(idContract))
        ui->endContractButton->setHidden(false);
    else
        ui->endContractButton->setHidden(true);
}

void RegisterContractsForm::resetOldData()
{
    ui->ContractInformationWidget->resetOldData();
}

void RegisterContractsForm::setHandBookForm(HandBookForm *value)
{
    ui->ContractInformationWidget->setHandBookForm(value);
}

void RegisterContractsForm::changeHideExportButton(ContractInformationWidget::States state)
{
    if (state == ContractInformationWidget::States::NewContract)
        ui->exportButton->setHidden(true);
    else
        ui->exportButton->setHidden(false);
}

void gui::RegisterContractsForm::on_closeButton_clicked()
{
    hide();
}

void gui::RegisterContractsForm::on_okButton_clicked()
{
    if (!ui->ContractInformationWidget->checkData())
    {
        createExceptionMessageBox(tr("Неккоректно введены данные или не заполнены некоторые поля"));
        return;
    }
    if (!ui->ContractInformationWidget->saveContractObj())
    {
        createErrorMessageBox(tr("Произошла ошибка записи!"));
        return;
    }
    hide();
    emit okClicked();
}

void gui::RegisterContractsForm::on_applyButton_clicked()
{
    if (!ui->ContractInformationWidget->checkData())
    {
        createExceptionMessageBox(tr("Неккоректно введены данные или не заполнены некоторые поля"));
        return;
    }
    if (!ui->ContractInformationWidget->saveContractObj())
    {
        createErrorMessageBox(tr("Произошла ошибка записи!"));
        return;
    }
    emit okClicked();
}

void gui::RegisterContractsForm::on_endContractButton_clicked()
{
    logics::InformationEndContracts::deleteId(idContract);
    ui->endContractButton->setHidden(true);
    ui->ContractInformationWidget->completeContract();
}

void gui::RegisterContractsForm::on_exportButton_clicked()
{
    ui->ContractInformationWidget->exportToExcel();
}
