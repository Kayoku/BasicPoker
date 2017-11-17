# Class PK_Player

import random
from PK_State import *

class PK_Player_Q:

    def __init__(self, game):
        self.hand = -1
        self.game = game
        self.state = PK_State.START
        """
        Dictionnaire des probas:
            10 states
            170 valeurs possibles
            2/3 actions (FOLD - CHECK - RAISE)
        """
        self.qtable = {}

        for i in range(len(possibles_states())):
            if i == 4 or i == 9:
                self.qtable[possibles_state()[i]] = [[0, 0] for _ in range(170)]
            else:
                self.qtable[possibles_state()[i]] = [[0, 0, 0] for _ in range(170)]

    def play(self):
        possibles_choice = [PK_State.FOLD, PK_State.CHECK]
        if self.game.history.count(PK_State.RAISE) < 4:
            possibles_choice.append(PK_State.RAISE)


        self.state = possibles_choice[random.randint(0, len(possibles_choice)-1)]
        return self.state
