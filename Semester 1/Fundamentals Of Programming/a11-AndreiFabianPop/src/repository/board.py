class Board:
    def __init__(self, size=10):
        self.__size = size
        self.__board = [[0] * size for _ in range(size)]

    def __str__(self):
        board_str = "/"
        alphabet = "ABCDEFGHIJ"
        for number in range(10):
            board_str += f" {number + 1}"
        board_str += "\n"
        for line in range(self.__size):
            convert_to_string = " ".join([str(self.__board[line][column]) for column in range(self.__size)]) + "\n"
            board_str += alphabet[line] + " " + convert_to_string
        return board_str

    def pos(self, x, y):
        try:
            return self.__board[x-1][y-1]
        except IndexError:
            return 0

    def set_point(self, x, y, symbol):
        self.__board[x-1][y-1] = symbol

    def get_board(self):
        return self.__board

    def fill_with_coord(self, coordinates):
        for point in coordinates:
            self.__board[point["row"]][point["col"]] = "+"
