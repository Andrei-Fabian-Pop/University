"""
Implement the solution here. 
You may add other source files.
Make sure you commit & push the source code before the end of the test.

Solutions using user-defined classes will not be graded.
"""
import time
from src.ui import *
from src.functions import *

if __name__ == "__main__":
    secret_num = UI_generate_secret_number()
    computer_wins = False
    game_time = time.time()
    while not computer_wins:
        user_command = UI_get_user_command()
        if time.time() - game_time >= 60:
            computer_wins = True
            break
        elif int(user_command) == 8086:
            print("Cheat code, number is:", secret_num)
        elif not check_valid_input(user_command):
            computer_wins = True
            break
        elif int(user_command) == secret_num:
            break
        else:
            runner_number, codes_number = number_of_runners_and_codes(int(user_command), secret_num)
            report_runners_and_codes(runner_number, codes_number)

    if not computer_wins:
        print("Congratulations, you guessed it :)")
    elif computer_wins:
        if time.time() - game_time >= 60:
            print("Sorry, time expired, better luck next time.")
        else:
            print("Wrong number, computer wins")
