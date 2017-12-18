# Class PK_Player

import random
from PK_State import *
from PK_Player import PK_Player

class PK_Player_Greedy(PK_Player):

    def __init__(self, game, probas={}):
        PK_Player.__init__(self, game)

        """
        Dictionnaire des probas:
            10 states
            170 valeurs possibles
            2/3 actions (FOLD - CHECK - RAISE)
        """
        self.probas = probas 

    def play(self, train=False):
        # On prend les coups possibles
        possibles_choice = self.game.possibles_moves()

        # On récupère les probas des coups possibles
        what_move = np.array(self.probas[tuple(self.game.history)][self.hand])

        # On prend le coup le plus probable en faisant attention
        # dans le cas ou il n'y aurait que deux coups possibles
        # dans le cas d'une égalité, on choisit aléatoirement 
        possibles_index = np.argwhere(what_move == np.max(what_move)) 
        index_max = np.random.choice(possibles_index)

        # On joue le coup
        if index_max == 0:
            self.state = PK_State.FOLD
        elif index_max == 1:
            self.state = PK_State.CHECK
        else:
            self.state = PK_State.RAISE

        return self.state
