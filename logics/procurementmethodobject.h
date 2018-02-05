#ifndef PROCUREMENTMETHODOBJECT_H
#define PROCUREMENTMETHODOBJECT_H

#include <QDate>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>

#include "logics/registerobjectabstract.h"
#include "logics/contractprocurementmethodobject.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс предоставляющий интерфейс и управление к конкретному конкурентному способу закупки */
    class ProcurementMethodObject : public RegisterObjectAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit ProcurementMethodObject(QObject *parent = 0);
        /*!
         * \brief Получить номер извещения
         * \return номер извещения
         */
        QString getNumberNotice() const;
        /*!
         * \brief Изменить номер извещения
         * \param value номер извещения
         */
        void setNumberNotice(const QString &value);
        /*!
         * \brief Получить Дата извещения
         * \return Дата извещения
         */
        QDate getNoticeDate() const;
        /*!
         * \brief Изменить Дата извещения
         * \param value Дата извещения
         */
        void setNoticeDate(const QDate &value);
        /*!
         * \brief Получить Предмет закупки
         * \return Предмет закупки
         */
        QString getProcurementObject() const;
        /*!
         * \brief Изменить Предмет закупки
         * \param value Предмет закупки
         */
        void setProcurementObject(const QString &value);
        /*!
         * \brief Получить Начальная (максимальная) цена договора
         * \return Начальная (максимальная) цена договора
         */
        double getStartingPrice() const;
        /*!
         * \brief Изменить Начальная (максимальная) цена договора
         * \param value Начальная (максимальная) цена договора
         */
        void setStartingPrice(double value);
        /*!
         * \brief Получить Дата начала срока подачи заявок
         * \return Дата начала срока подачи заявок
         */
        QDate getStartDateDeadline() const;
        /*!
         * \brief Изменить Дата начала срока подачи заявок
         * \param value Дата начала срока подачи заявок
         */
        void setStartDateDeadline(const QDate &value);
        /*!
         * \brief Получить Дата окончания срока подачи заявок
         * \return Дата окончания срока подачи заявок
         */
        QDate getEndDateDeadline() const;
        /*!
         * \brief Изменить Дата окончания срока подачи заявок
         * \param value Дата окончания срока подачи заявок
         */
        void setEndDateDeadline(const QDate &value);
        /*!
         * \brief Получить Дата протокола вскрытия конвертов
         * \return Дата протокола вскрытия конвертов
         */
        QDate getOpeningEnvelopesDate() const;
        /*!
         * \brief Изменить Дата протокола вскрытия конвертов
         * \param value Дата протокола вскрытия конвертов
         */
        void setOpeningEnvelopesDate(const QDate &value);
        /*!
         * \brief Получить Дата протокола рассмотрения подведения итогов
         * \return Дата протокола рассмотрения подведения итогов
         */
        QDate getSummarizingDate() const;
        /*!
         * \brief Изменить Дата протокола рассмотрения подведения итогов
         * \param value Дата протокола рассмотрения подведения итогов
         */
        void setSummarizingDate(const QDate &value);
        /*!
         * \brief Получить Состояние процедуры
         * \returnСостояние процедуры
         */
        bool getProcedureComplete() const;
        /*!
         * \brief Изменить Состояние процедуры
         * \param value Состояние процедуры
         */
        void setProcedureComplete(bool value);
        /*!
         * \brief Получить СМП
         * \return СМП
         */
        bool getSmp() const;
        /*!
         * \brief Установить СМП
         * \param value СМП
         */
        void setSmp(bool value);
        /*!
         * \brief Получить Способ закупки
         * \return Способ закупки
         */
        uint getProcurementMethodId() const;
        /*!
         * \brief Изменить Способ закупки
         * \param value Способ закупки
         */
        void setProcurementMethodId(const uint &value);
        /*!
         * \brief Получить дата регистрации
         * \return дата регистрации
         */
        QDate getRegistrationDate() const;
        /*!
         * \brief Изменить дата регистрации
         * \param value дата регистрации
         */
        void setRegistrationDate(const QDate &value);
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
         * \brief Сохраняет новый конкурентный спосо закупки в БД
         * \return успешность выполнения операции
         */
        virtual bool add();
        /*!
         * \brief Получить обьект контракта
         * \return обьект контракта
         */
        ContractProcurementMethodObject *getContractProcurementMethodObject();
        /*!
         * \brief Изменить id
         * \param id идентификатор
         * \return успешность выполнения операции
         */
        virtual bool changeId(const uint &id);
        /*!
         * \brief Копирование данных из другого обьекта
         * \param other другой обьект
         */
        void copyData(const ProcurementMethodObject &other);
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
        ProcurementMethodObject &operator=(const ProcurementMethodObject &other);

    protected:
        /*!
         * \brief Обновления данных, после смены id
         * \return успешность выполнения операции
         */
        virtual bool update();

    public:
        static const QString
            /*! \brief № извещения */
            NUMBER_NOTICE_STR,
            /*! \brief Дата измещения */
            NOTICE_DATE_STR,
            /*! \brief Предмет закупки */
            PROCUREMENT_OBJECT_STR,
            /*! \brief Начальная (максимальная) цена договора */
            STARTING_PRICE_STR,
            /*! \brief Дата начала срока подачи заявок */
            START_DATE_DEADLINE_STR,
            /*! \brief Дата окончания срока подачи заявок */
            END_DATE_DEADLINE_STR,
            /*! \brief Дата протокола вскрытия конвертов */
            OPENING_ENVELOPES_DATE_STR,
            /*! \brief Дата протокола рассмотрения подведения итогов */
            SUMMARIZING_DATE_STR,
            /*! \brief Способы закупки */
            PROCUREMENT_METHODS_STR,
            /*! \brief Статус */
            PROCEDURE_COMPLETE_STR,
            /*! \brief СМП */
            SMP_STR,
            /*! \brief дата регистрации */
            DATE_REGISTRATION_STR,
            /*! \brief Завершенность */
            COMPLETENESS;

    private:
        QString numberNotice = "";
        QDate noticeDate = QDate();
        QString procurementObject = "";
        double startingPrice = 0.;
        QDate startDateDeadline = QDate();
        QDate endDateDeadline = QDate();
        QDate openingEnvelopesDate = QDate();
        QDate summarizingDate = QDate();
        bool procedureComplete = false;
        uint procurementMethodId = 0;
        bool smp = false;
        QDate registrationDate = QDate();
        bool completeness = false;
        ContractProcurementMethodObject contractObj;
    };
}

#endif // PROCUREMENTMETHODOBJECT_H
