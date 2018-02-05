#include "contractinformationwidget.h"
#include "ui_contractinformationwidget.h"

using namespace gui;

ContractInformationWidget::ContractInformationWidget(QWidget *parent) :
    HandBookViewManager(parent),
    ui(new Ui::ContractInformationWidget)
{
    ui->setupUi(this);
    providersBox = ui->providersBox;
    subdivisionsBox = ui->subdivisionsBox;
    responsiblesBox = ui->responsiblesBox;
    sourcesFinancingBox = ui->sourcesFinancingBox;
}

ContractInformationWidget::~ContractInformationWidget()
{
    delete ui;
}

void ContractInformationWidget::setContractObj(logics::ContractObject *value)
{
    if (contractObj != NULL && contractObj != value)
        delete contractObj;
    contractObj = value;
    ui->contractNumbeEdit->setText(contractObj->getNumber());
    ui->contractsSumEdit->setValue(contractObj->getSum());
    ui->startDateEdit->setDate(contractObj->getStartDate());
    ui->endDateEdit->setDate(contractObj->getEndDate());
    ui->conclusionDateEdit->setDate(contractObj->getConclusionDate());
    ui->registrationDateEdit->setDate(contractObj->getRegistrationDate());
    ui->providersBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::PROVIDERS_INDEX).key(
                            contractObj->getProviderId()));
    ui->subdivisionsBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).key(
                            contractObj->getSubdivisionId()));
    ui->responsiblesBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX).key(
                            contractObj->getResponsibleId()));
    ui->sourcesFinancingBox->setCurrentText(handBookManager->getMapHandBook(
                        logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).key(
                            contractObj->getSourceFinancingId()));
    ui->completenessBox->setCurrentIndex(contractObj->getCompleteness());
    ui->commentEdit->setText(contractObj->getComment());
    changeModel();
    if (contractObj->isEmpty())
        changeState(States::NewContract);
    else
        changeState(States::OldContract);
}

bool ContractInformationWidget::saveContractObj()
{
    if (!checkData())
        return false;
    changeDataContractObj();
    if (!checkModel->submitAll())
        return false;
    if (currentState == States::OldContract)
        return contractObj->save();
    else
    {
        if (!contractObj->add())
            return false;
        changeModel();
        changeState(States::OldContract);
        return true;
    }
}

void ContractInformationWidget::resetOldData()
{
    HandBookViewManager::resetOldData();
    ui->contractNumbeEdit->clear();
    ui->contractsSumEdit->clear();
    ui->startDateEdit->setDate(QDate::currentDate());
    ui->endDateEdit->setDate(QDate::currentDate());
    ui->conclusionDateEdit->setDate(QDate::currentDate());
    ui->registrationDateEdit->setDate(QDate::currentDate());
    ui->completenessBox->setCurrentIndex(0);
    ui->commentEdit->clear();
}

void ContractInformationWidget::exportToExcel()
{
    QString filePath = createSaveFileNameExcelMessageBox();
    if (filePath.isEmpty())
        return;
    if (!contractObj->saveExtendedToExcel(filePath))
        createErrorMessageBox(tr("Ошибка записи файла."));
}

void ContractInformationWidget::completeContract()
{
    ui->completenessBox->setCurrentIndex(1);
}

void ContractInformationWidget::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key())
    {
    case Qt::Key_Delete:
        on_deleteCheckButton_clicked();
        break;
    }
    QWidget::keyPressEvent(keyEvent);
}

void ContractInformationWidget::changeDataContractObj()
{
    contractObj->setNumber(ui->contractNumbeEdit->text());
    contractObj->setSum(ui->contractsSumEdit->value());
    contractObj->setStartDate(ui->startDateEdit->date());
    contractObj->setEndDate(ui->endDateEdit->date());
    contractObj->setConclusionDate(ui->conclusionDateEdit->date());
    contractObj->setRegistrationDate(ui->registrationDateEdit->date());

    auto foo = ui->completenessBox->currentIndex();
    contractObj->setCompleteness((foo >= 0 ? foo : 0));

    contractObj->setComment(ui->commentEdit->text());
    contractObj->setProviderId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::PROVIDERS_INDEX).value(
                        ui->providersBox->currentText()));
    contractObj->setSubdivisionId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX).value(
                        ui->subdivisionsBox->currentText()));
    contractObj->setResponsibleId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX).value(
                        ui->responsiblesBox->currentText()));
    contractObj->setSourceFinancingId(handBookManager->getMapHandBook(
                    logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX).value(
                        ui->sourcesFinancingBox->currentText()));
}

