#ifndef CONTRACTPROCUREMENTMETHODOBJECT_H
#define CONTRACTPROCUREMENTMETHODOBJECT_H

#include "logics/contractobject.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс предоставляющий интерфейс и управление к конкретному контракту */
    class ContractProcurementMethodObject : public ContractObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit ContractProcurementMethodObject(QObject *parent = 0);

        /*!
         * \brief Получить id реестра конкурентных способов закупки
         * \return id реестра конкурентных способов закупки
         */
        uint getRegisterProcurementMethodId() const;
        /*!
         * \brief Изменить id реестра конкурентных способов закупки
         * \param value id реестра конкурентных способов закупки
         * \return id реестра конкурентных способов закупки
         */
        bool setRegisterProcurementMethodId(const uint &value);
        /*!
         * \brief Сохраняет новый договор в БД
         * \return успешность выполнения операции
         */
        virtual bool add();
        /*!
         * \brief Копирование данных из другого обьекта
         * \param other другой обьект
         */
        virtual void copyData(const ContractProcurementMethodObject &other);

    public:
        /*!
         * \brief Оператор присваивания
         * \param other другой обьект
         * \return ссылка на данный обьект
         */
        ContractProcurementMethodObject &operator=(const ContractProcurementMethodObject &other);

    public:
        /*! \brief Реестр конкурентных способов закупки */
        static const QString REGISTER_PROCUREMENT_METHODS;

    protected:
        /*! \brief Счета реестра конкурентных способов закупки */
        static const QString REGISTER_PROCUREMENT_METHODS_CHECKS;

    private:
        uint registerProcurementMethodId = 0;
    };
}

#endif // CONTRACTPROCUREMENTMETHODOBJECT_H
