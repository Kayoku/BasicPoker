# Class PK_Player

import random
import numpy as np
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
        self.optimizer = None 

    def set_optimizer(self, opt):
        self.optimizer = opt

    def play(self, train=False):
        # On prend les coups possibles
        possibles_choice = self.game.possibles_moves()

        # On récupère les probas des coups possibles
        what_move = np.array(self.probas[tuple(self.game.history)][self.hand])

        # On prend le coup le plus probable en faisant attention
        # dans le cas ou il n'y aurait que deux coups possibles
        # dans le cas d'une égalité, on choisit aléatoirement 
        possibles_index = np.squeeze(np.argwhere(what_move == np.max(what_move)))
        if possibles_index.ndim == 0:
            possibles_index = np.array([possibles_index])

        index_max = 1 + np.random.choice(possibles_index)


        # On entraine le joueur s'il est en mode training
        if train and self.optimizer != None:
            index_max = self.optimizer.train(index_max, what_move)

        # On joue le coup
        self.state = PK_State(index_max)

        return self.state
