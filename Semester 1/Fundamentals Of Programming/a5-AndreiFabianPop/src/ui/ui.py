from src.domain.students import Student
from src.services.history_service import HistoryService
from src.services.student_service import StudentService


class UI:
    def __init__(self, student_service, history_service):
        self.__stud_service = student_service
        self.__history_service = history_service
        self.command_dict = {
            "add": self.UI_add_student,
            "list": self.UI_display_list_of_students,
            "delete": self.UI_delete_group,
            "undo": self.UI_undo_operation
        }

    @staticmethod
    def UI_add_student(stud_service, history_service):
        stud_id = int(input("Enter the student ID: "))
        stud_name = input("Enter the student name: ")
        stud_group = int(input("Enter the student group: "))
        student = Student(stud_id, stud_name, stud_group)
        stud_service.add_student(student, history_service)

    @staticmethod
    def UI_delete_group(stud_service, history_service):
        group = int(input("Enter the group that you want to delete: "))
        stud_service.delete_by_group(group, history_service)
        print("Deleted students from group", group, end=".\n")

    def UI_display_list_of_students(self, stud_service, history_service):
        try:
            stud_list = stud_service.list_all_students()
            if not stud_list:
                raise ValueError
            for student in stud_list:
                self.print_stud(student)
        except ValueError:
            print("There are no students in the list.")

    @staticmethod
    def UI_undo_operation(stud_service, history_service):
        history_service.undo(stud_service)

    @staticmethod
    def print_stud(student):
        print("Student named ", student.name,
              ", from group ", student.group,
              " has the ID: ", student.id, end=".\n", sep="")

    @staticmethod
    def print_options():
        print("Choose an option: ")
        print("exit - exits the program")
        print("add - adds a student")
        print("list - lists all students")
        print("delete - deletes all students from the specified group")
        print("undo - undoes the last operation")

    @staticmethod
    def get_user_input():
        command = input("> ")
        command.lower()
        command.strip()
        return command

    def start(self):
        while True:
            self.print_options()
            user_choice = self.get_user_input()
            if user_choice == "exit":
                break
            elif user_choice not in self.command_dict:
                print("Unrecognized command.")
            else:
                self.command_dict[user_choice](self.__stud_service, self.__history_service)
