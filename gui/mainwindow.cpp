#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace gui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /* Инициализация БД */
    databaseConnectionDialog = new DatabaseConnectionDialog(this);
    dataBase = new logics::DataBase(this);
    logics::DataBase::setUserName(logics::SettingApp::getSettingApp().getUserNameForDB());
    logics::DataBase::setHostName(logics::SettingApp::getSettingApp().getHostNameForDB());
    logics::DataBase::setPassword(logics::SettingApp::getSettingApp().getPasswordForDB());
    connectToDB();
    /* Инициализация менеджера моделей */
    try
    {
        modelManager = new logics::TableModelManager(logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX, this);
    }
    catch (exceptions::TableModelException &tm_exc)
    {
        createExceptionMessageBox(tm_exc);
        QCoreApplication::exit(0);
    }
    sortFilterProxyModel = new QSortFilterProxyModel(this);
    /* Инициализация справочников */
    handBookManager = new logics::HandBookManager(this);
    handBookForm = new HandBookForm(handBookManager);
    logics::RegisterObjectAbstract::setHandBookManager(handBookManager);
    /* Инициализация формы контрактов */
    registerContractsForm = new RegisterContractsForm;
    registerContractsForm->setHandBookManager(handBookManager);
    registerContractsForm->setHandBookForm(handBookForm);
    connect(registerContractsForm, SIGNAL(okClicked()), modelManager, SLOT(updateModel()));
    logics::InformationEndContracts::read();
    /* Инициализация формы счетов */
    registerCheckForm = new RegisterCheckForm;
    registerCheckForm->setHandBookManager(handBookManager);
    registerCheckForm->setHandBookForm(handBookForm);
    connect(registerCheckForm, SIGNAL(okClicked()), modelManager, SLOT(updateModel()));
    /* Инициализация формы конкурентных способов закупки */
    registerProcurementMethodsForm = new RegisterProcurementMethodsForm;
    registerProcurementMethodsForm->setHandBookManager(handBookManager);
    registerProcurementMethodsForm->setHandBookForm(handBookForm);
    connect(registerProcurementMethodsForm, SIGNAL(okClicked()), modelManager, SLOT(updateModel()));
    /* Инициализация форм поиска */
    findFormContract = new FindFormContract;
    findFormContract->setHandBookManager(handBookManager);
    connect(findFormContract, SIGNAL(okClicked()), this, SLOT(findContract()));
    findFormCheck = new FindFormCheck;
    findFormCheck->setHandBookManager(handBookManager);
    connect(findFormCheck, SIGNAL(okClicked()), this, SLOT(findCheck()));
    findFormProcurementMethod = new FindFormProcurementMethod;
    findFormProcurementMethod->setHandBookManager(handBookManager);
    connect(findFormProcurementMethod, SIGNAL(okClicked()), this, SLOT(findProcurementMethod()));
    /* Иициализация формы с отчетами */
    reportForm = new ReportForm;
    /* Инициализация формы с настройками */
    settingForm = new SettingForm;
    connect(settingForm, SIGNAL(reconnect()), this, SLOT(connectToDB()));
    connect(settingForm, SIGNAL(settingChange()), this, SLOT(settingChange()));
    /* Инициализация формы о программе */
    aboutAppForm = new AboutAppForm;
    /* Инициализация окна ожидания */
    expectationForm = new ExpectationForm;
    QList<QWidget *> widgetList;
    widgetList  << this
                << reportForm
                << settingForm
                << aboutAppForm
                << findFormContract
                << findFormCheck
                << findFormProcurementMethod
                << registerContractsForm
                << registerCheckForm
                << registerProcurementMethodsForm
                << handBookForm;
    expectationForm->setWidgets(widgetList);
    /* Установка первоначального состояния программы */
    on_registerContractsAction_triggered();
}

MainWindow::~MainWindow()
{
    delete expectationForm;
    delete reportForm;
    delete settingForm;
    delete aboutAppForm;
    delete findFormContract;
    delete findFormCheck;
    delete findFormProcurementMethod;
    delete registerContractsForm;
    delete registerCheckForm;
    delete registerProcurementMethodsForm;
    delete handBookForm;
    delete ui;
}

