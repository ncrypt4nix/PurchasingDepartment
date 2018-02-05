#include "addcheckdialog.h"
#include "ui_addcheckdialog.h"

using namespace gui;

AddCheckDialog::AddCheckDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AddCheckDialog)
{
    ui->setupUi(this);
}

AddCheckDialog::~AddCheckDialog()
{
    delete ui;
}

QString AddCheckDialog::getNumber() const
{
    return ui->numberEdit->text();
}

QDate AddCheckDialog::getRegistrationDate() const
{
    return ui->registrationDateEdit->date();
}

QDate AddCheckDialog::getCheckDate() const
{
    return ui->checkDateEdit->date();
}

double AddCheckDialog::getSum() const
{
    return ui->sumSpinBox->value();
}

QString AddCheckDialog::getDescription() const
{
    return ui->descriptionEdit->text();
}
