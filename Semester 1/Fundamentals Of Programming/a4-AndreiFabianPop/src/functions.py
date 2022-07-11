"""
  Program functionalities module
"""
from src.ui import *


def new_apartment(number, water=0, heating=0, electricity=0, gas=0, other=0):
    return{"number": number, "water": water, "heating": heating, "electricity": electricity, "gas": gas, "other": other}


def init_apartment(number_of_apartments=10):
    """
    Returns a list of 'number_of_apartments' dictionaries using the new_apartment() function
    :param number_of_apartments: unsigned number, 10 by default
    :return: a list of 'number_of_apartments' dictionaries using the new_apartment() function
    """
    return [new_apartment(apartment_num) for apartment_num in range(1, number_of_apartments+1)]


def populate_apartments(apartments):
    set_expense_to_apartment(apartments, 4, "gas", 200)
    set_expense_to_apartment(apartments, 8, "water", 50)
    set_expense_to_apartment(apartments, 1, "electricity", 68)
    set_expense_to_apartment(apartments, 6, "heating", 111)
    set_expense_to_apartment(apartments, 4, "other", 400)


def split_user_command(user_command):
    """
    Receives a string and splits it into 2 parts, the command and the parameters(cmd_params)
    :param user_command: string containing the user input
    :return: a tuple with the command and the parameters
    """
    user_command.strip()
    tokens = user_command.split(" ", 1)
    command = tokens[0].lower() if len(tokens) > 0 else None  # in case we have an empty string
    cmd_params = tokens[1].lower() if len(tokens) == 2 else None  # in case we have just a word
    return command, cmd_params


def split_parameters(param_string):
    """
    Splits every word and saves it in a list of tokens
    :param param_string: String containing the parameters
    :return: List of parameters
    """
    if not param_string:
        return None
    else:
        tokens = param_string.split()
        return [token for token in tokens]


def get_apartment_expense(apartments, apartment_number, expense_type):
    try:
        if not check_if_dict_key(apartments, expense_type):
            raise ValueError
        for apartment in apartments:
            if apartment["number"] == apartment_number:
                return apartment[expense_type]
    except ValueError:
        invalid_parameters()


def get_expense(apartment, expense):
    return apartment[expense]


def set_expense_to_apartment(apartments, apartment_number, expense_type, amount):
    apartment_in_range = False
    for apartment in apartments:
        if apartment["number"] == apartment_number:
            apartment[expense_type] = amount
            apartment_in_range = True
            break
    if not apartment_in_range:
        out_of_range_error()


def set_expense(apartment, expense_type, amount):
    apartment[expense_type] = amount


def add_new_transaction(apartments, param_string, instance_list):
    """
    Adds a new expense to the apartment specified in 'param_string'
    :param instance_list: list of all instances for the undo function
    :param apartments: list of apartments
    :param param_string: string of parameters containing the apartment number, expense and amount
    :return: None
    """
    param_elements = split_parameters(param_string)
    try:
        if param_elements is None:
            raise ValueError
        if len(param_elements) != 3:
            raise ValueError
        apartment_number = int(param_elements[0])
        expense_type = param_elements[1]
        amount = int(param_elements[2])
        if not check_if_dict_key(apartments, expense_type):
            raise ValueError
        # add the already existing expenses from this apartment for this type, if they exist
        set_expense_to_apartment(apartments, apartment_number, expense_type,
                                 amount+get_apartment_expense(apartments, apartment_number, expense_type))
        confirm_transaction(apartment_number, expense_type, amount)
        add_new_instance(apartments, instance_list)
    except ValueError:
        invalid_parameters()


def remove_expenses_of_apartment(apartments, apartment_number):
    """
    Removes all expenses of the apartment with the number 'apartment number'
    :param apartments: list of apartments
    :param apartment_number: natural number
    :return: None
    """
    try:
        in_range = False
        if apartment_number >= len(apartments):
            raise IndexError
        for expense in apartments[apartment_number]:
            if expense != "number":
                in_range = True
                set_expense_to_apartment(apartments, apartment_number, expense, 0)
        if not in_range:
            raise IndexError
    except IndexError:
        out_of_range_error()


