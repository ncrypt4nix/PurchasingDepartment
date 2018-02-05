#ifndef EXPECTATIONFORM_H
#define EXPECTATIONFORM_H

#include <QWidget>
#include <QList>
#include <QTime>

namespace Ui
{
    class ExpectationForm;
}

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Окно ожидания */
    class ExpectationForm : public QWidget
    {
        Q_OBJECT

        /*!
         * \brief Конструктор
         * \param parent Родительский виджет окна
         */
    public:
        explicit ExpectationForm(QWidget *parent = 0);
        /*! \brief Деструктор окна */
        ~ExpectationForm();
        /*!
         * \brief  Прорисовывает окно до выполнения длительных операций,
         * Блокирует псевдо-родительски-виджет
         * Внимание, под капотом лайфхак!
        */
        void expectation();
        /*! \brief скрывает окно и разблокирует псевдо-родительский-виджет */
        void end();
        /*!
         * \brief Устанавливает список виджетов приложения для их блокировки
         * \return список виджетов
         */
        QList<QWidget *> getWidgets() const;
        /*!
         * \brief Получить список заблокированных виджетов
         * \param value список виджетов
         */
        void setWidgets(const QList<QWidget *> &value);

    private:
        Ui::ExpectationForm *ui;
        QList<QWidget *> widgets;
        static const int TIME_EXPECTATION;
    };
}

#endif // EXPECTATIONFORM_H
