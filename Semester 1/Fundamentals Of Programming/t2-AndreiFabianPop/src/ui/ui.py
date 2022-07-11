class UI:
    def __init__(self, taxi_service):
        self.__taxi_service = taxi_service
        self.__operational_taxi = 0
        self.__command_dict = {
            "1": self.UI_add_ride,
            "2": self.simulate_rides
        }

    def start(self):
        self.__operational_taxi = int(input("Please enter then number of operational taxis:\n> "))

        for i in range(self.__operational_taxi):
            self.__taxi_service.generate_taxi(i)

        while True:
            self.prompt()
            user_input = input("> ")

            # basic check of input
            if user_input != "1" and user_input != "2":
                print("Invalid inputs. Program terminated.")
            else:
                self.__command_dict[user_input]()

            self.print_situation()

    def UI_add_ride(self):
        start_x = int(input("Enter the start of the ride, x coordinate: "))
        start_y = int(input("Enter the start of the ride, y coordinate: "))
        end_x = int(input("Enter the end of the ride, x coordinate: "))
        end_y = int(input("Enter the end of the ride, y coordinate: "))

        ride_details = self.__taxi_service.add_ride(start_x, start_y, end_x, end_y)
        self.print_ride_details(ride_details)

    def simulate_rides(self):
        rides_num = int(input("Enter the amount of rides to be simulated: "))

        for i in range(rides_num):
            ride_details = self.__taxi_service.simulate_ride()
            self.print_ride_details(ride_details)

    def print_situation(self):
        situation_list = self.__taxi_service.generate_situation()
        for sit in situation_list:
            self.print_situation_details(sit)

    @staticmethod
    def print_situation_details(details):
        str(details[0]).ljust(20, " ")
        str(details[1:]).rjust(20, " ")

    @staticmethod
    def print_ride_details(ride_details):
        print(f"The taxi {ride_details[0]} picked up a ride ar coordinates ({ride_details[1]},{ride_details[2]})"
              f", and is now located at coordinates ({ride_details[3]}, {ride_details[4]}), having a total flare"
              f" of {ride_details[5]}.")

    @staticmethod
    def prompt():
        print("Enter 1 to manually enter ride.")
        print("Enter 2 to simulate given number of rides")
