#ifndef SETTINGAPP_H
#define SETTINGAPP_H

#include <QSettings>

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс обрабатывающий все настройки приложения */
    class SettingApp : public QSettings
    {
        Q_OBJECT
    public:
        /*!
         * \brief Возвращает обьект настроек, для работы с ним, используя паттерн Singleton.
         * \return Обьект настроек
         */
        static SettingApp &getSettingApp();
        /*!
         * \brief Записывает имя пользователя БД в настройки приложения
         * \param user_name Имя пользователя БД
         */
        void setUserNameForDB(const QString &user_name);
        /*!
         * \brief Возвращает имя пользователя к БД из настроек приложения
         * \return Имя пользователя к БД
         */
        QString getUserNameForDB() const;
        /*!
         * \brief Записывает имя хоста БД в настройки приложения
         * \param host_name Имя хоста БД
         */
        void setHostNameForDB(const QString &host_name);
        /*!
         * \brief Возвращает имя хоста БД из настроек приложения
         * \return Имя хоста к БД
         */
        QString getHostNameForDB() const;
        /*!
         * \brief Записывает пароль к БД в настройки приложения
         * \param password Пароль к БД
         */
        void setPasswordForDB(const QString &password);
        /*!
         * \brief Возвращает пароль к БД из настроек приложения
         * \return Пароль к БД
         */
        QString getPasswordForDB() const;
        /*!
         * \brief Получить данные о предупреждении о окончании договора
         * \return данные о предупреждении о окончании договора
         */
        int getWarningExpirationContract() const;
        /*!
         * \brief Установить данные о предупреждении о окончании договора
         * \param value данные о предупреждении о окончании договора
         */
        void setWarningExpirationContract(const int &value);
        /*!
         * \brief Получить данные о рястягивании таблицы с реестрами
         * \return данные о рястягивании таблицы с реестрами
         */
        bool getStretchTable() const;
        /*!
         * \brief Установить данные о рястягивании таблицы с реестрами
         * \param value данные о рястягивании таблицы с реестрами
         */
        void setStretchTable(const bool &value);

    protected:
        /*! \brief Константа с именем организации */
        static const QString ORGANIZATION;
        /*! \brief Константа с именем приложения */
        static const QString APPLICATION;
        /*! \brief Константа с началом пути к настройкам */
        static const QString SETTING_GROUP;
        /*! \brief Константа с группой базы данных к пути к настройкам */
        static const QString DATABASE_GROUP;
        /*! \brief Константа с группой настроек приложения */
        static const QString APP_GROUP;
        /*! \brief Константа с пользователя БД к пути к настройкам */
        static const QString USER_VALUE;
        /*! \brief Константа с хоста БД  к пути к настройкам */
        static const QString HOST_VALUE;
        /*! \brief Константа с паролем к БД к пути к настройкам */
        static const QString PASSWORD_VALUE;
        /*! \brief Константа с данными о предупреждении о окончании договора */
        static const QString WARNING_EXPIRATION_CONTRACT_VALUE;
        /*! \brief Константа с данными о рястягивании таблицы с реестрами */
        static const QString STRETCH_TABLE_VALUE;

    private:
        SettingApp(const QString &organization, const QString &application = QString(), QObject *parent = 0);
    };
}

#endif // SETTINGAPP_H
