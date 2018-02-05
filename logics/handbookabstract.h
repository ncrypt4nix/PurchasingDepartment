#ifndef HANDBOOKABSTRACT_H
#define HANDBOOKABSTRACT_H

#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QMap>

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*!
     * \brief Абстрактный класс для всех справочников.
     * При наследовании необходимо проинизиализировать модель model методами setTable и setRelation, и вызвать select
     */
    class HandBookAbstract : public QSqlTableModel
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit HandBookAbstract(QObject *parent = 0);
        /*!
         * \brief Инициализирует модель.
         * Необходимо проинизиализировать модель методами setTable и setNoteName, и вызвать select и updateMap
         * \return Успешность инициализации модели
         */
        virtual bool modelInitialization() = 0;
        /*!
         * \brief Обновляет данные карты справочника
         * \return Успешность операции
         */
        virtual bool updateMap();
        /*!
         * \brief Предоставляет словарь справочника для извлечения данных из нее
         * \return Словарь справочника
         */
        QMap<QString, uint> getMapHandBook();
        /*!
         * \brief Устанавливает фильтр на таблицу, используя прилизительный поиск.
         * Если Будет передана пустая строка, то отменяет предыдущийй фильтр
         * \param value фильтр
         */
        virtual void setApproximateFilter(const QString &value) = 0;

    protected:
        /*! \brief Устанавливает сортировку для справочника */
        void initSort();

    public:
        /*!
         * \brief Возвращает id индекс колонки текущей модели.
         * По умолчанию возвращает 0-ю колонку с id
         */
        static const int COLUMN_ID_INDEX;
        /*!
         * \brief Возвращает индекс колонки со данными текущей модели.
         * По умолчанию возвращает 1-ю колонку с данными
         */
        static const int COLUMN_VALUE_INDEX;

    signals:
        /*! \brief Посылается при изменении данных словаря справочника */
        void mapHandBookChanged();

    protected:
        /*! \brief Словарь хранящий все данные справочника для предоствления их виджетам выбора */
        QMap<QString, uint> mapHandBook;
    };
}

#endif // HANDBOOKABSTRACT_H
