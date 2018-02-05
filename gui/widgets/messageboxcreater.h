#ifndef MESSAGEBOXCREATER_H
#define MESSAGEBOXCREATER_H

#include <QMessageBox>
#include <QFileDialog>

#include "exceptions/exception.h"

/*!
namespace gui
@brief Хранит в себе все элементы интерфейса приложения
*/
namespace gui
{
    /*! \brief Класс-Интерфейс для создания диалоговых окон */
    class MessageBoxCreater
    {
    protected:
        /*!
         * \brief Создает предупреждающее диалоговое окно выбора, обрабатывает и возвращает ответ пользователя
         * \param message Сообщение пользователю
         * \return Положительный или отрицательный ответ пользователя
         */
        bool createMessageBox(const QString& message) const;
        /*!
         * \brief Создает и показывает информативное сообщение о ошибке
         * \param message Сообщение пользователю
         */
        void createErrorMessageBox(const QString &message) const;
        /*!
         * \brief Выводит сообщение о ошибке, возникшее во время исключения
         * \param exception Возникшее исключение
         */
        void createExceptionMessageBox(const exceptions::Exception exception) const;
        /*!
         * \brief Создает диалоговое окно выбора файла для сохранения
         * \return путь к выранному файлу
         */
        QString createSaveFileNameExcelMessageBox() const;
    };
}

#endif // MESSAGEBOXCREATER_H
