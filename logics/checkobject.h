#ifndef CHECKOBJECT_H
#define CHECKOBJECT_H

#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>

#include "logics/registerobjectabstract.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс предоставляющий интерфейс и управление к конкретному счету */
    class CheckObject : public RegisterObjectAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit CheckObject(QObject *parent = 0);
        /*!
         * \brief Получить номер счета
         * \return номер счета
         */
        QString getNumber() const;
        /*!
         * \brief Изменить номер счета
         * \param value номер счета
         */
        void setNumber(const QString &value);
        /*!
         * \brief Получить дату регистрации
         * \return дата регистрации
         */
        QDate getRegistrationDate() const;
        /*!
         * \brief Изменить дату регистрации
         * \param value дата регистрации
         */
        void setRegistrationDate(const QDate &value);
        /*!
         * \brief Получить дату счета
         * \return дата счета
         */
        QDate getCheckDate() const;
        /*!
         * \brief Изменить дату счета
         * \param value дата счета
         */
        void setCheckDate(const QDate &value);
        /*!
         * \brief Получить сумму счета
         * \return сумма счета
         */
        double getSum() const;
        /*!
         * \brief Изменить сумму счета
         * \param value сумма счета
         */
        void setSum(double value);
        /*!
         * \brief Получить описание
         * \return описание
         */
        QString getDescription() const;
        /*!
         * \brief Изменить описание
         * \param value описание
         */
        void setDescription(const QString &value);
        /*!
         * \brief Получить количество чеков
         * \return количество чеков
         */
        uint getNumberChecks() const;
        /*!
         * \brief Изменить количество чеков
         * \param value количество чеков
         */
        void setNumberChecks(const uint &value);
        /*!
         * \brief Получить id поставщика
         * \return id поставщика
         */
        uint getProviderId() const;
        /*!
         * \brief Изменить id поставщика
         * \param value id поставщика
         */
        void setProviderId(const uint &value);
        /*!
         * \brief Получить id подразделения заказчика
         * \return id подразделения заказчика
         */
        uint getSubdivisionId() const;
        /*!
         * \brief Изменить id подразделения заказчика
         * \param value id подразделения заказчика
         */
        void setSubdivisionId(const uint &value);
        /*!
         * \brief Получить id ответственного лица
         * \return id ответственного лица
         */
        uint getResponsibleId() const;
        /*!
         * \brief Изменить id ответственного лица
         * \param value id ответственного лица
         */
        void setResponsibleId(const uint &value);
        /*!
         * \brief Получить id источника финансирования
         * \return id источника финансирования
         */
        uint getSourceFinancingId() const;
        /*!
         * \brief Изменить id источника финансирования
         * \param value id источника финансирования
         */
        void setSourceFinancingId(const uint &value);
        /*!
         * \brief Изменить id платежного документа
         * \return id платежного документа
         */
        uint getPaymentDocumentId() const;
        /*!
         * \brief Изменить id платежного документа
         * \param value id платежного документая
         */
        void setPaymentDocumentId(const uint &value);
        /*!
         * \brief Получить завершенность
         * \return завершенность
         */
        bool getCompleteness() const;
        /*!
         * \brief Установить завершенность
         * \param value завершенность
         */
        void setCompleteness(bool value);
        /*!
         * \brief Сохраняет все изменения в БД
         * \return успешность выполнения операции
         */
        virtual bool save() const;
        /*!
         * \brief Сохраняет новый счет в БД
         * \return успешность выполнения операции
         */
        virtual bool add();
        /*!
         * \brief Копирование данных из другого обьекта
         * \param other другой обьект
         */
        void copyData(const CheckObject &other);
        /*!
         * \brief Создает и возвращает шапку excel-файла
         * \return шапку excel-файла
         */
        virtual QString headerExcel() const;
        /*!
         * \brief Создает и возвращает расширенную шапку excel-файла
         * \return шапку excel-файла
         */
        virtual QString headerExtendedExcel() const;
        /*!
         * \brief Создает и возвращает строку с данными excel-файла
         * \return строку с данными excel-файла
         */
        virtual QString rowDataExcel() const;
        /*!
         * \brief Создает и возвращает строку со всеми данными excel-файла
         * \return строку с данными excel-файла
         */
        virtual QString rowDataExtendedExcel() const;

    public:
        /*!
         * \brief Оператор присваивания
         * \param other другой обьект
         * \return ссылка на данный обьект
         */
        CheckObject &operator=(const CheckObject &other);

    protected:
        /*!
         * \brief Обновления данных, после смены id
         * \return успешность выполнения операции
         */
        virtual bool update();

    public:
        static const QString
            /*! \brief № чека */
            CHECK_NUMBER_STR,
            /*! \brief Дата регистрации */
            REGISTRATION_DATE_STR,
            /*! \brief Дата счета */
            CHECK_DATE_STR,
            /*! \brief Сумма счета */
            CHECK_SUM_STR,
            /*! \brief Описание */
            DESCRIPTION_STR,
            /*! \brief Колличество чеков */
            NUMBER_CHECKS_STR,
            /*! \brief Поставщики товаров/услуг */
            PROVIDERS_STR,
            /*! \brief Подразделение-заказчик */
            SUBDIVISIONS_STR,
            /*! \brief Ответственные лица */
            RESPONSIBLES_STR,
            /*! \brief Источники финансирования */
            SOURCE_FINANCINGS_STR,
            /*! \brief Платежные документы */
            PAYMENT_DOCUMENTS_STR,
            /*! \brief завершенность */
            COMPLETENESS;

    private:
        QString number = "";
        QDate registrationDate = QDate();
        QDate checkDate = QDate();
        double sum = 0.;
        QString description = "";
        uint numberChecks = 0;
        uint providerId = 0;
        uint subdivisionId = 0;
        uint responsibleId = 0;
        uint sourceFinancingId = 0;
        uint paymentDocumentId = 0;
        bool completeness = false;
    };
}

#endif // CHECKOBJECT_H
