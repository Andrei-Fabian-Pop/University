import re


class UI:
    def __init__(self, flight_service):
        self.__flight_service = flight_service
        self.__commands = {
            "exit": -1,
            "add": self.add_flight,
            "del": self.del_flight,
            "airports": self.list_airports,
            "noflight": self.no_flights,
        }

    @staticmethod
    def __print_commands():
        print("Commands: ")
        print("exit - exits the program")
        print("add - add a new flight")
        print("del - delete a flight")
        print("airports - list all airports in decreasing order of activity")

    def __get_user_input(self):
        user_input = input("> ")
        if user_input not in self.__commands:
            print("This is not a valid command.")
            return None
        else:
            return user_input

    def add_flight(self):
        try:
            _id = input("Enter an id: ")
            dep_city = input("Enter a departure city: ")
            dep_time = input("Enter a departure time(hh:mm): ")
            if not re.match("[0-2][0-4]:[0-5][0-9]$", dep_time.strip()):
                raise ValueError("Invalid input.")
            arr_city = input("Enter an arrival city: ")
            arr_time = input("Enter an arrival time: ")
            if not re.match("[0-2][0-4]:[0-5][0-9]$", arr_time.strip()):
                raise ValueError("Invalid input.")

            self.__flight_service.add(_id, dep_city, dep_time, arr_city, arr_time)
        except IndexError:
            print("ID is already taken.")
        except ValueError as ve:
            print(str(ve))

    def del_flight(self):
        user_input = input("Enter the flight ID: ")
        self.__flight_service.delete(user_input.strip())

    def list_airports(self):
        airports = self.__flight_service.get_airports()
        for airport in airports:
            for item in airport:
                print(f"{item} | {airport[item]}")

    def no_flights(self):
        flights = self.__flight_service.get_no_flights()

    def start(self):
        while True:
            self.__print_commands()
            user_input = self.__get_user_input()
            if user_input == "exit":
                break
            if user_input is not None:
                self.__commands[user_input]()
