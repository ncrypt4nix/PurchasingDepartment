#ifndef COMPLETENESSSTYLEDITEMDELEGATE_H
#define COMPLETENESSSTYLEDITEMDELEGATE_H

#include "gui/widgets/tablestyleditemdelegate.h"

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Делегат корренктирования оторажения таблицы завершенности */
    class CompletenessStyledItemDelegate : public TableStyledItemDelegate
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор делегата
         * \param parent Родительский виджет окна
         */
        explicit CompletenessStyledItemDelegate(QObject *parent = 0);
        /*!
         * \brief Переопределенный метод QSomeColumnDelegate::paint отрисовки и раскрашивания строк талицы
         * \param painter Выполняет низкоуровневое рисование на виджетах и других устройствах рисования
         * \param option Используется для описания параметров, используемых для рисования элемента в виджете
         * \param index Используется для поиска данных в модели данных
         */
        virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        /*!
         * \brief Получить номер столбца завершенности
         * \return номер столбца завершенности
         */
        static uint getCompletenessNumber();
        /*!
         * \brief Установить номер столбца завершенности
         * \param value номер столбца завершенности
         */
        static void setCompletenessNumber(const uint &value);
        /*!
         * \brief Рисует текст
         * \param painter Выполняет низкоуровневое рисование на виджетах и других устройствах рисования
         * \param option Используется для описания параметров, используемых для рисования элемента в виджете
         * \param index Используется для поиска данных в модели данных
         */
        virtual void drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        /*!
         * \brief Рисует область без текста
         * \param painter Выполняет низкоуровневое рисование на виджетах и других устройствах рисования
         * \param option Используется для описания параметров, используемых для рисования элемента в виджете
         * \param index Используется для поиска данных в модели данных
         */
        void paintWithoutText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    private:
        static uint completenessNumber;
    };
}

#endif // COMPLETENESSSTYLEDITEMDELEGATE_H
