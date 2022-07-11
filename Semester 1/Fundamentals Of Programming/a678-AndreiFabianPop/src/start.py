# 1. Students Register Management
"""

@author: Pop Andrei-Fabian

"""
from src.repository.Repository import Repository
from src.ui.UI import UI
from src.services.StudentService import StudentService
from src.services.DisciplineService import DisciplineService
from src.services.GradeService import GradeService
from src.services.HistoryService import HistoryService

student_repo = Repository()
discipline_repo = Repository()
grade_repo = Repository()

student_service = StudentService(student_repo)
discipline_service = DisciplineService(discipline_repo)
grade_service = GradeService(grade_repo, student_repo, discipline_repo)
history_service = HistoryService(student_repo, discipline_repo, grade_repo)

ui = UI(student_service, discipline_service, grade_service, history_service)
ui.start()
