

class GradeValidator:
    def __init__(self, stud_repo, disc_repo):
        self.__stud_repo = stud_repo
        self.__disc_repo = disc_repo

    def validate_grade(self, grade):
        valid_stud, valid_discipline = False, False
        all_stud = self.__stud_repo.get_all()
        all_disc = self.__disc_repo.get_all()
        for stud in all_stud:
            if grade.student_id == stud.id:
                valid_stud = True
        for disc in all_disc:
            if grade.discipline_id == disc.id:
                valid_discipline = True
        return valid_stud and valid_discipline
