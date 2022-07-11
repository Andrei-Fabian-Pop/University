from src.domain.history import History
from src.repo.repository import Repository
from src.services.student_service import StudentService


class HistoryService:
    def __init__(self):
        self.__history_repo = Repository()
        self.__step_list = list()
        self.__step_id = 0  # unique to each operation set, __step_id - 1 represents the last value of __step_list
        self.__next_id = 0  # unique to each operation, represents len() of self.__step_list

    def next_step(self):
        """
        increments __self_id
        :return:
        """
        self.__step_id += 1

    def add_operation(self, student, operation):
        """
        inverts the operation given ("add" -> "del" and vice versa), creates the History object and adds it to
        __history_repo(Repository)
        :param student: student(Class)
        :param operation: "add" or "del"
        :return:
        """
        operation = "add" if operation == "del" else "del"  # switches the operation
        history = History(self.__next_id, student, operation, self.__step_id)
        self.__step_list.append(self.__step_id)
        self.__next_id += 1
        self.__history_repo.add(history)

    def undo(self, student_service):
        """
        modifies the repository from student_service to its previous iteration by using __history_repo
        :param student_service:
        :return:
        """
        try:
            if self.__step_id == 0:
                raise ValueError
            current_step = self.__step_id - 1
            for i in reversed(range(self.__next_id)):
                if self.__step_list[i] != current_step:
                    break
                elif self.__history_repo[i].operation == "add":
                    student_service.add_student(self.__history_repo[i].student)
                else:  # operation == del
                    student_service.delete_student(self.__history_repo[i].student)
                self.__next_id -= 1
                self.__step_list.pop()
            self.__step_id -= 1
        except ValueError:
            print("Nothing to undo")
