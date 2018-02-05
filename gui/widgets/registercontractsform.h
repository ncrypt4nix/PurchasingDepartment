#ifndef REGISTERCONTRACTSFORM_H
#define REGISTERCONTRACTSFORM_H

#include <QWidget>
#include "logics/handbook.h"
#include "logics/contractobject.h"
#include "logics/informationendcontracts.h"
#include "gui/widgets/handbookform.h"
#include "gui/widgets/messageboxcreater.h"
#include "gui/widgets/contractinformationwidget.h"

namespace Ui
{
    class RegisterContractsForm;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Форма реестра договоров */
    class RegisterContractsForm : public QWidget, MessageBoxCreater
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit RegisterContractsForm(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~RegisterContractsForm();
        /*!
         * \brief Передает ссылку на справочник виджету контрактов
         * \param value Справочник
         */
        void setHandBookManager(logics::HandBookManager *value);
        /*!
         * \brief Передает обьект договора в форму реестра договоров
         * \param value обьект контракта
         */
        void setContractObj(logics::ContractObject *value);
        /*! \brief Удаляет всю информацию о прошлом посещении виджета */
        void resetOldData();
        /*!
         * \brief Запоминает форму справочников для быстрого перехода к ним
         * \param value форма справочников
         */
        virtual void setHandBookForm(HandBookForm *value);

    protected slots:
        /*! \brief Скрывает или нет кнопку экспорта, в зависимости от состояния виджета */
        void changeHideExportButton(ContractInformationWidget::States);

    private slots:
        void on_closeButton_clicked();
        void on_okButton_clicked();
        void on_applyButton_clicked();
        void on_endContractButton_clicked();
        void on_exportButton_clicked();

    signals:
        /*! \brief Сигнал завершения раоты формы */
        void okClicked();

    private:
        Ui::RegisterContractsForm *ui;
        uint idContract;
    };
}

#endif // REGISTERCONTRACTSFORM_H
