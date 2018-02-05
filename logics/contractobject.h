#ifndef CONTRACTOBJECT_H
#define CONTRACTOBJECT_H

#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>
#include <QSqlTableModel>

#include "logics/registerobjectabstract.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс предоставляющий интерфейс и управление к конкретному контракту */
    class ContractObject : public RegisterObjectAbstract
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit ContractObject(QObject *parent = 0);
        /*!
         * \brief Конструктор копирования
         * \param other другой обьект
         */
        explicit ContractObject(const ContractObject &other);
        /*!
         * \brief Получить номер контракта
         * \return номер
         */
        QString getNumber() const;
        /*!
         * \brief Изменить номер контракта
         * \param value номер контракта
         */
        void setNumber(const QString &value);
        /*!
         * \brief Получить сумму контракта
         * \return сумма
         */
        double getSum() const;
        /*!
         * \brief Изменить сумма контракта
         * \param value сумма контракта
         */
        void setSum(double value);
        /*!
         * \brief Получить дату начала контракта
         * \return дата начала
         */
        QDate getStartDate() const;
        /*!
         * \brief Изменить дату начала контракта
         * \param value дата начала контракта
         */
        void setStartDate(const QDate &value);
        /*!
         * \brief Получить дату окончания контракта
         * \return дата окончания
         */
        QDate getEndDate() const;
        /*!
         * \brief Изменить дату окончания контракта
         * \param value дата окончания контракта
         */
        void setEndDate(const QDate &value);
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
         * \brief Получить комментарий по контракту
         * \return комментарий по контракту
         */
        QString getComment() const;
        /*!
         * \brief Изменить комментарий по контракту
         * \param value комментарий по контракту
         */
        virtual void setComment(const QString &value);
        /*!
         * \brief Получить дата заключения договора
         * \return дата заключения договора
         */
        QDate getConclusionDate() const;
        /*!
         * \brief Изменить дата заключения договора
         * \param value дата заключения договора
         */
        void setConclusionDate(const QDate &value);
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
         * \brief Изменить завершенность
         * \param value завершенность
         */
        void setCompleteness(bool value);
        /*!
         * \brief Сохраняет все изменения в БД
         * \return успешность выполнения операции
         */
        virtual bool save() const;
        /*!
         * \brief Сохраняет новый договор в БД
         * \return успешность выполнения операции
         */
        virtual bool add();
        /*!
         * \brief Возвращает готовую модель счетов реестра договоров
         * \return модель счетов
         */
        virtual QSqlTableModel *getModel() const;
        /*!
         * \brief Копирование данных из другого обьекта
         * \param other другой обьект
         */
        virtual void copyData(const ContractObject &other);
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
        /*!
         * \brief Генерирует данные для экспорта в эксел в расширенном формате
         * \param spaces пустые пространства
         * \return данные для экспорта в эксел
         */
        QString genRowDataExcel(const uint &spaces = 0) const;

    public:
        /*!
         * \brief Оператор присваивания
         * \param other другой обьект
         * \return ссылка на данный обьект
         */
        ContractObject &operator=(const ContractObject &other);

    protected:
        /*!
         * \brief Обновления данных, после смены id
         * \return успешность выполнения операции
         */
        virtual bool update();
        /*!
         * \brief Получить имя таблицы реестра в БД
         * \return имя таблицы реестра
         */
        QString getRegisterName() const;
        /*!
         * \brief Установить имя таблицы реестра в БД
         * \param value имя таблицы реестра
         */
        void setRegisterName(const QString &value);
        /*!
         * \brief Получить имя таблицы счетов в БД
         * \return имя таблицы счетов
         */
        QString getCheckTableName() const;
        /*!
         * \brief Установить имя таблицы счетов в БД
         * \param value имя таблицы счетов
         */
        void setCheckTableName(const QString &value);


    public:
        /*! \brief Реестр договоров */
        static const QString REGISTER_CONTRACTS;
        /*! \brief Список скрытых колонок */
        static const QList<uint> columnsHidden;
        /*! \brief Перечесление номеров колонок талицы счетов */
        enum class CheckColumnNumbers
        {
            /*! \brief Id счета */
            checkId = 0,
            /*! \brief номер счета */
            checkNumber = 1,
            /*! \brief дата регистрации счета */
            registrationDate = 2,
            /*! \brief дата счета */
            checkDate = 3,
            /*! \brief сумма счета */
            checkSum = 4,
            /*! \brief описание счета */
            description = 5,
            /*! \brief Id контракта */
            contractId = 6
        };

        static const QString
                /*! \brief № Договора */
                CONTRACT_NUMBER_STR,
                /*! \brief Сумма */
                CONTRACTS_SUM_STR,
                /*! \brief Освоено */
                DISBURSED_STR,
                /*! \brief Остаток */
                BALANCE_STR,
                /*! \brief Дата Начала */
                START_DATE_STR,
                /*! \brief Дата Окончания */
                END_DATE_STR,
                /*! \brief Поставщик Услуг */
                PROVIDERS_STR,
                /*! \brief Подразделение-Заказчик */
                SUBDIVISIONS_STR,
                /*! \brief Ответственные лица */
                RESPONSIBLES_STR,
                /*! \brief Источники финансирования */
                SOURCE_FINANCINGS_STR,
                /*! \brief Комментарий */
                COMMENT_STR,
                /*! \brief дата заключения договора */
                CONCLUSION_DATE_STR,
                /*! \brief дата регистрации */
                DATE_REGISTRATION_STR,
                /*! \brief завершенность */
                COMPLETENESS_STR,
                /*! \brief № счета */
                CHECK_NUMBER_STR,
                /*! \brief Дата регистрации */
                REGISTRATION_DATE_STR,
                /*! \brief Дата счета */
                CHECK_DATE_STR,
                /*! \brief Сумма счета */
                CHECK_SUM_STR,
                /*! \brief Описание */
                DESCRIPTION_STR;

    protected:
        /*! \brief Счета реестра договоров */
        static const QString REGISTER_CONTRACTS_CHECKS;
        /*! \brief Перечисление индексов модели счетов */
        enum INDEX_CHECK_MODEL : int
        {
            /*! \brief Индекс столбца с № счета */
            CHECK_NUMBER_INDEX = 1,
            /*! \brief Индекс столбца с Дата регистрации */
            REGISTRATION_DATE_INDEX,
            /*! \brief Индекс столбца с Дата счета */
            CHECK_DATE_INDEX,
            /*! \brief  суммой в модели счетов */
            CHECK_SUM_INDEX,
            /*! \brief Индекс столбца с Описание */
            DESCRIPTION_INDEX
        };

    private:
        QString number = "";
        double sum = 0.;
        QDate startDate = QDate();
        QDate endDate = QDate();
        uint providerId = 0;
        uint subdivisionId = 0;
        uint responsibleId = 0;
        uint sourceFinancingId = 0;
        QDate conclusionDate = QDate();
        QDate registrationDate = QDate();
        bool completeness = false;
        QString comment = "";
        QString registerName;
        QString checkTableName;
    };
}

#endif // CONTRACTOBJECT_H
