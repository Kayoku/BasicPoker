# Class PK_Q_Learning.py

from PK_Player_Q import PK_Player_Q

class PK_Q_Learning:

    def __init__(self, y, game):
        self.y = y
        self.game = game
        self.qtable = {}
        for i in range(len(possibles_states())):
            if i == 4 or i == 9:
                self.qtable[possibles_state()[i]] = [[0, 0] for _ in range(170)]
            else:
                self.qtable[possibles_state()[i]] = [[0, 0, 0] for _ in range(170)]
        self.game.set_players(PK_Player_Q(qtable), PK_Player_Q(qtable))

    def train(self, iterations):
        for _ in range(iterations):
            # Génération d'un état du jeu aléatoire
            self.game.play_random()
