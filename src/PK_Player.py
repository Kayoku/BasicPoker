# Class PK_Player

import random
from PK_State import PK_State

class PK_Player:

    def __init__(self, game):
        self.hand = -1
        self.game = game
        self.state = PK_State.START

    def make_play(self, move):
        self.state = move
        return self.state
