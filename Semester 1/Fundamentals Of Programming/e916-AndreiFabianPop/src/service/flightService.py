import unittest

from src.domain.flight import Flight
from src.repository.repository import RepositoryText


class FlightService:
    def __init__(self, repo):
        self.__repo = repo

    def add(self, _id, dep_city, dep_time, arr_city, arr_time):
        """
        Creates a Flight object with the given variables and stores it in self__repo
        :param _id: id
        :param dep_city: departure city
        :param dep_time: departure time
        :param arr_city: arrival city
        :param arr_time: arrival time
        :return: None
        """
        flights = self.__repo.get_all()
        # no more than 1 flight per minute
        for flight in flights:
            if flight.dep_time == dep_time or flight.arr_time == arr_time:
                raise ValueError("The airport can only handle a single arrive or departure per minute.")

        # flights between 15 and 90 minutes
        dep_in_min = int(dep_time[0]) * 600 + int(dep_time[1]) * 60 + int(dep_time[3]) * 10 + int(dep_time[4])
        arr_in_min = int(arr_time[0]) * 600 + int(arr_time[1]) * 60 + int(arr_time[3]) * 10 + int(arr_time[4])

        if arr_in_min - dep_in_min > 90:
            raise ValueError("The flight time is above 90 minutes")
        if arr_in_min - dep_in_min < 15:
            raise ValueError("The flight time is below 15 minutes")

        self.__repo.add(_id, Flight(_id, dep_city, dep_time, arr_city, arr_time))

    def delete(self, _id):
        """
        Deletes an existing flight from self.__repo by its ID
        :param _id: id
        :return: None
        """
        try:
            self.__repo.delete(_id)
        except IndexError:
            print("The ID does not exist.")

    def get_airports(self):
        """
        sorts the airports in order of activity
        :return: sorted list of airport disctionaries, {{airport:flight_num}, ...}
        """
        flights = []
        airports_list = {}
        flights_packed = self.__repo.get_all()
        for flight in flights_packed:
            if flight.dep_city not in flights:
                flights.append(flight.dep_city)
                airports_list[flight.dep_city] = 1
            else:
                airports_list[flight.dep_city] += 1

            if flight.arr_city not in flights:
                flights.append(flight.arr_city)
                airports_list[flight.arr_city] = 1
            else:
                airports_list[flight.arr_city] += 1

        return [{item: airports_list[item]}
                for item in sorted(airports_list, key=lambda x: airports_list[x], reverse=True)]

    def get_no_flights(self):
        flights_packed = self.__repo.get_all()
        for flight in flights_packed:
            pass


class FlightServiceTest(unittest.TestCase):
    def setUp(self) -> None:
        pass

    def tearDown(self) -> None:
        pass

    def test_add_good(self):
        repo = RepositoryText("", test_flag=True)
        serv = FlightService(repo)
        serv.add("RO650", "Cluj", "05:45", "Bucuresti", "06:40")

        self.assertEqual(repo.get_all()[0].dep_city, "Cluj")

    def test_add_id_taken(self):
        repo = RepositoryText("", test_flag=True)
        serv = FlightService(repo)
        serv.add("RO650", "Cluj", "05:45", "Bucuresti", "06:40")

        with self.assertRaises(IndexError) as err:
            serv.add("RO650", "Cluj", "05:48", "Bucuresti", "06:41")
        self.assertEqual(str(err.exception), "ID is already taken.")

    def test_add_same_time(self):
        repo = RepositoryText("", test_flag=True)
        serv = FlightService(repo)
        serv.add("RO650", "Cluj", "05:45", "Bucuresti", "06:40")

        with self.assertRaises(ValueError) as err:
            serv.add("RO651", "Cluj", "05:45", "Bucuresti", "06:40")
        self.assertEqual(str(err.exception), "The airport can only handle a single arrive or departure per minute.")

    def test_add_above_90_mins(self):
        repo = RepositoryText("", test_flag=True)
        serv = FlightService(repo)
        serv.add("RO650", "Cluj", "05:45", "Bucuresti", "06:40")

        with self.assertRaises(ValueError) as err:
            serv.add("RO651", "Cluj", "05:46", "Bucuresti", "16:41")
        self.assertEqual(str(err.exception), "The flight time is above 90 minutes")

    def test_add_below_15_mins(self):
        repo = RepositoryText("", test_flag=True)
        serv = FlightService(repo)
        serv.add("RO650", "Cluj", "05:45", "Bucuresti", "06:40")

        with self.assertRaises(ValueError) as err:
            serv.add("RO651", "Cluj", "05:46", "Bucuresti", "05:50")
        self.assertEqual(str(err.exception), "The flight time is below 15 minutes")

    def test_del(self):
        repo = RepositoryText("", test_flag=True)
        serv = FlightService(repo)
        serv.add("RO650", "Cluj", "05:45", "Bucuresti", "06:40")
        serv.delete("RO650")
        self.assertEqual(repo.get_all(), [])