void MainWindow::showHandBook(const logics::HandBookManager::ModelIndex &index)
{
    try
    {
        handBookForm->setModel(index);
        handBookForm->show();
        handBookForm->activateWindow();
    }
    catch(exceptions::TableModelException &tm_exc)
    {
        createExceptionMessageBox(tm_exc);
    }
}

void MainWindow::exportToExcel(const bool &extended)
{
    int rowCount = ui->tableRegisterView->model()->rowCount();
    if (rowCount == 0)
    {
        createErrorMessageBox(tr("Не выделена ни одна запись для сохранения!"));
        return;
    }
    QString filePath = createSaveFileNameExcelMessageBox();
    if (filePath.isEmpty())
        return;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        createErrorMessageBox(tr("Ошибка открытия файла"));
    QTextStream stream(&file);
    logics::RegisterObjectAbstract *registerObj;
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
        registerObj = new logics::ContractObject;
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CHECK_MODEL_INDEX)
        registerObj = new logics::CheckObject;
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
        registerObj = new logics::ProcurementMethodObject;

    stream << ((extended) ? registerObj->headerExtendedExcel() : registerObj->headerExcel());

    for (int i = 0; i < rowCount; i++)
    {
        QModelIndex index = ui->tableRegisterView->model()->index(i, modelManager->getColumnIdNumber());
        registerObj->changeId( index.data().toInt() );
        stream << ((extended) ? registerObj->rowDataExtendedExcel() : registerObj->rowDataExcel());
    }

    stream << registerObj->endExcel();
    file.close();
}

void MainWindow::changeModel()
{
    ui->showRegisterAction->setEnabled(false);
    sortFilterProxyModel->setSourceModel(modelManager->getCurrentModel());
    ui->tableRegisterView->setModel(sortFilterProxyModel);
    try
    {
        if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
        {
            ContactTableStyledItemDelegate::setNumberDate(modelManager->getColumnEndDateNumber());
            ContactTableStyledItemDelegate::setNumberId(modelManager->getColumnIdNumber());
            ContactTableStyledItemDelegate::setCompletenessNumber(modelManager->getColumnCompletenessNumber());
            ui->tableRegisterView->setItemDelegate(new ContactTableStyledItemDelegate);
        }
        else if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
        {
            ProcurementMethodsTableStyledItemDelegate::setProcedureCompleteNumber(modelManager->getColumnProcedureCompleteNumber());
            ProcurementMethodsTableStyledItemDelegate::setSmpNumber(modelManager->getColumnSMPNumber());
            ProcurementMethodsTableStyledItemDelegate::setCompletenessNumber(modelManager->getColumnCompletenessNumber());
            ui->tableRegisterView->setItemDelegate(new ProcurementMethodsTableStyledItemDelegate);
        }
        else
        {
            CompletenessStyledItemDelegate::setCompletenessNumber(modelManager->getColumnCompletenessNumber());
            ui->tableRegisterView->setItemDelegate(new CompletenessStyledItemDelegate);
        }
    }
    catch(exceptions::TableModelException &tm_exc)
    {
        createExceptionMessageBox(tm_exc);
        ui->tableRegisterView->setItemDelegate(new TableStyledItemDelegate);
    }
    if (logics::SettingApp::getSettingApp().getStretchTable())
        ui->tableRegisterView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    else
        ui->tableRegisterView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableRegisterView->setColumnHidden(modelManager->getColumnIdNumber(), true);
}

void MainWindow::uncheckedRegisterActions()
{
    ui->registerContractsAction->setChecked(false);
    ui->registerChecksAction->setChecked(false);
    ui->registerProcurementMethodsAction->setChecked(false);
}

