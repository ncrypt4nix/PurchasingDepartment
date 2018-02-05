#include "databaseexception.h"

using namespace exceptions;

const QString DataBaseException::ERROR_QUERY = tr("Ошибка обращения к базе данных");

DataBaseException::DataBaseException(QObject *parent)
      : Exception(parent)
{}

DataBaseException::DataBaseException(const QString &errorMessage, QObject *parent)
    : Exception(errorMessage, parent)
{}

DataBaseException::DataBaseException(const DataBaseException &other)
    : Exception(other)
{}

DataBaseException::DataBaseException(const Exception &other)
    : Exception(other)
{}
