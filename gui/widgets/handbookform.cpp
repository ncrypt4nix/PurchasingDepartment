#include "handbookform.h"
#include "ui_handbookform.h"

using namespace gui;

HandBookForm::HandBookForm(logics::HandBookManager* handBookManager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HandBookForm)
{
    ui->setupUi(this);
    this->handBookManager = handBookManager;
}

void HandBookForm::setModel(const logics::HandBookManager::ModelIndex &modelIndex)
{
    ui->handBookTableView->setModel(handBookManager->getModelIndex(modelIndex));
    ui->handBookTableView->setColumnHidden(handBookManager->getColumnIdIndex(), true);
    handBookManager->cancelFilter();
    ui->findCancelButton->setEnabled(false);
}

HandBookForm::~HandBookForm()
{
    delete ui;
}

void HandBookForm::keyPressEvent(QKeyEvent *keyEvent)
{
    switch (keyEvent->key())
    {
    case Qt::Key_Delete:
        deleteRows();
        break;
    }
    QWidget::keyPressEvent(keyEvent);
}

void HandBookForm::deleteRows()
{
    QString deleteErrorMessage = tr("К сожалению, произошла ошибка удаления записи.\n"
                                    "Попробуйте снова выделить нужные записи и удалить их.\n"
                                    "Возможно запись которую вы хотите удалить все еще где-то используется.");
    if (ui->handBookTableView->selectionModel()->selectedRows().count() == 0)
    {
        createErrorMessageBox(deleteErrorMessage);
        return;
    }
    if (!createMessageBox(tr("Вы точно хотите безвозвратно удалить выделенные данные?")))
        return;
    auto count = ui->handBookTableView->selectionModel()->selectedRows().count();
    for(auto i = 0; i < count; i++)
    {
        auto selectedRow = ui->handBookTableView->selectionModel()->selectedRows().at(i).row();
        if (!handBookManager->removeRow(selectedRow))
        {
            createErrorMessageBox(deleteErrorMessage);
            return;
        }
    }
    if (!handBookManager->updateModel())
    {
        createErrorMessageBox(deleteErrorMessage);
        return;
    }
}

void HandBookForm::addRow()
{
    QString addErrorMessage = tr("Произошла ошибка добавления записи. Возможно вы ввели недопустимые символы или произошел другой сбой.\n"
                                 "Возможно, такая запись уже существует");
    if (!handBookManager->addRow(ui->addLineEdit->text())
            || !handBookManager->updateModel())
    {
        createErrorMessageBox(addErrorMessage);
        return;
    }
    ui->addLineEdit->setText(QString());
}

void gui::HandBookForm::on_closeButton_clicked()
{
    ui->addLineEdit->setText(QString());
    handBookManager->updateModel();
    hide();
}

void gui::HandBookForm::on_deleteButton_clicked()
{
    deleteRows();
}

void gui::HandBookForm::on_addButton_clicked()
{
    addRow();
}

void gui::HandBookForm::on_addLineEdit_returnPressed()
{
    addRow();
}

void gui::HandBookForm::on_findButton_clicked()
{
    if (ui->findEdit->text().isEmpty())
        return;
    handBookManager->setFilter(ui->findEdit->text());
    ui->findCancelButton->setEnabled(true);
    ui->findEdit->clear();
}

void gui::HandBookForm::on_findCancelButton_clicked()
{
    handBookManager->cancelFilter();
    ui->findCancelButton->setEnabled(false);
}
