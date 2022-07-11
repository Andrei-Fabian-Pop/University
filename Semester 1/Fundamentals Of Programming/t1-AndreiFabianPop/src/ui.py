from src.functions import *


def UI_get_user_command():
    user_input = input("your guess> ")
    user_input.strip()
    user_input.lower()
    return user_input


def UI_generate_secret_number():
    print("4 digit random number generated, try to guess it ;)")
    return generate_random()


def report_runners_and_codes(runner_number, codes_number):
    print("computer reports", codes_number, "code(s) and", runner_number, "runner(s)")
