#include "tests/logics_tests/test_database.h"

using namespace tests;

Test_Database::Test_Database(QObject *parent)
    : GlobalTestModule(parent)
{}

Test_Database::Test_Database(const QString& module_name, QObject *parent)
    : GlobalTestModule(module_name, parent)
{}

Test_Database::Test_Database(const GlobalTestModule &other)
    : GlobalTestModule(other)
{}

void Test_Database::test()
{
    GlobalTestModule::test();
    createConnection();
}

void tests::Test_Database::createConnection()
{
    logics::DataBase database;
    QCOMPARE(database.createConnection(), true);
}
