#ifndef GLOBALTEST_H
#define GLOBALTEST_H

#include <QList>
#include "tests/globaltestmodule.h"
#include "tests/logics_tests/test_database.h"
#include "tests/logics_tests/test_tablecontractsmodel.h"

namespace tests
{
    class GlobalTest : public QObject
    {
        Q_OBJECT
    public:
        /* Регистрирует все тестируемые модули */
        explicit GlobalTest(QObject *parent = 0);

    private slots:
        /* Тестирует все модули */
        void tests();

    private:
        /* Список всех зарегестрированных тестируемых модулей */
        QList<GlobalTestModule*> testModules;
    };
}

#endif // GLOBALTEST_H
