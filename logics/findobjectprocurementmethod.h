#ifndef FINDOBJECTPROCUREMENTMETHOD_H
#define FINDOBJECTPROCUREMENTMETHOD_H
#include <QDebug>
#include "logics/findobjectcontract.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс для реализации поиска модели конкурентных способов закупки */
    class FindObjectProcurementMethod : public FindObjectContract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский оьбект
         */
        explicit FindObjectProcurementMethod(QObject *parent = 0);
        /*!
         * \brief Возвращает поисковой запрос для модели
         * \return поисковой запрос
         */
        virtual QString getFindQuery() const;
        /*!
         * \brief Изменить номер извещения
         * \param value номер извещения
         */
        void setNumberNotice(const QString &value);
        /*!
         * \brief Изменить Дата извещения от
         * \param value Дата извещения от
         */
        void setNoticeDateFrom(const QDate &value);
        /*!
         * \brief Изменить Дата извещения до
         * \param value Дата извещения до
         */
        void setNoticeDateTo(const QDate &value);
        /*!
         * \brief Изменить Предмет закупки
         * \param value Предмет закупки
         */
        void setProcurementObject(const QString &value);
        /*!
         * \brief Изменить Начальная (максимальная) цена договора до
         * \param value Начальная (максимальная) цена договора до
         */
        void setStartingPriceFrom(const double &value);
        /*!
         * \brief Изменить Начальная (максимальная) цена договора до
         * \param value Начальная (максимальная) цена договора до
         */
        void setStartingPriceTo(const double &value);
        /*!
         * \brief Изменить Дата начала срока подачи заявок от
         * \param value Дата начала срока подачи заявок от
         */
        void setStartDateDeadlineFrom(const QDate &value);
        /*!
         * \brief Изменить Дата начала срока подачи заявок до
         * \param value Дата начала срока подачи заявок до
         */
        void setStartDateDeadlineTo(const QDate &value);
        /*!
         * \brief Изменить Дата окончания срока подачи заявок от
         * \param value Дата окончания срока подачи заявок от
         */
        void setEndDateDeadlineFrom(const QDate &value);
        /*!
         * \brief Изменить Дата окончания срока подачи заявок до
         * \param value Дата окончания срока подачи заявок до
         */
        void setEndDateDeadlineTo(const QDate &value);
        /*!
         * \brief Изменить Дата протокола вскрытия конвертов от
         * \param value Дата протокола вскрытия конвертов от
         */
        void setOpeningEnvelopesDateFrom(const QDate &value);
        /*!
         * \brief Изменить Дата протокола вскрытия конвертов до
         * \param value Дата протокола вскрытия конвертов до
         */
        void setOpeningEnvelopesDateTo(const QDate &value);
        /*!
         * \brief Изменить Дата протокола рассмотрения подведения итогов от
         * \param value Дата протокола рассмотрения подведения итогов от
         */
        void setSummarizingDateFrom(const QDate &value);
        /*!
         * \brief Изменить Дата протокола рассмотрения подведения итогов до
         * \param value Дата протокола рассмотрения подведения итогов до
         */
        void setSummarizingDateTo(const QDate &value);
        /*!
         * \brief Изменить Состояние процедуры
         * \param value Состояние процедуры
         */
        void setProcedureComplete(const bool &value);
        /*!
         * \brief Изменить Способы закупки
         * \param value Способы закупки
         */
        void setProcurementMethodId(const uint &value);
        /*!
         * \brief Изменить СМП
         * \param value СМП
         */
        void setSmp(const bool &value);
        /*!
         * \brief Изменить дата регистрации
         * \param value дата регистрации
         */
        void setRegistrationDateRPMFrom(const QDate &value);
        /*!
         * \brief Изменить дата регистрации
         * \param value дата регистрации
         */
        void setRegistrationDateRPMTo(const QDate &value);
        /*!
         * \brief Изменить завершенность
         * \param value завершенность
         */
        void setCompletenessRPM(const bool &value);

    private:
        FindField
            numberNotice,
            noticeDateFrom,
            noticeDateTo,
            procurementObject,
            startingPriceFrom,
            startingPriceTo,
            startDateDeadlineFrom,
            startDateDeadlineTo,
            endDateDeadlineFrom,
            endDateDeadlineTo,
            openingEnvelopesDateFrom,
            openingEnvelopesDateTo,
            summarizingDateFrom,
            summarizingDateTo,
            procedureComplete,
            smp,
            registrationDateRPMFrom,
            registrationDateRPMTo,
            procurementMethodId,
            completenessRPM;
    };
}

#endif // FINDOBJECTPROCUREMENTMETHOD_H
