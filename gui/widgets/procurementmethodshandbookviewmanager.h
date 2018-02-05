#ifndef PROCUREMENTMETHODSHANDBOOKVIEWMANAGER_H
#define PROCUREMENTMETHODSHANDBOOKVIEWMANAGER_H

#include "gui/widgets/handbookviewmanagerabstract.h"

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс-Менеджер Box элементов отображения справочника */
    class ProcurementMethodsHandBookViewManager : public HandBookViewManagerAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit ProcurementMethodsHandBookViewManager(QWidget *parent = 0);
        /*!
         * \brief Устанавливает справочник и налаживает коннекты, для обработки изменения справочников
         * \param value Справочник
         */
        virtual void setHandBookManager(logics::HandBookManager *value);
        /*! \brief Удаляет всю информацию о прошлом посещении виджета */
        virtual void resetOldData();
        /*!
         * \brief Проверяет целостность данных
         * \return целостность данных
         */
        virtual bool checkData();

    protected slots:
        /*! \brief Заполняет новыми значениями способы закупки */
        void procurementMethodsChange();

    protected:
        /*! \brief Виджет способов закупки */
        QComboBox *procurementMethodsBox;
    };
}

#endif // PROCUREMENTMETHODSHANDBOOKVIEWMANAGER_H
