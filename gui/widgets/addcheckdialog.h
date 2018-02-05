#ifndef ADDCHECKDIALOG_H
#define ADDCHECKDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui
{
    class AddCheckDialog;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*!
     * \brief Класс диалогового окна добавления нового счета
     */
    class AddCheckDialog : public QDialog
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit AddCheckDialog(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~AddCheckDialog();
        /*!
         * \brief Возвращает номер счета, введенный пользователем
         * \return номер счета
         */
        QString getNumber() const;
        /*!
         * \brief Возвращает дату регистрации счета, введенный пользователем
         * \return дата регистрации счета
         */
        QDate getRegistrationDate() const;
        /*!
         * \brief Возвращает дату счета, введенный пользователем
         * \return дата счета
         */
        QDate getCheckDate() const;
        /*!
         * \brief Возвращает сумму счета, введенный пользователем
         * \return сумма счета
         */
        double getSum() const;
        /*!
         * \brief Возвращает описание, введенный пользователем
         * \return описание
         */
        QString getDescription() const;

    private:
        Ui::AddCheckDialog *ui;
    };
}

#endif // ADDCHECKDIALOG_H
