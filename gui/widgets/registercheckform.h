#ifndef REGISTERCHECKFORM_H
#define REGISTERCHECKFORM_H

#include <QWidget>
#include <QComboBox>

#include "gui/widgets/messageboxcreater.h"
#include "gui/widgets/paymentdocumenthandbookviewmanager.h"
#include "logics/checkobject.h"

namespace Ui
{
    class RegisterCheckForm;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Форма реестра счетов */
    class RegisterCheckForm : public PaymentDocumentHandBookViewManager, MessageBoxCreater
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit RegisterCheckForm(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~RegisterCheckForm();
        /*!
         * \brief Устанавливает класс для работы со счетом
         * \param value обьект счета
         */
        void setCheckObj(const logics::CheckObject &value);
        /*! \brief Переопределенный метод от HandBookViewManager.
         * Удаляет всю информацию о прошлом посещении виджета */
        virtual void resetOldData();

    protected:
        /*! \brief Состояние виджета, добавление нового или операции с существующим счетом */
        enum class States
        {
            /*! \brief Состояние виджета, добавление нового счета */
            NewCheck,
            /*! \brief Состояние виджета, операции с существующим счетом */
            OldCheck
        };

    protected:
        /*!
         * \brief сохраняет данные счета в БД
         * \return успешность операции
         */
        bool saveCheckObj();
        /*! \brief Заполнить обьект CheckObj данными с формы */
        void changeDataCheckObj();

    signals:
        /*! \brief Сигнал завершения раоты формы */
        void okClicked();

    private slots:
        void on_okButton_clicked();
        void on_closeButton_clicked();
        void on_exportButton_clicked();
        void on_paymentDocumentHandBookButton_clicked();
        void on_providersHandBookButton_clicked();
        void on_subdivisionsHandBookButton_clicked();
        void on_responsiblesHandBookButton_clicked();
        void on_sourcesFinancingHandBookButton_clicked();

    private:
        Ui::RegisterCheckForm *ui;
        logics::CheckObject checkObj;
        States currentState;
    };
}

#endif // REGISTERCHECKFORM_H
