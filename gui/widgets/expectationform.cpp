#include "expectationform.h"
#include "ui_expectationform.h"

using namespace gui;

const int ExpectationForm::TIME_EXPECTATION = 100;

ExpectationForm::ExpectationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpectationForm)
{
    ui->setupUi(this);
}

ExpectationForm::~ExpectationForm()
{
    delete ui;
}

void ExpectationForm::expectation()
{
    show();
    for (auto widget : widgets)
        widget->setEnabled(false);
    repaint();
    QTime time;
    time.start();
    for(;time.elapsed() < TIME_EXPECTATION;)
        QApplication::processEvents();
}

void ExpectationForm::end()
{
    for (auto widget : widgets)
        widget->setEnabled(true);
    hide();
}

QList<QWidget *> ExpectationForm::getWidgets() const
{
    return widgets;
}

void ExpectationForm::setWidgets(const QList<QWidget *> &value)
{
    widgets = value;
}
