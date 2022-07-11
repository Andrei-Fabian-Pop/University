"""

@author: radu


Write an application which manages the students of a faculty.
Each student has a unique id, a name and a grade. The application should
allow to:

F1: print all students
F2: add students
F3: delete students
F4: show students whose grades are >= a given value
F5: find a student with the maximal grade
F6_: split the application into modules (main, ui, domain, util)
F7_: validate input data
F8_: student_id is unique - validation in add, delete etc.
F9: find all students whose name contain a string t (the match should not be
    case sensitive)
F10: undo
F11: remove all students with the grade smaller than 5 (using TDD)
F12: sort students according to their grade (descending)  (using TDD)
F13: given an integer 'nr', find the top nr students according
     to their grade  (using TDD)
F14: compute the average grade of all students having the grade >= 5 (using TDD)
F15: sort all students according to their grade and alphabetically (using TDD).
------------

I1: F1, F2, F3, F4, F5
I2: F6_, F7_
I3: F8_, F9
I4: F10
I5: F11, F12, F13, F14, F15
-----------

I1: F2, F1, F3, F4, F5
I2: F6_, F7_
I3: F8_, F9
I4: F10
I5: F11, F12, F13, F14, F15

 
"""

# =============DOMAIN=====================

def create_student(id, name, grade):
    """
    Creates a student
    :param id:
    :param name:
    :param grade:
    :return: a dictionary with the params
    """
    return {
        "id": id,
        "name": name,
        "grade": grade
    }

def get_ID(student):
    return student["id"]

def get_name(student):
    return student["name"]

def get_grade(student):
    return student["grade"]

def set_id(student, id):
    student["id"] = id

def set_name(student, name):
    student["name"] = name

def set_grade(student, grade):
    student["grade"] = grade

# ===========OPERATION===================

def add_student(students, id, name, grade):
    # TODO: Check if ID is unique
    student = create_student(id, name, grade)
    students.append(student)

def find_by_id(students, id):
    #                           x is a student
    result = list(filter(lambda x: get_ID(x) == id, students))
    return result[0] if len(result) > 0 else None

# =============UI========================

def UI_add_student(students):
    id = int(input("Enter the ID: "))
    name = input("Enter the name: ")
    grade = int(input("Enter the grade: "))
    add_student(students, id, name, grade)


def print_menu_options():
    print("1: Add student\n"
          "2: Print all students\n")

def print_all_students(students):
    # TODO: print students in a more friendly format
    print(students)

def run_menu():
    students = []
    options = {
        1: UI_add_student,
        2: print_all_students
    }
    while True:
        print_menu_options()
        opt = input("Option: ")
        if opt == 'x':
            break
        opt = int(opt)
        options[opt](students) # UI_add_student(students), but it looks better than many ifs
        # if opt == 1:
        #     UI_add_student(students)
        # if opt == 2:
        #     print_all_students(students)


if __name__ == '__main__':
    run_menu()
