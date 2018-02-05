#include "gui/mainwindow.h"
#include "tests/globaltest.h"
#include "tests/logics_tests/test_database.h"
#include "tests/logics_tests/test_tablecontractsmodel.h"

#include <QApplication>
#include <QDebug>
#include <QObject>

/* Директива модульному тестированию */
//#define TEST_PURCHASING_DEPARTMENT_APP
/* Директива глобальному тестингу (Директива модульному тестированию должна быть расскоментирована) */
//#define GLOBAL_TEST_PURCHASING_DEPARTMENT_APP

#ifndef TEST_PURCHASING_DEPARTMENT_APP
/* Основная программа */
int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);

        gui::MainWindow w;
        w.show();

        return a.exec();
    }
    catch (std::exception& e)
    {
        QString errorMessage = QObject::tr("Стандартное исключение: ") + e.what();
        qDebug() << errorMessage << '\n';
        QMessageBox* exceptionBox =
                new QMessageBox(QMessageBox::Critical,
                QObject::tr("Ошибка"),
                QObject::tr("Программа выловила необработанное стандартное исключение\n") + errorMessage,
                QMessageBox::Ok);
        exceptionBox->exec();
        delete exceptionBox;
        QCoreApplication::exit(0);
    }
}
#else
#ifdef GLOBAL_TEST_PURCHASING_DEPARTMENT_APP
/* Глобальное тестирование */
QTEST_MAIN(tests::GlobalTest)
#else
/* Модульное тестирование (Расскоментировать нужный модуль) */
//QTEST_MAIN(tests::Test_Database)
//QTEST_MAIN(tests::Test_TableContractsModel)
#endif  //GLOBAL_TEST_PURCHASING_DEPARTMENT_APP
#endif  //TEST_PURCHASING_DEPARTMENT_APP
