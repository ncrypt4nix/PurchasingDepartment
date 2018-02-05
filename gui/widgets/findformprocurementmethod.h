#ifndef FINDFORMPROCUREMENTMETHOD_H
#define FINDFORMPROCUREMENTMETHOD_H

#include <QWidget>
#include "gui/widgets/procurementmethodshandbookviewmanager.h"
#include "gui/widgets/messageboxcreater.h"
#include "logics/findobjectprocurementmethod.h"

namespace Ui
{
    class FindFormProcurementMethod;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс формы для реализации поиска модели конкурентных спосоов закупки */
    class FindFormProcurementMethod : public ProcurementMethodsHandBookViewManager, MessageBoxCreater
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit FindFormProcurementMethod(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~FindFormProcurementMethod();
        /*! \brief Удаляет всю информацию о прошлом посещении виджета */
        virtual void resetOldData();
        /*!
         * \brief Установить обьект поиска конкурентных способов закупки
         * \param value обьект поиска конкурентных способов закупки
         */
        void setFindObjectProcurementMethod(logics::FindObjectProcurementMethod *value);
        /*!
         * \brief Получить обьект поиска конкурентных способов закупки
         * \return обьект поиска конкурентных способов закупки
         */
        logics::FindObjectProcurementMethod *getFindObjectProcurementMethod();
        /*!
         * \brief Устанавливает справочник и налаживает коннекты, для обработки изменения справочников
         * \param value Справочник
         */
        virtual void setHandBookManager(logics::HandBookManager *value);
        /*!
         * \brief Проверяет целостность данных
         * \return целостность данных
         */
        virtual bool checkData();

    protected:
        /*!
         * \brief Заполняет обьект FindObjectProcurementMethod значениями с формы
         */
        void fillingFindObjectProcurementMethod();

    private slots:
        void on_closeButton_clicked();
        void on_okButton_clicked();

    signals:
        /*! сигнал окончания работы формы */
        void okClicked();

    private:
        Ui::FindFormProcurementMethod *ui;
        logics::FindObjectProcurementMethod *findObjectProcurementMethod = NULL;
        static const QDate DEFAULT_DATE;
    };
}

#endif // FINDFORMPROCUREMENTMETHOD_H
