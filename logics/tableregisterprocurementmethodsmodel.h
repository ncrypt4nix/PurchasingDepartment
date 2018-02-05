#ifndef TABLEREGISTERPROCUREMENTMETHODSMODEL_H
#define TABLEREGISTERPROCUREMENTMETHODSMODEL_H

#include <QSqlRecord>
#include <QModelIndex>

#include "logics/tablemodelabstract.h"
#include "logics/findobjectprocurementmethod.h"
#include "logics/procurementmethodobject.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс-Обертка для модели реестра конкурентных способов закупки */
    class TableRegisterProcurementMethodsModel : public TableModelAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit TableRegisterProcurementMethodsModel(QObject *parent = 0);

    public:
        /*!
         * \brief Выполняет запрос к БД и инициализирует модель
         * \return Успешность инициализации модели
         */
        virtual bool modelInitialization();
        /*!
         * \brief Удаляет запись о контракте в БД.
         * \param index Любой индекс в удаляемой строке
         * \return Успешность удаления контракта
         */
        virtual bool deleteColumn(const QModelIndex &index) const;
        /*!
         * \brief Устанавливает начальное состояние модели
         * \return Успешность установки состояния
         */
        virtual bool setStartQueryState() const;

        /*!
         * \brief Возвращает номер столбца завершенности процедуры
         * \return Номер столбца завершенности процедуры
         */
        uint getColumnProcedureCompleteNumber() const;
        /*!
         * \brief Получить обьект поиска
         * \return обьект поиска
         */
        virtual FindObjectAbstract *getFindObject();
        /*!
         * \brief Получить СМП
         * \return СМП
         */
        uint getColumnSMPNumber() const;
        /*!
         * \brief Установить СМП
         * \param value СМП
         */
        void setColumnSMPNumber(const uint &value);

    protected:
        /*!
         * \brief Устанавливает номер столбца завершенности процедуры
         * \param value Номер столбца завершенности процедуры
         */
        void setColumnProcedureCompleteNumber(const uint &value);

    private:
        uint columnProcedureCompleteNumber;
        uint columnSMPNumber;
    };
}

#endif // TABLEREGISTERPROCUREMENTMETHODSMODEL_H
