#ifndef TEST_TABLECONTRACTSMODEL_H
#define TEST_TABLECONTRACTSMODEL_H

#include <QtTest/QtTest>
#include "tests/globaltestmodule.h"
#include "logics/database.h"
#include "logics/tableregistercontractsmodel.h"

namespace tests
{
    class Test_TableContractsModel : public GlobalTestModule
    {
        Q_OBJECT
    public:
        Test_TableContractsModel(QObject *parent = 0);
        Test_TableContractsModel(const QString& moduleName, QObject *parent = 0);
        Test_TableContractsModel(const Test_TableContractsModel& other);
        virtual void test();

    private slots:
        void modelInitialization() const;
    };
}

#endif // TEST_TABLECONTRACTSMODEL_H
