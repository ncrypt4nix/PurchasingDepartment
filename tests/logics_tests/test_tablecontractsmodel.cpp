#include "test_tablecontractsmodel.h"

using namespace tests;

Test_TableContractsModel::Test_TableContractsModel(QObject *parent)
    : GlobalTestModule(parent)
{}

Test_TableContractsModel::Test_TableContractsModel(const QString &module_name, QObject *parent)
    : GlobalTestModule(module_name, parent)
{}

Test_TableContractsModel::Test_TableContractsModel(const Test_TableContractsModel &other)
    : GlobalTestModule(other)
{}

void Test_TableContractsModel::test()
{
    GlobalTestModule::test();
    modelInitialization();
}

void Test_TableContractsModel::modelInitialization() const
{
    logics::DataBase database;
    database.createConnection();
    logics::TableRegisterContractsModel table_contracts_model;
    QCOMPARE(table_contracts_model.modelInitialization(), true);
}
