class Taxi:
    def __init__(self, _id, x, y, flare=0):
        self.__id = _id
        self.__x = x
        self.__y = y
        self.__flare = flare

    @property
    def id(self):
        return self.__id

    @property
    def x(self):
        return self.__x

    @x.setter
    def x(self, value):
        self.__x = value

    @property
    def y(self):
        return self.__y

    @y.setter
    def y(self, value):
        self.__y = value

    @property
    def flare(self):
        return self.__flare

    @flare.setter
    def flare(self, value):
        self.__flare += value
