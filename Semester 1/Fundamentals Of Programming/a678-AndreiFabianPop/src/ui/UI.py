class UI:
    def __init__(self, stud_serv, disc_serv, grade_serv, history_serv, test_flag=False):
        self.__stud_service = stud_serv
        self.__disc_service = disc_serv
        self.__grade_service = grade_serv
        self.__hist_service = history_serv
        self.__command_dict = {
            "add": self.UI_add,
            "remove": self.UI_remove,
            "update": self.UI_update,
            "list": self.UI_list,
            "search": self.UI_search,
            "statistics": self.UI_statistics,
            "undo": self.UI_undo,
            "redo": self.UI_redo
        }
        if test_flag is False:
            self.add_20_instances()

    def start(self):
        while True:
            self.print_options()
            user_choice = self.get_user_input()
            user_choice_list = user_choice.split()
            command = user_choice_list[0]
            params = user_choice_list[1:]
            if command == "exit":
                break
            elif command not in self.__command_dict:
                print("Unrecognized command")
            else:
                self.__command_dict[command](params)

    @staticmethod
    def print_options():
        print("add - adds new entry(student, discipline, grade)")
        print("remove - removes an entry(by id)")
        print("update - updates an entry(by id)")
        print("list - lists all entries(student, discipline, grade)")
        print("search - search by id, or name, has partial string matching")
        print("statistics - failing(students failing), best(best students), grades(disciplines with at least 1 grade)")
        print("undo - undoes the last operation")
        print("redo - redoes the last undone operation")
        print("exit - exist the program")

    @staticmethod
    def get_user_input():
        lower_words = "add remove update list exit student grade discipline".split()
        command = input("> ")
        command = command.strip()
        command_list = command.split()
        final_command = []
        final_command += [word.lower() if word.lower() in lower_words else word for word in command_list]
        command = " ".join(final_command)
        return command

    def UI_add(self, params):
        try:
            if 2 > len(params) < 4:
                raise ValueError
            if params[0] == "student":
                self.__stud_service.add_student(params[1], self.__hist_service)
                # self.__hist_service.add_expression("add", "student", params[1])
            elif params[0] == "discipline":
                self.__disc_service.add_discipline(params[1], self.__hist_service)
                # self.__hist_service.add_expression("add", "discipline", params[1])
            elif params[0] == "grade":
                self.__grade_service.add_grade(*params[1:], history_service=self.__hist_service)
                # self.__hist_service.add_expression("add", "grade", *params[1:])
            else:
                raise ValueError
        except ValueError:
            print("Invalid parameters\nSyntax: add (student, discipline, grade) (extra parameters eg. name)")

    def UI_remove(self, params):
        try:
            if len(params) != 2:
                raise ValueError
            if not params[1].isdigit():
                raise ValueError
            params[1] = int(params[1])
            if params[0] == "student":
                self.__hist_service.add_expression("del", "student", [params[1],
                                                   self.__stud_service.search_student_by_id(params[1]).name])
                self.__grade_service.delete_all_grades_of_student(params[1])
                self.__stud_service.delete_student(params[1])
            elif params[0] == "discipline":
                self.__hist_service.add_expression("del", "discipline", [params[1],
                                                   self.__disc_service.search_discipline_by_id(params[1]).name])
                self.__grade_service.delete_all_grades_of_discipline(params[1])
                self.__disc_service.delete_discipline(params[1])
            elif params[0] == "grade":
                grade = self.__grade_service.search_grade_by_id(params[1])
                self.__hist_service.add_expression("del", "grade",
                                                   [params[1], grade.discipline_id, grade.student_id, grade.grade])
                self.__grade_service.delete_grade(params[1])
            else:
                raise ValueError
        except ValueError:
            print("Invalid parameters")

    def UI_update(self, params):
        try:
            if len(params) != 3:
                raise ValueError
            if not params[1].isdigit():
                raise ValueError
            if params[0] == "student":
                self.__hist_service.add_expression("update", "student", [*params[1:]])
                self.__stud_service.update_student(*params[1:])
            elif params[0] == "discipline":
                self.__hist_service.add_expression("update", "discipline", [*params[1:]])
                self.__disc_service.update_discipline(*params[1:])
            else:
                raise ValueError
        except ValueError:
            print("Invalid parameters")

    def UI_list(self, params):
        try:
            if len(params) != 1:
                raise ValueError
            if params[0] == "student":
                for student in self.__stud_service.list_students():
                    self.print_student(*student)
            elif params[0] == "discipline":
                for discipline in self.__disc_service.list_disciplines():
                    self.print_discipline(*discipline)
            elif params[0] == "grade":
                for grade in self.__grade_service.list_grades():
                    self.print_grade(*grade)
            else:
                raise ValueError
        except ValueError:
            print("Invalid parameters")

    def UI_search(self, params):
        try:
            if params is None:
                raise ValueError
            if len(params) != 2:
                raise ValueError
            if params[0] == "student":
                if params[1].isdigit():
                    params[1] = int(params[1])
                    student_found = self.__stud_service.search_student_by_id(params[1])
                    if student_found is not False:
                        self.print_student(student_found.id, student_found.name)
                    else:
                        print("No student with this ID found.")
                else:
                    student_found = self.__stud_service.search_student_by_string(params[1])
                    if student_found is not False:
                        for student in student_found:
                            self.print_student(student.id, student.name)
                    else:
                        print("No student with this name found.")
            elif params[0] == "discipline":
                if params[1].isdigit():
                    params[1] = int(params[1])
                    discipline_found = self.__disc_service.search_discipline_by_id(params[1])
                    if discipline_found is not False:
                        self.print_discipline(discipline_found.id, discipline_found.name)
                    else:
                        print("No discipline with this Id found.")
                else:
                    discipline_found = self.__disc_service.search_discipline_by_string(params[1])
                    if discipline_found is not False:
                        for discipline in discipline_found:
                            self.print_discipline(discipline.id, discipline.name)
                    else:
                        print("No discipline with this name found.")
            else:
                raise ValueError
        except ValueError:
            print("Invalid parameters.")

    def UI_statistics(self, params):
        try:
            if params is None:
                raise ValueError
            if len(params) != 1:
                raise ValueError
            if params[0] == "failing":
                students_failing_list = self.__grade_service.generate_statistic_failing()
                for i in range(0, len(students_failing_list), 2):
                    self.print_failing(students_failing_list[i], students_failing_list[i+1])
            elif params[0] == "best":
                stud_grade_list, stud_id_list = self.__grade_service.generate_statistic_best()
                for i in range(len(stud_id_list)):
                    self.print_best(i, stud_id_list[i], stud_grade_list[i])
            elif params[0] == "grades":
                disc_grade_list, disc_id_list = self.__grade_service.generate_statistic_disciplines_with_grades()
                for i in range(len(disc_id_list)):
                    self.print_statistic_discipline(i, disc_id_list[i], disc_grade_list[i])
            else:
                raise ValueError
        except ValueError:
            print("Invalid parameters.")

    def UI_undo(self, _):
        self.__hist_service.undo()

    def UI_redo(self, _):
        self.__hist_service.redo()

    @staticmethod
    def print_student(_id, name):
        print("Student with ID", _id, "is named", name, end=".\n")

    @staticmethod
    def print_discipline(_id, name):
        print("Discipline with ID", _id, "is named", name, end=".\n")

    @staticmethod
    def print_grade(_id, student_id, discipline_id, grade_value):
        print("Grade with ID", _id, "from student with ID", student_id, "from discipline with ID", discipline_id,
              "has grade", grade_value, end=".\n")

    @staticmethod
    def print_failing(student, discipline):
        print("Student with ID", student, "is failing discipline with ID", discipline, end=".\n")

    @staticmethod
    def print_best(place_on_list, student_id, average):
        print("No. ", place_on_list+1, ": The student with ID ", student_id, " and average ", average, ".", sep="")

    @staticmethod
    def print_statistic_discipline(place_on_list, discipline_id, average):
        print("No. ", place_on_list+1, ": The discipline with ID ", discipline_id, " has all it\'s students averaging ",
              average, ".", sep="")

    def add_20_instances(self):
        self.UI_add("student Al".split())  # ID: 1
        self.UI_add("student Mike".split())  # ID: 2
        self.UI_add("student Andi".split())  # ID: 3
        self.UI_add("student Pink".split())  # ID: 4
        self.UI_add("student Vik".split())  # ID: 5
        self.UI_add("student Jack".split())  # ID: 6
        self.UI_add("discipline Algebra".split())  # ID: 1
        self.UI_add("discipline IT".split())  # ID: 2
        self.UI_add("discipline CSA".split())  # ID: 3
        self.UI_add("discipline Calculus".split())  # ID: 4
        self.UI_add("discipline Logic".split())  # ID: 5
        self.UI_add("discipline Sport".split())  # ID: 6
        self.UI_add("grade 1 1 6".split())  # ID: 1
        self.UI_add("grade 6 1 2".split())  # ID: 2
        self.UI_add("grade 4 3 9".split())  # ID: 3
        self.UI_add("grade 1 1 10".split())  # ID: 4
        self.UI_add("grade 2 4 9".split())  # ID: 5
        self.UI_add("grade 2 4 10".split())  # ID: 6
        self.UI_add("grade 5 6 10".split())  # ID: 7
        self.UI_add("grade 3 2 7".split())  # ID: 8
