#ifndef DATABASECONNECTIONDIALOG_H
#define DATABASECONNECTIONDIALOG_H

#include <QDialog>

namespace Ui
{
    class DatabaseConnectionDialog;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс диалогового окна подключения к базе данных */
    class DatabaseConnectionDialog : public QDialog
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский виджет окна
         */
        explicit DatabaseConnectionDialog(QWidget *parent = 0);
        /*! \brief Деструктор окна */
        ~DatabaseConnectionDialog();
        /*!
         * \brief Возвращает имя пользователя к БД, которое ввел пользователь в форме ввода
         * \return Введенное пользователем имя пользователя БД
         */
        QString getUserName() const;
        /*!
         * \brief Возвращает имя хоста БД, которое ввел пользователь в форме ввода
         * \return Введенное пользователем имя хоста БД
         */
        QString getHostName() const;
        /*!
         * \brief Возвращает пароль к БД, которое ввел пользователь в форме ввода
         * \return Введенной пользователем пароль к БД
         */
        QString getPassword() const;

    private:
        Ui::DatabaseConnectionDialog *ui;
    };
}

#endif // DATABASECONNECTIONDIALOG_H