void MainWindow::findContract()
{
    expectationForm->expectation();
    if (!modelManager->findQuery(findFormContract->getFindObjectContract()))
    {
        expectationForm->end();
        createErrorMessageBox(tr("Произошла ошибка поиска!"));
        on_showRegisterAction_triggered();
        return;
    }
    ui->showRegisterAction->setEnabled(true);
    expectationForm->end();
}

void MainWindow::findCheck()
{
    expectationForm->expectation();
    if (!modelManager->findQuery(findFormCheck->getFindObjectCheck()))
    {
        expectationForm->end();
        createErrorMessageBox(tr("Произошла ошибка поиска!"));
        on_showRegisterAction_triggered();
        return;
    }
    ui->showRegisterAction->setEnabled(true);
    expectationForm->end();
}

void MainWindow::findProcurementMethod()
{
    expectationForm->expectation();
    if (!modelManager->findQuery(findFormProcurementMethod->getFindObjectProcurementMethod()))
    {
        expectationForm->end();
        createErrorMessageBox(tr("Произошла ошибка поиска!"));
        on_showRegisterAction_triggered();
        return;
    }
    ui->showRegisterAction->setEnabled(true);
    expectationForm->end();
}

void MainWindow::connectToDB()
{
    bool setSettingFlag = false;
    while (!dataBase->createConnection())
    {
        setSettingFlag = true;
        if (databaseConnectionDialog->exec() == QDialog::Accepted)
        {
            logics::DataBase::setUserName(databaseConnectionDialog->getUserName());
            logics::DataBase::setHostName(databaseConnectionDialog->getHostName());
            logics::DataBase::setPassword(databaseConnectionDialog->getPassword());
        }
        else
        {
            if (createMessageBox(tr("Без подключения к БД, программа не будет работоспособной, вы хотите выйти из программы?")))
            {
                delete databaseConnectionDialog;
                QCoreApplication::exit(0);
            }
        }
    }
    if (setSettingFlag)
    {
        logics::SettingApp::getSettingApp().setUserNameForDB(logics::DataBase::getUserName());
        logics::SettingApp::getSettingApp().setHostNameForDB(logics::DataBase::getHostName());
        logics::SettingApp::getSettingApp().setPasswordForDB(logics::DataBase::getPassword());
    }
}

void MainWindow::settingChange()
{
    expectationForm->expectation();
    changeModel();
    expectationForm->end();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!logics::InformationEndContracts::save())
        createErrorMessageBox(tr("Ошибка записи данных!!"));
    QMainWindow::closeEvent(event);
}

void gui::MainWindow::on_exitAction_triggered()
{
    QCoreApplication::exit(0);
}

void gui::MainWindow::on_deleteAction_triggered()
{
    QString deleteErrorMessage = tr("К сожалению, произошла ошибка удаления записи. Попробуйте снова выделить нужные записи и удалить их.");
    if (ui->tableRegisterView->selectionModel()->selectedRows().count() == 0)
    {
        createErrorMessageBox(deleteErrorMessage);
        return;
    }
    if (!createMessageBox(tr("Вы точно хотите безвозвратно удалить выделенные данные?")))
        return;
    expectationForm->expectation();
    auto count = ui->tableRegisterView->selectionModel()->selectedRows().count();
    for(auto i = 0; i < count; i++)
    {
        auto selectedRow = ui->tableRegisterView->selectionModel()->selectedRows().at(i);
        if (!modelManager->deleteColumn(selectedRow))
        {
            expectationForm->end();
            createErrorMessageBox(deleteErrorMessage);
            return;
        }
    }
    if (!modelManager->updateModel())
    {
        expectationForm->end();
        createErrorMessageBox(deleteErrorMessage);
        return;
    }
    expectationForm->end();
}

void gui::MainWindow::on_registerContractsAction_triggered()
{
    expectationForm->expectation();
    if (!modelManager->changeModel(logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX))
    {
        expectationForm->end();
        createErrorMessageBox(tr("Реестр договоров недоступен. Обратитесь к администратору"));
    }
    changeModel();
    uncheckedRegisterActions();
    ui->registerContractsAction->setChecked(true);
    expectationForm->end();
}

