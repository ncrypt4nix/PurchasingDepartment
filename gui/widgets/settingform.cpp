#include "settingform.h"
#include "ui_settingform.h"

using namespace gui;

SettingForm::SettingForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingForm)
{
    ui->setupUi(this);
}

SettingForm::~SettingForm()
{
    delete ui;
}

void SettingForm::resetData()
{
    ui->WarningExpirationContractSpinBox->setValue(logics::SettingApp::getSettingApp().getWarningExpirationContract());
    if (logics::SettingApp::getSettingApp().getStretchTable())
        ui->stretchTableBox->setChecked(true);
    else
        ui->stretchTableBox->setChecked(false);
}

void gui::SettingForm::on_closeButton_clicked()
{
    hide();
}

void gui::SettingForm::on_saveButton_clicked()
{
    logics::SettingApp::getSettingApp().setWarningExpirationContract(ui->WarningExpirationContractSpinBox->value());
    logics::SettingApp::getSettingApp().setStretchTable(ui->stretchTableBox->isChecked());
    emit settingChange();
}

void gui::SettingForm::on_pushButton_clicked()
{
    logics::DataBase::setUserName("");
    logics::DataBase::setHostName("");
    logics::DataBase::setPassword("");
    emit reconnect();
}
