from src.domain.validators import DomainError


class Discipline:
    def __init__(self, discipline_id, name):
        self.validate_discipline_id(discipline_id)
        self.__id = int(discipline_id)
        self.validate_discipline_name(name)
        self.__name = name

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, new_name):
        self.__name = new_name

    @staticmethod
    def validate_discipline_id(_id):
        if not isinstance(_id, int):
            raise DomainError("Discipline ID should have only digits")
        if int(_id) < 1:
            raise DomainError("Discipline ID should be greater than 0")

    @staticmethod
    def validate_discipline_name(name):
        if name is None:
            raise DomainError("Discipline name should not be None")
        if name == "":
            raise DomainError("Discipline name should not be \"\"")
