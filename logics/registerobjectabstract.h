#ifndef REGISTEROBJECTABSTRACT_H
#define REGISTEROBJECTABSTRACT_H

#include <QObject>
#include <QFile>
#include <QTextStream>

#include "logics/handbook.h"

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Астрактный класс предоставляющий интерфейс и управление к конкретному обьекту регистра */
    class RegisterObjectAbstract : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit RegisterObjectAbstract(QObject *parent = 0);
        /*!
         * \brief Получить id счета
         * \return id счета
         */
        virtual uint getId() const;
        /*!
         * \brief Изменить id
         * \param id идентификатор
         * \return успешность выполнения операции
         */
        virtual bool changeId(const uint &id);
        /*!
         * \brief Сохраняет все изменения в БД
         * \return успешность выполнения операции
         */
        virtual bool save() const = 0;
        /*!
         * \brief Сохраняет новый счет в БД
         * \return успешность выполнения операции
         */
        virtual bool add() = 0;
        /*!
         * \brief Проверка на пустоту обьекта
         * \return true если пуст, иначе ложь
         */
        virtual bool isEmpty() const;
        /*!
         * \brief Копирование данных из другого обьекта
         * \param other другой обьект
         */
        virtual void copyData(const RegisterObjectAbstract &other);
        /*!
         * \brief Создает и возвращает шапку excel-файла
         * \return шапку excel-файла
         */
        virtual QString headerExcel() const = 0;
        /*!
         * \brief Создает и возвращает расширенную шапку excel-файла
         * \return шапку excel-файла
         */
        virtual QString headerExtendedExcel() const = 0;
        /*!
         * \brief Создает и возвращает конец excel-файла
         * \return конец excel-файла
         */
        virtual QString endExcel() const;
        /*!
         * \brief Создает и возвращает строку с данными excel-файла
         * \return строку с данными excel-файла
         */
        virtual QString rowDataExcel() const = 0;
        /*!
         * \brief Создает и возвращает строку со всеми данными excel-файла
         * \return строку с данными excel-файла
         */
        virtual QString rowDataExtendedExcel() const = 0;
        /*!
         * \brief Сохраняет обьект в excel-файл
         * \param filePath путь к файлу для сохранения
         * \return Успешность операции
         */
        virtual bool saveToExcel(const QString &filePath) const;
        /*!
         * \brief Сохраняет расширенный обьект в excel-файл
         * \param filePath путь к файлу для сохранения
         * \return Успешность операции
         */
        virtual bool saveExtendedToExcel(const QString &filePath) const;
        /*!
         * \brief Получить ссылку на сравочник
         * \return ссылку на сравочник
         */
        static HandBookManager *getHandBookManager();
        /*!
         * \brief Установить ссылку на сравочник
         * \param value ссылку на сравочник
         */
        static void setHandBookManager(HandBookManager *value);

    protected:
        /*!
         * \brief Обновления данных, после смены id
         * \return успешность выполнения операции
         */
        virtual bool update() = 0;
        /*!
         * \brief Создает и возвращает шапку excel-файла
         * \param list список элементов в строке
         * \return шапку excel-файла
         */
        QString headerExcel(const QStringList &list) const;
        /*!
         * \brief Создает и возвращает строку с данными excel-файла
         * \param list список элементов в строке
         * \return строку с данными excel-файла
         */
        QString rowDataExcel(const QStringList &list) const;

    protected:
        /*! \brief id обьекта */
        uint id = 0;
        /*! \brief Обьявление колонки excel-файла */
        static const QString ROW_EXCEL,
            /*! \brief Обьявление конца колонки excel-файла */
            ROW_END_EXCEL,
            /*! \brief Обьявление ячейки excel-файла */
            CELL_EXCEL,
            /*! \brief Обьявление конца ячейки excel-файла */
            CELL_END_EXCEL,
            /*! \brief Обьявление шапки excel-файла */
            HEADER_EXCEL,
            /*! \brief Обьявление конца excel-файла */
            END_EXCEL_FILE;
        /*! \brief Формат даты для печати в excel-файл */
        static const QString DATE_FORMAT;
        /*! \brief ссылка на справочник */
        static HandBookManager *handBookManager;
    };
}

#endif // REGISTEROBJECTABSTRACT_H
