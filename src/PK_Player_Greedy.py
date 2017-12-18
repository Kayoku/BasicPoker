# Class PK_Player

import random
from PK_State import *
from PK_Player import PK_Player

class PK_Player_Greedy(PK_Player):

    def __init__(self, game, probas):
        PK_Player.__init__(self, game)
        self.e = 0.05
        self.lr = 0.8
        self.y = 0.95

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

        # Si on est en apprentissage, on a une chance epsilon de choisir
        # un coup aléatoire pour explorer
        if train and np.random.random < self.e:
            index_max = np.random.choice([i for i in range(len(what_move))])

        # On joue le coup
        if index_max == 0:
            self.state = PK_State.FOLD
        elif index_max == 1:
            self.state = PK_State.CHECK
        else:
            self.state == PK_State.RAISE

        # Si on est en apprentissage, alors on fait les actions d'apprentissage
        # selon le coup choisit
        if train:
            new_state = tuple(self.game.history) + tuple(self.state)
            new_reward = # win_game ? 
            self.probas[tuple(self.game.history)][self.hand][index_max] *= (1 - self.lr)
            self.probas[tuple(self.game.history)][self.hand][index_max] += self.lr * (new_reward + self.y * np.max(self.probas[new_state][self.hand]))


        return self.state
