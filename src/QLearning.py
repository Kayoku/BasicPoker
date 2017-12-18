# QLearning
# Classe permettant de lancer
# un algorithme de renforcement

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

    def train(self):
        # Chance de choisir un coup aléatoire
        # Si on est en apprentissage, on a une chance epsilon de choisir
        # un coup aléatoire pour explorer
        #if train and np.random.random < self.e:
        #    index_max = np.random.choice([i for i in range(len(what_move))])        

        # Si on est en apprentissage, alors on fait les actions d'apprentissage
        # selon le coup choisit
        """
        if train:
            new_state = tuple(self.game.history) + tuple(self.state)
            new_reward = # win_game ? 
            self.probas[tuple(self.game.history)][self.hand][index_max] *= (1 - self.lr)
            self.probas[tuple(self.game.history)][self.hand][index_max] += self.lr * (new_reward + self.y * np.max(self.probas[new_state][self.hand]))
        """

