#ifndef TABLEREGISTERCHECKSMODEL_H
#define TABLEREGISTERCHECKSMODEL_H

#include <QSqlRecord>
#include <QModelIndex>

#include "logics/tablemodelabstract.h"
#include "logics/findobjectcheck.h"
#include "logics/checkobject.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief класс обертка для модели реестра счетов */
    class TableRegisterChecksModel : public TableModelAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit TableRegisterChecksModel(QObject *parent = 0);

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
         * \brief Получить обьект поиска
         * \return обьект поиска
         */
        virtual FindObjectAbstract *getFindObject();
    };
}

#endif // TABLEREGISTERCHECKSMODEL_H
