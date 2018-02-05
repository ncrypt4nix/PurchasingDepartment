#ifndef GLOBALTESTMODULE_H
#define GLOBALTESTMODULE_H

#include <QDebug>

namespace tests
{
    class GlobalTestModule : public QObject
    {
        Q_OBJECT
    public:
        GlobalTestModule(QObject *parent = 0);
        GlobalTestModule(const QString &moduleName, QObject *parent = 0);
        GlobalTestModule(const GlobalTestModule &other);
        /* Виртуальная функция, регистрирущая(вызывающая) все тестируемые методы класса */
        virtual void test();

    protected:
        void setModuleName(const QString &moduleName);
        QString getModuleName() const;

    private:
        QString moduleName;
    };
}

#endif // GLOBALTESTMODULE_H
