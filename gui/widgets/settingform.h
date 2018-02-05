#ifndef SETTINGFORM_H
#define SETTINGFORM_H

#include <QWidget>
#include "logics/settingapp.h"
#include "logics/database.h"

namespace Ui
{
    class SettingForm;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс формы с настройками приложения */
    class SettingForm : public QWidget
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit SettingForm(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~SettingForm();
        /*! \brief Очистить данные */
        void resetData();

    private slots:
        void on_closeButton_clicked();
        void on_saveButton_clicked();
        void on_pushButton_clicked();

    signals:
        /*! \brief Сигнал о переподключении к БД */
        void reconnect();
        /*! \brief Сигнал о изменении настроек */
        void settingChange();

    private:
        Ui::SettingForm *ui;
    };
}

#endif // SETTINGFORM_H
