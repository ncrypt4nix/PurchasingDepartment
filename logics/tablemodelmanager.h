#ifndef TABLEMODELMANAGER_H
#define TABLEMODELMANAGER_H

#include "logics/tableregistercontractsmodel.h"
#include "logics/tableregisterchecksmodel.h"
#include "logics/tableregisterprocurementmethodsmodel.h"
#include "exceptions/tablemodelexception.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс управлящий всеми моделями таблицы, их состояниями */
    class TableModelManager : public QObject
    {
        Q_OBJECT
    public:
        /*! \brief Константы определяющие индексы моделей */
        enum class RegisterModelIndex
        {
            /*! \brief константа определящая индекс модели реестра договоров */
            REGISTER_CONTRACT_MODEL_INDEX,
            /*! \brief константа определящая индекс модели реестра счетов */
            REGISTER_CHECK_MODEL_INDEX,
            /*! \brief константа определящая индекс модели реестра конкурентных способов закупки */
            REGISTER_PROCUREMENT_METHODS_MODEL_INDEX
        };

    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         * \param currentModelNum Номер будущей текущей модели
         * \throw TableModelException при ошибке инициализации модели и отсутствии модели
         */
        explicit TableModelManager(const RegisterModelIndex &currentModelNum, QObject *parent = 0);
        /*!
         * \brief Возвращает ссылку на модель, для подключения к виду
         * \return Модель класса QSqlQueryModel
         */
        QSqlQueryModel *getCurrentModel() const;
        /*!
         * \brief Изменяет текущую действующую модель на новую
         * \param changedModelNum Номер будущей текущей модели
         * \return  Успешность смены действующей модели
         */
        bool changeModel(const RegisterModelIndex &changedModelNum);
        /*!
         * \brief Удаляет запись из таблицы в БД.
         * \param index Любой индекс в удаляемой строке
         * \return Успешность удаления строки из БД
         */
        bool deleteColumn(const QModelIndex &index) const;
        /*!
         * \brief Возвращает индекс текущей модели
         * \return Индекс текущей модели
         */
        RegisterModelIndex getModelIndex() const;
        /*!
         * \brief Возвращает номер колонки с датой окончания из запроса модели контракта к БД
         * \return Номер колонки с датой окончания
         * \throw TableModelException при ошибке использования другой модели
         */
        uint getColumnEndDateNumber() const;
        /*!
         * \brief Получить индекс завершенности в таблице
         * \return индекс завершенности в таблице
         */
        uint getColumnCompletenessNumber() const;
        /*!
         * \brief Возвращает номер колонки с завершоностью процесса из запроса модели конкурентных способов закупки к БД
         * \return Номер колонки с завершоностью процесса
         * \throw TableModelException при ошибке использования другой модели
         */
        uint getColumnProcedureCompleteNumber() const;
        /*!
         * \brief Возвращает номер столбца c id, определенный в момент инициализации модели
         * \return Номер столбца c id
         */
        uint getColumnIdNumber() const;
        /*!
         * \brief Возвращает номер столбца c СМП, определенный в момент инициализации модели
         * \return Номер столбца c СМП
         * \throw TableModelException при ошибке использования другой модели
         */
        uint getColumnSMPNumber() const;
        /*!
         * \brief Устанавливает начальное состояние модели
         * \return Успешность установки состояния
         */
        bool setStartState() const;
        /*!
         * \brief Получить обьект поиска
         * \return обьект поиска
         */
        virtual FindObjectAbstract *getFindObject();
        /*!
         * \brief Применить запрос поиска к модели
         * \param findObj обьект поиска
         * \return успешность операции
         */
        bool findQuery(FindObjectAbstract *findObj);


    public slots:
        /*!
         * \brief Обновляет модель БД
         * \return Успешность обновления модели
         */
        bool updateModel() const;

    protected:
        /*!
         * \brief Изменяет текущую модель на новую
         * \param value Номер будущей текущей модели
         * \return Успешность смены модели
         */
        bool setCurrentModel(const RegisterModelIndex &value);

    private:
        TableModelAbstract* currentModel;
        TableRegisterContractsModel* registerContractsModel;
        TableRegisterChecksModel* registerChecksModel;
        TableRegisterProcurementMethodsModel* registerProcurementMethodsModel;
        RegisterModelIndex modelIndex;
    };
}

#endif // TABLEMODELMANAGER_H
