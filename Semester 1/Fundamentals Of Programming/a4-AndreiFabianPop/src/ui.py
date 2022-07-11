"""
  User interface module
"""

def out_of_range_error():
    print("Apartment number does not exist.")


def confirm_transaction(apartment_number, expense_type, amount):
    print("Added", amount, "RON for", expense_type, "in apartment no.", apartment_number, end=".\n")


def no_expenses_due():
    print("There are no apartments with expenses due.")


def apartment_total_expenses(s, apartment_number):
    print("Apartment", apartment_number, "has a total sum of expenses of", s, end=".\n")


def print_apartment_expense(expense, apartment_number, expense_value):
    print("Apartment", apartment_number, "has a", expense_value, "RON expense for", expense, end=".\n")


def invalid_parameters():
    print("Invalid parameters.")


def print_total(s, expense):
    print("The total amount of", expense, "expenses is", s, end=".\n")


def nothing_to_undo_error():
    print("Nothing left to undo.")
