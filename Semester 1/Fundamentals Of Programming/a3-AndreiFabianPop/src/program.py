# Task 5. Apartment Building Administrator

"""
  Write non-UI functions below
"""


def new_apartment(number, water=0, heating=0, electricity=0, gas=0, other=0):
    return {"number": number, "water": water, "heating": heating, "electricity": electricity, "gas": gas, "other": other}


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
    for apartment in apartments:
        if apartment["number"] == apartment_number:
            return apartment[expense_type]


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


def add_new_transaction(apartments, param_string):
    """
    Adds a new expense to the apartment specified in 'param_string'
    :param apartments: list of apartments
    :param param_string: string of parameters containing the apartment number, expense and amount
    :return: None
    """
    param_elements = split_parameters(param_string)
    try:
        if len(param_elements) != 3:
            raise Exception
        apartment_number = int(param_elements[0])
        expense_type = param_elements[1]
        amount = int(param_elements[2])
        # add the already existing expenses from this apartment for this type, if they exist
        amount += get_apartment_expense(apartments, apartment_number, expense_type)
        set_expense_to_apartment(apartments, apartment_number, expense_type,
                                 amount)
        confirm_transaction(apartment_number, expense_type, amount)
    except:
        invalid_parameters()


def remove_expenses_of_apartment(apartments, apartment_number):
    """
    Removes all expenses of the apartment with the number 'apartment number'
    :param apartments: list of apartments
    :param apartment_number: natural number
    :return: None
    """
    in_range = False
    for expense in apartments[apartment_number]:
        if expense != "number":
            in_range = True
            set_expense_to_apartment(apartments, apartment_number, expense, 0)
    if not in_range:
        out_of_range_error()


def remove_expenses(apartments, param_string):
    """
    Depending on the parameters from param_string, the function either removes all expenses for apartment X, or
    removes all expenses E from all of the apartments.
    :param apartments: list of apartments
    :param param_string: string of parameters
    :return: None
    """
    param_elements = split_parameters(param_string)
    try:
        if param_elements[0].isnumeric():
            if len(param_elements) == 1:  # remove all expenses for apartment X
                apartment_number = int(param_elements[0])
                remove_expenses_of_apartment(apartments, apartment_number)
            elif len(param_elements) == 3 and param_elements[1] == "to":
                first_apartment = int(param_elements[0])
                last_apartment = int(param_elements[2])
                for apartment_number in range(first_apartment, last_apartment+1):
                    remove_expenses_of_apartment(apartments, apartment_number)
            else:
                raise Exception
        else:  # remove all expenses E from all of the apartments
            expense = param_elements[0]
            valid_expense = False
            for apartment in apartments:
                if expense in apartment.keys():
                    valid_expense = True
            if not valid_expense:
                raise Exception
            for apartment_number in range(1, len(apartments)+1):
                set_expense_to_apartment(apartments, apartment_number, expense, 0)
    except:
        invalid_parameters()
    pass


def replace_expenses(apartments, param_string):
    """
    Replaces expense specified in param_string with the wanted expense. The form of param_strings should be
    "<apartment> <type> with <amount>"
    :param apartments: list of apartments
    :param param_string: string containing "<apartment> <type> with <amount>"
    :return: None
    """
    try:
        param_elements = split_parameters(param_string)
        if len(param_elements) != 4 or param_elements[2] != "with":
            invalid_parameters()
        apartment_number = int(param_elements[0])
        expense_type = param_elements[1]
        expense_value = int(param_elements[3])
        set_expense_to_apartment(apartments, apartment_number, expense_type, expense_value)
    except:
        invalid_parameters()


def apartment_list(apartments, param_string):
    """
    Lists all the apartments if "param_string" is empty, otherwise prints all apartments that meet the requested
    properties: "<apartment>", "[ < , = , > ] <amount>"
    :param apartments: list of apartments
    :param param_string: string containing the parameters of this command
    :return: None
    """
    param_elements = split_parameters(param_string)
    if not param_elements:  # if there are no parameters display all expenses
        expenses_due = False  # this variable is false by default, and turns true when an apartment with expenses due is found
        for apartment in apartments:
            for expense in apartment:
                if expense != "number" and get_expense(apartment, expense) != 0:
                    print_apartment_expense(apartment, expense)
                    expenses_due = True
        if not expenses_due:
            no_expenses_due()
    elif len(param_elements) == 1:
        apartment_number = int(param_elements[0])
        for expense in apartments[apartment_number]:
            if expense != "number" and get_apartment_expense(apartments, apartment_number, expense) != 0:
                print_apartment_expense(apartments[apartment_number-1], expense)
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
                    apartment_total_expenses(apartment, s)
            elif comparison == "=":
                if s == compared_number:
                    apartment_total_expenses(apartment, s)
            elif comparison == "<":
                if s < compared_number:
                    apartment_total_expenses(apartment, s)
            else:
                invalid_parameters()
    else:
        invalid_parameters()


"""
  Write the command-driven UI below
"""


def out_of_range_error():
    print("Apartment number does not exist.")


def confirm_transaction(apartment_number, expense_type, amount):
    print("Added", amount, "RON for", expense_type, "in apartment no.", apartment_number, end=".\n")


def no_expenses_due():
    print("There are no apartments with expenses due.")


def apartment_total_expenses(apartment, s):
    print("Apartment", get_expense(apartment, "number"), "has a total sum of expenses of", s, end=".\n")


def print_apartment_expense(apartment, expense):
    print("Apartment", get_expense(apartment, "number"), "has a", get_expense(apartment, expense), "RON expense for", expense, end=".\n")


def invalid_parameters():
    print("Invalid parameters.")


def command_ui():
    apartments = init_apartment()
    populate_apartments(apartments)
    # print(apartments)
    command_dict = {
                    "add": add_new_transaction,
                    "remove": remove_expenses,
                    "replace": replace_expenses,
                    "list": apartment_list
                    }

    while True:
        user_command = input("> ")
        user_command.lower()
        if user_command == "exit":
            break
        command, cmd_params = split_user_command(user_command)
        if command not in command_dict:
            print("Unrecognized command.")
        else:
            command_dict[command](apartments, cmd_params)


command_ui()
