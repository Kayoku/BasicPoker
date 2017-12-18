# QLearning
# Classe permettant de lancer
# un algorithme de renforcement

import numpy as np
from PK_State import *

class QLearning:

    def __init__(self, game, qplayer, e, y, lr):
        self.e = e
        self.y = y
        self.lr = lr
        self.game = game
        self.qplayer = qplayer
        self.probas = {}

        ps = possibles_states()
        for i in range(len(ps)):
            # Cas ou il n'y a que deux choix
            if i == 4 or i == 9:
                self.probas[ps[i]] = [[0, 0] for _ in range(170)]
            # Cas ou il y a trois choix
            else:
                self.probas[ps[i]] = [[0, 0, 0] for _ in range(170)]

        self.qplayer.probas = self.probas

    def train(self, a, moves):
        # Chance de choisir un coup aléatoire
        # Si on est en apprentissage, on a une chance epsilon de choisir
        # un coup aléatoire pour explorer
        if np.random.random() < self.e:
            a = 1 + np.random.choice([i for i in range(len(moves))])        

        # Si on est en apprentissage, alors on fait les actions d'apprentissage
        # selon le coup choisit
        s1, r = self.game.step(self.qplayer, PK_State(a))
        current_prob = self.probas[tuple(self.game.history)][self.qplayer.hand][a-1]

        current_prob *= (1 - self.lr)
        if s1 in self.probas:
            current_prob += self.lr * (r + self.y * np.max(self.probas[s1][self.qplayer.hand]))
        else:
            current_prob += self.lr * r

        self.probas[tuple(self.game.history)][self.qplayer.hand][a-1] = current_prob
        return a
