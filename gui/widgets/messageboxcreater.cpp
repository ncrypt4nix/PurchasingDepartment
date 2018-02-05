#include "messageboxcreater.h"

using namespace gui;

bool MessageBoxCreater::createMessageBox(const QString &message) const
{
    QMessageBox* messageBox =
            new QMessageBox(QMessageBox::Warning,
            QObject::tr("Вы уверены?"),
            message,
            QMessageBox::Yes | QMessageBox::No);
    auto answer = messageBox->exec();
    delete messageBox;
    if (answer == QMessageBox::Yes)
        return true;
    else
        return false;
}

void MessageBoxCreater::createErrorMessageBox(const QString &message) const
{
    QMessageBox* messageBox =
            new QMessageBox(QMessageBox::Critical,
            QObject::tr("Ошибка"),
            message,
            QMessageBox::Ok);
    messageBox->exec();
    delete messageBox;
}

void MessageBoxCreater::createExceptionMessageBox(const exceptions::Exception exception) const
{
    QString error_msg = QObject::tr("К сожалению произошла ошибка.\n")
            + exception.getErrorMessage()
            + QObject::tr("\nОбратитесь к администратору.");
    createErrorMessageBox(error_msg);
}

QString MessageBoxCreater::createSaveFileNameExcelMessageBox() const
{
    QString filter;
    QString fileName = QFileDialog::getSaveFileName(0, QObject::tr("Выберите файл, для сохранения"), "", "*.xls ;; *.xml", &filter);
    filter.remove(filter.indexOf("*"), 1);
    return fileName + filter;
}
