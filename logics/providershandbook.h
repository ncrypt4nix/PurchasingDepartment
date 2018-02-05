#ifndef PROVIDERSHANDBOOK_H
#define PROVIDERSHANDBOOK_H

#include <QDebug>
#include "logics/handbookabstract.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс-Справочник для Поставщиков товаров\услуг */
    class ProvidersHandBook : public HandBookAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit ProvidersHandBook(QObject *parent = 0);

        // HandBookAbstract interface
    public:
        /*!
         * \brief Инициализирует модель.
         * \return Успешность инициализации модели
         */
        virtual bool modelInitialization();
        /*!
         * \brief Устанавливает фильтр на таблицу, используя прилизительный поиск.
         * Если Будет передана пустая строка, то отменяет предыдущийй фильтр
         * \param value фильтр
         */
        virtual void setApproximateFilter(const QString &value);
    };
}

#endif // PROVIDERSHANDBOOK_H
