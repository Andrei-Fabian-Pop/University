import unittest

from src.domain.Discipline import Discipline
from src.domain.Grade import Grade
from src.domain.Student import Student
from src.domain.validators import DomainError
from src.repository.Repository import Repository, RepositoryException
from src.services.DisciplineService import DisciplineService
from src.services.HistoryService import HistoryService, HistoryException
from src.services.StudentService import StudentService
from src.services.GradeService import GradeService


class StudentTest(unittest.TestCase):
    def setUp(self) -> None:
        self.stud = Student(1, "Al")

    def tearDown(self) -> None:
        pass

    def testStudent(self):
        self.assertEqual(self.stud.id, 1)
        self.assertEqual(self.stud.name, "Al")
        self.stud.name = "Mik"
        self.assertEqual(self.stud.name, "Mik")

    def testNameNoneError(self):
        with self.assertRaises(DomainError) as err:
            Student(1, None)
        self.assertEqual(str(err.exception), "Student name should not be None")

    def testNameEmptyError(self):
        with self.assertRaises(DomainError) as err:
            Student(1, "")
        self.assertEqual(str(err.exception), "Student name should not be \"\"")


class DisciplineTest(unittest.TestCase):
    def setUp(self) -> None:
        self.discipline = Discipline(255, "Computer Science")

    def tearDown(self) -> None:
        pass

    def testDiscipline(self):
        self.assertEqual(self.discipline.id, 255)
        self.assertEqual(self.discipline.name, "Computer Science")
        self.discipline.name = "Comp Sci"
        self.assertEqual(self.discipline.name, "Comp Sci")

    def testDisciplineIdNotInt(self):
        with self.assertRaises(DomainError) as err:
            Discipline("1", "CS")
        self.assertEqual(str(err.exception), "Discipline ID should have only digits")

    def testDisciplineIdLessThanOne(self):
        with self.assertRaises(DomainError) as err:
            Discipline(-1, "CS")
        self.assertEqual(str(err.exception), "Discipline ID should be greater than 0")

    def testDisciplineNameNotNone(self):
        with self.assertRaises(DomainError) as err:
            Discipline(1, None)
        self.assertEqual(str(err.exception), "Discipline name should not be None")

    def testDisciplineNameNotEmpty(self):
        with self.assertRaises(DomainError) as err:
            Discipline(1, "")
        self.assertEqual(str(err.exception), "Discipline name should not be \"\"")


class GradeTest(unittest.TestCase):
    def setUp(self) -> None:
        self.grade = Grade(21, 45, 1, 6)

    def tearDown(self) -> None:
        pass

    def testGrade(self):
        self.assertEqual(self.grade.id, 21)
        self.assertEqual(self.grade.discipline_id, 45)
        self.assertEqual(self.grade.student_id, 1)
        self.assertEqual(self.grade.grade, 6)

        self.grade.discipline_id = 22
        self.grade.student_id = 2
        self.grade.grade = 4.6

        self.assertEqual(self.grade.discipline_id, 22)
        self.assertEqual(self.grade.student_id, 2)
        self.assertEqual(self.grade.grade, 4.6)

    def testGradeIntStudId(self):
        with self.assertRaises(DomainError) as err:
            Grade(1, 1, "1", 1)
        self.assertEqual(str(err.exception), "Student id should be a number in order to create grade object")

    def testGradeIntDiscId(self):
        with self.assertRaises(DomainError) as err:
            Grade(1, "1", 1, 1)
        self.assertEqual(str(err.exception), "Discipline id should be a number in order to create grade object")

    def testGradeIntGradeId(self):
        with self.assertRaises(DomainError) as err:
            Grade(1, 1, 1, "1")
        self.assertEqual(str(err.exception), "Grade value should be a number in order to create grade object")


