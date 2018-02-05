#include "allowedexception.h"

using namespace exceptions;

const QString AllowedException::ERROR_CREATE_DIRECTORY = tr("Ошибка создания каталога");

AllowedException::AllowedException(QObject *parent) :
    Exception(parent)
{}

AllowedException::AllowedException(const QString &errorMessage, QObject *parent)
    : Exception(errorMessage, parent)
{}

AllowedException::AllowedException(const AllowedException &other)
    : Exception(other)
{}

AllowedException::AllowedException(const Exception &other)
    : Exception(other)
{}
