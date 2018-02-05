#ifndef PROCUREMENTMETHODSTABLESTYLEDITEMDELEGATE_H
#define PROCUREMENTMETHODSTABLESTYLEDITEMDELEGATE_H

#include "gui/widgets/completenessstyleditemdelegate.h"
#include <QPainter>

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*!
     * \brief Класс-Делегат преображающий внешний вид таблицы реестра конкурентных способов закупки
     */
    class ProcurementMethodsTableStyledItemDelegate : public CompletenessStyledItemDelegate
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit ProcurementMethodsTableStyledItemDelegate(QObject *parent = 0);
        /*!
         * \brief Переопределенный метод QSomeColumnDelegate::paint отрисовки и раскрашивания строк талицы
         * \param painter Выполняет низкоуровневое рисование на виджетах и других устройствах рисования
         * \param option Используется для описания параметров, используемых для рисования элемента в виджете
         * \param index Используется для поиска данных в модели данных
         */
        virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
        /*!
         * \brief Возвращает номер столбца завершенности процедуры
         * \return Номер столбца завершенности процедуры
         */
        static uint getProcedureCompleteNumber();
        /*!
         * \brief Устанавливает номер столбца завершенности процедуры
         * \param value Номер столбца завершенности процедуры
         */
        static void setProcedureCompleteNumber(const uint &value);
        /*!
         * \brief Получить СМП
         * \return СМП
         */
        static uint getSmpNumber();
        /*!
         * \brief Установить СМП
         * \param value СМП
         */
        static void setSmpNumber(const uint &value);

    protected:
        /*! \brief Номер столбца завершенной процедуры */
        static uint procedureCompleteNumber;
        /*! \brief Номер столбца СМП */
        static uint smpNumber;
    };
}

#endif // PROCUREMENTMETHODSTABLESTYLEDITEMDELEGATE_H
