#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QObject>
#include <QDebug>

/*!
namespace exceptions
@brief Пространство имен exceptions, содержит в себе все программные исключения
*/
namespace exceptions
{
    /*! \brief Базовый класс для всех исключений */
    class Exception : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        explicit Exception(QObject *parent = 0);
        /*!
         * \brief Конструктор
         * \param errorMessage Описание ошибки
         * \param parent Родительский обьект
         */
        Exception(const QString &errorMessage, QObject *parent = 0);
        /*!
         * \brief Конструктор копирования
         * \param other Другой обьект исключения
         */
        Exception(const Exception &other);
        /*!
         * \brief Возвращает описание возникшей ошибки
         * \return Описание ошибки
         */
        QString getErrorMessage() const;

    private:
        QString errorMessage;
    };
}

#endif // EXCEPTION_H
