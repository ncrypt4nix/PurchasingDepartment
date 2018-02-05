#ifndef REPORT_H
#define REPORT_H

#include <QObject>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

#include "exceptions/databaseexception.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс отчетов */
    class Report : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit Report(QObject *parent = 0);
        /*! \brief Структура отчета */
        struct ReportData
        {
            /*! \brief сумма  */
            double sum;
            /*! \brief количество */
            int count;
            /*!
             * \brief operator +
             * \param other другой обьект
             * \return результат
             */
            ReportData operator+(const ReportData other) const;
        };
        /*!
         * \brief Получить отчет рееста договоров
         * \param date Дата для отчета
         * \return отчет реестра договоров
         * \throw DataBaseException при неудачном запросе к БД
         */
        static ReportData reportContract(const QDate &date);
        /*!
         * \brief Получить отчет рееста счетов
         * \param date Дата для отчета
         * \return отчет реестра счетов
         * \throw DataBaseException при неудачном запросе к БД
         */
        static ReportData reportCheck(const QDate &date);
        /*!
         * \brief Получить отчет рееста конкурентных сособов закупки
         * \param date Дата для отчета
         * \return отчет реестра конкурентных сособов закупки
         * \throw DataBaseException при неудачном запросе к БД
         */
        static ReportData reportProcurementMethods(const QDate &date);
        /*!
         * \brief Получить отчет рееста договоров и счетов
         * \param date Дата для отчета
         * \return отчет реестра договоров и счетов
         * \throw DataBaseException при неудачном запросе к БД
         */
        static ReportData reportContractAndCheck(const QDate &date);
        /*!
         * \brief Получить отчет всех реестов
         * \param date Дата для отчета
         * \return отчет всех реестов
         * \throw DataBaseException при неудачном запросе к БД
         */
        static ReportData reportAll(const QDate &date);

    protected:
        /*!
         * \brief Проверяет модель на наличие последних ошибок.
         * Внимание! Если ошибка была инициализирована не в вызываещем методе, то будет все равно возвращена последнаяя ошибка
         * \param query обьект запроса для информативного qDebug
         * \param operation Текст операции для информативного qDebug
         * \return true если ошибки не было, false в противном случае
         */
        static bool isNotValidLastError(const QSqlQuery& query, const QString& operation);
    };
}

#endif // REPORT_H
