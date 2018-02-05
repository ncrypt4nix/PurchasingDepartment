#include "handbookviewmanagerabstract.h"

using namespace gui;

const int HandBookViewManagerAbstract::DEFAULT_VALUE = -1;

HandBookViewManagerAbstract::HandBookViewManagerAbstract(QWidget *parent) :
    QWidget(parent)
{
}

void HandBookViewManagerAbstract::setHandBookManager(logics::HandBookManager *value)
{
    handBookManager = value;
}

void HandBookViewManagerAbstract::setHandBookForm(HandBookForm *value)
{
    handBookForm = value;
}

void HandBookViewManagerAbstract::changeBox(QComboBox *box, const logics::HandBookManager::ModelIndex &index)
{
    int currentIndex = box->currentIndex();
    QString currentText = box->currentText();
    QStringList textList;
    if (currentIndex != DEFAULT_VALUE)
        for (int i = 0; i < box->count(); i++)
            textList << box->itemText(i);
    box->clear();
    auto map = handBookManager->getMapHandBook(index);
    box->addItems(map.keys());
    if (currentIndex == DEFAULT_VALUE)
        return;
    if (static_cast<int>(map.value(currentText, DEFAULT_VALUE)) != DEFAULT_VALUE)
        box->setCurrentText(currentText);
    else
        for (auto i = map.begin(); i != map.end(); i++)
            if (!textList.contains(i.key(), Qt::CaseInsensitive))
            {
                box->setCurrentText(i.key());
                return;
            }
}

void HandBookViewManagerAbstract::showHandBook(const logics::HandBookManager::ModelIndex &index)
{
    try
    {
        handBookForm->setModel(index);
        handBookForm->show();
        handBookForm->activateWindow();
    }
    catch(exceptions::TableModelException &tm_exc)
    {
        qDebug() << tm_exc.getErrorMessage();
    }
}
