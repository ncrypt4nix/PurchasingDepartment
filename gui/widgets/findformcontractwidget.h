#ifndef FINDFORMCONTRACTWIDGET_H
#define FINDFORMCONTRACTWIDGET_H

#include <QDate>

#include "gui/widgets/handbookviewmanager.h"
#include "logics/findobjectcontract.h"

namespace Ui
{
    class FindFormContractWidget;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс формы для реализации поиска модели договоров */
    class FindFormContractWidget : public HandBookViewManager
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit FindFormContractWidget(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~FindFormContractWidget();
        /*! \brief Удаляет всю информацию о прошлом посещении виджета */
        virtual void resetOldData();
        /*!
         * \brief Установить обьект поиска договора
         * \param value обьект поиска договора
         */
        void setFindObjectContract(logics::FindObjectContract *value);
        /*!
         * \brief Получить обьект поиска договора
         * \return обьект поиска договора
         */
        logics::FindObjectContract *getFindObjectContract();
        /*! \brief Заполняет обьект FindObjectContract значениями с формы */
        void fillingFindObjectContract();        
        /*! \brief Очистить память от обьекта договора */
        void freeObject();
        /*!
         * \brief Проверяет целостность данных
         * \return целостность данных
         */
        virtual bool checkData();

    private:
        Ui::FindFormContractWidget *ui;
        logics::FindObjectContract *findObjectContract = NULL;
        static const QDate DEFAULT_DATE;
    };
}

#endif // FINDFORMCONTRACTWIDGET_H
