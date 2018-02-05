#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>

#include "gui/widgets/contacttablestyleditemdelegate.h"
#include "gui/widgets/databaseconnectiondialog.h"
#include "gui/widgets/procurementmethodstablestyleditemdelegate.h"
#include "gui/widgets/handbookform.h"
#include "gui/widgets/messageboxcreater.h"
#include "gui/widgets/registercontractsform.h"
#include "gui/widgets/registercheckform.h"
#include "gui/widgets/registerprocurementmethodsform.h"
#include "gui/widgets/findformcontract.h"
#include "gui/widgets/findformcheck.h"
#include "gui/widgets/findformprocurementmethod.h"
#include "gui/widgets/aboutappform.h"
#include "gui/widgets/settingform.h"
#include "gui/widgets/reportform.h"
#include "gui/widgets/expectationform.h"

#include "logics/database.h"
#include "logics/tablemodelmanager.h"
#include "logics/settingapp.h"
#include "logics/handbook.h"
#include "logics/contractobject.h"
#include "logics/checkobject.h"
#include "logics/procurementmethodobject.h"
#include "logics/findobjectcontract.h"
#include "logics/findobjectcheck.h"
#include "logics/findobjectprocurementmethod.h"
#include "logics/informationendcontracts.h"


namespace Ui
{
    class MainWindow;
}
/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*!
     * \brief Основной класс для работы с окном приложения.
     * Класс соединяется с ui и управляет главным окном и всеми виджетами расположеными на нем
     */
    class MainWindow : public QMainWindow, MessageBoxCreater
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор главного окна
         * \param parent Родительский виджет окна
         */
        explicit MainWindow(QWidget *parent = 0);
        /*! \brief Деструктор главного окна */
        ~MainWindow();

    protected:
        /*!
         * \brief Открывает виджет нужного справочника
         * \param index индекс справочника
         */
        void showHandBook(const logics::HandBookManager::ModelIndex &index);
        /*!
         * \brief Экспортирование модели в файл
         * \param extended флаг расширенного экспортирования
         */
        void exportToExcel(const bool &extended = false);

    protected slots:
        /*! \brief Изменение модели изменит представление таблицы */
        void changeModel();
        /*! \brief Отключает флажки на всех событиях выбора регистра */
        void uncheckedRegisterActions();
        /*! \brief Поиск договоров */
        void findContract();
        /*! \brief Поиск счетов */
        void findCheck();
        /*! \brief Поиск конкурентных способов закупки */
        void findProcurementMethod();
        /*! \brief Подключение к БД */
        void connectToDB();
        /*! \brief Применение изменения настроек */
        void settingChange();

        // QWidget interface
    protected:
        /*!
         * \brief Событие закрытия приложения
         * \param event событие
         */
        void closeEvent(QCloseEvent *event);

    private slots:
        void on_exitAction_triggered();
        void on_deleteAction_triggered();
        void on_registerContractsAction_triggered();
        void on_registerChecksAction_triggered();
        void on_registerProcurementMethodsAction_triggered();
        void on_providersHandBookAction_triggered();
        void on_subdivisionsHandBookAction_triggered();
        void on_responsiblesHandBookAction_triggered();
        void on_sourcesFinancingHandBookAction_triggered();
        void on_paymentDocumentsHandBookAction_triggered();
        void on_procurementMethodsHandBookAction_triggered();
        void on_informationAction_triggered();
        void on_addAction_triggered();
        void on_tableRegisterView_doubleClicked(const QModelIndex &index);
        void on_showRegisterAction_triggered();
        void on_findAction_triggered();
        void on_aboutAction_triggered();
        void on_normalExportAction_triggered();
        void on_extendedExportAction_triggered();
        void on_settingAction_triggered();
        void on_reportAction_triggered();

    private:
        Ui::MainWindow *ui;
        DatabaseConnectionDialog* databaseConnectionDialog;
        HandBookForm* handBookForm;
        logics::HandBookManager* handBookManager;
        logics::DataBase *dataBase;
        logics::TableModelManager *modelManager;
        QSortFilterProxyModel *sortFilterProxyModel;
        RegisterContractsForm *registerContractsForm;
        RegisterCheckForm *registerCheckForm;
        RegisterProcurementMethodsForm *registerProcurementMethodsForm;
        FindFormContract *findFormContract;
        FindFormCheck *findFormCheck;
        FindFormProcurementMethod *findFormProcurementMethod;
        AboutAppForm *aboutAppForm;
        SettingForm *settingForm;
        ReportForm *reportForm;
        ExpectationForm *expectationForm;
    };
}
#endif // MAINWINDOW_H
