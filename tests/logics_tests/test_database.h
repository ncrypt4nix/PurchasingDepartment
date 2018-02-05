#ifndef TEST_DATABASE_H
#define TEST_DATABASE_H

#include <QtTest/QtTest>
#include "tests/globaltestmodule.h"
#include "logics/database.h"

namespace tests
{
    class Test_Database : public GlobalTestModule
    {
        Q_OBJECT
    public:
        Test_Database(QObject *parent = 0);
        Test_Database(const QString& moduleName, QObject *parent = 0);
        Test_Database(const GlobalTestModule& other);
        virtual void test();

    private slots:
        void createConnection();
    };
}

#endif // TEST_DATABASE_H
