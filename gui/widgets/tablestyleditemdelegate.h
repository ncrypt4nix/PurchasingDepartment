#ifndef DATESTYLEDITEMDELEGATE_H
#define DATESTYLEDITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>
#include <QDate>

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Делегат корренктирования оторажения таблицы */
    class TableStyledItemDelegate : public QStyledItemDelegate
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор делегата
         * \param parent Родительский виджет окна
         */
        explicit TableStyledItemDelegate(QObject *parent = 0);
        /*!
         * \brief Переопределенный метод QSomeColumnDelegate::paint отрисовки и раскрашивания строк талицы
         * \param painter Выполняет низкоуровневое рисование на виджетах и других устройствах рисования
         * \param option Используется для описания параметров, используемых для рисования элемента в виджете
         * \param index Используется для поиска данных в модели данных
         */
        virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        /*!
         * \brief Рисует текст
         * \param painter Выполняет низкоуровневое рисование на виджетах и других устройствах рисования
         * \param option Используется для описания параметров, используемых для рисования элемента в виджете
         * \param index Используется для поиска данных в модели данных
         */
        virtual void drawText(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        /*! \brief Формат даты для отображения */
        static const QString DATE_FORMAT;
    };
}

#endif // DATESTYLEDITEMDELEGATE_H
