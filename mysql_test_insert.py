#!/usr/bin/python
# -*- coding: UTF-8 -*-
"""Python-скрипт для создания тестовой БД.
Внимание: используйте этот скрипт только для целей разработки и тестирования данного проекта, но никогда не при боевом развертывании БД.
Зависимости и условия полностью идентичны скрипту 'mysql_create.py'.
Также скрипт 'mysql_create.py' должен быть запущен до запуска данного скрипта
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
import random
import datetime

def testInsertMySQL(user, password, host):
    """Подключается к СУБД и создает тестовые записи. БД registry и тыблицы в ней должны быть созданы."""
    USER = user
    PASSWORD = password
    HOST = host

    def inputData(data_name, default_val, max_val = 0):
        """Фильтрованный ввод данных. Принимает имя данных, значение по умолчанию и максимально допустимое значение,
        и возвращает введеное пользователем и фильтрованное значение."""
        temp = input("Введите {name} (по умолчанию {default}): ".format(name = data_name, default = default_val))
        if len(temp) == 0:
            return default_val
        temp = int(temp)
        if 0 < max_val < temp:
            return max_val
        return temp

    MIN_NUM = 1
    MAX_NUM = inputData("количество данных в справочниках", 10)
    MAX_CONTRACTS = inputData("количество договоров", 100)
    FACTOR_CHECKS = inputData("количество счетов на договор", 5)
    MAX_CHECKS = MAX_CONTRACTS * FACTOR_CHECKS
    MAX_SUM = inputData("максимальную сумму договоров", 10000)
    TIME_DIFFERENCE_YEAR = inputData("разницу в годах, там, где она нужна", 10)
    TIME_DIFFERENCE_DAY = inputData("разницу в днях, там, где она нужна", 5, 28)

    def randomStartEndDate(time_difference = TIME_DIFFERENCE_YEAR):
        """Генерация двух дат в виде строк, первая меньше второй и может отличаться на time_difference лет"""
        date_start = datetime.date(random.randint(datetime.datetime.now().year - time_difference, datetime.datetime.now().year),
                            random.randint(1, 12),
                            random.randint(1, 28))
        date_end = datetime.date(random.randint(date_start.year + 1, date_start.year + time_difference + 1),
                            random.randint(1, 12),
                            random.randint(1, 28))
        return date_start.strftime("%y%m%d"), date_end.strftime("%y%m%d")

    def randomCheckAndRegistrationDate(date_start_now, date_end_now, time_difference = TIME_DIFFERENCE_DAY):
        """Генерация двух дат в виде строк, с наименьшим отличием в time_difference дней и находящимся в промешутке между двумя датами"""
        date_start = datetime.datetime.strptime(date_start_now, "%y%m%d")
        date_end = datetime.datetime.strptime(date_end_now, "%y%m%d")
        date_check = datetime.date
        if date_start.year != date_end.year:
            date_check = datetime.date(random.randint(date_start.year, date_end.year),
                                        random.randint(1, 12),
                                        random.randint(1, 28))
        elif date_start.month != date_end.month:
            date_check = datetime.date(date_start.year,
                                        random.randint(date_start.month, date_end.month) if date_start.month < date_end.month
                                        else random.randint(date_end.month, date_start.month),
                                        random.randint(1, 28))
        else:
            date_check = datetime.date(date_start.year,
                                        date_start.month,
                                        random.randint(date_start.day, date_end.day) if date_start.day < date_end.day
                                        else random.randint(date_end.day, date_start.day))
        date_registration = date_check + datetime.timedelta(days=random.randint(1, time_difference))
        return date_check.strftime("%y%m%d"), date_registration.strftime("%y%m%d")

    def randomDeltaDayDates(start_date, start_day, delta_day, direction):
        """Генерация даты в строковом формате от даты date с разницей в delta_day дней, начиная от start_day дней и в направлении direction(true=+, false=-)"""
        date = datetime.datetime.strptime(start_date, "%y%m%d")
        delta = datetime.timedelta(days=random.randint(0, delta_day))
        date_now = date + delta if direction else date - delta
        return date_now.strftime("%y%m%d")

    con = mysql.connector.connect(user = USER, password = PASSWORD, host = HOST, database='registry')
    cur = con.cursor()
    cur.execute("SHOW TABLES FROM registry")
    table_list = list(cur.fetchall())
    #Поставщики товаров\услуг
    if ('providers',) in table_list:
        for num in range(MIN_NUM, MAX_NUM + 1):
            cur.execute("INSERT INTO providers(provider) VALUES('Поставщик №_" + str(num) + "');")
    start_end_date = []
    contracts_sum = []
    #Подразделение-заказчик
    if ('subdivisions',) in table_list:
        for num in range(MIN_NUM, MAX_NUM + 1):
            cur.execute("INSERT INTO subdivisions(subdivision) VALUES('Подразделение №_" + str(num) + "');")
    #Ответственные лица
    if ('responsibles',) in table_list:
        for num in range(MIN_NUM, MAX_NUM + 1):
            cur.execute("INSERT INTO responsibles(responsible) VALUES('Ответственный №_" + str(num) + "');")
    #Источники финансирования
    if ('sources_financing',) in table_list:
        for num in range(MIN_NUM, MAX_NUM + 1):
            cur.execute("INSERT INTO sources_financing(source_financing) VALUES('Источник финансирования №_" + str(num) + "');")
    #Реестр договоров
    if ('register_contracts',) in table_list:
        for i in range(MIN_NUM, MAX_CONTRACTS + 1):
            start_end_date.append(randomStartEndDate())
            contracts_sum.append(random.randint(0, MAX_SUM))
            cur.execute("INSERT INTO register_contracts(contract_number, contracts_sum, start_date, end_date,"
                            "conclusion_date, date_registration, completeness,"
                            "provider_id, subdivision_id, responsible_id, source_financing_id, comment) "
                            "VALUES('№_{num}', {contracts_sum}, {start_date}, {end_date},"
                            "{conclusion_date}, {date_registration}, {completeness},"
                            "{provider_id}, {subdivision_id}, {responsible_id}, {source_financing_id}, 'Комментарий №_{num}')".format(
                                num = i,
                                contracts_sum = contracts_sum[i - MIN_NUM],
                                start_date = start_end_date[i - MIN_NUM][0],
                                end_date = start_end_date[i - MIN_NUM][1],
                                conclusion_date = start_end_date[i - MIN_NUM][0],
                                date_registration = start_end_date[i - MIN_NUM][1],
                                completeness = random.randint(0, 1),
                                provider_id = random.randint(MIN_NUM, MAX_NUM),
                                subdivision_id = random.randint(MIN_NUM, MAX_NUM),
                                responsible_id = random.randint(MIN_NUM, MAX_NUM),
                                source_financing_id = random.randint(MIN_NUM, MAX_NUM)
                                ))
    #Счета реестра договоров
    if ('checks_register_contracts',) in table_list:
        for i in range(MIN_NUM, MAX_CHECKS + 1):
            contract_id = random.randint(MIN_NUM, MAX_CONTRACTS)
            dates_check_registration = randomCheckAndRegistrationDate(start_end_date[contract_id - MIN_NUM][0], start_end_date[contract_id - MIN_NUM][1])
            check_sum = random.randint(1, contracts_sum[contract_id - MIN_NUM]) if contracts_sum[contract_id - MIN_NUM] > 0 else 0
            contracts_sum[contract_id - MIN_NUM] -= check_sum
            cur.execute("INSERT INTO checks_register_contracts("
                            "check_number, registration_date, check_date, check_sum, description, contract_id) "
                            "VALUES('№_{num}', {registration_date}, {check_date}, {check_sum}, 'Описание №_{num}',"
                            "{contract_id})".format(
                                num = i,
                                registration_date = dates_check_registration[1],
                                check_date = dates_check_registration[0],
                                check_sum = check_sum,
                                contract_id = contract_id,
                                ))
    #Платежные документы
    if ('payment_documents',) in table_list:
        for num in range(MIN_NUM, MAX_NUM + 1):
            cur.execute("INSERT INTO payment_documents(payment_document) VALUES('Платежный документ №_" + str(num) + "');")
    #Реестр счетов
    if ('register_checks',) in table_list:
        for i in range(MIN_NUM, MAX_CHECKS + 1):
            start_end_date = randomStartEndDate()
            dates_check_registration = randomCheckAndRegistrationDate(start_end_date[0], start_end_date[1])
            cur.execute("INSERT INTO register_checks("
                            "check_number, registration_date, check_date, check_sum, description, number_checks,"
                            "provider_id, subdivision_id, responsible_id, source_financing_id, payment_document_id, completeness) "
                            "VALUES('№_{num}', {registration_date}, {check_date}, {check_sum}, 'Описание №_{num}', {number_checks},"
                            "{provider_id}, {subdivision_id}, {responsible_id}, {source_financing_id}, {payment_document_id},"
                            "{completeness});".format(
                    num = i,
                    registration_date = dates_check_registration[1],
                    check_date = dates_check_registration[0],
                    check_sum = random.randint(0, MAX_SUM),
                    number_checks = random.randint(MIN_NUM, MAX_NUM),
                    provider_id = random.randint(MIN_NUM, MAX_NUM),
                    subdivision_id = random.randint(MIN_NUM, MAX_NUM),
                    responsible_id = random.randint(MIN_NUM, MAX_NUM),
                    source_financing_id = random.randint(MIN_NUM, MAX_NUM),
                    payment_document_id = random.randint(MIN_NUM, MAX_NUM),
                    completeness = random.randint(0, 1),
                    ))
    #Способы закупки
    if ('procurement_methods',) in table_list:
        for num in range(MIN_NUM, MAX_NUM + 1):
            cur.execute("INSERT INTO procurement_methods(procurement_method) VALUES('Способ закупки №_" + str(num) + "');")
    #Реестр конкурентных способов закупки
    procedure_completes = []
    start_end_date = []
    if ('register_procurement_methods',) in table_list:
        for i in range(MIN_NUM, MAX_CONTRACTS + 1):
            procedure_completes.append(random.randint(0, 1))
            start_end_date.append(randomStartEndDate())
            cur.execute("INSERT INTO register_procurement_methods(number_notice, notice_date, procurement_object, starting_price,"
                            "start_date_deadline, end_date_deadline, opening_envelopes_date, summarizing_date, procedure_complete,"
                            "smp, completeness, date_registration, procurement_method_id) "
                            "VALUES('№_{num}', {notice_date}, 'Предмет закупки №{num}', {starting_price},"
                            "{start_date_deadline}, {end_date_deadline}, {opening_envelopes_date},"
                            "{summarizing_date}, {procedure_complete}, {smp}, {completeness}, {date_registration}, {procurement_method_id})".format(
                                num = i,
                                notice_date = randomDeltaDayDates(start_end_date[i - MIN_NUM][0], 0, TIME_DIFFERENCE_DAY, False),
                                starting_price = random.randint(0, MAX_SUM),
                                start_date_deadline = start_end_date[i - MIN_NUM][0],
                                end_date_deadline = start_end_date[i - MIN_NUM][1],
                                opening_envelopes_date = randomDeltaDayDates(start_end_date[i - MIN_NUM][1], 0, TIME_DIFFERENCE_DAY, True),
                                summarizing_date = randomDeltaDayDates(start_end_date[i - MIN_NUM][1], TIME_DIFFERENCE_DAY, TIME_DIFFERENCE_DAY * 2, True),
                                procedure_complete = procedure_completes[i - MIN_NUM],
                                smp = random.randint(0, 1),
                                completeness = random.randint(0, 1),
                                date_registration = start_end_date[i - MIN_NUM][0],
                                procurement_method_id = random.randint(MIN_NUM, MAX_NUM)
                                ))
    contracts_sum = []
    contracts_size = 0
    #Договора реестра конкурентных способов закупки
    if ('contracts_register_procurement_methods',) in table_list:
        for i in range(MIN_NUM, MAX_CONTRACTS + 1):
            if procedure_completes[i - MIN_NUM] == True:
                contracts_size += 1
                contracts_sum.append(random.randint(0, MAX_SUM))
                cur.execute("INSERT INTO contracts_register_procurement_methods(contract_number, contracts_sum,"
                                "start_date, end_date, provider_id, comment, conclusion_date, date_registration, completeness,"
                                "register_procurement_method_id, subdivision_id, responsible_id, source_financing_id) "
                                "VALUES('№_{num}', {contracts_sum}, {start_date}, {end_date}, {provider_id}, 'Комментарий №_{num}',"
                                "{conclusion_date}, {date_registration}, {completeness},"
                                "{register_procurement_method_id}, {subdivision_id}, {responsible_id}, {source_financing_id})".format(
                                    num = i,
                                    contracts_sum = contracts_sum[-1],
                                    start_date = start_end_date[i - MIN_NUM][0],
                                    end_date = start_end_date[i - MIN_NUM][1],                                    
                                    conclusion_date = start_end_date[i - MIN_NUM][0],
                                    date_registration = start_end_date[i - MIN_NUM][1],
                                    completeness = random.randint(0, 1),
                                    provider_id = random.randint(MIN_NUM, MAX_NUM),
                                    register_procurement_method_id = i,
                                    subdivision_id = random.randint(MIN_NUM, MAX_NUM),
                                    responsible_id = random.randint(MIN_NUM, MAX_NUM),
                                    source_financing_id = random.randint(MIN_NUM, MAX_NUM)
                                    ))
    #Счета реестра конкурентных способов закупки
    if ('checks_register_procurement_methods',) in table_list:
        for i in range(MIN_NUM, contracts_size * FACTOR_CHECKS + 1):
            contract_id = random.randint(MIN_NUM, contracts_size)
            dates_check_registration = randomCheckAndRegistrationDate(start_end_date[contract_id - MIN_NUM][0], start_end_date[contract_id - MIN_NUM][1])
            check_sum = random.randint(1, contracts_sum[contract_id - MIN_NUM]) if contracts_sum[contract_id - MIN_NUM] > 0 else 0
            contracts_sum[contract_id - MIN_NUM] -= check_sum
            cur.execute("INSERT INTO checks_register_procurement_methods("
                            "check_number, registration_date, check_date, check_sum, description, contract_id) "
                            "VALUES('№_{num}', {registration_date}, {check_date}, {check_sum}, 'Описание №_{num}',"
                            "{contract_id})".format(
                                num = i,
                                registration_date = dates_check_registration[1],
                                check_date = dates_check_registration[0],
                                check_sum = check_sum,
                                contract_id = contract_id
                                ))
    con.commit()
    cur.close()
    con.close()

if __name__ == '__main__':
    parse_params = params.createParams()
    parse_params = parse_params.parse_args(sys.argv[1:])
    parse_params = params.parseParams(parse_params)
    testInsertMySQL(user = parse_params.user, password = parse_params.password, host = parse_params.host)
