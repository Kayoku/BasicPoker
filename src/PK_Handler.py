# Class PK_Handler

from PK_Game import PK_Game
from PK_State import PK_Win

class PK_Handler:

    def __init__(self, game):
        self.stat_run = [0, 0]
        self.stat_train = [0, 0]
        self.game = game 

    def run(self, iterations):
        for _ in range(iterations):
            self.game.reset_state()
            self.game.run_game()
            if self.game.winner() == PK_Win.PLAYER1_WIN:
                self.stat_run[0] += 1
            else:
                self.stat_run[1] += 1

            print(self.stat_run)

    def train(self, iterations):
        for i in range(iterations):
            self.game.reset_state()
            self.game.run_game(train=True)
            if self.game.winner() == PK_Win.PLAYER1_WIN:
                self.stat_train[0] += 1
            else:
                self.stat_train[1] += 1
            print(i, end='\r')
            #print(self.stat_train)
