from src.domain.validators import DomainError


class Student:
    def __init__(self, student_id, name):
        self.__id = student_id
        self.validate_name(name)
        self.__name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    @staticmethod
    def validate_name(name):
        if name is None:
            raise DomainError("Student name should not be None")
        if name == "":
            raise DomainError("Student name should not be \"\"")
