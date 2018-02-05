#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include "logics/findobjectabstract.h"
#include "logics/findobjectabstract.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Абстрактный класс модели таблицы */
    class TableModelAbstract : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit TableModelAbstract(QObject *parent = 0);
        /*!
         * \brief Выполняет запрос к БД и инициализирует модель
         * \return Успешность инициализации модели
         */
        virtual bool modelInitialization() = 0;
        /*!
         * \brief Возвращает ссылку на модель, для подключения к виду
         * \return Модель класса QSqlQueryModel
         */
        QSqlQueryModel *getModel() const;
        /*!
         * \brief Получить обьект поиска
         * \return обьект поиска
         */
        virtual FindObjectAbstract *getFindObject() = 0;
        /*!
         * \brief Применить запрос поиска к модели
         * \param findObj обьект поиска
         * \return успешность операции
         */
        bool findQuery(FindObjectAbstract *findObj);
        /*!
         * \brief Возвращает номер столбца c id, определенный в момент инициализации модели
         * \return Номер столбца c id
         */
        uint getColumnIdNumber() const;
        /*!
         * \brief Удаляет запись из таблицы в БД.
         * \param index Любой индекс в удаляемой строке
         * \return Успешность удаления строки из БД
         */
        virtual bool deleteColumn(const QModelIndex& index) const = 0;
        /*!
         * \brief Обновляет модель БД
         * \return  Успешность обновления модели
         */
        bool updateModel() const;
        /*!
         * \brief Устанавливает начальное состояние модели
         * \return Успешность установки состояния
         */
        virtual bool setStartQueryState() const = 0;
        /*!
         * \brief Получить индекс завершенности в таблице
         * \return индекс завершенности в таблице
         */
        uint getCompletenessNumber() const;
        /*!
         * \brief Установить индекс завершенности в таблице
         * \param value индекс завершенности в таблице
         */
        void setCompletenessNumber(const uint &value);

    protected:
        /*!
         * \brief Проверяет модель на наличие последних ошибок.
         * Внимание! Если ошибка была инициализирована не в вызываещем методе, то будет все равно возвращена последнаяя ошибка
         * \param operation Текст операции для информативного qDebug
         * \return true если ошибки не было, false в противном случае
         */
        bool isNotValidLastError(const QString& operation) const;
        /*!
         * \brief Проверяет модель на наличие последних ошибок.
         * Внимание! Если ошибка была инициализирована не в вызываещем методе, то будет все равно возвращена последнаяя ошибка
         * \param query обьект запроса для информативного qDebug
         * \param operation Текст операции для информативного qDebug
         * \return true если ошибки не было, false в противном случае
         */
        bool isNotValidLastError(const QSqlQuery& query, const QString& operation) const;

    protected:
        /*!
         * \brief Устанавливает номер столбца с id в таблице модели
         * \param value Номер столца с id
         */
        void setColumnIdNumber(const uint &value);
        /*! \brief Модель запроса */
        QSqlQueryModel *model;

    private:
        uint columnIdNumber;
        uint completenessNumber;
    };
}

#endif // TABLEMODEL_H
