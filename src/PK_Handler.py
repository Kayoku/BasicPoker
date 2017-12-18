# Class PK_Handler

from PK_Game import PK_Game
from PK_State import PK_Win

class PK_Handler:

    def __init__(self, game):
        self.stat = [0, 0]
        self.game = game 

    def run(self, iterations):
        for _ in range(iterations):
            self.game.reset_state()
            self.game.run_game()
            if self.game.winner() == PK_Win.PLAYER1_WIN:
                self.stat[0] += 1
            else:
                self.stat[1] += 1

            print(self.stat)

    def train(self, iterations):
        #for _ in range(iterations):
