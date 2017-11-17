# Class PK_Player

import random
from PK_State import PK_State

class PK_Player:

    def __init__(self, game):
        self.hand = -1
        self.game = game
        self.state = PK_State.START

    def play(self):
        possibles_choice = [PK_State.FOLD, PK_State.CHECK]
        if self.game.history.count(PK_State.RAISE) < 4:
            possibles_choice.append(PK_State.RAISE)
        self.state = possibles_choice[random.randint(0, len(possibles_choice)-1)]
        return self.state
