from src.domain.Student import Student
from src.domain.Discipline import Discipline
from src.domain.Grade import Grade


class HistoryException(Exception):
    pass


class HistoryService:
    def __init__(self, student_repo, discipline_repo, grade_repo):
        self.__undo_list = []
        self.__redo_list = []
        self.__student_repo = student_repo
        self.__discipline_repo = discipline_repo
        self.__grade_repo = grade_repo
        self.__id = 1
        self.__step = 1

    @staticmethod
    def invert_add_del(command, args):
        if command == "add":
            command = "del"
        elif command == "del":
            command = "add"
        return command, args

    def invert_update(self, command, domain, args):
        if not isinstance(args, list):
            args = list(args)
        if isinstance(args[0], list):
            args = args[0]
        if domain == "student":
            args[1] = self.__student_repo[1].name
        elif domain == "discipline":
            args[1] = self.__discipline_repo[1].name
        return command, args

    def add_expression(self, command, domain, args):
        command, domain, args = self.make_inverse([command, domain, args])
        if isinstance(args[0], list):
            args = args[0]
        if isinstance(args, int):
            args = [args]
        self.__undo_list.append(str(command + " " + domain + " " + " ".join(str(arg) for arg in args)))
        self.__redo_list[:] = []

    def modify_repo(self, last_op_list):
        if last_op_list[0] == "add":
            if last_op_list[1] == "student":
                self.__student_repo.add(Student(int(last_op_list[2]), last_op_list[3]))
            elif last_op_list[1] == "discipline":
                self.__discipline_repo.add(Discipline(int(last_op_list[2]), last_op_list[3]))
            elif last_op_list[1] == "grade":
                self.__grade_repo.add(
                    Grade(int(last_op_list[2]), int(last_op_list[3]), int(last_op_list[4]), int(last_op_list[5])))
        elif last_op_list[0] == "del":
            if last_op_list[1] == "student":
                self.__student_repo.delete(int(last_op_list[2]))
            elif last_op_list[1] == "discipline":
                self.__discipline_repo.delete(int(last_op_list[2]))
            elif last_op_list[1] == "grade":
                self.__grade_repo.delete(int(last_op_list[2]))
        elif last_op_list[0] == "update":
            if last_op_list[1] == "student":
                self.__student_repo.update(int(last_op_list[2]), Student(int(last_op_list[2]), last_op_list[3]))
            elif last_op_list[1] == "discipline":
                self.__discipline_repo.update(int(last_op_list[2]), Discipline(int(last_op_list[2]), last_op_list[3]))

    def make_inverse(self, last_op_list):
        command = last_op_list[0]
        domain = last_op_list[1]
        args = last_op_list[2:]
        if command == "add" or command == "del":
            command, args = self.invert_add_del(command, args)
        elif command == "update":
            command, args = self.invert_update(command, domain, args)
        return command, domain, args

    def undo(self):
        if len(self.__undo_list) == 0:
            raise HistoryException("Nothing left to undo.")
        last_operation = self.__undo_list.pop()
        last_op_list = last_operation.split(" ")
        self.modify_repo(last_op_list)
        command, domain, args = self.make_inverse(last_op_list)
        self.__redo_list.append(str(command + " " + domain + " " + " ".join(str(arg) for arg in args)))

    def redo(self):
        if len(self.__redo_list) == 0:
            raise HistoryException("Nothing left to redo.")
        last_operation = self.__redo_list.pop()
        last_op_list = last_operation.split(" ")
        self.modify_repo(last_op_list)
        command, domain, args = self.make_inverse(last_op_list)
        self.__undo_list.append(str(command + " " + domain + " " + " ".join(str(arg) for arg in args)))
