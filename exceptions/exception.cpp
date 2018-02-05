#include "exception.h"

using namespace exceptions;

Exception::Exception(QObject *parent)
    : QObject(parent)
{
    errorMessage = tr("нет информации");
}

Exception::Exception(const QString &errorMessage, QObject *parent)
    : QObject(parent), errorMessage(errorMessage)
{}

Exception::Exception(const Exception &other)
    : QObject(other.parent()), errorMessage(other.errorMessage)
{}

QString Exception::getErrorMessage() const
{
    return errorMessage;
}
