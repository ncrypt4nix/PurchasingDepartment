#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Управляет подключением и управлением базой данных */
    class DataBase : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         */
        DataBase(QObject *parent = 0);
        /*!
         * \brief Создает подключение к базе данных.
         * Перед использованием данной функции необходимо задать имя хоста, пользователя и пароль
         * \return Успешность подключение к БД
         */
        bool createConnection();
        /*!
         * \brief Устанавливает пользователя базы данных, необходимое для подключения к серверу БД
         * \param value Имя пользователя БД
         */
        static void setUserName(const QString &value);
        /*!
         * \brief Возвращает имя пользователя базы данных
         * \return Имя БД
         */
        static QString getUserName();
        /*!
         * \brief Устанавливает пароль базы данных, необходимое для подключения к серверу БД
         * \param value Пароль к БД
         */
        static void setPassword(const QString &value);
        /*!
         * \brief Возвращает пароль базы данных
         * \return Пароль к БД
         */
        static QString getPassword();
        /*!
         * \brief Устанавливает хост базы данных, необходимое для подключения к серверу БД
         * \param value Хост БД
         */
        static void setHostName(const QString &value);
        /*!
         * \brief Возвращает хост базы данных
         * \return Хост БД
         */
        static QString getHostName();

    protected:
        /*! \brief Драйвер базы данных */
        static const QString DATABASE_DRV;
        /*! \brief Имя базы данных */
        static const QString DATABASE_NAME;
        /*! \brief Имя пользователя БД */
        static QString userName;
        /*! \brief Имя хоста */
        static QString hostName;
        /*! \brief Пароль БД */
        static QString password;

    private:
        QSqlDatabase* db;
    };
}

#endif // DATABASE_H
