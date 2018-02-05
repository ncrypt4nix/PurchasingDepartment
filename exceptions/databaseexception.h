#ifndef DATABASEEXCEPTION_H
#define DATABASEEXCEPTION_H

#include "exceptions/exception.h"

/*!
namespace exceptions
@brief Пространство имен exceptions, содержит в себе все программные исключения
*/
namespace exceptions
{
    /*! \brief Класс исключений связанных с БД */
    class DataBaseException : public Exception
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit DataBaseException(QObject *parent = 0);
        /*!
         * \brief Конструктор
         * \param errorMessage Описание ошибки
         * \param parent Родительский обьект
         */
        DataBaseException(const QString &errorMessage, QObject *parent = 0);
        /*!
         * \brief Конструктор копирования
         * \param other Другой обьект исключения
         */
        DataBaseException(const DataBaseException& other);
        /*!
         * \brief Конструктор копирования
         * \param other Другой обьект исключения
         */
        DataBaseException(const Exception& other);

        /*! \brief Исключение связанное с ошибкой обращения к БД */
        static const QString ERROR_QUERY;

    };
}

#endif // DATABASEEXCEPTION_H
