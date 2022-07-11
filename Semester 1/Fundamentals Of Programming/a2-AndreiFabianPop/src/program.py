#
# Write the implementation for A2 in this file
#

# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities

def menu():
    print("Write the number corresponding to the wanted operation:\n"
          "[1] Read a complex number.\n"
          "[2] Display the entire list of numbers on the console.\n"
          "[3] Display the longest sequence where the real part is in the form of a mountain (sequence property 11.).\n"
          "[4] Display the longest sequence of real numbers (sequence property 5.).\n"
          "[5] Exit the program.")

def user_choice():
    return int(input("-> "))

def add_complex_number():
    real = int(input("Real part: "))
    imag = int(input("Imaginary part: "))
    return {"real": real, "imag": imag}

def write_complex_number(dict_list, index):
    """
    The function receives the list of complex numbers and the index of the one that is to be written
    and formats them in a way that is easy to read by users
    :param dict_list: list of dictionary containing the 2 parts of a complex number
    :param index: natural number - the index of the complex number from the dict_list
    :return: prints the complex number in a user friendly way
    """
    if dict_list[index]["imag"] < 0:
        print(dict_list[index]["real"], "-", -dict_list[index]["imag"], "i", sep="")
    elif dict_list[index]["imag"] > 0:
        print(dict_list[index]["real"], "+", dict_list[index]["imag"], "i", sep="")
    else:
        print(dict_list[index]["real"])

def write_list_of_numbers(dict_list):
    """
    The function prints and indexes all the contents of the 'dict_list' dictionary list
    :param dict_list: list of dictionary containing the 2 parts of a complex number
    :return: prints and indexes all the contents of the 'dict_list'
    """
    for i in range(len(dict_list)):
        print("[", i+1, "]", sep="", end=" ")
        write_complex_number(dict_list, i)

# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!
def print_sequence(l_start_index, l_end_index, dict_list):
    """
    Cycles through the complex numbers from dict_list, starting with the l_start_index to the l_start_end
    :param l_start_index: natural number
    :param l_end_index: natural number
    :param dict_list: list of dictionary containing the 2 parts of a complex number
    :return: None
    """
    for i in range(l_start_index, l_end_index+1):
        write_complex_number(dict_list, i)

def init_complex_number_dictionary():
    """
    :return: 10 complex numbers in the form of a dictionary list
    """
    return ({"real": 85, "imag": 0}, {"real": 7, "imag": 0},
            {"real": 19, "imag": 0}, {"real": 66, "imag": 0},
            {"real": 24, "imag": 0}, {"real": 40, "imag": 55},
            {"real": 59, "imag": -59}, {"real": 142, "imag": 0},
            {"real": 55, "imag": 61}, {"real": 37, "imag": 2})

def mountain(dict_list):
    """
    The function goes through the list of complex numbers dict_list and interprets the real part of the numbers as the
    altitude points of a mountain array. The 'peak' refers to a number who's real part is greater than it's neighbours.
    A mountain is a sequence of complex numbers who have their real part in an ascending then descending order. The
    function remembers the longest mountain's starting point in l_start_index and its ending point in l_end_index.
    :param dict_list: list of dictionary containing the 2 parts of a complex number
    :return: None
    """
    l_start_index = 0
    l_end_index = 0
    start = False
    descending = dict_list[0]["real"] > dict_list[1]["real"]
    start_index = 0
    if not descending:  # determine the initial angle of the mountain
        start = True
    for i in range(len(dict_list)-1):
        if not start and dict_list[i+1]["real"] > dict_list[i]["real"]:  # the first 'mountain' starts
            start = True
            start_index = i
            descending = False
        if start and descending and dict_list[i+1]["real"] > dict_list[i]["real"]:  # this 'mountain' ended and a new one starts
            if i - start_index > l_end_index - l_start_index:  # compare the current 'mountain' with the biggest one yet
                l_start_index = start_index
                l_end_index = i
            start_index = i
            descending = False
        if not descending and dict_list[i+1]["real"] < dict_list[i]["real"]:  # peak of the 'mountain'
            descending = True
    if start and descending:  # check the 'end' of the 'mountain'
        if len(dict_list) - 1 - start_index > l_end_index - l_start_index:
            l_start_index = start_index
            l_end_index = len(dict_list) - 1
    print_sequence(l_start_index, l_end_index, dict_list)


def real_sequence(dict_list):
    """
    This function computes the longest sequence of real numbers from a list of complex numbers and remembers the
    starting point in the l_start_index variable and the end of the sequence in the l_end_index variable.
    :param dict_list: list of dictionary containing the 2 parts of a complex number
    :return: None
    """
    l_start_index = l_end_index = start_index = 0
    in_sequence = False
    for i in range(len(dict_list)-1):
        if not in_sequence and dict_list[i]["imag"] == 0:  # the beginning of a new sequence
            in_sequence = True
            start_index = i
        if in_sequence and dict_list[i]["imag"] != 0:  # the end of the current sequence
            if l_end_index - l_start_index < i - start_index:  # determines the longest sequence
                l_start_index = start_index
                l_end_index = i - 1
            in_sequence = False
    print_sequence(l_start_index, l_end_index, dict_list)

if __name__ == '__main__':
    dict_list = []
    dict_list.extend(init_complex_number_dictionary())
    while True:
        menu()
        operation = user_choice()
        if operation == 1:
            dict_list.append(add_complex_number())
        if operation == 2:
            write_list_of_numbers(dict_list)
        if operation == 3:
            mountain(dict_list)
        if operation == 4:
            real_sequence(dict_list)
        if operation == 5:
            break
        print("\n")
