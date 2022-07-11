from src.service.rand_board import RandomizeBoard


class User(RandomizeBoard):
    def __init__(self, attack_board, defence_board):
        self.__attack_board = attack_board
        self.__defence_board = defence_board
        self.__ship_list = []
        super().__init__(board=self.__defence_board)

    def set_boats(self, boat_list):
        self.__ship_list = boat_list

    def get_board_str(self):
        att_board = str(self.__attack_board)
        def_board = str(self.__defence_board)

        return att_board, def_board

    def make_user_move(self, row, col):
        if self.__attack_board.pos(row, col) == 0:
            self.__attack_board.set_point(row, col, "*")
            return 1
        elif self.__attack_board.pos(row, col) == "*" or self.__attack_board.pos(row, col) == "X":
            return 0

    def confirm_hit(self, row, col):
        self.__attack_board.set_point(row, col, "X")

    def receive_shot(self, row, col):
        if self.__defence_board.pos(row, col) == 0:
            self.__defence_board.set_point(row, col, "*")
            return 0  # MISS
        elif self.__defence_board.pos(row, col) == "+":
            self.__defence_board.set_point(row, col, "X")
            if self.__defence_board.pos(row, col+1) != "+" and self.__defence_board.pos(row+1, col) != "+" and \
                    self.__defence_board.pos(row, col-1) != "+" and self.__defence_board.pos(row-1, col) != "+":
                return 2  # DESTROYED
            return 1  # HIT
