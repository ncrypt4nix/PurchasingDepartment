#ifndef REPORTFORM_H
#define REPORTFORM_H

#include <QWidget>
#include "gui/widgets/messageboxcreater.h"
#include "logics/report.h"

namespace Ui
{
    class ReportForm;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Форма отчетов */
    class ReportForm : public QWidget, MessageBoxCreater
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit ReportForm(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~ReportForm();
        /*! \brief Переопределенны метод показа виджета */
        void show();

    private slots:
        void on_closeButton_clicked();
        void on_reportButton_clicked();

    protected:
        static const QString
            /*! \brief Реестр договоров */
            CONTRACT_REGISTER,
            /*! \brief Реестр счетов */
            CHECK_REGISTER,
            /*! \brief Реестр конкурентных методов закупки */
            PROCUREMENT_METHODS_REGISTER,
            /*! \brief Реестры договоров и счетов */
            CONTRACT_CHECK_REGISTERS,
            /*! \brief Все реестры */
            ALL_REGISTERS;

    private:
        Ui::ReportForm *ui;
    };
}

#endif // REPORTFORM_H
