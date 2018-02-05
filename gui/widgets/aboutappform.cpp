#include "aboutappform.h"
#include "ui_aboutappform.h"

using namespace gui;

AboutAppForm::AboutAppForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutAppForm)
{
    ui->setupUi(this);
}

AboutAppForm::~AboutAppForm()
{
    delete ui;
}

void gui::AboutAppForm::on_closeButton_clicked()
{
    hide();
}
