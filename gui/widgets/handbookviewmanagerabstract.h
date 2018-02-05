#ifndef HANDBOOKVIEWMANAGERABSTRACT_H
#define HANDBOOKVIEWMANAGERABSTRACT_H

#include <QWidget>
#include <QDebug>
#include <QComboBox>

#include "logics/handbook.h"
#include "gui/widgets/handbookform.h"

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Абстрактный Класс-Менеджер Box элементов отображения справочника */
    class HandBookViewManagerAbstract : public QWidget
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit HandBookViewManagerAbstract(QWidget *parent = 0);
        /*!
         * \brief Устанавливает справочник и налаживает коннекты, для обработки изменения справочников
         * \param value Справочник
         */
        virtual void setHandBookManager(logics::HandBookManager *value);
        /*! \brief Удаляет всю информацию о прошлом посещении виджета */
        virtual void resetOldData() = 0;
        /*!
         * \brief Запоминает форму справочников для быстрого перехода к ним
         * \param value форма справочников
         */
        virtual void setHandBookForm(HandBookForm *value);
        /*!
         * \brief Проверяет целостность данных
         * \return целостность данных
         */
        virtual bool checkData() = 0;

    protected:
        /*!
         * \brief Синхронизирует значения виджета и модели справочника
         * \param box виджет изменения которого неоходимо провести
         * \param index индекс модели
         */
        void changeBox(QComboBox *box, const logics::HandBookManager::ModelIndex &index);
        /*!
         * \brief Открывает виджет нужного справочника
         * \param index индекс справочника
         */
        void showHandBook(const logics::HandBookManager::ModelIndex &index);

    protected:
        /*! \brief менеджер справочников */
        logics::HandBookManager *handBookManager;
        /*! \brief Виджет справочников */
        HandBookForm *handBookForm;
        /*! \brief Значение по умолчанию для виджетов справочника */
        static const int DEFAULT_VALUE;
    };
}

#endif // HANDBOOKVIEWMANAGERABSTRACT_H
