from src.repository.repository import Repository
from src.service.taxi_service import TaxiService
from src.ui.ui import UI

taxi_repo = Repository()

taxi_service = TaxiService(taxi_repo)

ui = UI(taxi_service)

if __name__ == "__main__":
    ui.start()

    ui.UI_add_ride()
