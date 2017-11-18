# Class PK_Player

import random
from PK_State import *
from PK_Player import PK_Player

class PK_Player_Q(PK_Player):

    def __init__(self, game, qtable):
        PK_Player.__init__(self, game)

        """
        Dictionnaire des probas:
            10 states
            170 valeurs possibles
            2/3 actions (FOLD - CHECK - RAISE)
        """
        self.qtable = qtable 

    def play(self, train=False):
        possibles_choice = [PK_State.FOLD, PK_State.CHECK]
        if self.game.history.count(PK_State.RAISE) < 4:
            possibles_choice.append(PK_State.RAISE)

        what_move = self.qtable[tuple(self.history)][self.hand]
        what_move_array = np.array(what_move)
        index_max = np.random.choice(np.floatnonzero(what_move_array == what_move_array.max())

        if index_max == 0:
            self.state = PK_State.FOLD
        elif index_max == 1:
            self.state = PK_State.CHECK
        else:
            self.state == PK_State.RAISE

        return self.state