void gui::MainWindow::on_registerChecksAction_triggered()
{
    expectationForm->expectation();
    if (!modelManager->changeModel(logics::TableModelManager::RegisterModelIndex::REGISTER_CHECK_MODEL_INDEX))
    {
        expectationForm->end();
        createErrorMessageBox(tr("Реестр счетов недоступен. Обратитесь к администратору"));
    }
    changeModel();
    uncheckedRegisterActions();
    ui->registerChecksAction->setChecked(true);
    expectationForm->end();
}

void gui::MainWindow::on_registerProcurementMethodsAction_triggered()
{
    expectationForm->expectation();
    if (!modelManager->changeModel(logics::TableModelManager::RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX))
    {
        expectationForm->end();
        createErrorMessageBox(tr("Реестр конкурентных способов закупки недоступен. Обратитесь к администратору"));
    }
    changeModel();
    uncheckedRegisterActions();
    ui->registerProcurementMethodsAction->setChecked(true);
    expectationForm->end();
}

void gui::MainWindow::on_providersHandBookAction_triggered()
{
    expectationForm->expectation();
    showHandBook(logics::HandBookManager::ModelIndex::PROVIDERS_INDEX);
    expectationForm->end();
}

void gui::MainWindow::on_subdivisionsHandBookAction_triggered()
{
    expectationForm->expectation();
    showHandBook(logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX);
    expectationForm->end();
}

void gui::MainWindow::on_responsiblesHandBookAction_triggered()
{
    expectationForm->expectation();
    showHandBook(logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX);
    expectationForm->end();
}

void gui::MainWindow::on_sourcesFinancingHandBookAction_triggered()
{
    expectationForm->expectation();
    showHandBook(logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX);
    expectationForm->end();
}

void gui::MainWindow::on_paymentDocumentsHandBookAction_triggered()
{
    expectationForm->expectation();
    showHandBook(logics::HandBookManager::ModelIndex::PAYMENT_DOCUMENTS_INDEX);
    expectationForm->end();
}

void gui::MainWindow::on_procurementMethodsHandBookAction_triggered()
{
    expectationForm->expectation();
    showHandBook(logics::HandBookManager::ModelIndex::PROCUREMENT_METHODS_INDEX);
    expectationForm->end();
}

void gui::MainWindow::on_informationAction_triggered()
{
    if (ui->tableRegisterView->selectionModel()->selectedRows().count() == 0)
    {
        createErrorMessageBox(tr("Не выделена ни одна запись для просмотра!"));
        return;
    }
    expectationForm->expectation();
    auto index = ui->tableRegisterView->selectionModel()->selectedRows().at(0);
    auto elementId = index.sibling(index.row(), modelManager->getColumnIdNumber()).data().toInt();
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
    {
        logics::ContractObject *contractObj = new logics::ContractObject;
        contractObj->changeId(elementId);
        registerContractsForm->setContractObj(contractObj);
        registerContractsForm->show();
        registerContractsForm->activateWindow();
    }
    else if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CHECK_MODEL_INDEX)
    {
        logics::CheckObject checkObj;
        checkObj.changeId(elementId);
        registerCheckForm->setCheckObj(checkObj);
        registerCheckForm->show();
        registerCheckForm->activateWindow();
    }
    else if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
    {
        logics::ProcurementMethodObject procurementMethodObj;
        procurementMethodObj.changeId(elementId);
        registerProcurementMethodsForm->setProcurementMethodObj(procurementMethodObj);
        registerProcurementMethodsForm->show();
        registerProcurementMethodsForm->activateWindow();
    }
    expectationForm->end();
}