void ContractInformationWidget::changeState(const enum ContractInformationWidget::States &state)
{
    if (state == States::NewContract)
    {
        currentState = States::NewContract;
        ui->checksTableView->setHidden(true);
        ui->addCheckButton->setHidden(true);
        ui->deleteCheckButton->setHidden(true);
        ui->hideCheckTableButton->setHidden(true);
    }
    else if (state == States::OldContract)
    {
        currentState = States::OldContract;
        ui->checksTableView->setHidden(false);
        ui->addCheckButton->setHidden(false);
        ui->deleteCheckButton->setHidden(false);
        ui->hideCheckTableButton->setHidden(false);
    }
    emit changedState(state);
}

void ContractInformationWidget::changeModel()
{
    checkModel = QSharedPointer<QSqlTableModel>(contractObj->getModel());
    ui->checksTableView->setModel(checkModel.data());
    for (auto nextColumns : contractObj->columnsHidden)
        ui->checksTableView->setColumnHidden(nextColumns, true);
    ui->checksTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->checksTableView->setItemDelegate(new TableStyledItemDelegate);
}

void gui::ContractInformationWidget::on_hideCheckTableButton_clicked()
{
    if (ui->checksTableView->isHidden())
        ui->checksTableView->setHidden(false);
    else
        ui->checksTableView->setHidden(true);
}

void gui::ContractInformationWidget::on_deleteCheckButton_clicked()
{
    QString deleteErrorMessage = tr("К сожалению, произошла ошибка удаления записи. Попробуйте снова выделить нужные записи и удалить их.");
    if (ui->checksTableView->selectionModel()->selectedIndexes().count() == 0)
    {
        createErrorMessageBox(deleteErrorMessage);
        return;
    }
    if (!createMessageBox(tr("Вы точно хотите безвозвратно удалить выделенные данные?")))
        return;
    for(auto i = 0; i < ui->checksTableView->selectionModel()->selectedIndexes().count(); i++)
    {
        auto selectedIndex = ui->checksTableView->selectionModel()->selectedIndexes().at(i);
        if (!checkModel->removeRow(selectedIndex.row()))
            createErrorMessageBox(deleteErrorMessage);
    }
}

void gui::ContractInformationWidget::on_addCheckButton_clicked()
{
    AddCheckDialog addCheckDialog;
    if (addCheckDialog.exec() != QDialog::Accepted)
        return;
    checkModel->insertRow(0);
    checkModel->setData(checkModel->index(0, static_cast<int>(contractObj->CheckColumnNumbers::checkNumber)),
                        addCheckDialog.getNumber());
    checkModel->setData(checkModel->index(0, static_cast<int>(contractObj->CheckColumnNumbers::registrationDate)),
                        addCheckDialog.getRegistrationDate());
    checkModel->setData(checkModel->index(0, static_cast<int>(contractObj->CheckColumnNumbers::checkDate)),
                        addCheckDialog.getCheckDate());
    checkModel->setData(checkModel->index(0, static_cast<int>(contractObj->CheckColumnNumbers::checkSum)),
                        addCheckDialog.getSum());
    checkModel->setData(checkModel->index(0, static_cast<int>(contractObj->CheckColumnNumbers::description)),
                        addCheckDialog.getDescription());
    checkModel->setData(checkModel->index(0, static_cast<int>(contractObj->CheckColumnNumbers::contractId)),
                       contractObj->getId());
}

void gui::ContractInformationWidget::on_providersHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::PROVIDERS_INDEX);
}

void gui::ContractInformationWidget::on_sourcesFinancingHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::SOURCES_FINANCING_INDEX);
}

void gui::ContractInformationWidget::on_subdivisionsHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::SUBDIVISIONS_INDEX);
}

void gui::ContractInformationWidget::on_responsiblesHandBookButton_clicked()
{
    showHandBook(logics::HandBookManager::ModelIndex::RESPONSIBLES_INDEX);
}
