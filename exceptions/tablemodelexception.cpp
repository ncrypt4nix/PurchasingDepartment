#include "tablemodelexception.h"

using namespace exceptions;

const QString TableModelException::ERROR_MODEL_INIT = tr("Ошибка инициализации модели");
const QString TableModelException::ERROR_ABSENCE_MODEL = tr("Отсутствует модель");
const QString TableModelException::USING_MODEL_ERROR = tr("Ошика использования модели");

TableModelException::TableModelException(QObject *parent)
    : Exception(parent)
{}

TableModelException::TableModelException(const QString &errorMessage, QObject *parent)
    : Exception(errorMessage, parent)
{}

TableModelException::TableModelException(const TableModelException &other)
    : Exception(other)
{}

TableModelException::TableModelException(const Exception &other)
    : Exception(other)
{}

