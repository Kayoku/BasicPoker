# Class PK_Handler

from PK_Game import PK_Game

class PK_Handler:

    def __init__(self):
        self.stat = [0, 0]
        self.game = PK_Game() 

    def run(self, iterations):
        for _ in range(iterations):
            self.game.run_game()
            if self.game.winner():
                self.stat[0] += 1
            else:
                self.stat[1] += 1

            print(self.stat)
