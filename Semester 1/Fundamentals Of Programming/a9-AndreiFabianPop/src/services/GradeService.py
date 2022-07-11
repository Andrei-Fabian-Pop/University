from src.domain.Grade import Grade
from src.validators.Validators import GradeValidator


class GradeService:
    def __init__(self, grade_repo, stud_repo, disc_repo, test_flag=False):
        self.__grade_repo = grade_repo
        self.__stud_repo = stud_repo
        self.__disc_repo = disc_repo
        self.__test_flag = test_flag
        self.__validator = GradeValidator(stud_repo, disc_repo)

    def add_grade(self, _id, student_id, discipline_id, grade_value, history_service):
        """
        Validates a grade, creates the grade classObject, gives it a unique ID and adds it in the repository
        :param _id:
        :param history_service:
        :param student_id: int
        :param discipline_id: int
        :param grade_value: int
        :return: None
        """
        student_id = int(student_id)
        discipline_id = int(discipline_id)
        grade_value = int(grade_value)
        try:
            for item in self.__grade_repo.get_all():
                if int(_id) == int(item.id):
                    raise ValueError
            self.__grade_repo.add(Grade(_id, discipline_id, student_id, grade_value))
            history_service.add_expression("add", "grade", [_id, discipline_id, student_id, grade_value])
        except ValueError:
            print("This ID already exists.")
        else:
            raise ValueError

    def delete_grade(self, grade_id):
        """
        deletes the grade with given grade_id
        :param grade_id: int
        :return: None
        """
        self.__grade_repo.delete(grade_id)

    def list_grades(self):
        """
        :return: list of all the grades, the list contains the grade id, student id, discipline id, grade, grouped
        in another list
        """
        return [[grade.id, grade.student_id, grade.discipline_id, grade.grade] for grade in self.__grade_repo.get_all()]

    def search_grade_by_id(self, _id):
        grade_list = self.__grade_repo.get_all()
        for grade in grade_list:
            if int(grade.id) == _id:
                return grade
        return False

    def delete_all_grades_of_student(self, student_id):
        """
        deletes all the grades from the student with the id student_id
        :param student_id: int
        :return: None
        """
        all_grades = self.__grade_repo.get_all()
        for grade in all_grades:
            if grade.student_id == student_id:
                self.delete_grade(self.__grade_repo[grade.id].id)

    def delete_all_grades_of_discipline(self, discipline_id):
        """
        deletes all the grades from the discipline with the discipline id given in the Repository
        :param discipline_id: int
        :return: None
        """
        all_grades = self.__grade_repo.get_all()
        for grade in all_grades:
            if grade.discipline_id == discipline_id:
                self.delete_grade(self.__grade_repo[grade.id].id)

    def generate_statistic_failing(self):
        """
        Generates the list of Students that have the grade average lower than 5
        :return: list of student ids that have the grade lower than 5
        """
        grades_list = self.__grade_repo.get_all()
        stud_with_grade_list = []
        discipline_with_grades_list = []
        students_failing_list = []

        for grade in grades_list:
            if grade.student_id not in stud_with_grade_list:
                stud_with_grade_list.append(grade.student_id)
            if grade.discipline_id not in discipline_with_grades_list:
                discipline_with_grades_list.append(grade.discipline_id)

        for student_id in stud_with_grade_list:
            for discipline_id in discipline_with_grades_list:
                _sum = 0
                elements = 0
                for grade in grades_list:
                    if grade.student_id == student_id and grade.discipline_id == discipline_id:
                        _sum += grade.grade
                        elements += 1
                if elements != 0:
                    average = _sum/elements
                    if average < 5 and average != 0:
                        students_failing_list.append(student_id)
                        students_failing_list.append(discipline_id)

        return students_failing_list

    def generate_statistic_best(self):
        """
        Generates an ordered list of students and another ones containing the average grade of all average grades
        of each student
        :return: 2 lists, one with the grades and one with the ids of the students
        """
        grades_list = self.__grade_repo.get_all()
        stud_with_grade_list = []
        discipline_with_grades_list = []
        student_averages_list = []
        student_averages_list_id = []

        for grade in grades_list:
            if grade.student_id not in stud_with_grade_list:
                stud_with_grade_list.append(grade.student_id)
            if grade.discipline_id not in discipline_with_grades_list:
                discipline_with_grades_list.append(grade.discipline_id)

        for student_id in stud_with_grade_list:
            per_student_average = 0
            per_student_average_size = 0
            for discipline_id in discipline_with_grades_list:
                _sum = 0
                elements = 0
                for grade in grades_list:
                    if grade.student_id == student_id and grade.discipline_id == discipline_id:
                        _sum += grade.grade
                        elements += 1
                if elements != 0:
                    average = _sum/elements
                    per_student_average += average
                    per_student_average_size += 1
            if per_student_average_size != 0:
                student_averages_list_id.append(student_id)
                student_averages_list.append(per_student_average/per_student_average_size)

        result_id_list = [i for _, i in sorted(zip(student_averages_list, student_averages_list_id), reverse=True)]
        student_averages_list.sort(reverse=True)

        return student_averages_list, result_id_list

    def generate_statistic_disciplines_with_grades(self):
        """
        generate a list of the disciplines that have the best grade averages
        :return: tuple of 2 lists
        """
        grades_list = self.__grade_repo.get_all()
        stud_with_grade_list = []
        discipline_with_grades_list = []
        discipline_averages_list = []
        discipline_averages_list_id = []

        for grade in grades_list:
            if grade.student_id not in stud_with_grade_list:
                stud_with_grade_list.append(grade.student_id)
            if grade.discipline_id not in discipline_with_grades_list:
                discipline_with_grades_list.append(grade.discipline_id)

        for discipline_id in discipline_with_grades_list:
            per_discipline_average = 0
            per_discipline_average_size = 0
            for student_id in stud_with_grade_list:
                _sum = 0
                elements = 0
                for grade in grades_list:
                    if grade.student_id == student_id and grade.discipline_id == discipline_id:
                        _sum += grade.grade
                        elements += 1
                if elements != 0:
                    average = _sum / elements
                    per_discipline_average += average
                    per_discipline_average_size += 1
            if per_discipline_average_size != 0:
                discipline_averages_list_id.append(discipline_id)
                discipline_averages_list.append(per_discipline_average / per_discipline_average_size)

        result_id_list = \
            [i for _, i in sorted(zip(discipline_averages_list, discipline_averages_list_id), reverse=True)]
        discipline_averages_list.sort(reverse=True)

        return discipline_averages_list, result_id_list