def remove_expenses(apartments, param_string, instance_list):
    """
    Depending on the parameters from param_string, the function either removes all expenses for apartment X, or
    removes all expenses E from all of the apartments.
    :param instance_list: list of all instances for the undo function
    :param apartments: list of apartments
    :param param_string: string of parameters
    :return: None
    """
    param_elements = split_parameters(param_string)
    try:
        if param_elements is None:
            raise ValueError
        if param_elements[0].isdigit():
            if len(param_elements) == 1:  # remove all expenses for apartment X
                apartment_number = int(param_elements[0])
                remove_expenses_of_apartment(apartments, apartment_number)
            elif len(param_elements) == 3 and param_elements[1] == "to" and param_elements[2].isdigit():
                first_apartment = int(param_elements[0])
                last_apartment = int(param_elements[2])
                for apartment_number in range(first_apartment, last_apartment+1):
                    remove_expenses_of_apartment(apartments, apartment_number)
            else:
                raise ValueError
        else:  # remove all expenses E from all of the apartments
            expense = param_elements[0]
            if not check_if_dict_key(apartments, expense):
                raise ValueError
            for apartment_number in range(1, len(apartments)+1):
                set_expense_to_apartment(apartments, apartment_number, expense, 0)
        add_new_instance(apartments, instance_list)
    except ValueError:
        invalid_parameters()


def replace_expenses(apartments, param_string, instance_list):
    """
    Replaces expense specified in param_string with the wanted expense. The form of param_strings should be
    "<apartment> <type> with <amount>"
    :param instance_list: list of all instances for the undo function
    :param apartments: list of apartments
    :param param_string: string containing "<apartment> <type> with <amount>"
    :return: None
    """
    try:
        param_elements = split_parameters(param_string)
        if param_elements is None or \
                len(param_elements) != 4 or \
                param_elements[2] != "with" or \
                not check_if_dict_key(apartments, param_elements[1]) or \
                not param_elements[0].isdigit() or \
                not param_elements[3].isdigit():
            raise ValueError
        apartment_number = int(param_elements[0])
        expense_type = param_elements[1]
        expense_value = int(param_elements[3])
        set_expense_to_apartment(apartments, apartment_number, expense_type, expense_value)
        add_new_instance(apartments, instance_list)
    except ValueError:
        invalid_parameters()


def apartment_list(apartments, param_string, instance_list):
    """
    Lists all the apartments if "param_string" is empty, otherwise prints all apartments that meet the requested
    properties: "<apartment>", "[ < , = , > ] <amount>"
    :param instance_list: list of all instances for the undo function
    :param apartments: list of apartments
    :param param_string: string containing the parameters of this command
    :return: None
    """
    try:
        param_elements = split_parameters(param_string)
        if not param_elements:  # if there are no parameters display all expenses
            expenses_due = False
            # this variable is false by default, and turns true when an apartment with expenses due is found
            for apartment in apartments:
                for expense in apartment:
                    if expense != "number" and get_expense(apartment, expense) != 0:
                        print_apartment_expense(expense, get_expense(apartment, "number"), get_expense(apartment, expense))
                        expenses_due = True
            if not expenses_due:
                no_expenses_due()
        elif len(param_elements) == 1:
            if not param_elements[0].isdigit():
                raise ValueError
            apartment_number = int(param_elements[0])
            for expense in apartments[apartment_number]:
                if expense != "number" and get_apartment_expense(apartments, apartment_number, expense) != 0:
                    print_apartment_expense(expense, get_expense(apartments[apartment_number-1], "number"),
                                            get_expense(apartments[apartment_number-1], expense))
        elif len(param_elements) == 2:
            compared_number = int(param_elements[1])
            comparison = param_elements[0]
            for apartment in apartments:
                s = 0
                for element in apartment:
                    if element != "number":
                        s += apartment[element]
                if comparison == ">":
                    if s > compared_number:
                        apartment_total_expenses(s, get_expense(apartment, "number"))
                elif comparison == "=":
                    if s == compared_number:
                        apartment_total_expenses(s, get_expense(apartment, "number"))
                elif comparison == "<":
                    if s < compared_number:
                        apartment_total_expenses(s, get_expense(apartment, "number"))
                else:
                    raise ValueError
        else:
            raise ValueError
    except ValueError:
        invalid_parameters()
    except IndexError:
        out_of_range_error()


def check_if_dict_key(apartments, key):
    """
    Checks if the 'key' is a field in the dictionary of apartments
    :param apartments: list of apartments
    :param key: a string containing a field in the dictionary
    :return:
    """
    apartment = apartments[0]
    if key in apartment:
        return True
    return False


def test_check_if_dict_key(apartments):
    assert not check_if_dict_key(apartments, "woah")
    assert check_if_dict_key(apartments, "water")
    assert not check_if_dict_key(apartments, "")


