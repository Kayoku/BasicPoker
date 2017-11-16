# Class PK_Game

from enum import Enum
import random

class PK_State(Enum):
    START = 0
    FOLD  = 1 
    CHECK = 2
    RAISE = 3

class PK_Player:

    def __init__(self, game):
        self.hand = -1
        self.game = game
        self.state = PK_State.START

    def play(self):
        possibles_choice = [PK_State.FOLD, PK_State.CHECK]
        if self.game.history.count(PK_State.RAISE) < 4:
            possibles_choice.append(PK_State.RAISE)
        self.state = possibles_choice[random.randint(0, len(possibles_choice)-1)]
        return self.state

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
        elif (len(self.history) > 1 and (self.history[-1] == PK_State.CHECK and (self.history[-2] == PK_State.CHECK or self.history[-2] == PK_State.PK_State.RAISE))):
            return True
        else:
            return False

    """
    Permet de reset l'état du jeu à son état initial
    """
    def reset_state(self):
        self.history = []
        self.next_player = self.nb_game % 2 

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
    Joue une partie avec tous les joueurs
    """
    def run_game(self):
        self.reset_state()
        self.display_state()
        self.random_card()

        while not self.game_end():
            if self.next_player:
                self.history.append(self.player1.play()) 
            else:
                self.history.append(self.player2.play())
            self.display_state()
            self.next_player = (self.next_player + 1) % 2

        self.nb_game += 1

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
        print("===")

