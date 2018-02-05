#ifndef ALLOWEDEXCEPTION_H
#define ALLOWEDEXCEPTION_H

#include "exceptions/exception.h"

/*!
namespace exceptions
@brief Пространство имен exceptions, содержит в себе все программные исключения
*/
namespace exceptions
{
    /*! \brief Класс Исключений, связанных с ошибками прав и доступа */
    class AllowedException : public Exception
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit AllowedException(QObject *parent = 0);
        /*!
         * \brief Конструктор
         * \param errorMessage Описание ошибки
         * \param parent Родительский обьект
         */
        AllowedException(const QString &errorMessage, QObject *parent = 0);
        /*!
         * \brief Конструктор копирования
         * \param other Другой обьект исключения
         */
        AllowedException(const AllowedException& other);
        /*!
         * \brief Конструктор копирования
         * \param other Другой обьект исключения
         */
        AllowedException(const Exception& other);
        /*! \brief Ошибка создания каталога */
        static const QString ERROR_CREATE_DIRECTORY;
    };
}

#endif // ALLOWEDEXCEPTION_H
