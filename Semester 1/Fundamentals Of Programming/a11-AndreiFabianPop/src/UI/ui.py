class UI:
    def __init__(self, player, ship_count, board_size=10):
        self.__player_serv = player
        self.__board_size = board_size
        self.__ship_count = ship_count
        self.__turn = 1

    @staticmethod
    def start():
        print("Welcome to Battleship!\n")
        print("Here are the notations: ")
        print("0 - location without interaction")
        print("* - player/AI missed a shot")
        print("X - player/AI hit a shot")
        print("+ - your ships")
        print("")

    def print_board(self):
        att_board, def_board = self.__player_serv.get_board_str()
        att_lines = att_board.split("\n")
        def_lines = def_board.split("\n")
        board = "Enemy board(attack)    |  Your board(defence)\n"
        board += att_lines[0] + " |  " + def_lines[0] + "\n"
        for line in range(1, self.__board_size + 1):
            board += att_lines[line] + "  |  " + def_lines[line] + "\n"
        print(board)

    def set_player_battleships(self, ship_size_list):
        print("Let\'s start by choosing where you put your ships :)")
        print("If you are lazy, just type \'random\' and let the computer choose, else type anything else")
        user_input = input("> ")
        if user_input.lower() == "random":
            player_ships = self.__player_serv.randomize_board(ship_size_list, self.__board_size)
        else:
            print("You have too much time on your hands :/")
            print("I\'m still choosing to randomize it :)")
            player_ships = self.__player_serv.randomize_board(ship_size_list, self.__board_size)
        self.__player_serv.set_boats(player_ships)

    def turn_prompt(self, enemy_ship_count, friendly_ship_count):
        print(f"Turn: {self.__turn}")
        self.__turn += 1
        print(f"Enemy ships left: {enemy_ship_count}")
        print(f"Friendly ships left: {friendly_ship_count}")
        print()

    def get_validated_input(self, message):
        while True:
            guess = input(message)
            try:
                if guess == "":
                    guess = "E"
                    raise ValueError
                if ord("A") <= int(guess) <= ord("Z"):
                    raise ValueError
                guess = int(guess)
            except ValueError:
                guess = ord(guess) - ord("A") + 1
            finally:
                if guess in range(1, self.__board_size + 1):
                    return guess
                else:
                    print("\nOops, that's not even in the ocean.")

    def get_player_input(self):
        row = self.get_validated_input("Row guess: ")
        col = self.get_validated_input("Column guess: ")

        return row, col
