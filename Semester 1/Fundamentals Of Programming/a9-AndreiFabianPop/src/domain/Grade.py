from src.domain.validators import DomainError


class Grade:
    def __init__(self, _id, discipline_id, student_id, grade_value):
        self.__id = int(_id)
        self.__discipline_id = int(discipline_id)
        self.validate_discipline_id(self.__discipline_id)

        self.__student_id = int(student_id)
        self.validate_student_id(self.__student_id)

        self.__grade_value = int(grade_value)
        self.validate_grade_value(self.__grade_value)

    @property
    def id(self):
        return self.__id

    @property
    def discipline_id(self):
        return self.__discipline_id

    @discipline_id.setter
    def discipline_id(self, value):
        self.__discipline_id = value

    @property
    def student_id(self):
        return self.__student_id

    @student_id.setter
    def student_id(self, value):
        self.__student_id = value

    @property
    def grade(self):
        return self.__grade_value

    @grade.setter
    def grade(self, value):
        self.__grade_value = value

    @staticmethod
    def validate_student_id(_id):
        if not isinstance(_id, int):
            raise DomainError("Student id should be a number in order to create grade object")

    @staticmethod
    def validate_discipline_id(_id):
        if not isinstance(_id, int):
            raise DomainError("Discipline id should be a number in order to create grade object")

    @staticmethod
    def validate_grade_value(grade):
        if not isinstance(grade, int):
            raise DomainError("Grade value should be a number in order to create grade object")
