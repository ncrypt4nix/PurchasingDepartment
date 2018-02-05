#ifndef TABLEMODELEXCEPTION_H
#define TABLEMODELEXCEPTION_H

#include "exceptions/exception.h"

/*!
namespace exceptions
@brief Пространство имен exceptions, содержит в себе все программные исключения
*/
namespace exceptions
{
    /*! \brief Класс исключений связанных с таблицами моделей и видов */
    class TableModelException : public Exception
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit TableModelException(QObject *parent = 0);
        /*!
         * \brief Конструктор
         * \param errorMessage Описание ошибки
         * \param parent Родительский обьект
         */
        TableModelException(const QString &errorMessage, QObject *parent = 0);
        /*!
         * \brief Конструктор копирования
         * \param other Другой обьект исключения
         */
        TableModelException(const TableModelException& other);
        /*!
         * \brief Конструктор копирования
         * \param other Другой обьект исключения
         */
        TableModelException(const Exception& other);

        /*! \brief Исключение инициализации модели */
        static const QString ERROR_MODEL_INIT;
        /*!  \brief Исключение отсутствия модели */
        static const QString ERROR_ABSENCE_MODEL;
        /*!
         * \brief Исключение ошибки использования модели.
         * Как правило возникает при попытке вызвать метод существующий у одной модели, но не существующий у другой
         */
        static const QString USING_MODEL_ERROR;
    };
}

#endif // TABLEMODELEXCEPTION_H
