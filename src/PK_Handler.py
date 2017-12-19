# Class PK_Handler

from PK_Game import PK_Game
from PK_State import PK_Win

class PK_Handler:

    def __init__(self, game):
        self.stat_run = [0, 0]
        self.stat_train = [0, 0]
        self.game = game 

    def run(self, iterations, verbose=True):
        for _ in range(iterations):
            self.game.reset_state()
            self.game.run_game()
            if self.game.winner() == PK_Win.PLAYER1_WIN:
                self.stat_run[0] += 1
            else:
                self.stat_run[1] += 1

            if verbose:
                print(self.stat_run)

    def train(self, iterations):
        f = open('train.txt','w')
        for i in range(iterations):
            self.game.reset_state()
            self.game.run_game(train=True)
            if self.game.winner() == PK_Win.PLAYER1_WIN:
                self.stat_train[0] += 1
            else:
                self.stat_train[1] += 1

            # Calcul du taux de victoire
            if i % 500 == 0:
                self.run(1000, verbose=False)
                f.write("{}\n".format(self.stat_run[1]/self.stat_run[0]))
                f.flush()
                self.stat_run = [0, 0]

            print(i, end='\r')
            #print(self.stat_train)
