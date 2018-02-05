#ifndef FINDFORMCHECK_H
#define FINDFORMCHECK_H

#include <QWidget>

#include "logics/findobjectcheck.h"
#include "gui/widgets/paymentdocumenthandbookviewmanager.h"
#include "gui/widgets/messageboxcreater.h"

namespace Ui
{
    class FindFormCheck;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс формы для реализации поиска модели счетов */
    class FindFormCheck : public PaymentDocumentHandBookViewManager, MessageBoxCreater
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit FindFormCheck(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~FindFormCheck();
        /*! \brief Удаляет всю информацию о прошлом посещении виджета */
        virtual void resetOldData();
        /*!
         * \brief Установить обьект поиска счетов
         * \param value обьект поиска счетов
         */
        void setFindObjectCheck(logics::FindObjectCheck *value);
        /*!
         * \brief Получить обьект поиска счетов
         * \return обьект поиска счетов
         */
        logics::FindObjectCheck *getFindObjectCheck();
        /*!
         * \brief Проверяет целостность данных
         * \return целостность данных
         */
        virtual bool checkData();

    protected:
        /*! \brief Заполняет обьект FindObjectCheck значениями с формы */
        void fillingFindObjectCheck();

    private slots:
        void on_okButton_clicked();
        void on_closeButton_clicked();

    signals:
        /*! сигнал окончания работы формы */
        void okClicked();

    private:
        Ui::FindFormCheck *ui;
        logics::FindObjectCheck *findObjectCheck = NULL;
        static const QDate DEFAULT_DATE;
    };
}

#endif // FINDFORMCHECK_H
