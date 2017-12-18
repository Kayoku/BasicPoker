#!/usr/bin/python3

from PK_Handler import PK_Handler
from PK_Game import PK_Game
from PK_Player_Greedy import PK_Player_Greedy
from QLearning import QLearning

game = PK_Game()

qplayer = PK_Player_Greedy(game)
qlearning = QLearning(game, qplayer, 0.05, 0.95, 0.8)
qplayer.set_optimizer(qlearning)
game.set_player1(qplayer)

handler = PK_Handler(game)

handler.train(3000000)
print(qplayer.probas)

handler.run(2000)
