#ifndef DATEINFORMATIONCONTACTTABLE_H
#define DATEINFORMATIONCONTACTTABLE_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QDir>
#include <QtAlgorithms>
#include <QDebug>

/*!
namespace logics
@brief Пространство имен logics, содержит в себе всю логику приложения.
*/
namespace logics
{
    /*! \brief Класс следящий за окончанием договоров */
    class InformationEndContracts : public QObject
    {
        Q_OBJECT
    public:
        /*!
         * \brief Конструктор
         * \param parent родительский обьект
         */
        explicit InformationEndContracts(QObject *parent = 0);
        /*!
         * \brief Проверить id договора на приближение окончания
         * \param id id договора
         * \return true если приближается окончания договора
         */
        static bool checkId(const uint &id);
        /*!
         * \brief Проверяет удалялся ли уже данный id
         * \param id id договора
         * \return удаление id
         */
        static bool deletedId(const uint &id);
        /*!
         * \brief добавить id договора окончание которого приближается
         * \param id id договора
         */
        static void addId(const uint &id);
        /*!
         * \brief удалить id договора окончание которого приближается
         * \param id id договора
         */
        static void deleteId(const uint &id);
        /*!
         * \brief Сохраняет все данные в файл
         * \return успешность операции
         */
        static bool save();
        /*!
         * \brief Читает все данные с файла
         * \return успешность операции
         */
        static bool read();

    protected:
        /*!
         * \brief Получить путь к файлу
         * \return путь к файлу
         */
        static QString getFilePathInfo();
        /*!
         * \brief Получить путь к файлу с удаленными id
         * \return путь к файлу
         */
        static QString getFilePathDeleted();

    private:
        static QVector<uint> idVector;
        static QVector<uint> idDeleted;
    };
}

#endif // DATEINFORMATIONCONTACTTABLE_H
