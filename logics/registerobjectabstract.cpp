#include "registerobjectabstract.h"

using namespace logics;

const QString RegisterObjectAbstract::ROW_EXCEL = "<ss:Row>";
const QString RegisterObjectAbstract::ROW_END_EXCEL = "</ss:Row>";
const QString RegisterObjectAbstract::CELL_EXCEL = "<ss:Cell><ss:Data ss:Type=\"String\">";
const QString RegisterObjectAbstract::CELL_END_EXCEL = "</ss:Data></ss:Cell>";
const QString RegisterObjectAbstract::HEADER_EXCEL = "<?xml version=\"1.0\"?><ss:Workbook xmlns:ss=\"urn:schemas-microsoft-com:office:spreadsheet\"><ss:Worksheet ss:Name=\"Sheet1\"><ss:Table>";
const QString RegisterObjectAbstract::END_EXCEL_FILE = "</ss:Table></ss:Worksheet></ss:Workbook>";
const QString RegisterObjectAbstract::DATE_FORMAT = "dd.MM.yyyy";
HandBookManager *RegisterObjectAbstract::handBookManager = NULL;

RegisterObjectAbstract::RegisterObjectAbstract(QObject *parent) :
    QObject(parent)
{
}

uint RegisterObjectAbstract::getId() const
{
    return id;
}

bool RegisterObjectAbstract::changeId(const uint &id)
{
    this->id = id;
    return update();
}

bool RegisterObjectAbstract::isEmpty() const
{
    return id == 0;
}

void RegisterObjectAbstract::copyData(const RegisterObjectAbstract &other)
{
    id = other.id;
    this->setParent(other.parent());
}

QString RegisterObjectAbstract::endExcel() const
{
    return END_EXCEL_FILE;
}

bool RegisterObjectAbstract::saveToExcel(const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream stream(&file);
    stream << headerExcel();
    stream << rowDataExcel();
    stream << endExcel();

    file.close();
    return true;
}

bool RegisterObjectAbstract::saveExtendedToExcel(const QString &filePath) const
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QTextStream stream(&file);
    stream << headerExtendedExcel();
    stream << rowDataExtendedExcel();
    stream << endExcel();

    file.close();
    return true;
}
HandBookManager *RegisterObjectAbstract::getHandBookManager()
{
    return handBookManager;
}

void RegisterObjectAbstract::setHandBookManager(HandBookManager *value)
{
    handBookManager = value;
}

QString RegisterObjectAbstract::headerExcel(const QStringList &list) const
{
    QString headerStr = HEADER_EXCEL + ROW_EXCEL;
    for (auto i : list)
        headerStr += CELL_EXCEL + i + CELL_END_EXCEL;
    headerStr += ROW_END_EXCEL;
    return headerStr;
}

QString RegisterObjectAbstract::rowDataExcel(const QStringList &list) const
{
    QString headerStr = ROW_EXCEL;
    for (auto i : list)
        headerStr += CELL_EXCEL + i + CELL_END_EXCEL;
    headerStr += ROW_END_EXCEL;
    return headerStr;
}

