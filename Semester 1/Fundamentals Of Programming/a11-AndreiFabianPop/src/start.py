"""
TODO: docs and tests!!

board entities:

no.     class         size
1       carrier       5
2       battleship    4
2       cruiser       3
2       destroyer     2


"""

from src.repository.board import Board
from src.UI.ui import UI
from src.service.user_service import User
from src.service.AI import AI
from src.service.AI_strategy_01 import Strategy_01

""" Game variables """
ship_size_list = [5, 4, 4, 3, 3, 2, 2]
SHIP_NUMBER = len(ship_size_list)
BOARD_SIZE = 10
STRATEGY = Strategy_01(BOARD_SIZE)

""" Game Preparation """
player_attack = Board()
player_defence = Board()

AI_attack = Board()
AI_defence = Board()

player = User(player_attack, player_defence)
ai = AI(AI_attack, AI_defence, strategy=STRATEGY)

ui = UI(player, ship_count=SHIP_NUMBER, board_size=BOARD_SIZE)

enemy_ships_left = SHIP_NUMBER
friendly_ships_left = SHIP_NUMBER

if __name__ == "__main__":
    ui.start()

    # make player board
    ui.set_player_battleships(ship_size_list=ship_size_list)
    ui.print_board()

    # ai generate
    ai_ships = ai.randomize_board(ship_size_list=ship_size_list, board_size=BOARD_SIZE)

    # start game
    while True:
        # -----------------PLAYER INTERACTION---------------------
        ui.turn_prompt(enemy_ships_left, friendly_ships_left)
        player_input = ui.get_player_input()
        player_decision = player.make_user_move(*player_input)
        if player_decision == 0:
            print("You already hit that point, try again")
            continue
        elif player_decision == 1:
            player_turn_result = ai.receive_shot(*player_input)
            if player_turn_result == 1:
                print("\n\nIt\'s a hit!")
                player.confirm_hit(*player_input)
            elif player_turn_result == 2:
                print("\n\nYou destroyed a ship!")
                enemy_ships_left -= 1
                player.confirm_hit(*player_input)
            else:
                print("\n\nYou missed!")

        # -----------------AI INTERACTION-----------------------
        ai_input = ai.make_a_move()  # x,y - tuple
        # print(f"ai input = {ai_input}")
        ai_turn_result = player.receive_shot(*ai_input)
        print(f"Enemy attacked {ai_input}")
        if ai_turn_result == 1:
            print(f"Enemy hit on {ai_input}!")
            ai.confirm_hit(*ai_input)
        elif ai_turn_result == 2:
            print(f"Enemy destroyed a friendly ship!!")
            friendly_ships_left -= 1
            ai.confirm_destroyed(*ai_input)
        elif ai_turn_result == 0:
            ai.confirm_miss(*ai_input)
        ai_turn_result = 0

        # -------------PRINT BOARD AND END TURN-----------------
        ui.print_board()

        if enemy_ships_left == 0:
            print("Congratulations, you are the best capitan!!")
            break
        if friendly_ships_left == 0:
            print("Bad luck, the enemy capitan was better :(")
            break

    """
    1. player choice
    2. result of choice
    3. ai choice + result
    """
