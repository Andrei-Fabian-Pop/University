from random import randint
from src.domain.ship import Ship


class RandomizeBoard:
    def __init__(self, board):
        self.__board = board

    def randomize_board(self, ship_size_list, board_size):
        ship_list = []
        for ship_size in ship_size_list:
            orientation = 'horizontal' if randint(0, 1) == 0 else 'vertical'
            location = None
            while location is None:
                location = self.search_locations(ship_size, orientation, board_size)

            coordinates = []
            ship_loc = location[randint(0, len(location) - 1)]
            if orientation == 'horizontal':
                if ship_loc["row"] in range(board_size):
                    for index in range(ship_size):
                        if ship_loc['col'] + index in range(board_size):
                            coordinates.append({'row': ship_loc['row'], 'col': ship_loc['col'] + index})
                        else:
                            raise IndexError("Column is out of range.")
                else:
                    raise IndexError("Row is out of range.")
            elif orientation == 'vertical':
                if ship_loc['col'] in range(board_size):
                    for index in range(ship_size):
                        if ship_loc['row'] + index in range(board_size):
                            coordinates.append({'row': ship_loc['row'] + index, 'col': ship_loc['col']})
                        else:
                            raise IndexError("Row is out of range.")
                else:
                    raise IndexError("Column is out of range.")

            ship = Ship(ship_size, orientation, coordinates)
            ship_list.append(ship)

            self.__board.fill_with_coord(coordinates)

        return ship_list

    def search_locations(self, size, orientation, board_size):
        locations = []

        if orientation != 'horizontal' and orientation != 'vertical':
            raise ValueError("Orientation must have a value of either 'horizontal' or 'vertical'.")

        board = self.__board.get_board()

        if orientation == 'horizontal':
            if size <= board_size:
                for r in range(board_size):
                    for c in range(board_size - size + 1):
                        if "+" not in board[r][c:c + size]:
                            locations.append({'row': r, 'col': c})
        elif orientation == 'vertical':
            if size <= board_size:
                for c in range(board_size):
                    for r in range(board_size - size + 1):
                        if "+" not in [board[i][c] for i in range(r, r + size)]:
                            locations.append({'row': r, 'col': c})

        if not locations:
            return None
        else:
            return locations
