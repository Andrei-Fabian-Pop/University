class Flight:
    def __init__(self, _id, dep_city, dep_time, arr_city, arr_time):
        self.__id = _id
        self.__dep_city = dep_city
        self.__dep_time = dep_time
        self.__arr_city = arr_city
        self.__arr_time = arr_time

    @property
    def id(self):
        return self.__id

    @property
    def dep_city(self):
        return self.__dep_city

    @property
    def dep_time(self):
        return self.__dep_time

    @property
    def arr_city(self):
        return self.__arr_city

    @property
    def arr_time(self):
        return self.__arr_time