def sum_of_expense(apartments, param_string, instance_list):
    """
    Calculates the sum of all expenses by type(specified in 'param_string')
    :param apartments: list of apartments and their expenses
    :param param_string: string of parameters
    :param instance_list: list containing the history of 'apartments'
    :return:
    """
    s = 0
    try:
        param_elements = split_parameters(param_string)
        if param_elements is None:
            raise ValueError
        expense = param_elements[0]
        if len(param_elements) != 1:
            raise ValueError
        if not check_if_dict_key(apartments, expense):
            raise ValueError
        for apartment in apartments:
            s += get_expense(apartment, expense)
        print_total(s, expense)
    except ValueError:
        invalid_parameters()


def sort_apartments_by_key(apartments, param_string, instance_list):
    """
    Displays, in ascending order, depending on the 'param_string' value:
        1. the apartments, sorted by their total expenses
        2. the total expense of each expense type
    :param apartments: list of apartments and their expenses
    :param param_string: string of parameters
    :param instance_list: list containing the history of 'apartments'
    :return None
    """
    param_elements = split_parameters(param_string)
    try:
        if param_elements is None:
            raise ValueError
        if len(param_elements) != 1:
            raise ValueError
        if param_elements[0] == 'apartment':
            apartment_sums = []
            for apartment in apartments:
                s = 0
                for expense in apartment:
                    if expense != "number":
                        s += get_expense(apartment, expense)
                apartment_sums.append(s)

            for i in range(len(apartment_sums)):
                max_expense_index = -1
                for sum_index in range(len(apartment_sums)):
                    if apartment_sums[sum_index] > apartment_sums[max_expense_index]:
                        max_expense_index = sum_index
                if max_expense_index != -1:
                    apartment_total_expenses(apartment_sums[max_expense_index], max_expense_index+1)
                    apartment_sums[max_expense_index] = 0
        elif param_elements[0] == 'type':
            apartments_sum = new_apartment(0)
            for apartment in apartments:
                for expense in apartment:
                    if expense != "number":
                        apartments_sum[expense] += get_expense(apartment, expense)
            for i in range(len(apartments_sum)-1):
                max_value = 0
                expense_of_max_value = ''
                for index in apartments_sum:
                    if get_expense(apartments_sum, index) > max_value:
                        expense_of_max_value = index
                        max_value = get_expense(apartments_sum, index)
                print_total(max_value, expense_of_max_value)
                set_expense(apartments_sum, expense_of_max_value, -1)
        else:
            raise ValueError
    except ValueError:
        invalid_parameters()


def filter_by_key(apartments, param_string, instance_list):
    """
    sets to 0 all expense from apartments that are not of the specified type(in param_string) or sets to 0 all expenses
    from all the apartments that are less than the specified amount(in param_string)
    :param apartments: list of apartments and their expenses
    :param param_string: string of parameters
    :param instance_list: list containing the history of 'apartments'
    :return: None
    """
    param_elements = split_parameters(param_string)
    try:
        if param_elements is None:
            raise ValueError
        if len(param_elements) != 1:
            raise ValueError
        expense_key = param_elements[0]
        if check_if_dict_key(apartments, expense_key):
            for apartment in apartments:
                for expense in apartment:
                    if expense != "number" and expense != expense_key:
                        set_expense(apartment, expense, 0)
        elif expense_key.isdigit():
            expense_key = int(expense_key)
            for apartment in apartments:
                for expense in apartment:
                    if expense != "number" and get_expense(apartment, expense) >= expense_key:
                        set_expense(apartment, expense, 0)
        else:
            raise ValueError
        add_new_instance(apartments, instance_list)
    except ValueError:
        invalid_parameters()


def add_new_instance(apartments, instance_list):
    """
    Appends the apartments list to the instance list
    :param apartments: list of apartments
    :param instance_list: history of all versions of  'apartments'
    :return: None
    """
    new_list = init_apartment()
    apartment_number = 1
    for apartment in apartments:
        for expense in apartment:
            if expense != "number":
                set_expense_to_apartment(new_list, apartment_number, expense,
                                         get_apartment_expense(apartments, apartment_number, expense))
        apartment_number += 1
    instance_list.append(new_list)


def undo(apartments, param_string, instance_list):
    """
    Reverts the apartments list to the previous version, all the versions are stored in instance_list
    :param apartments: list of apartments
    :param param_string: string of parameters
    :param instance_list: history of all versions of 'apartments'
    :return: None
    """
    try:
        if len(instance_list) == 1:
            raise IndexError
        instance_list.pop()
        apartments[:] = instance_list[-1]
    except IndexError:
        nothing_to_undo_error()
