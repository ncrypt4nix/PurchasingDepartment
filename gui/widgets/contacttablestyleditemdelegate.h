#ifndef CONTACTTABLESTYLEDITEMDELEGATE_H
#define CONTACTTABLESTYLEDITEMDELEGATE_H

#include <QBrush>
#include <QPainter>

#include "gui/widgets/completenessstyleditemdelegate.h"
#include "logics/informationendcontracts.h"
#include "logics/settingapp.h"

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*!
     * \brief Делегат для раскрашивания таблицы контактов в различные цвета, в зависимости от истечения срока договора.
     * Прежде чем использовать делегат, необходимо установить номер столбца даты.
     */
    class ContactTableStyledItemDelegate : public CompletenessStyledItemDelegate
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор делегата
         * \param parent Родительский виджет окна
         */
        explicit ContactTableStyledItemDelegate(QObject *parent = 0);
        /*!
         * \brief Переопределенный метод QSomeColumnDelegate::paint отрисовки и раскрашивания строк талицы
         * \param painter Выполняет низкоуровневое рисование на виджетах и других устройствах рисования
         * \param option Используется для описания параметров, используемых для рисования элемента в виджете
         * \param index Используется для поиска данных в модели данных
         */
        virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        /*!
         * \brief Set метод для номера столбца с датой, необходимой для окрашивания строк в нужный цвет
         * \param value Номер столбца с датой в модели
         */
        static void setNumberDate(const uint &value);
        /*!
         * \brief Get метод для номера столбца с датой, необходимой для окрашивания строк в нужный цвет
         * \return Номер столбца с датой в модели.
         */
        static uint getNumberDate();
        /*!
         * \brief Получить номер столбца с id
         * \return Номер столбца с id
         */
        static uint getNumberId();
        /*!
         * \brief Установить номер столбца с id
         * \param value Номер столбца с id
         */
        static void setNumberId(const uint &value);

    protected:
        /*! \brief Хранит в себе номер столбца с датой */
        static uint numberDate;
        /*! \brief Определяет разницу в днях до текущего дня */
        static int DIFFERENCES_DAYS;
        /*! \brief Номер столбца с id */
        static uint numberId;
    };
}

#endif // CONTACTTABLESTYLEDITEMDELEGATE_H