class RepositoryTest(unittest.TestCase):
    def setUp(self) -> None:
        self._repo = Repository()

    def tearDown(self) -> None:
        pass

    def test_repo_get(self):
        self._repo.add(Student(1, "Al"))
        self.assertEqual(self._repo[1].name, "Al")

    def test_id_exist(self):
        with self.assertRaises(RepositoryException) as err:
            _ = self._repo[100]
        self.assertEqual(str(err.exception), "Error. This ID does not exist.")

    def test_empty_repo(self):
        self.assertEqual(len(self._repo), 0)

    def test_repo_get_all(self):
        self._repo.add(Student(1, "Al"))
        self._repo.add(Student(2, "Mik"))
        self.assertEqual(self._repo.get_all()[0].id, 1)
        self.assertEqual(self._repo.get_all()[0].name, "Al")
        self.assertEqual(self._repo.get_all()[1].id, 2)
        self.assertEqual(self._repo.get_all()[1].name, "Mik")

    def test_repo_add_instance(self):
        self._repo.add(Student(1, "Al"))
        self.assertEqual(len(self._repo), 1)

    def test_repo_add_existing_id(self):
        self._repo.add(Student(1, "Al"))
        with self.assertRaises(RepositoryException) as err:
            self._repo.add(Student(1, "Mik"))
        self.assertEqual(str(err.exception), "Error. This id is already taken 1")

    def test_repo_delete_non_existing_id(self):
        with self.assertRaises(RepositoryException) as err:
            self._repo.delete(1)
        self.assertEqual(str(err.exception), "Error. This id does not exist")

    def test_repo_update(self):
        self._repo.add(Student(1, "Al"))
        self._repo.update(1, Student(1, "Mik"))
        self.assertEqual(self._repo[1].id, 1)
        self.assertEqual(self._repo[1].name, "Mik")

    def test_repo_update_no_id(self):
        with self.assertRaises(RepositoryException) as err:
            self._repo.update(100, Student(100, "Mik"))
        self.assertEqual(str(err.exception), "Error. This id does not exist")

    def test_repo_update_diff_id(self):
        self._repo.add(Student(1, "Al"))
        with self.assertRaises(RepositoryException) as err:
            self._repo.update(1, Student(2, "Mik"))
        self.assertEqual(str(err.exception), "Error. The id\'s are not the same")

    def test_repository(self):
        student = Student(1, "Al")
        self._repo.add(student)
        self._repo.add(Student(2, "Mik"))

        self.assertEqual(len(self._repo), 2)

        with self.assertRaises(RepositoryException) as re:
            _ = self._repo[3]
        self.assertEqual(str(re.exception), "Error. This ID does not exist.")

        self._repo.delete(2)
        self.assertEqual(len(self._repo), 1)

        with self.assertRaises(RepositoryException):
            _ = self._repo[2]


class StudentServiceTest(unittest.TestCase):
    def setUp(self) -> None:
        self._stud_serv = StudentService(Repository())
        self.__history_service = HistoryService(Repository(), Repository(), Repository())

    def tearDown(self) -> None:
        pass

    def test_add_student(self):
        self._stud_serv.add_student("Mik", self.__history_service)
        self._stud_serv.add_student("Al", self.__history_service)
        self.assertEqual(self._stud_serv.list_students(), [[1, "Mik"], [2, "Al"]])
        self._stud_serv.delete_student(1)
        self._stud_serv.add_student("Mikey", self.__history_service)
        self.assertEqual(self._stud_serv.list_students(), [[2, "Al"], [1, "Mikey"]])

    def test_delete_student(self):
        self._stud_serv.add_student("Mik", self.__history_service)
        self._stud_serv.add_student("Al", self.__history_service)
        self._stud_serv.delete_student(1)
        self.assertEqual(self._stud_serv.list_students(), [[2, "Al"]])

    def test_update_student(self):
        self._stud_serv.add_student("Mik", self.__history_service)
        self._stud_serv.add_student("Al", self.__history_service)
        self._stud_serv.update_student(2, "Miguel")
        self.assertEqual(self._stud_serv.list_students(), [[1, "Mik"], [2, "Miguel"]])

    def test_search_by_id(self):
        self._stud_serv.add_student("Mik", self.__history_service)
        self._stud_serv.add_student("Al", self.__history_service)
        self.assertEqual(self._stud_serv.search_student_by_id(1).name, "Mik")
        self.assertEqual(self._stud_serv.search_student_by_id(1).id, 1)
        self.assertEqual(self._stud_serv.search_student_by_id(7), False)

    def test_search_by_string(self):
        self._stud_serv.add_student("Mik", self.__history_service)
        self.assertEqual(self._stud_serv.search_student_by_string("Maik")[0].name, "Mik")
        self.assertEqual(self._stud_serv.search_student_by_string("Maik")[0].id, 1)
        self.assertEqual(self._stud_serv.search_student_by_string("Mi")[0].id, 1)
        self.assertEqual(self._stud_serv.search_student_by_string("L"), False)


