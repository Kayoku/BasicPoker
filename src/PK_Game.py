# Class PK_Game

import random
from PK_State import PK_State
from PK_Player import PK_Player

class PK_Game:

    def __init__(self):
        self.player1 = PK_Player(self)
        self.player2 = PK_Player(self)
        self.nb_game = 0
        self.reset_state()

    """
    Permet de savoir si le round en cours est terminé
     - Fold
     - raise + 1 coup check 
     - double check
    """
    def game_end(self):
        if len(self.history) > 0 and self.history[-1] == PK_State.FOLD:
            return True
        elif (len(self.history) > 1 and (self.history[-1] == PK_State.CHECK and (self.history[-2] == PK_State.CHECK or self.history[-2] == PK_State.RAISE))):
            return True
        else:
            return False

    """
    Permet de reset l'état du jeu à son état initial
    """
    def reset_state(self):
        self.history = []
        self.next_player = self.nb_game % 2 
        self.player1.hand = -1
        self.player2.hand = -1
        self.player1.state = PK_State.START
        self.player2.state = PK_State.START

    """
    Distribue deux cartes aux deux joueurs
    """
    def random_card(self):
        card1 = random.randint(1, 170)
        card2 = random.randint(1, 170)
        while card1 == card2:
            card2 = random.randint(1, 170)        
        self.player1.hand = card1
        self.player2.hand = card2

    """
    Permet de savoir qui a gagné
    Renvoie False si c'est le joueur 1
    Renvoie True si c'est le joueur 2
    """
    def winner(self):
        if self.player1.state == PK_State.FOLD:
            return True 
        elif self.player2.state == PK_State.FOLD:
            return False 
        else:
            if self.player1.hand > self.player2.hand:
                return False 
            else:
                return True 

    """
    Joue une partie avec tous les joueurs
    """
    def run_game(self):
        self.reset_state()
        #self.display_state()
        self.random_card()

        while not self.game_end():
            if self.next_player:
                self.history.append(self.player1.play()) 
            else:
                self.history.append(self.player2.play())
            #self.display_state()
            self.next_player = (self.next_player + 1) % 2
 
        self.nb_game += 1

        """
        if self.winner():
            print("Player 2 win the game.")
        else:
            print("Player 1 win the game.")
        """

    """
    Affiche l'état du jeu
    """
    def display_state(self):
        print("Game: ", end='')
        print(self.nb_game)
        print("Player 1: ", end='')
        print(self.player1.hand, end=' ')
        print(self.player1.state)
        print("Player 2: ", end='')
        print(self.player2.hand, end=' ')
        print(self.player2.state)
