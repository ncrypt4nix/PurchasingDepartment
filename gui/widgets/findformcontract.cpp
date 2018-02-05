#include "findformcontract.h"
#include "ui_findformcontract.h"

using namespace gui;

FindFormContract::FindFormContract(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindFormContract)
{
    ui->setupUi(this);
}

FindFormContract::~FindFormContract()
{
    delete ui;
}

void FindFormContract::resetOldData()
{
    ui->FindFormContractWidget->resetOldData();
}

void FindFormContract::setFindObjectContract(logics::FindObjectContract *value)
{
    ui->FindFormContractWidget->setFindObjectContract(value);
}

logics::FindObjectContract *FindFormContract::getFindObjectContract()
{
    return ui->FindFormContractWidget->getFindObjectContract();
}

void FindFormContract::setHandBookManager(logics::HandBookManager *value)
{
    ui->FindFormContractWidget->freeObject();
    ui->FindFormContractWidget->setHandBookManager(value);
}

void gui::FindFormContract::on_okButton_clicked()
{
    if (!ui->FindFormContractWidget->checkData())
    {
        createExceptionMessageBox(tr("Данные не были введены."));
        return;
    }
    ui->FindFormContractWidget->fillingFindObjectContract();
    hide();
    emit okClicked();
}

void gui::FindFormContract::on_closeButton_clicked()
{
    hide();
}
