#include "globaltest.h"

using namespace tests;

GlobalTest::GlobalTest(QObject *parent)
    : QObject(parent)
{
    testModules << (GlobalTestModule*) new Test_Database("Test_Database", this)
                 << (GlobalTestModule*) new Test_TableContractsModel("Test_TableContractsModel", this);
}

void GlobalTest::tests()
{
    for (auto next : testModules)
        next->test();
}
