class Ship:
    def __init__(self, size, orientation, location):
        self.__size = size
        self.__orientation = ''
        self.__coordinates = location

        if orientation == 'horizontal' or orientation == 'vertical':
            self.__orientation = orientation
        else:
            raise ValueError("Value must be 'horizontal' or 'vertical'.")

    def get_coordinates(self):
        return self.__coordinates
