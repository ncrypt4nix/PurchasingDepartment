#ifndef HANDBOOK_H
#define HANDBOOK_H

#include "logics/providershandbook.h"
#include "logics/subdivisionshandbook.h"
#include "logics/responsibleshandbook.h"
#include "logics/sourcesfinancinghandbook.h"
#include "logics/paymentdocumentshandbook.h"
#include "logics/procurementmethodshandbook.h"
#include "exceptions/tablemodelexception.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*!
     * \brief Класс-Обертка для справочников.
     * Содержит в себе справочники и управляет их поведением
     */
    class HandBookManager : public QObject
    {
        Q_OBJECT       
    public:
        /*! \brief Константы определяющие модели справочника */
        enum class ModelIndex
        {
            /*! \brief Константа определяющая модель справочника поставщиков товаров\услуг */
            PROVIDERS_INDEX,
            /*! \brief Константа определяющая модель справочника подразделение-заказчик */
            SUBDIVISIONS_INDEX,
            /*! \brief Константа определяющая модель справочника ответственных лиц */
            RESPONSIBLES_INDEX,
            /*! \brief Константа определяющая модель справочника источников финансирования */
            SOURCES_FINANCING_INDEX,
            /*! \brief Константа определяющая модель справочника платежных документов */
            PAYMENT_DOCUMENTS_INDEX,
            /*! \brief Константа определяющая модель справочника способов закупки */
            PROCUREMENT_METHODS_INDEX
        };

    public:
        /*!
         * \brief Конструктор
         * \param parent Родительский обьект
         * \throw TableModelException при ошибке инициализации модели
         */
        explicit HandBookManager(QObject *parent = 0);
        /*!
         * \brief Возвращает текущую установленную в менеджере модель
         * \return Модель БД
         */
        QSqlTableModel *getCurrentModel() const;
        /*!
         * \brief Возвращает модель по индексу и делает ее текущей моделью
         * \param modelIndex Константа с индексом модели
         * \return Модель БД
         * \throw TableModelException при ошибке отсутствии модели
         */
        QSqlTableModel *getModelIndex(const ModelIndex &modelIndex);
        /*!
         * \brief Возвращает индекс колонки текущей модели для скрытия
         * \return Индекс колонки для скрытия
         */
        int getColumnIdIndex() const;
        /*!
         * \brief Устанавливает текущую модель по индексу
         * \param modelIndex Константа с индексом модели
         * \return Успешность установки модели
         */
        bool setCurrentModel(const ModelIndex &modelIndex);
        /*!
         * \brief Удаляет указанную строку из модели
         * \param row Удаляемая строка
         * \return Успешность операции
         */
        bool removeRow(const uint& row) const;
        /*!
         * \brief Добавляет новую запись в модель таблицы БД
         * \param value Значение для добавления
         * \return  Успешность операции
         */
        bool addRow(const QString &value) const;
        /*!
         * \brief Установить фильтр на справочник
         * \param value значение
         */
        void setFilter(const QString value);
        /*! \brief Отменить фильтр */
        void cancelFilter();
        /*!
         * \brief Предоставляет словарь справочника для извлечения данных из него
         * \param modelIndex Константа с индексом модели
         * \return Словарь справочника
         */
        QMap<QString, uint> getMapHandBook(const ModelIndex &modelIndex) const;

    protected:
        /*!
         * \brief Определяет нужную модель по ее индексу и возвращает ее или генерирует исключение
         * \param modelIndex Индекс модели
         * \return Модель
         * \throw TableModelException при ошибке отсутствии модели
         */
        HandBookAbstract *getModelInIndex(const ModelIndex &modelIndex) const;

    signals:
        /*! \brief Сигнал о изменении модели поставщиков товаров\услуг */
        void providersChanged();
        /*! \brief Сигнал о изменении модели подразделение-заказчик */
        void subdivisionsChanged();
        /*! \brief Сигнал о изменении модели ответственных лиц */
        void responsiblesChanged();
        /*! \brief Сигнал о изменении модели источников финансирования */
        void sourcesFinancingChanged();
        /*! \brief Сигнал о изменении модели платежных документов */
        void paymentDocumentsChanged();
        /*! \brief Сигнал о изменении модели способов закупки */
        void procurementMethodsChanged();

    public slots:
        /*!
         * \brief Обновляет текущую установленную модель
         * \return Успешность операции
         */
        bool updateModel() const;

    protected slots:
        /*!
         * \brief Слот принимающий сигнал модели о изменении,
         * определяющий модель и посылающий специфичный для модели сигнал всем слушателям
         */
        void modelChanged();

    protected:
        /*! \brief Константа определяющая имя обьекта модели справочника поставщиков товаров\услуг */
        static const QString PROVIDERS_OBJECT_NAME;
        /*! \brief Константа определяющая имя обьекта модели справочника подразделение-заказчик */
        static const QString SUBDIVISIONS_OBJECT_NAME;
        /*! \brief Константа определяющая имя обьекта модели справочника ответственных лиц */
        static const QString RESPONSIBLES_OBJECT_NAME;
        /*! \brief Константа определяющая имя обьекта модели справочника источников финансирования */
        static const QString SOURCES_FINANCING_OBJECT_NAME;
        /*! \brief Константа определяющая имя обьекта модели справочника платежных документов */
        static const QString PAYMENT_DOCUMENTS_OBJECT_NAME;
        /*! \brief Константа определяющая имя обьекта модели справочника способов закупки */
        static const QString PROCUREMENT_METHODS_OBJECT_NAME;

    private:
        ProvidersHandBook *providers;
        SubdivisionsHandBook *subdivisions;
        ResponsiblesHandBook *responsibles;
        SourcesFinancingHandBook *sourcesFinancing;
        PaymentDocumentsHandBook *paymentDocuments;
        ProcurementMethodsHandBook *procurementMethods;
        HandBookAbstract *currentModel;
    };
}

#endif // HANDBOOK_H
