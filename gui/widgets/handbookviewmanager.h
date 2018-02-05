#ifndef HANDBOOKVIEWMANAGER_H
#define HANDBOOKVIEWMANAGER_H

#include "gui/widgets/handbookviewmanagerabstract.h"

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс-Менеджер Box элементов отображения справочника */
    class HandBookViewManager : public HandBookViewManagerAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit HandBookViewManager(QWidget *parent = 0);
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
        /*! \brief Заполняет новыми значениями список поставщиков */
        void providersChange();
        /*! \brief Заполняет новыми значениями список подразления заказчика */
        void subdivisionsChange();
        /*! \brief Заполняет новыми значениями список ответственных лиц */
        void responsiblesChange();
        /*! \brief Заполняет новыми значениями список источников финансирования */
        void sourcesFinancingChange();

    protected:
        /*! \brief Виджет поставщиков */
        QComboBox *providersBox;
        /*! \brief Виджет подразделения заказчика */
        QComboBox *subdivisionsBox;
        /*! \brief Виджет ответственных лиц */
        QComboBox *responsiblesBox;
        /*! \brief Виджет источников финансирования */
        QComboBox *sourcesFinancingBox;
    };
}

#endif // HANDBOOKVIEWMANAGER_H
