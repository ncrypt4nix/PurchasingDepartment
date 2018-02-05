#include "reportform.h"
#include "ui_reportform.h"

using namespace gui;

const QString ReportForm::CONTRACT_REGISTER = tr("Реестр договоров");
const QString ReportForm::CHECK_REGISTER = tr("Реестр счетов");
const QString ReportForm::PROCUREMENT_METHODS_REGISTER = tr("Реестр конкурентных методов закупки");
const QString ReportForm::CONTRACT_CHECK_REGISTERS = tr("Реестры договоров и счетов");
const QString ReportForm::ALL_REGISTERS = tr("Все реестры");

ReportForm::ReportForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReportForm)
{
    ui->setupUi(this);
    ui->registerBox->addItem(CONTRACT_REGISTER);
    ui->registerBox->addItem(CHECK_REGISTER);
    ui->registerBox->addItem(PROCUREMENT_METHODS_REGISTER);
    ui->registerBox->addItem(CONTRACT_CHECK_REGISTERS);
    ui->registerBox->addItem(ALL_REGISTERS);
}

ReportForm::~ReportForm()
{
    delete ui;
}

void ReportForm::show()
{
    ui->dateEdit->setDate(QDate::currentDate());
    QWidget::show();
}

void gui::ReportForm::on_closeButton_clicked()
{
    hide();
}

void gui::ReportForm::on_reportButton_clicked()
{
    QString currentText = ui->registerBox->currentText();
    QDate date = ui->dateEdit->date();
    logics::Report::ReportData report_data;
    try
    {
        if (currentText == CONTRACT_REGISTER)
            report_data = logics::Report::reportContract(date);
        if (currentText == CHECK_REGISTER)
            report_data = logics::Report::reportCheck(date);
        if (currentText == PROCUREMENT_METHODS_REGISTER)
            report_data = logics::Report::reportProcurementMethods(date);
        if (currentText == CONTRACT_CHECK_REGISTERS)
            report_data = logics::Report::reportContractAndCheck(date);
        if (currentText == ALL_REGISTERS)
            report_data = logics::Report::reportAll(date);
    }
    catch(exceptions::DataBaseException &db_exc)
    {
        createErrorMessageBox(db_exc.getErrorMessage());
    }
    ui->sumReportEdit->setText(QString::number(report_data.sum));
    ui->countReportEdit->setText(QString::number(report_data.count));
}
