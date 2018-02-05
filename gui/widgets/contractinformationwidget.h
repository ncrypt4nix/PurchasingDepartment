#ifndef CONTRACTINFORMATIONWIDGET_H
#define CONTRACTINFORMATIONWIDGET_H

#include <QKeyEvent>
#include <QSharedPointer>

#include "logics/contractobject.h"
#include "gui/widgets/messageboxcreater.h"
#include "gui/widgets/addcheckdialog.h"
#include "gui/widgets/handbookviewmanager.h"
#include "gui/widgets/tablestyleditemdelegate.h"

namespace Ui
{
    class ContractInformationWidget;
}
/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*!  \brief Виджет показа и редактирования контракта и счетов, связанных с контрактом */
    class ContractInformationWidget : public HandBookViewManager, MessageBoxCreater
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit ContractInformationWidget(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~ContractInformationWidget();
        /*!
         * \brief Устанавливает класс для работы с договором
         * \param value обьект договора
         */
        void setContractObj(logics::ContractObject *value);
        /*!
         * \brief сохраняет данные договора в БД
         * \return успешность операции
         */
        bool saveContractObj();
        /*!
         * \brief Переопределенный метод от HandBookViewManager.
         * Удаляет всю информацию о прошлом посещении виджета
         */
        virtual void resetOldData();
        /*! \brief Экспортирование модели в файл */
        void exportToExcel();
        /*! \brief Завершить договор */
        void completeContract();

    public:
        /*! \brief Состояние виджета, добавление нового или операции с существующим договором */
        enum class States
        {
            /*! \brief Состояние виджета, добавление нового договора */
            NewContract,
            /*! \brief Состояние виджета, операции с существующим договором */
            OldContract
        };

    protected:
        /*!
         * \brief Событие нажатия на клавишу
         * \param keyEvent Нажатая клавиша
         */
        virtual void keyPressEvent(QKeyEvent *keyEvent);
        /*!
         * \brief Заполнить обьект ContractObj данными с формы
         */
        void changeDataContractObj();
        /*!
         * \brief Изменяет состояние виджета
         * \param state новое состояние
         */
        void changeState(const enum States &state);
        /*!
         * \brief Изменяет модель счетов
         */
        void changeModel();

    signals:
        /*! \brief Сигнал о смене состояния */
        void changedState(ContractInformationWidget::States);

    private slots:
        void on_hideCheckTableButton_clicked();
        void on_deleteCheckButton_clicked();
        void on_addCheckButton_clicked();
        void on_providersHandBookButton_clicked();
        void on_sourcesFinancingHandBookButton_clicked();
        void on_subdivisionsHandBookButton_clicked();
        void on_responsiblesHandBookButton_clicked();

    private:
        Ui::ContractInformationWidget *ui;
        logics::ContractObject *contractObj = NULL;
        QSharedPointer<QSqlTableModel> checkModel;
        States currentState;
    };
}

#endif // CONTRACTINFORMATIONWIDGET_H
