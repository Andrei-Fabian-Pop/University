"""
  Start the program by running this module
"""
from src.functions import *

if __name__ == "__main__":
    apartments = init_apartment()
    populate_apartments(apartments)
    instance_list = []
    add_new_instance(apartments, instance_list)

    command_dict = {
        "add": add_new_transaction,
        "remove": remove_expenses,
        "replace": replace_expenses,
        "list": apartment_list,
        "sum": sum_of_expense,
        "sort": sort_apartments_by_key,
        "filter": filter_by_key,
        "undo": undo
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
            command_dict[command](apartments, cmd_params, instance_list)
