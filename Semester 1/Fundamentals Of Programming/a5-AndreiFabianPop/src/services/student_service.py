from src.repo.repository import Repository
from src.domain.students import Student
# from src.services.history_service import HistoryService


class StudentService:
    def __init__(self, test_flag=False):
        self.__stud_repo = Repository()
        self.__stud_id_list = list()
        if test_flag is False:
            self.initialize_with_students()

    def initialize_with_students(self):
        self.add_student(Student(112,   "Ala",        900))
        self.add_student(Student(145,   "Bala",       900))
        self.add_student(Student(456,   "Portocala",  900))
        self.add_student(Student(789,   "Sa",         900))
        self.add_student(Student(123,   "Intalnit",   916))
        self.add_student(Student(753,   "In",         916))
        self.add_student(Student(159,   "Cos",        786))
        self.add_student(Student(41,    "Cu",         256))
        self.add_student(Student(8,     "Para",       456))
        self.add_student(Student(15968, "Alimentara", 916))

    def add_student(self, student, history_service=None):
        """
        adds a student entity to the stud_repo repository
        :param student: student class
        :param history_service: repository for undo functionality
        :return:
        """
        if self.__stud_repo.is_in_repo(student):
            print("upsie")
        self.__stud_repo.add(student)
        self.__stud_id_list.append(student.id)
        if history_service is not None:
            history_service.add_operation(student, "add")
            history_service.next_step()

    def delete_student(self, student):
        """
        deletes the specified student(class) from stud_repo
        :param student: student class
        :return:
        """
        self.__stud_repo.delete(student)
        self.__stud_id_list.remove(student.id)

    def delete_by_group(self, group_number, history_service):
        """
        cycles through __stud_id_list(list of students id) and when the group is the same with group_number,
        it calls delete_student() and deletes the entity
        :param group_number: int - group number
        :param history_service: repository for undo functionality
        :return:
        """
        recheck = True
        while recheck:
            recheck = False
            for student_id in self.__stud_id_list:
                if self.__stud_repo[student_id].group == group_number:
                    recheck = True
                    history_service.add_operation(self.__stud_repo[student_id], "del")
                    self.delete_student(self.__stud_repo[student_id])
        history_service.next_step()

    def list_all_students(self):
        """
        returns a list of all students by cycling through __stud_id_list(list of students id)
        :return:
        """
        student_list = list()
        for _id in self.__stud_id_list:
            student_list.append(Student(_id, self.__stud_repo[_id].name, self.__stud_repo[_id].group))
        return student_list


def test_student_service():
    test_students = StudentService(test_flag=True)
    stud = Student(1, "test", 916)
    test_students.add_student(stud, None)
    assert test_students.list_all_students()[0].id == stud.id
    assert test_students.list_all_students()[0].name == stud.name
    assert test_students.list_all_students()[0].group == stud.group
    test_students.delete_student(stud)
    assert test_students.list_all_students() == []


test_student_service()
