#ifndef FINDFORMCONTRACT_H
#define FINDFORMCONTRACT_H

#include <QWidget>
#include "gui/widgets/messageboxcreater.h"
#include "logics/findobjectcontract.h"
#include "logics/handbook.h"

namespace Ui
{
    class FindFormContract;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс формы для реализации поиска модели договоров */
    class FindFormContract : public QWidget, MessageBoxCreater
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit FindFormContract(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~FindFormContract();
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
        /*!
         * \brief Устанавливает справочник и налаживает коннекты, для обработки изменения справочников
         * \param value Справочник
         */
        virtual void setHandBookManager(logics::HandBookManager *value);

    private slots:
        void on_closeButton_clicked();
        void on_okButton_clicked();

    signals:
        /*! сигнал окончания работы формы */
        void okClicked();

    private:
        Ui::FindFormContract *ui;
    };
}

#endif // FINDFORMCONTRACT_H
