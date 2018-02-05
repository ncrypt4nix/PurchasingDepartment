import sys
import argparse

LOCAL_HOST = 'localhost'

def createParams():
    params = argparse.ArgumentParser()
    params.add_argument ('-u', '--user')
    params.add_argument ('-p', '--password')
    params.add_argument ('-hn', '--host', default=LOCAL_HOST)

    return params

def parseParams(params):
    if params.user == None:
        params.user = input("Введите пользователя: ")
    if params.password == None:
        params.password = input("Введите пароль: ")
    if params.host == LOCAL_HOST:
        temp = input("Введите хост (по умолчанию localhost): ")
        if len(temp) != 0:
            params.host = temp
    return params