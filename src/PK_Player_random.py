# Class PK_Player_Random

import random
from PK_State import PK_State
from PK_Player import PK_Player

class PK_Player_Random(PK_Player):

    def __init__(self, game):
        PK_Player.__init__(self, game)

    def play(self):
        possibles_choice = [PK_State.FOLD, PK_State.CHECK]
        if self.game.history.count(PK_State.RAISE) < 4:
            possibles_choice.append(PK_State.RAISE)
        self.state = possibles_choice[random.randint(0, len(possibles_choice)-1)]
        return self.state