class DisciplineUnitTest(unittest.TestCase):
    def setUp(self) -> None:
        self._disc_serv = DisciplineService(Repository())
        self.__history_service = HistoryService(Repository(), Repository(), Repository())

    def tearDown(self) -> None:
        pass

    def test_add_discipline(self):
        self._disc_serv.add_discipline("Math", self.__history_service)
        self._disc_serv.add_discipline("Comp Sci", self.__history_service)
        self.assertEqual(self._disc_serv.list_disciplines(), [[1, "Math"], [2, "Comp Sci"]])
        self._disc_serv.delete_discipline(1)
        self._disc_serv.add_discipline("Better Math", self.__history_service)
        self.assertEqual(self._disc_serv.list_disciplines(), [[2, 'Comp Sci'], [1, 'Better Math']])

    def test_delete_discipline(self):
        self._disc_serv.add_discipline("Math", self.__history_service)
        self._disc_serv.add_discipline("Comp Sci", self.__history_service)
        self._disc_serv.delete_discipline(1)
        self.assertEqual(self._disc_serv.list_disciplines(), [[2, "Comp Sci"]])

    def test_update_discipline(self):
        self._disc_serv.add_discipline("Math", self.__history_service)
        self._disc_serv.add_discipline("Comp Sci", self.__history_service)
        self._disc_serv.update_discipline(2, "English")
        self.assertEqual(self._disc_serv.list_disciplines(), [[1, "Math"], [2, "English"]])

    def test_search_by_id(self):
        self._disc_serv.add_discipline("Math", self.__history_service)
        self._disc_serv.add_discipline("Comp Sci", self.__history_service)
        self.assertEqual(self._disc_serv.search_discipline_by_id(1).name, "Math")
        self.assertEqual(self._disc_serv.search_discipline_by_id(1).id, 1)
        self.assertEqual(self._disc_serv.search_discipline_by_id(7), False)

    def test_search_by_string(self):
        self._disc_serv.add_discipline("Math", self.__history_service)
        self.assertEqual(self._disc_serv.search_discipline_by_string("Mat")[0].name, "Math")
        self.assertEqual(self._disc_serv.search_discipline_by_string("Mat")[0].id, 1)
        self.assertEqual(self._disc_serv.search_discipline_by_string("Mth")[0].name, "Math")
        self.assertEqual(self._disc_serv.search_discipline_by_string("k"), False)


