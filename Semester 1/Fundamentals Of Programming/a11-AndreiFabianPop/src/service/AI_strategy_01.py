from random import randint


class Strategy_01:
    def __init__(self, board_size):
        self.__board_size = board_size
        self.__critical_point = (-1, -1)
        self.__direction_dict = {
            "Right": (0, -1),
            "Left": (0, 1),
            "Up": (-1, 0),
            "Down": (1, 0)
        }
        self.__direction_test = "Right"
        self.__direction = "None"  # Right, Left, Up, Down
        self.__guesses_list = []
        self.__confused = False

    def miss(self):
        if len(self.__guesses_list) >= 2:
            self.__critical_point = self.__guesses_list[-2]
        else:
            self.__critical_point = (-1, -1)
        self.__direction = "None"

    def crit(self, row, col):
        if self.__critical_point == (-1, -1):
            self.__critical_point = (row, col)
        else:
            self.__direction = self.__direction_test

    def destroyed(self):
        self.__critical_point = (-1, -1)
        self.__direction_test = "Right"
        self.__direction = "None"

    def turn(self):
        if self.__confused:
            self.__confused = False
            self.__critical_point = (-1, -1)
            self.__direction = "None"
            self.__direction_test = "Right"
        while self.__critical_point == (-1, -1):
            guess = (randint(1, self.__board_size), randint(1, self.__board_size))
            if guess in self.__guesses_list:
                continue
            else:
                self.__guesses_list.append(guess)
                return guess

        if self.__direction == "None":
            if self.__direction_test == "Right":
                self.__direction_test = "Left"
            elif self.__direction_test == "Left":
                self.__direction_test = "Up"
            elif self.__direction_test == "Up":
                self.__direction_test = "Down"
            elif self.__direction_test == "Down":
                self.__direction_test = "Right"
                self.__confused = True
            return tuple(map(sum, zip(self.__critical_point, self.__direction_dict[self.__direction_test])))
        else:
            self.__critical_point = tuple(map(sum, zip(self.__critical_point, self.__direction_dict[self.__direction])))
            return tuple(map(sum, zip(self.__critical_point, self.__direction_dict[self.__direction])))
