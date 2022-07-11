# a5 - 3. Students

# from src.domain.students import Student
from src.repo.repository import Repository
from src.ui.ui import UI
from src.services.student_service import StudentService
from src.services.history_service import HistoryService

"""
    UI -> StudentService -> Repository -> students
       -> HistoryService -> Repository -> history
"""


stud_service = StudentService()
history_service = HistoryService()
ui = UI(stud_service, history_service)

ui.start()
