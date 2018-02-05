#!/usr/bin/python
# -*- coding: UTF-8 -*-
"""Прежде чем использовать данный скрипт создайте БД 'registry'.
Для создания БД используйте команду 'CREATE DATABASE registry;' в клиенте MySQL.
Данный скрипт можно запускать с параметрами или без. При запуске скрипта без параметров, скрипт запросит логин, пароль и хост.
Параметры можно вводить выборочно, но если какой-то параметр не будет введен, скрипт запросит его.
Параметрами являются:
-u --user : Имя пользователя к базе данных
-p --password : Пароль к базе данных
-hn --host : Имя хоста
"""

import sys
import params
import mysql.connector

def createMySQL(user, password, host):
    """Подключается к СУБД MySQL и создает базу данных. БД registry должна быть создана."""
    USER = user
    PASSWORD = password
    HOST = host

    con = mysql.connector.connect(user = USER, password = PASSWORD, host = HOST, database='registry')
    cur = con.cursor()
    cur.execute("SHOW TABLES FROM registry")
    table_list = list(cur.fetchall())
    #Поставщики товаров\услуг
    if ('providers',) not in table_list:
        cur.execute("CREATE TABLE providers("
                        "provider_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "provider VARCHAR(255) NOT NULL,"
                        "PRIMARY KEY (provider_id)"
                        ") CHARACTER SET=UTF8;")
    #Подразделение-заказчик
    if ('subdivisions',) not in table_list:
        cur.execute("CREATE TABLE subdivisions("
                        "subdivision_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "subdivision VARCHAR(255) NOT NULL,"
                        "PRIMARY KEY (subdivision_id)"
                        ") CHARACTER SET=UTF8;")
    #Ответственные лица
    if ('responsibles',) not in table_list:
        cur.execute("CREATE TABLE responsibles("
                        "responsible_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "responsible VARCHAR(255) NOT NULL,"
                        "PRIMARY KEY (responsible_id)"
                        ") CHARACTER SET=UTF8;")
    #Источники финансирования
    if ('sources_financing',) not in table_list:
        cur.execute("CREATE TABLE sources_financing("
                        "source_financing_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "source_financing VARCHAR(255) NOT NULL,"
                        "PRIMARY KEY (source_financing_id)"
                        ") CHARACTER SET=UTF8;")
    #Реестр договоров
    if ('register_contracts',) not in table_list:
        cur.execute("CREATE TABLE register_contracts("
                        "contract_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "contract_number VARCHAR(255) NOT NULL,"
                        "contracts_sum DOUBLE UNSIGNED NOT NULL DEFAULT 0,"
                        "start_date DATE NOT NULL,"
                        "end_date DATE NOT NULL,"
                        "conclusion_date DATE NOT NULL," #дата заключения договора
                        "date_registration DATE NOT NULL," # дата регистрации
                        "provider_id INT UNSIGNED NOT NULL,"
                        "subdivision_id INT UNSIGNED NOT NULL,"
                        "responsible_id INT UNSIGNED NOT NULL,"
                        "source_financing_id INT UNSIGNED NOT NULL,"
                        "completeness  BOOL NOT NULL DEFAULT 0,"    #завершенность
                        "comment TEXT,"
                        "PRIMARY KEY (contract_id),"
                        "FOREIGN KEY (provider_id) REFERENCES providers(provider_id),"
                        "FOREIGN KEY (subdivision_id) REFERENCES subdivisions(subdivision_id),"
                        "FOREIGN KEY (responsible_id) REFERENCES responsibles(responsible_id),"
                        "FOREIGN KEY (source_financing_id) REFERENCES sources_financing(source_financing_id)"
                        ") CHARACTER SET=UTF8;")
    #Счета реестра договоров
    if ('checks_register_contracts',) not in table_list:
        cur.execute("CREATE TABLE checks_register_contracts("
                        "check_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "check_number VARCHAR(255) NOT NULL,"
                        "registration_date DATE NOT NULL,"  #Дата регистрации
                        "check_date DATE NOT NULL,"         #Дата счета
                        "check_sum DOUBLE UNSIGNED NOT NULL DEFAULT 0,"
                        "description TEXT,"
                        "contract_id INT UNSIGNED NOT NULL,"
                        "PRIMARY KEY (check_id),"
                        "FOREIGN KEY (contract_id) REFERENCES register_contracts(contract_id) ON DELETE CASCADE"
                        ") CHARACTER SET=UTF8;")
    #Платежные документы
    if ('payment_documents',) not in table_list:
        cur.execute("CREATE TABLE payment_documents("
                        "payment_document_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "payment_document VARCHAR(255) NOT NULL,"
                        "PRIMARY KEY (payment_document_id)"
                        ") CHARACTER SET=UTF8;")
    #Реестр счетов
    if ('register_checks',) not in table_list:
        cur.execute("CREATE TABLE register_checks("
                        "check_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "check_number VARCHAR(255) NOT NULL,"   #Номер чека
                        "registration_date DATE NOT NULL,"  #Дата регистрации
                        "check_date DATE NOT NULL,"         #Дата счета
                        "check_sum DOUBLE UNSIGNED NOT NULL DEFAULT 0,"
                        "description TEXT,"
                        "number_checks INT UNSIGNED NOT NULL DEFAULT 0,"    #Колличество чеков
                        "provider_id INT UNSIGNED NOT NULL,"
                        "subdivision_id INT UNSIGNED NOT NULL,"
                        "responsible_id INT UNSIGNED NOT NULL,"
                        "source_financing_id INT UNSIGNED NOT NULL,"
                        "payment_document_id INT UNSIGNED NOT NULL,"
                        "completeness  BOOL NOT NULL DEFAULT 0,"    #завершенность
                        "PRIMARY KEY (check_id),"
                        "FOREIGN KEY (provider_id) REFERENCES providers(provider_id),"
                        "FOREIGN KEY (subdivision_id) REFERENCES subdivisions(subdivision_id),"
                        "FOREIGN KEY (responsible_id) REFERENCES responsibles(responsible_id),"
                        "FOREIGN KEY (payment_document_id) REFERENCES payment_documents(payment_document_id),"
                        "FOREIGN KEY (source_financing_id) REFERENCES sources_financing(source_financing_id)"
                        ") CHARACTER SET=UTF8;")
    #Способы закупки
    if ('procurement_methods',) not in table_list:
        cur.execute("CREATE TABLE procurement_methods("
                        "procurement_method_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "procurement_method VARCHAR(255) NOT NULL,"
                        "PRIMARY KEY (procurement_method_id)"
                        ") CHARACTER SET=UTF8;")
    #Реестр конкурентных способов закупки
    if ('register_procurement_methods',) not in table_list:
        cur.execute("CREATE TABLE register_procurement_methods("
                        "register_procurement_method_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "number_notice VARCHAR(255) NOT NULL,"  #номер извещения
                        "notice_date DATE NOT NULL,"    #Дата извещения
                        "procurement_object TEXT,"    #Предмет закупки
                        "date_registration DATE NOT NULL," # дата регистрации
                        "starting_price DOUBLE UNSIGNED NOT NULL DEFAULT 0,"   #Начальная (максимальная) цена договора
                        "start_date_deadline DATE NOT NULL,"    #Дата начала срока подачи заявок
                        "end_date_deadline DATE NOT NULL,"  #Дата окончания срока подачи заявок
                        "opening_envelopes_date DATE NOT NULL," #Дата протокола вскрытия конвертов
                        "summarizing_date DATE NOT NULL,"   #Дата протокола рассмотрения подведения итогов
                        "procedure_complete BOOL NOT NULL DEFAULT 0,"   #Состолась процедура или несостоялась
                        "smp BOOL NOT NULL DEFAULT 0," #СМП
                        "completeness  BOOL NOT NULL DEFAULT 0,"    #завершенность
                        "procurement_method_id INT UNSIGNED NOT NULL,"
                        "PRIMARY KEY (register_procurement_method_id),"
                        "FOREIGN KEY (procurement_method_id) REFERENCES procurement_methods(procurement_method_id)"
                        ") CHARACTER SET=UTF8;")
    #Договора реестра конкурентных способов закупки
    if ('contracts_register_procurement_methods',) not in table_list:
        cur.execute("CREATE TABLE contracts_register_procurement_methods("
                        "contract_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "contract_number VARCHAR(255) NOT NULL,"
                        "contracts_sum DOUBLE UNSIGNED NOT NULL DEFAULT 0,"
                        "start_date DATE NOT NULL,"
                        "end_date DATE NOT NULL,"
                        "conclusion_date DATE NOT NULL," #дата заключения договора
                        "date_registration DATE NOT NULL," # дата регистрации
                        "provider_id INT UNSIGNED NOT NULL,"
                        "completeness  BOOL NOT NULL DEFAULT 0,"    #завершенность
                        "comment TEXT,"
                        "register_procurement_method_id INT UNSIGNED NOT NULL,"
                        "subdivision_id INT UNSIGNED NOT NULL,"
                        "responsible_id INT UNSIGNED NOT NULL,"
                        "source_financing_id INT UNSIGNED NOT NULL,"
                        "PRIMARY KEY (contract_id),"
                        "FOREIGN KEY (provider_id) REFERENCES providers(provider_id),"
                        "FOREIGN KEY (subdivision_id) REFERENCES subdivisions(subdivision_id),"
                        "FOREIGN KEY (responsible_id) REFERENCES responsibles(responsible_id),"
                        "FOREIGN KEY (source_financing_id) REFERENCES sources_financing(source_financing_id),"
                        "FOREIGN KEY (register_procurement_method_id) REFERENCES register_procurement_methods(register_procurement_method_id) ON DELETE CASCADE"
                        ") CHARACTER SET=UTF8;")
    #Счета реестра конкурентных способов закупки
    if ('checks_register_procurement_methods',) not in table_list:
        cur.execute("CREATE TABLE checks_register_procurement_methods("
                        "check_id INT UNSIGNED NOT NULL AUTO_INCREMENT,"
                        "check_number VARCHAR(255) NOT NULL,"
                        "registration_date DATE NOT NULL,"  #Дата регистрации
                        "check_date DATE NOT NULL,"         #Дата счета
                        "check_sum DOUBLE UNSIGNED NOT NULL DEFAULT 0,"
                        "description TEXT,"
                        "contract_id INT UNSIGNED NOT NULL,"
                        "PRIMARY KEY (check_id),"
                        "FOREIGN KEY (contract_id) REFERENCES contracts_register_procurement_methods(contract_id) ON DELETE CASCADE"
                        ") CHARACTER SET=UTF8;")
    con.commit()
    cur.close()
    con.close()

if __name__ == '__main__':
    parse_params = params.createParams()
    parse_params = parse_params.parse_args(sys.argv[1:])
    parse_params = params.parseParams(parse_params)
    createMySQL(user = parse_params.user, password = parse_params.password, host = parse_params.host)
