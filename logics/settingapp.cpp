#include "settingapp.h"

using namespace logics;

const QString SettingApp::ORGANIZATION = "OuroborosSK";
const QString SettingApp::APPLICATION = tr("Реестр 223-ФЗ");
const QString SettingApp::SETTING_GROUP = "/Settings";
const QString SettingApp::DATABASE_GROUP = "/DataBase";
const QString SettingApp::USER_VALUE = "/User";
const QString SettingApp::HOST_VALUE = "/Host";
const QString SettingApp::PASSWORD_VALUE = "/Password";
const QString SettingApp::APP_GROUP = "/AppsGroup";
const QString SettingApp::WARNING_EXPIRATION_CONTRACT_VALUE = "/WarningExpirationContract";
const QString SettingApp::STRETCH_TABLE_VALUE = "/StretchTable";

SettingApp &SettingApp::getSettingApp()
{
    static SettingApp self(ORGANIZATION, APPLICATION);
    return self;
}

void SettingApp::setUserNameForDB(const QString &user_name)
{
    setValue(SETTING_GROUP + DATABASE_GROUP + USER_VALUE, user_name);
}

QString SettingApp::getUserNameForDB() const
{
    return value(SETTING_GROUP + DATABASE_GROUP + USER_VALUE, "root").toString();
}

void SettingApp::setHostNameForDB(const QString &host_name)
{
    setValue(SETTING_GROUP + DATABASE_GROUP + HOST_VALUE, host_name);
}

QString SettingApp::getHostNameForDB() const
{
    return value(SETTING_GROUP + DATABASE_GROUP + HOST_VALUE, "localhost").toString();
}

void SettingApp::setPasswordForDB(const QString &password)
{
    setValue(SETTING_GROUP + DATABASE_GROUP + PASSWORD_VALUE, password);
}

QString SettingApp::getPasswordForDB() const
{
    return value(SETTING_GROUP + DATABASE_GROUP + PASSWORD_VALUE, "").toString();
}

int SettingApp::getWarningExpirationContract() const
{
    return value(SETTING_GROUP + APP_GROUP + WARNING_EXPIRATION_CONTRACT_VALUE, 3).toInt();
}

void SettingApp::setWarningExpirationContract(const int &value)
{
    setValue(SETTING_GROUP + APP_GROUP + WARNING_EXPIRATION_CONTRACT_VALUE, value);
}

bool SettingApp::getStretchTable() const
{
    return value(SETTING_GROUP + APP_GROUP + STRETCH_TABLE_VALUE, false).toBool();
}

void SettingApp::setStretchTable(const bool &value)
{
    setValue(SETTING_GROUP + APP_GROUP + STRETCH_TABLE_VALUE, value);
}

SettingApp::SettingApp(const QString &organization, const QString &application, QObject *parent)
    : QSettings(organization, application, parent)
{}

