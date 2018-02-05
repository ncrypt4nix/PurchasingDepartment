#ifndef FINDOBJECTCONTRACT_H
#define FINDOBJECTCONTRACT_H

#include <QDate>

#include "logics/findobjectabstract.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс для реализации поиска модели договоров */
    class FindObjectContract : public FindObjectAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский оьбект
         */
        explicit FindObjectContract(QObject *parent = 0);
        /*!
         * \brief Возвращает поисковой запрос для модели
         * \return поисковой запрос
         */
        virtual QString getFindQuery() const;
        /*!
         * \brief Установить номер договора
         * \param value номер договора
         */
        void setContractNumber(const QString &value);
        /*!
         * \brief Установить сумму от
         * \param value сумму от
         */
        void setContractsSumFrom(const double &value);
        /*!
         * \brief Установить сумму до
         * \param value сумму до
         */
        void setContractsSumTo(const double &value);
        /*!
         * \brief Установить комментарий
         * \param value комментарий
         */
        void setComment(const QString &value);
        /*!
         * \brief Установить дату начала от
         * \param value дату начала от
         */
        void setStartDateFrom(const QDate &value);
        /*!
         * \brief Установить дату начала до
         * \param value дату начала до
         */
        void setStartDateTo(const QDate &value);
        /*!
         * \brief Установить дату окончания от
         * \param value дату окончания от
         */
        void setEndDateFrom(const QDate &value);
        /*!
         * \brief Установить дату окончания до
         * \param value дату окончания до
         */
        void setEndDateTo(const QDate &value);
        /*!
         * \brief Установить id поставщика товаров и услуг
         * \param value id поставщика товаров и услуг
         */
        void setProviderId(const uint &value);
        /*!
         * \brief Установить id подразделения-заказчика
         * \param value id подразделения-заказчика
         */
        void setSubdivisionId(const uint &value);
        /*!
         * \brief Установить id ответственного лица
         * \param value id ответственного лица
         */
        void setResponsibleId(const uint &value);
        /*!
         * \brief Установить id источник финансирования
         * \param value id источник финансирования
         */
        void setSourceFinancingId(const uint &value);
        /*!
         * \brief Установить дата заключения договора от
         * \param value дата заключения договора от
         */
        void setConclusionDateFrom(const QDate &value);
        /*!
         * \brief Установить дата заключения договора до
         * \param value дата заключения договора до
         */
        void setConclusionDateTo(const QDate &value);
        /*!
         * \brief Установить дата регистрации от
         * \param value дата регистрации от
         */
        void setRegistrationDateFrom(const QDate &value);
        /*!
         * \brief Установить дата регистрации до
         * \param value дата регистрации до
         */
        void setRegistrationDateTo(const QDate &value);
        /*!
         * \brief Установить завершенность
         * \param value завершенность
         */
        void setCompleteness(const bool &value);

    protected:
        FindField
        /*! \brief номер договора */
            contractNumber,
            /*! \brief сумма договора от */
            contractsSumFrom,
            /*! \brief сумма договора после */
            contractsSumTo,
            /*! \brief комментарий */
            comment,
            /*! \brief дата начала от */
            startDateFrom,
            /*! \brief дата начала после */
            startDateTo,
            /*! \brief дата окончания до */
            endDateFrom,
            /*! \brief дата окончания после */
            endDateTo,
            /*! \brief дата заключения договора до */
            conclusionDateFrom,
            /*! \brief дата заключения договора после */
            conclusionDateTo,
            /*! \brief дата регистрации до */
            registrationDateFrom,
            /*! \brief дата регистрации после */
            registrationDateTo,
            /*! \brief завершенность */
            completeness,
            /*! \brief id поставщика */
            providerId,
            /*! \brief id Подразделение-заказчик */
            subdivisionId,
            /*! \brief id Ответственные лица */
            responsibleId,
            /*! \brief id источника финансирования */
            sourceFinancingId;
    };
}

#endif // FINDOBJECTCONTRACT_H
