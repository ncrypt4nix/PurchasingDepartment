#ifndef PAYMENTDOCUMENTHANDBOOKMANAGER_H
#define PAYMENTDOCUMENTHANDBOOKMANAGER_H

#include "gui/widgets/handbookviewmanager.h"

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс-Менеджер Box элементов отображения справочника */
    class PaymentDocumentHandBookViewManager : public HandBookViewManager
    {
         Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        PaymentDocumentHandBookViewManager(QWidget *parent = 0);
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
        /*! Изменяет виджет платежных документов */
        void paymentDocumentChange();

    protected:
        /*! \brief Виджет платежных документов */
        QComboBox *paymentDocumentBox;
    };
}

#endif // PAYMENTDOCUMENTHANDBOOKMANAGER_H
