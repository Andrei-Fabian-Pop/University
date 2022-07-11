from random import randint
from src.domain.taxi import Taxi


class TaxiService:
    def __init__(self, taxi_repo):
        self.__taxi_repo = taxi_repo

    def generate_taxi(self, _id):
        all_taxi = self.__taxi_repo.get_all()
        redo = True
        x, y = 0, 0

        while redo:
            redo = False
            x = randint(0, 100)
            y = randint(0, 100)

            for taxi in all_taxi:
                distance = abs(taxi.x - x) + abs(taxi.y - y)
                if distance < 5:
                    redo = True
                    break

        taxi = Taxi(_id, x, y)
        self.__taxi_repo.add(taxi)

    def add_ride(self, start_x, start_y, end_x, end_y):
        all_taxi = self.__taxi_repo.get_all()
        min_dist = 200  # max possible distance
        min_taxi_id = 0

        for taxi in all_taxi:
            if abs(taxi.x - start_x) + abs(taxi.y - start_y) < min_dist:
                min_dist = abs(taxi.x - start_x) + abs(taxi.y - start_y)
                min_taxi_id = taxi.id

        self.__taxi_repo[min_taxi_id].flare = abs(start_x-end_x) + abs(start_y-end_y)
        self.__taxi_repo[min_taxi_id].x = end_x
        self.__taxi_repo[min_taxi_id].y = end_y

        return [self.__taxi_repo[min_taxi_id].id,
                start_x, start_y, end_x, end_y,
                self.__taxi_repo[min_taxi_id].flare]

    def simulate_ride(self):
        redo = True
        start_x, start_y, end_x, end_y = 0, 0, 0, 0

        while redo:
            redo = False
            start_x = randint(0, 100)
            start_y = randint(0, 100)
            end_x = randint(0, 100)
            end_y = randint(0, 100)

            if abs(start_x-end_x) + abs(start_y-end_y) < 10:
                redo = True

        return self.add_ride(start_x, start_y, end_x, end_y)

    def generate_situation(self):
        all_taxi = self.__taxi_repo.get_all()
        result = []
        for taxi in all_taxi:
            result.append([taxi.id, taxi.x, taxi.y, taxi.flare])

        return sorted(result, key=lambda x: x[-1])
