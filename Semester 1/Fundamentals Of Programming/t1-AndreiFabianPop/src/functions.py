import random


def generate_random():
    """
    generates a list of all 10 digits and takes random different values from it and assigns them to,
    in order, a,b,c,d, which represent the digits of the secret number and it forms the secret number
    :return: 4 digit positive integer with different digits
    """
    a, b, c, d = 0, 0, 0, 0
    while a == 0:
        a, b, c, d = random.sample(range(10), 4)
    return a*1000 + b*100 + c*10 + d


def check_valid_input(user_input):
    if not user_input.isdigit():
        return False
    else:
        user_input = int(user_input)
        if not (1000 <= user_input <= 9999):
            return False
        a, b, c, d = int(user_input/1000), int(user_input/100 % 10), int(user_input/10 % 10), int(user_input % 10)
        if a != b and b != c and c != d and d != a and a != c and b != d:
            return True
        else:
            return False


def number_of_runners_and_codes(user_number, secret_number):
    runner_number = 0
    codes_number = 0
    user_number_list = \
        [int(user_number/1000), int(user_number/100 % 10), int(user_number/10 % 10), int(user_number % 10)]
    secret_number_list = \
        [int(secret_number/1000), int(secret_number/100 % 10), int(secret_number/10 % 10), int(secret_number % 10)]
    for i in range(0, 4):
        for j in range(i, 4):
            if user_number_list[i] == secret_number_list[j]:
                if i == j:
                    codes_number += 1
                else:
                    runner_number += 1
    return runner_number, codes_number


def test_check_valid_input():
    assert check_valid_input("4567") is True
    assert check_valid_input("4455") is False
    assert check_valid_input("54") is False
    assert check_valid_input("654456") is False


def test_number_of_runners_and_codes():
    assert number_of_runners_and_codes(9624, 5873) == (0, 0)
    assert number_of_runners_and_codes(9624, 5674) == (0, 2)
    assert number_of_runners_and_codes(9624, 5962) == (3, 0)
    assert number_of_runners_and_codes(9623, 9842) == (1, 1)


test_check_valid_input()
test_number_of_runners_and_codes()
