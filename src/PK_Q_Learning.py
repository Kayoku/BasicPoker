# Class PK_Q_Learning.py

from PK_Player_Greedy import PK_Player_Greedy
from PK_Game import PK_Game, PK_Game_Saver

class PK_Q_Learning:

    def __init__(self, y, e, lr, game):
        self.lr = lr # Learning rate
        self.y = y   # Facteur d'actualisation
        self.e = e   # Random probability
        self.game = game
        self.probas = {}

        ps = possibles_states()
        for i in range(len(ps)):
            # Cas particuliers
            if i == 4 or i == 9:
                self.probas[ps[i]] = [[0, 0] for _ in range(170)]
            else:
                self.probas[ps[i]] = [[0, 0, 0] for _ in range(170)]

        self.game.set_players(PK_Player_Greedy(probas), PK_Player_Greedy(probas))

    def train(self, iterations):
        for _ in range(iterations):
            # Génération d'un état du jeu aléatoire
            self.game.play_random()

            # On joue chaque coup jusqu'à un état terminal
            # en faisant les updates

            # Calcul du nouveau q
            q = self.probas[tuple(self.game.history)][self.hand] 