void gui::MainWindow::on_addAction_triggered()
{
    expectationForm->expectation();
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
    {
        registerContractsForm->setContractObj(new logics::ContractObject);
        registerContractsForm->resetOldData();
        registerContractsForm->show();
        registerContractsForm->activateWindow();
    }
    else if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CHECK_MODEL_INDEX)
    {
        registerCheckForm->setCheckObj(logics::CheckObject());
        registerCheckForm->resetOldData();
        registerCheckForm->show();
        registerCheckForm->activateWindow();
    }
    else if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
    {
        registerProcurementMethodsForm->setProcurementMethodObj(logics::ProcurementMethodObject());
        registerProcurementMethodsForm->resetOldData();
        registerProcurementMethodsForm->show();
        registerProcurementMethodsForm->activateWindow();
    }
    expectationForm->end();
}

void gui::MainWindow::on_tableRegisterView_doubleClicked(const QModelIndex &index)
{
    expectationForm->expectation();
    auto elementId = index.sibling(index.row(), modelManager->getColumnIdNumber()).data().toInt();
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
    {
        logics::ContractObject *contractObj = new logics::ContractObject;
        contractObj->changeId(elementId);
        registerContractsForm->setContractObj(contractObj);
        registerContractsForm->show();
        registerContractsForm->activateWindow();
    }
    else if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CHECK_MODEL_INDEX)
    {
        logics::CheckObject checkObj;
        checkObj.changeId(elementId);
        registerCheckForm->setCheckObj(checkObj);
        registerCheckForm->show();
        registerCheckForm->activateWindow();
    }
    else if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
    {
        logics::ProcurementMethodObject procurementMethodObj;
        procurementMethodObj.changeId(elementId);
        registerProcurementMethodsForm->setProcurementMethodObj(procurementMethodObj);
        registerProcurementMethodsForm->show();
        registerProcurementMethodsForm->activateWindow();
    }
    expectationForm->end();
}

void gui::MainWindow::on_showRegisterAction_triggered()
{
    expectationForm->expectation();
    if (!modelManager->setStartState() || !modelManager->updateModel())
    {
        expectationForm->end();
        createErrorMessageBox(tr("Ошибка запроса. Возможны какие то неполадки с сервером."));
    }
    else
        ui->showRegisterAction->setEnabled(false);
    expectationForm->end();
}

void gui::MainWindow::on_findAction_triggered()
{
    expectationForm->expectation();
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CONTRACT_MODEL_INDEX)
    {
        findFormContract->setFindObjectContract(dynamic_cast<logics::FindObjectContract*>(modelManager->getFindObject()));
        findFormContract->resetOldData();
        findFormContract->show();
        findFormContract->activateWindow();
    }
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_CHECK_MODEL_INDEX)
    {
        findFormCheck->setFindObjectCheck(dynamic_cast<logics::FindObjectCheck*>(modelManager->getFindObject()));
        findFormCheck->resetOldData();
        findFormCheck->show();
        findFormCheck->activateWindow();
    }
    if (modelManager->getModelIndex() == logics::TableModelManager::RegisterModelIndex::REGISTER_PROCUREMENT_METHODS_MODEL_INDEX)
    {
        findFormProcurementMethod->setFindObjectProcurementMethod(dynamic_cast<logics::FindObjectProcurementMethod*>(modelManager->getFindObject()));
        findFormProcurementMethod->resetOldData();
        findFormProcurementMethod->show();
        findFormProcurementMethod->activateWindow();
    }
    expectationForm->end();
}

void gui::MainWindow::on_aboutAction_triggered()
{
    expectationForm->expectation();
    aboutAppForm->show();
    expectationForm->end();
}

void gui::MainWindow::on_normalExportAction_triggered()
{
    expectationForm->expectation();
    exportToExcel();
    expectationForm->end();
}

void gui::MainWindow::on_extendedExportAction_triggered()
{
    expectationForm->expectation();
    exportToExcel(true);
    expectationForm->end();
}

void gui::MainWindow::on_settingAction_triggered()
{
    expectationForm->expectation();
    settingForm->resetData();
    settingForm->show();
    settingForm->activateWindow();
    expectationForm->end();
}

void gui::MainWindow::on_reportAction_triggered()
{
    expectationForm->expectation();
    reportForm->show();
    reportForm->activateWindow();
    expectationForm->end();
}
