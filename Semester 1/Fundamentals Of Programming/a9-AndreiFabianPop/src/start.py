# 1. Students Register Management
"""

@author: Pop Andrei-Fabian

"""
from src.repository.Repository import Repository, textFileRepository, binFileRepository
from src.ui.UI import UI
from src.services.StudentService import StudentService
from src.services.DisciplineService import DisciplineService
from src.services.GradeService import GradeService
from src.services.HistoryService import HistoryService

filepath = "settings.properties"
comment_char = '#'
sep = "="
properties = {}

with open(filepath, "rt") as f:
    for line in f:
        l: str = line.strip()
        if l and not l.startswith(comment_char):
            key_value = l.split(sep)
            key = key_value[0].strip()
            value = sep.join(key_value[1:]).strip().strip('"')
            properties[key] = value

if properties["repository"] == "inmemory":
    student_repo = Repository()
    discipline_repo = Repository()
    grade_repo = Repository()
elif properties["repository"] == "textfiles":
    student_repo = textFileRepository(properties["students"], "Student")
    discipline_repo = textFileRepository(properties["disciplines"], "Discipline")
    grade_repo = textFileRepository(properties["grades"], "Grade")
elif properties["repository"] == "binaryfiles":
    student_repo = binFileRepository(properties["students"], "Student")
    discipline_repo = binFileRepository(properties["disciplines"], "Discipline")
    grade_repo = binFileRepository(properties["grades"], "Grade")
else:
    print("No valid repository type found. Selected \"inmemory\" type.")
    student_repo = Repository()
    discipline_repo = Repository()
    grade_repo = Repository()

student_service = StudentService(student_repo)
discipline_service = DisciplineService(discipline_repo)
grade_service = GradeService(grade_repo, student_repo, discipline_repo)
history_service = HistoryService(student_repo, discipline_repo, grade_repo)

ui = UI(student_service, discipline_service, grade_service, history_service, test_flag=True)
ui.start()
