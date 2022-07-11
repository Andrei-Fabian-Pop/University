from src.domain.Student import Student
import re


class StudentServiceException(Exception):
    pass


class StudentService:
    def __init__(self, repo):
        self.__stud_repo = repo
        self.__id = 1
        self.__id_dump = list()

    def add_student(self, name, history_service):
        """
        Creates and adds a student entity to the repository, with the given name
        :param history_service: undo/redo service
        :param name: string
        :return: None
        """
        if self.__id_dump:
            self.__stud_repo.add(Student(self.__id_dump[-1], name))
            history_service.add_expression("add", "student", [self.__id_dump[-1], name])
            self.__id_dump.pop()
        else:
            self.__stud_repo.add(Student(self.__id, name))
            history_service.add_expression("add", "student", [self.__id, name])
            self.__id += 1

    def delete_student(self, stud_id):
        """
        Deletes student by the given id from the student repository
        :param stud_id: int
        :return: None
        """
        self.__id_dump.append(stud_id)
        self.__stud_repo.delete(stud_id)

    def update_student(self, stud_id, new_name):
        """
        updates the given student entity with the new name and the same id
        :param stud_id: int
        :param new_name: string
        :return: None
        """
        stud_id = int(stud_id)
        self.__stud_repo.update(stud_id, Student(stud_id, new_name))

    def list_students(self):
        """
        :return: list of all students, their id and name is grouped in sub-lists
        """
        return [[student.id, student.name] for student in self.__stud_repo.get_all()]

    def search_student_by_id(self, _id):
        """
        searches or the given id in the student Repository
        :param _id: int
        :return: False or the student name(string)
        """
        student_list = self.__stud_repo.get_all()
        for student in student_list:
            if student.id == _id:
                return student
        return False

    def search_student_by_string(self, stud_name):
        """
        searches for a student by using its name and partial matching, case sensitive search
        :param stud_name: string
        :return: False or list of name look-alike students
        """
        student_list = self.__stud_repo.get_all()
        result_list = []
        for student in student_list:
            if self.check_partial_string(student.name, stud_name):
                result_list.append(student)
        return False if result_list == [] else result_list

    @staticmethod
    def check_partial_string(string1, string2):
        """
        checks string1 and string2 and if they are partially matching, it returns True, else false
        :param string1: string
        :param string2: string
        :return: True or False
        """
        string1 = string1.lower()
        string2 = string2.lower()
        if (string1 in string2) or (string2 in string1):
            return True
        string1_reg = ".?".join(string1[i] for i in range(len(string1)))
        string2_reg = ".?".join(string2[i] for i in range(len(string2)))
        if re.search(string1_reg, string2) or re.search(string2_reg, string1):
            return True
        return False
