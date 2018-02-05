#ifndef FINDOBJECTCHECK_H
#define FINDOBJECTCHECK_H

#include "logics/findobjectabstract.h"
#include <QDate>

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс для реализации поиска модели счетов */
    class FindObjectCheck : public FindObjectAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский оьбект
         */
        explicit FindObjectCheck(QObject *parent = 0);
        /*!
         * \brief Возвращает поисковой запрос для модели
         * \return поисковой запрос
         */
        virtual QString getFindQuery() const;
        /*!
         * \brief Установить Номер чека
         * \param value Номер чека
         */
        void setCheckNumber(const QString &value);
        /*!
         * \brief Установить Дата регистрации до
         * \param value Дата регистрации до
         */
        void setRegistrationDateFrom(const QDate &value);
        /*!
         * \brief Установить Дата регистрации после
         * \param value Дата регистрации после
         */
        void setRegistrationDateTo(const QDate &value);
        /*!
         * \brief Установить Дата счета до
         * \param value Дата счета до
         */
        void setCheckDateFrom(const QDate &value);
        /*!
         * \brief Установить Дата счета после
         * \param value Дата счета после
         */
        void setCheckDateTo(const QDate &value);
        /*!
         * \brief Установить сумму счета до
         * \param value сумму счета до
         */
        void setCheckSumFrom(const double &value);
        /*!
         * \brief Установить сумму счета после
         * \param value сумму счета после
         */
        void setCheckSumTo(const double &value);
        /*!
         * \brief Установить Колличество чеков до
         * \param value Колличество чеков до
         */
        void setNumberChecksFrom(const uint &value);
        /*!
         * \brief Установить Колличество чеков после
         * \param value Колличество чеков после
         */
        void setNumberChecksTo(const uint &value);
        /*!
         * \brief Установить описание
         * \param value описание
         */
        void setDescription(const QString &value);
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
         * \brief Установить id платежных документов
         * \param value id платежных документов
         */
        void setPaymentDocumentId(const uint &value);
        /*!
         * \brief Установить завершенность
         * \param value завершенность
         */
        void setCompleteness(const bool &value);

    private:
        FindField checkNumber,
        registrationDateFrom,
            registrationDateTo,
            checkDateFrom,
            checkDateTo,
            checkSumFrom,
            checkSumTo,
            numberChecksFrom,
            numberChecksTo,
            description,
            providerId,
            subdivisionId,
            responsibleId,
            sourceFinancingId,
            paymentDocumentId,
            completeness;
    };
}

#endif // FINDOBJECTCHECK_H
