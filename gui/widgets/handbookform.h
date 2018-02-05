#ifndef HANDBOOKFORM_H
#define HANDBOOKFORM_H

#include <QWidget>
#include <QSqlTableModel>
#include <QKeyEvent>

#include "logics/handbook.h"
#include "gui/widgets/messageboxcreater.h"

namespace Ui
{
    class HandBookForm;
}
/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс-Форма для отображения и редактирования справочников */
    class HandBookForm : public QWidget, MessageBoxCreater
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param handBookManager Менеджер справочников
         * \param parent Родительский обьект
         */
        explicit HandBookForm(logics::HandBookManager* handBookManager, QWidget *parent = 0);
        /*!
         * \brief Устанавливает модель на табличный вид
         * \param modelIndex Индекс модели
         * \throw TableModelException при ошибке отсутствии модели
         */
        void setModel(const logics::HandBookManager::ModelIndex &modelIndex);
        /*! \brief Деструктор */
        ~HandBookForm();

    protected:
        /*!
         * \brief Событие нажатия на клавишу
         * \param keyEvent Нажатая клавиша
         */
        virtual void keyPressEvent(QKeyEvent *keyEvent);
        /*! \brief Удаляет выделенные записи из таблицы */
        void deleteRows();
        /*! \brief Добавляет новую запись в таблицу */
        void addRow();

    private slots:
        void on_closeButton_clicked();
        void on_deleteButton_clicked();
        void on_addButton_clicked();
        void on_addLineEdit_returnPressed();
        void on_findButton_clicked();
        void on_findCancelButton_clicked();

    private:
        Ui::HandBookForm *ui;
        logics::HandBookManager* handBookManager;
    };
}

#endif // HANDBOOKFORM_H
