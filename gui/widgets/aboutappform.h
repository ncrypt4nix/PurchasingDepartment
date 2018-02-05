#ifndef ABOUTAPPFORM_H
#define ABOUTAPPFORM_H

#include <QWidget>

namespace Ui
{
    class AboutAppForm;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Форма справочник о программе*/
    class AboutAppForm : public QWidget
    {
        Q_OBJECT

    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit AboutAppForm(QWidget *parent = 0);
        /*! \brief Деструктор */
        ~AboutAppForm();

    private slots:
        void on_closeButton_clicked();

    private:
        Ui::AboutAppForm *ui;
    };
}

#endif // ABOUTAPPFORM_H
