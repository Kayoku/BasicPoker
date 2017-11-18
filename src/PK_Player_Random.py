# Class PK_Player_Random

import random
from PK_State import PK_State
from PK_Player import PK_Player

class PK_Player_Random(PK_Player):

    def __init__(self, game):
        PK_Player.__init__(self, game)

    def play(self, train=False):
        possibles_choice = self.game.possibles_moves()
        self.state = possibles_choice[random.randint(0, len(possibles_choice)-1)]
        return self.state

