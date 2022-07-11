class Student:
    def __init__(self, _id, name, group):
        self.__id = _id
        self.__name = name
        self.__group = group

    @property
    def id(self):
        return self.__id

    @property
    def name(self):
        return self.__name

    @property
    def group(self):
        return self.__group


def test_student():
    stud = Student(456546, "Pizza", 916)
    assert stud.group == 916
    assert stud.name == "Pizza"
    assert stud.id == 456546


test_student()
