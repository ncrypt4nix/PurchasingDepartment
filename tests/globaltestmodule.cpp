#include "globaltestmodule.h"

using namespace tests;

GlobalTestModule::GlobalTestModule(QObject *parent)
    : QObject(parent)
{}

GlobalTestModule::GlobalTestModule(const QString &moduleName, QObject *parent)
    : QObject(parent)
{
    this->moduleName = moduleName;
}

GlobalTestModule::GlobalTestModule(const GlobalTestModule &other)
    : QObject(other.parent())
{
    this->moduleName = other.moduleName;
}

void GlobalTestModule::test()
{
    qDebug() << tr("Тестирование модуля: ") << moduleName;
}

void GlobalTestModule::setModuleName(const QString &moduleName)
{
    this->moduleName = moduleName;
}

QString GlobalTestModule::getModuleName() const
{
    return moduleName;
}
