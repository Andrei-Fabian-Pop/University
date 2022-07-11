from src.service.rand_board import RandomizeBoard


class AI(RandomizeBoard):
    def __init__(self, attack_board, defence_board, strategy):
        self.__attack_board = attack_board
        self.__defence_board = defence_board
        self.__strategy = strategy
        super().__init__(board=self.__defence_board)

    def receive_shot(self, row, col):
        if self.__defence_board.pos(row, col) == 0:
            return 0  # MISS
        elif self.__defence_board.pos(row, col) == "+":
            self.__defence_board.set_point(row, col, 0)
            if self.__defence_board.pos(row, col+1) != "+" and \
                    self.__defence_board.pos(row+1, col) != "+" and \
                    self.__defence_board.pos(row, col-1) != "+" and \
                    self.__defence_board.pos(row-1, col) != "+":
                return 2  # DESTROYED
            return 1  # HIT

    def confirm_miss(self, row, col):
        self.__attack_board.set_point(row, col, "*")
        self.__strategy.miss()

    def confirm_hit(self, row, col):
        self.__attack_board.set_point(row, col, "X")
        self.__strategy.crit(row, col)

    def confirm_destroyed(self, row, col):
        self.__attack_board.set_point(row, col, "X")
        self.__strategy.destroyed()

    def make_a_move(self):
        return self.__strategy.turn()
