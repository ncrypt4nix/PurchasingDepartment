#include "databaseconnectiondialog.h"
#include "ui_databaseconnectiondialog.h"

using namespace gui;

DatabaseConnectionDialog::DatabaseConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DatabaseConnectionDialog)
{
    ui->setupUi(this);
}

DatabaseConnectionDialog::~DatabaseConnectionDialog()
{
    delete ui;
}

QString DatabaseConnectionDialog::getUserName() const
{
    return ui->userNameEdit->text();
}

QString DatabaseConnectionDialog::getHostName() const
{
    return ui->hostNameEdit->text();
}

QString DatabaseConnectionDialog::getPassword() const
{
    return ui->passwordEdit->text();
}
