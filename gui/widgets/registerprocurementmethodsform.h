#ifndef REGISTERPROCUREMENTMETHODSFORM_H
#define REGISTERPROCUREMENTMETHODSFORM_H

#include <QWidget>

#include "gui/widgets/messageboxcreater.h"
#include "gui/widgets/procurementmethodshandbookviewmanager.h"
#include "logics/contractprocurementmethodobject.h"
#include "logics/procurementmethodobject.h"

namespace Ui
{
    class RegisterProcurementMethodsForm;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Форма реестра конкурентных способов закупки */
    class RegisterProcurementMethodsForm : public ProcurementMethodsHandBookViewManager, MessageBoxCreater
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit RegisterProcurementMethodsForm(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~RegisterProcurementMethodsForm();
        /*!
         * \brief Передает обьект конкурентных способов закупки в форму реестра конкурентных способов закупки
         * \param value обьект контракта
         */
        void setProcurementMethodObj(const logics::ProcurementMethodObject &value);
        /*! \brief Удаляет всю информацию о прошлом посещении виджета */
        void resetOldData();
        /*!
         * \brief Устанавливает справочник и налаживает коннекты, для обработки изменения справочников
         * \param value Справочник
         */
        virtual void setHandBookManager(logics::HandBookManager *value);
        /*!
         * \brief Запоминает форму справочников для быстрого перехода к ним
         * \param value форма справочников
         */
        virtual void setHandBookForm(HandBookForm *value);

    protected:
        /*! \brief Состояние виджета, добавление нового или операции с существующим конкурентным способом закупки */
        enum class States
        {
            /*! \brief Состояние виджета, добавление нового конкурентного способоба закупки */
            NewProcurementMethod,
            /*! \brief Состояние виджета, операции с существующим конкурентных способов закупки */
            OldProcurementMethod,
            /*! \brief Состояние виджета, добавление контракта */
            OldAddContractProcurementMethod,
            /*! \brief Состояние виджета, с существующим конкурентным способом закупки и контрактом */
            OldAllProcurementMethod
        };

    protected:
        /*!
         * \brief сохраняет данные конкурентного способа закупки в БД
         * \return успешность операции
         */
        bool saveProcurementMethodObj();
        /*! \brief Заполнить обьект ProcurementMethodObj данными с формы */
        void changeDataProcurementMethodObj();
        /*!
         * \brief Изменяет состояние виджета
         * \param state новое состояние
         */
        void changeState(const enum States &state);

    signals:
        /*! \brief Сигнал завершения раоты формы */
        void okClicked();

    private slots:
        void on_okButton_clicked();
        void on_closeButton_clicked();
        void on_hideContractButton_clicked();
        void on_addContractButton_clicked();
        void on_applyButton_clicked();
        void on_procurementMethodHandBookButton_clicked();
        void on_exportButton_clicked();
        void on_noticeExportButton_clicked();
        void on_contractExportButton_clicked();

    private:
        Ui::RegisterProcurementMethodsForm *ui;
        logics::ProcurementMethodObject procurementMethodObj;
        States currentState;
    };
}

#endif // REGISTERPROCUREMENTMETHODSFORM_H