class GradesUnitTest(unittest.TestCase):
    def setUp(self) -> None:
        self._grade_serv = GradeService(Repository(), Repository(), Repository(), test_flag=True)
        self.__stud_serv = StudentService(Repository())
        self.__disc_serv = DisciplineService(Repository())
        self.__history_service = HistoryService(Repository(), Repository(), Repository())

    def tearDown(self) -> None:
        pass

    def test_add_grade(self):
        self.__stud_serv.add_student("test1", self.__history_service)
        self.__stud_serv.add_student("test2", self.__history_service)
        self.__disc_serv.add_discipline("Math", self.__history_service)
        self._grade_serv.add_grade(1, 1, 6, self.__history_service)
        self._grade_serv.add_grade(2, 1, 5, self.__history_service)
        self.assertEqual(self._grade_serv.list_grades(), [[1, 1, 1, 6], [2, 2, 1, 5]])
        self._grade_serv.delete_grade(1)
        self._grade_serv.add_grade(1, 1, 7, self.__history_service)
        self.assertEqual(self._grade_serv.list_grades(), [[2, 2, 1, 5], [1, 1, 1, 7]])

    def test_delete_grade(self):
        self._grade_serv.add_grade(2, 45, 6, self.__history_service)
        self._grade_serv.add_grade(2, 13, 5, self.__history_service)
        self._grade_serv.delete_grade(1)
        self.assertEqual(self._grade_serv.list_grades(), [[2, 2, 13, 5]])

    def test_delete_all_grades_of_student(self):
        self._grade_serv.add_grade(2, 45, 6, self.__history_service)
        self._grade_serv.add_grade(2, 13, 5, self.__history_service)
        self._grade_serv.delete_all_grades_of_student(2)
        self.assertEqual(self._grade_serv.list_grades(), [])

    def test_delete_all_grades_of_discipline(self):
        self._grade_serv.add_grade(2, 45, 6, self.__history_service)
        self._grade_serv.add_grade(3, 45, 5, self.__history_service)
        self._grade_serv.delete_all_grades_of_discipline(45)
        self.assertEqual(self._grade_serv.list_grades(), [])

    def test_search_grade_by_id(self):
        self._grade_serv.add_grade(2, 45, 6, self.__history_service)
        self.assertEqual(self._grade_serv.search_grade_by_id(1).student_id, 2)
        self.assertEqual(self._grade_serv.search_grade_by_id(1).discipline_id, 45)
        self.assertEqual(self._grade_serv.search_grade_by_id(1).grade, 6)
        self.assertEqual(self._grade_serv.search_grade_by_id(2), False)

    def test_statistics_failing(self):
        self._grade_serv.add_grade(2, 45, 6, self.__history_service)
        self._grade_serv.add_grade(3, 11, 3, self.__history_service)
        self._grade_serv.add_grade(2, 45, 2, self.__history_service)
        self.assertEqual(self._grade_serv.generate_statistic_failing(), [2, 45, 3, 11])

    def test_statistics_best(self):
        self._grade_serv.add_grade(2, 45, 7, self.__history_service)
        self._grade_serv.add_grade(3, 11, 9, self.__history_service)
        self._grade_serv.add_grade(3, 45, 10, self.__history_service)
        self._grade_serv.add_grade(2, 45, 10, self.__history_service)
        self.assertEqual(self._grade_serv.generate_statistic_best(), ([9.5, 8.5], [3, 2]))

    def test_statistics_disciplines_w_grades(self):
        self._grade_serv.add_grade(2, 45, 7, self.__history_service)
        self._grade_serv.add_grade(3, 11, 9, self.__history_service)
        self._grade_serv.add_grade(3, 45, 10, self.__history_service)
        self._grade_serv.add_grade(2, 45, 10, self.__history_service)
        self.assertEqual(self._grade_serv.generate_statistic_disciplines_with_grades(), ([9.25, 9.0], [45, 11]))


class UndoRedoUnitTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__stud_repo = Repository()
        self.__disc_repo = Repository()
        self.__grade_repo = Repository()
        self.__history_service = HistoryService(self.__stud_repo, self.__disc_repo, self.__grade_repo)

    def tearDown(self) -> None:
        pass

    def testInvertAddDel(self):
        self.assertEqual(self.__history_service.invert_add_del("add", 1), ("del", 1))
        self.assertEqual(self.__history_service.invert_add_del("del", 1), ("add", 1))

    def testInvertUpdate(self):
        self.__stud_repo.add(Student(1, "Mike"))
        self.__disc_repo.add(Discipline(1, "Gabi Hour"))
        self.assertEqual(self.__history_service.invert_update("update", "student", [1, "Al"]), ('update', [1, 'Mike']))
        self.assertEqual(
            self.__history_service.invert_update("update", "discipline", [1, "FP"]), ('update', [1, "Gabi Hour"]))

    def testUndo(self):
        with self.assertRaises(HistoryException) as err:
            self.__history_service.redo()
        self.assertEqual(str(err.exception), "Nothing left to redo.")

        with self.assertRaises(HistoryException) as err:
            self.__history_service.undo()
        self.assertEqual(str(err.exception), "Nothing left to undo.")

        self.__stud_repo.add(Student(1, "Ali"))
        self.__disc_repo.add(Discipline(1, "MatLab"))
        self.__grade_repo.add(Grade(1, 2, 3, 4))

        self.__history_service.add_expression("add", "student", [1, "Al"])
        self.__history_service.undo()

        self.__history_service.add_expression("add", "discipline", [1, "Math"])
        self.__history_service.undo()

        self.__history_service.add_expression("add", "grade", [1, 2, 3, 4])
        self.__history_service.undo()

        self.__history_service.add_expression("del", "student", [1, "Al"])
        self.__history_service.undo()

        self.__history_service.add_expression("del", "discipline", [1, "Math"])
        self.__history_service.undo()

        self.__history_service.add_expression("del", "grade", [1, 2, 3, 4])
        self.__history_service.undo()

        self.__history_service.add_expression("update", "student", [1, "Al"])
        self.__history_service.undo()

        self.__history_service.add_expression("update", "discipline", [1, "Math"])
        self.__history_service.undo()
        self.__history_service.redo()
