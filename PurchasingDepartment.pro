#-------------------------------------------------
#
# Project created by QtCreator 2015-11-01T18:12:30
#
#-------------------------------------------------

QT       += core gui sql testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PurchasingDepartment
TEMPLATE = app


SOURCES += main.cpp\
        gui/mainwindow.cpp \
    logics/database.cpp \
    tests/logics_tests/test_database.cpp \
    tests/globaltest.cpp \
    tests/globaltestmodule.cpp \
    tests/logics_tests/test_tablecontractsmodel.cpp \
    gui/widgets/contacttablestyleditemdelegate.cpp \
    logics/tablemodelabstract.cpp \
    logics/tablemodelmanager.cpp \
    exceptions/exception.cpp \
    exceptions/tablemodelexception.cpp \
    gui/widgets/databaseconnectiondialog.cpp \
    logics/settingapp.cpp \
    logics/tableregistercontractsmodel.cpp \
    logics/tableregisterchecksmodel.cpp \
    logics/tableregisterprocurementmethodsmodel.cpp \
    gui/widgets/procurementmethodstablestyleditemdelegate.cpp \
    logics/handbook.cpp \
    logics/providershandbook.cpp \
    logics/handbookabstract.cpp \
    gui/widgets/handbookform.cpp \
    gui/widgets/messageboxcreater.cpp \
    logics/subdivisionshandbook.cpp \
    logics/responsibleshandbook.cpp \
    logics/sourcesfinancinghandbook.cpp \
    logics/paymentdocumentshandbook.cpp \
    logics/procurementmethodshandbook.cpp \
    gui/widgets/contractinformationwidget.cpp \
    gui/widgets/registercontractsform.cpp \
    logics/contractobject.cpp \
    gui/widgets/addcheckdialog.cpp \
    gui/widgets/registercheckform.cpp \
    gui/widgets/handbookviewmanager.cpp \
    logics/checkobject.cpp \
    gui/widgets/registerprocurementmethodsform.cpp \
    logics/procurementmethodobject.cpp \
    gui/widgets/handbookviewmanagerabstract.cpp \
    gui/widgets/paymentdocumenthandbookviewmanager.cpp \
    logics/registerobjectabstract.cpp \
    gui/widgets/procurementmethodshandbookviewmanager.cpp \
    logics/contractprocurementmethodobject.cpp \
    logics/findobjectabstract.cpp \
    logics/findobjectcontract.cpp \
    logics/findobjectcheck.cpp \
    logics/findobjectprocurementmethod.cpp \
    gui/widgets/findformcheck.cpp \
    gui/widgets/findformprocurementmethod.cpp \
    logics/informationendcontracts.cpp \
    exceptions/allowedexception.cpp \
    gui/widgets/findformcontractwidget.cpp \
    gui/widgets/findformcontract.cpp \
    gui/widgets/aboutappform.cpp \
    gui/widgets/settingform.cpp \
    gui/widgets/reportform.cpp \
    logics/report.cpp \
    gui/widgets/expectationform.cpp \
    exceptions/databaseexception.cpp \
    gui/widgets/tablestyleditemdelegate.cpp \
    gui/widgets/completenessstyleditemdelegate.cpp

HEADERS  += gui/mainwindow.h \
    logics/database.h \
    tests/logics_tests/test_database.h \
    tests/globaltest.h \
    tests/globaltestmodule.h \
    tests/logics_tests/test_tablecontractsmodel.h \
    gui/widgets/contacttablestyleditemdelegate.h \
    logics/tablemodelabstract.h \
    logics/tablemodelmanager.h \
    exceptions/exception.h \
    exceptions/tablemodelexception.h \
    gui/widgets/databaseconnectiondialog.h \
    logics/settingapp.h \
    logics/tableregistercontractsmodel.h \
    logics/tableregisterchecksmodel.h \
    logics/tableregisterprocurementmethodsmodel.h \
    gui/widgets/procurementmethodstablestyleditemdelegate.h \
    logics/handbook.h \
    logics/providershandbook.h \
    logics/handbookabstract.h \
    gui/widgets/handbookform.h \
    gui/widgets/messageboxcreater.h \
    logics/subdivisionshandbook.h \
    logics/responsibleshandbook.h \
    logics/sourcesfinancinghandbook.h \
    logics/paymentdocumentshandbook.h \
    logics/procurementmethodshandbook.h \
    gui/widgets/contractinformationwidget.h \
    gui/widgets/registercontractsform.h \
    logics/contractobject.h \
    gui/widgets/addcheckdialog.h \
    gui/widgets/registercheckform.h \
    gui/widgets/handbookviewmanager.h \
    logics/checkobject.h \
    gui/widgets/registerprocurementmethodsform.h \
    logics/procurementmethodobject.h \
    gui/widgets/handbookviewmanagerabstract.h \
    gui/widgets/paymentdocumenthandbookviewmanager.h \
    logics/registerobjectabstract.h \
    gui/widgets/procurementmethodshandbookviewmanager.h \
    logics/contractprocurementmethodobject.h \
    logics/findobjectabstract.h \
    logics/findobjectcontract.h \
    logics/findobjectcheck.h \
    logics/findobjectprocurementmethod.h \
    gui/widgets/findformcheck.h \
    gui/widgets/findformprocurementmethod.h \
    logics/informationendcontracts.h \
    exceptions/allowedexception.h \
    gui/widgets/findformcontractwidget.h \
    gui/widgets/findformcontract.h \
    gui/widgets/aboutappform.h \
    gui/widgets/settingform.h \
    gui/widgets/reportform.h \
    logics/report.h \
    gui/widgets/expectationform.h \
    exceptions/databaseexception.h \
    gui/widgets/tablestyleditemdelegate.h \
    gui/widgets/completenessstyleditemdelegate.h

FORMS    += gui/ui/mainwindow.ui \
    gui/ui/databaseconnectiondialog.ui \
    gui/ui/handbookform.ui \
    gui/ui/contractinformationwidget.ui \
    gui/ui/registercontractsform.ui \
    gui/ui/addcheckdialog.ui \
    gui/ui/registercheckform.ui \
    gui/ui/registerprocurementmethodsform.ui \
    gui/ui/findformcheck.ui \
    gui/ui/findformprocurementmethod.ui \
    gui/ui/findformcontractwidget.ui \
    gui/ui/findformcontract.ui \
    gui/ui/aboutappform.ui \
    gui/ui/settingform.ui \
    gui/ui/reportform.ui \
    gui/ui/expectationform.ui

CONFIG += c++11

RESOURCES += \
    resources/main.qrc
