#ifndef FINDOBJECTABSTRACT_H
#define FINDOBJECTABSTRACT_H

#include <QObject>
#include <QVariant>
#include <QDebug>

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Абстрактный класс для реализации поиска модели */
    class FindObjectAbstract : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский оьбект
         */
        explicit FindObjectAbstract(QObject *parent = 0);
        /*!
         * \brief Возвращает поисковой запрос для модели
         * \return поисковой запрос
         */
        virtual QString getFindQuery() const = 0;
        /*! \brief Класс хранящий данные о поле таблицы */
        class FindField
        {
        public:
            /*! \brief Конструктор */
            FindField();
            /*!
             * \brief Получить значение для поиска от пользователя
             * \return значение для поиска
             */
            QVariant getFindValue() const;
            /*!
             * \brief Установить значение для поиска пользователя
             * \param value значение для поиска
             */
            void setFindValue(const QVariant &value);
            /*!
             * \brief Определяет изменялось ли значение поля
             * \return изменение значения поля
             */
            bool isChanged() const;

        private:
            bool changed = false;
            QVariant findValue;
        };
    };
}
#endif // FINDOBJECTABSTRACT_H
