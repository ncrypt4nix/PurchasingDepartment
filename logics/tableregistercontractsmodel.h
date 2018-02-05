#ifndef TABLECONTRACTSMODEL_H
#define TABLECONTRACTSMODEL_H

#include <QSqlRecord>
#include <QModelIndex>

#include "logics/tablemodelabstract.h"
#include "logics/findobjectcontract.h"
#include "logics/contractobject.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс-Обертка для модели реестра договоров */
    class TableRegisterContractsModel : public TableModelAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit TableRegisterContractsModel(QObject *parent = 0);
        /*!
         * \brief Выполняет запрос к БД и инициализирует модель
         * \return Успешность инициализации модели
         */
        virtual bool modelInitialization();
        /*!
         * \brief Возвращает номер столбца даты окончания, определенный в момент инициализации модели
         * \return Номер столбца даты окончания
         */
        uint getColumnEndDateNumber() const;
        /*!
         * \brief Удаляет запись о контракте в БД.
         * \param index Любой индекс в удаляемой строке
         * \return Успешность удаления контракта
         */
        virtual bool deleteColumn(const QModelIndex& index) const;
        /*!
         * \brief Устанавливает начальное состояние модели
         * \return Успешность установки состояния
         */
        virtual bool setStartQueryState() const;
        /*!
         * \brief Получить обьект поиска
         * \return обьект поиска
         */
        virtual FindObjectAbstract *getFindObject();

    private:
        uint columnEndDateNumber;
    };
}

#endif // TABLECONTRACTSMODEL_H
