from src.repository.repository import RepositoryText
from src.service.flightService import FlightService
from src.ui.ui import UI

file_name = "input.txt"

repo = RepositoryText(file_name)
service = FlightService(repo)
ui = UI(service)

ui.start()
